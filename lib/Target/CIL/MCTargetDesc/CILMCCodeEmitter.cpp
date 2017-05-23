//===-- CILMCCodeEmitter.cpp - Convert CIL code to machine code -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the CILMCCodeEmitter class.
//
//===----------------------------------------------------------------------===//

#include "CILMCExpr.h"
#include "MCTargetDesc/CILFixupKinds.h"
#include "CILMCTargetDesc.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/Support/EndianStream.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "mccodeemitter"

STATISTIC(MCNumEmitted, "Number of MC instructions emitted");

namespace {
class CILMCCodeEmitter : public MCCodeEmitter {
  CILMCCodeEmitter(const CILMCCodeEmitter &) = delete;
  void operator=(const CILMCCodeEmitter &) = delete;
  const MCInstrInfo &MCII;
  MCContext &Ctx;

public:
  CILMCCodeEmitter(const MCInstrInfo &mcii, MCContext &ctx)
      : MCII(mcii), Ctx(ctx) {}

  ~CILMCCodeEmitter() override {}

  void encodeInstruction(const MCInst &MI, raw_ostream &OS,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const override;

  // getBinaryCodeForInstr - TableGen'erated function for getting the
  // binary encoding for an instruction.
  uint64_t getBinaryCodeForInstr(const MCInst &MI,
                                 SmallVectorImpl<MCFixup> &Fixups,
                                 const MCSubtargetInfo &STI) const;

  /// getMachineOpValue - Return binary encoding of operand. If the machine
  /// operand requires relocation, record the relocation and return zero.
  unsigned getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                             SmallVectorImpl<MCFixup> &Fixups,
                             const MCSubtargetInfo &STI) const;

  unsigned getCallTargetOpValue(const MCInst &MI, unsigned OpNo,
                             SmallVectorImpl<MCFixup> &Fixups,
                             const MCSubtargetInfo &STI) const;
  unsigned getBranchTargetOpValue(const MCInst &MI, unsigned OpNo,
                             SmallVectorImpl<MCFixup> &Fixups,
                             const MCSubtargetInfo &STI) const;
  unsigned getBranchPredTargetOpValue(const MCInst &MI, unsigned OpNo,
                                      SmallVectorImpl<MCFixup> &Fixups,
                                      const MCSubtargetInfo &STI) const;
  unsigned getBranchOnRegTargetOpValue(const MCInst &MI, unsigned OpNo,
                                       SmallVectorImpl<MCFixup> &Fixups,
                                       const MCSubtargetInfo &STI) const;

private:
  uint64_t computeAvailableFeatures(const FeatureBitset &FB) const;
  void verifyInstructionPredicates(const MCInst &MI,
                                   uint64_t AvailableFeatures) const;
};
} // end anonymous namespace

MCCodeEmitter *llvm::createCILMCCodeEmitter(const MCInstrInfo &MCII,
                                              const MCRegisterInfo &MRI,
                                              MCContext &Ctx) {
  return new CILMCCodeEmitter(MCII, Ctx);
}

void CILMCCodeEmitter::encodeInstruction(const MCInst &MI, raw_ostream &OS,
                                           SmallVectorImpl<MCFixup> &Fixups,
                                           const MCSubtargetInfo &STI) const {
  verifyInstructionPredicates(MI,
                              computeAvailableFeatures(STI.getFeatureBits()));

  unsigned Bits = getBinaryCodeForInstr(MI, Fixups, STI);

  if (Ctx.getAsmInfo()->isLittleEndian()) {
    // Output the bits in little-endian byte order.
    support::endian::Writer<support::little>(OS).write<uint32_t>(Bits);
  } else {
    // Output the bits in big-endian byte order.
    support::endian::Writer<support::big>(OS).write<uint32_t>(Bits);
  }
  unsigned tlsOpNo = 0;
  switch (MI.getOpcode()) {
  default: break;
  case SP::TLS_CALL:   tlsOpNo = 1; break;
  case SP::TLS_ADDrr:
  case SP::TLS_ADDXrr:
  case SP::TLS_LDrr:
  case SP::TLS_LDXrr:  tlsOpNo = 3; break;
  }
  if (tlsOpNo != 0) {
    const MCOperand &MO = MI.getOperand(tlsOpNo);
    uint64_t op = getMachineOpValue(MI, MO, Fixups, STI);
    assert(op == 0 && "Unexpected operand value!");
    (void)op; // suppress warning.
  }

  ++MCNumEmitted;  // Keep track of the # of mi's emitted.
}


unsigned CILMCCodeEmitter::
getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                  SmallVectorImpl<MCFixup> &Fixups,
                  const MCSubtargetInfo &STI) const {

  if (MO.isReg())
    return Ctx.getRegisterInfo()->getEncodingValue(MO.getReg());

  if (MO.isImm())
    return MO.getImm();

  assert(MO.isExpr());
  const MCExpr *Expr = MO.getExpr();
  if (const CILMCExpr *SExpr = dyn_cast<CILMCExpr>(Expr)) {
    MCFixupKind Kind = (MCFixupKind)SExpr->getFixupKind();
    Fixups.push_back(MCFixup::create(0, Expr, Kind));
    return 0;
  }

  int64_t Res;
  if (Expr->evaluateAsAbsolute(Res))
    return Res;

  llvm_unreachable("Unhandled expression!");
  return 0;
}

unsigned CILMCCodeEmitter::
getCallTargetOpValue(const MCInst &MI, unsigned OpNo,
                     SmallVectorImpl<MCFixup> &Fixups,
                     const MCSubtargetInfo &STI) const {
  const MCOperand &MO = MI.getOperand(OpNo);
  if (MO.isReg() || MO.isImm())
    return getMachineOpValue(MI, MO, Fixups, STI);

  if (MI.getOpcode() == SP::TLS_CALL) {
    // No fixups for __tls_get_addr. Will emit for fixups for tls_symbol in
    // encodeInstruction.
#ifndef NDEBUG
    // Verify that the callee is actually __tls_get_addr.
    const CILMCExpr *SExpr = dyn_cast<CILMCExpr>(MO.getExpr());
    assert(SExpr && SExpr->getSubExpr()->getKind() == MCExpr::SymbolRef &&
           "Unexpected expression in TLS_CALL");
    const MCSymbolRefExpr *SymExpr = cast<MCSymbolRefExpr>(SExpr->getSubExpr());
    assert(SymExpr->getSymbol().getName() == "__tls_get_addr" &&
           "Unexpected function for TLS_CALL");
#endif
    return 0;
  }

  MCFixupKind fixupKind = 0;//(MCFixupKind)CIL::fixup_CIL_call30;
/*
  if (const CILMCExpr *SExpr = dyn_cast<CILMCExpr>(MO.getExpr())) {
    if (SExpr->getKind() == CILMCExpr::VK_CIL_WPLT30)
      fixupKind = (MCFixupKind)CIL::fixup_CIL_wplt30;
  }*/

  Fixups.push_back(MCFixup::create(0, MO.getExpr(), fixupKind));

  return 0;
}

unsigned CILMCCodeEmitter::
getBranchTargetOpValue(const MCInst &MI, unsigned OpNo,
                  SmallVectorImpl<MCFixup> &Fixups,
                  const MCSubtargetInfo &STI) const {
  const MCOperand &MO = MI.getOperand(OpNo);
  if (MO.isReg() || MO.isImm())
    return getMachineOpValue(MI, MO, Fixups, STI);

  Fixups.push_back(MCFixup::create(0, MO.getExpr(),
                                   (MCFixupKind)0));//Sparc::fixup_sparc_br22));
  return 0;
}

unsigned CILMCCodeEmitter::
getBranchPredTargetOpValue(const MCInst &MI, unsigned OpNo,
                           SmallVectorImpl<MCFixup> &Fixups,
                           const MCSubtargetInfo &STI) const {
  const MCOperand &MO = MI.getOperand(OpNo);
  if (MO.isReg() || MO.isImm())
    return getMachineOpValue(MI, MO, Fixups, STI);

  Fixups.push_back(MCFixup::create(0, MO.getExpr(),
                                   (MCFixupKind)0));//Sparc::fixup_sparc_br19));
  return 0;
}
unsigned CILMCCodeEmitter::
getBranchOnRegTargetOpValue(const MCInst &MI, unsigned OpNo,
                           SmallVectorImpl<MCFixup> &Fixups,
                           const MCSubtargetInfo &STI) const {
  const MCOperand &MO = MI.getOperand(OpNo);
  if (MO.isReg() || MO.isImm())
    return getMachineOpValue(MI, MO, Fixups, STI);

  Fixups.push_back(MCFixup::create(0, MO.getExpr(),
                                   (MCFixupKind)0));//Sparc::fixup_sparc_br16_2));
  Fixups.push_back(MCFixup::create(0, MO.getExpr(),
                                   (MCFixupKind)0));//Sparc::fixup_sparc_br16_14));

  return 0;
}

#define ENABLE_INSTR_PREDICATE_VERIFIER
#include "CILGenMCCodeEmitter.inc"
