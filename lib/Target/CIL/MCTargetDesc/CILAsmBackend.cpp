//===-- SparcAsmBackend.cpp - Sparc Assembler Backend ---------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "llvm/MC/MCAsmBackend.h"
#include "MCTargetDesc/CILFixupKinds.h"
#include "MCTargetDesc/CILMCTargetDesc.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCFixupKindInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

static unsigned adjustFixupValue(unsigned Kind, uint64_t Value) {
  switch (Kind) {
  default:
    llvm_unreachable("Unknown fixup kind!");
    return 0;
  }
}

namespace {
  class CILAsmBackend : public MCAsmBackend {
  protected:
    const Target &TheTarget;

  public:
    CILAsmBackend(const Target &T)
        : MCAsmBackend(), TheTarget(T) {}

    unsigned getNumFixupKinds() const override {
      return 0;
    }

    bool mayNeedRelaxation(const MCInst &Inst) const override {
      // FIXME.
      return false;
    }

    bool writeNopData(uint64_t Count, MCObjectWriter *OW) const override {
      return true;
    }

    MCObjectWriter * createObjectWriter(raw_pwrite_stream &OS) const override {
      return 0;
    }

    void applyFixup(const MCFixup &Fixup, char *Data,
                                       unsigned DataSize, uint64_t Value,
                                       bool IsPCRel) const override {
      return;
    }
 bool fixupNeedsRelaxation(const MCFixup &Fixup, uint64_t Value,
                            const MCRelaxableFragment *DF,
                            const MCAsmLayout &Layout) const override {
    return false;
  }

void relaxInstruction(const MCInst &Inst, const MCSubtargetInfo &STI,
                        MCInst &Res) const override {}

  };

} // end anonymous namespace

MCAsmBackend *llvm::createCILAsmBackend(const Target &T,
                                          const MCRegisterInfo &MRI,
                                          const Triple &TT, StringRef CPU,
                                          const MCTargetOptions &Options) {
  return new CILAsmBackend(T);
}
