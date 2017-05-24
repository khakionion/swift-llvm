//==-- CILInstPrinter.cpp - Convert CIL MCInst to assembly syntax ----------==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This class prints an CIL MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#include "CILInstPrinter.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/Format.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define DEBUG_TYPE "asm-printer"

#define GET_INSTRUCTION_NAME
#define PRINT_ALIAS_INSTR
#include "CILGenAsmWriter.inc"


CILInstPrinter::CILInstPrinter(const MCAsmInfo &MAI,
                                       const MCInstrInfo &MII,
                                       const MCRegisterInfo &MRI)
    : MCInstPrinter(MAI, MII, MRI) {
    }

void CILInstPrinter::printRegName(raw_ostream &OS, unsigned RegNo) const {
  // This is for .cfi directives.
  OS << getRegisterName(RegNo);
}

void CILInstPrinter::printInst(const MCInst *MI, raw_ostream &O,
                                   StringRef Annot,
                                   const MCSubtargetInfo &STI) {

}

void CILInstPrinter::printCustomAliasOperand(const MCInst *MI, unsigned OpIdx,
                                       unsigned PrintMethodIdx,
                                       const MCSubtargetInfo &STI,
                                       raw_ostream &O)
{

}

static bool isTblTbxInstruction(unsigned Opcode, StringRef &Layout,
                                bool &IsTbx) {
  return false;
}

bool CILInstPrinter::printSysAlias(const MCInst *MI,
                                       const MCSubtargetInfo &STI,
                                       raw_ostream &O) {

  return false;
}

void CILInstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                      const MCSubtargetInfo &STI,
                                      raw_ostream &O) {
}

void CILInstPrinter::printImm(const MCInst *MI, unsigned OpNo,
                                     const MCSubtargetInfo &STI,
                                     raw_ostream &O) {
}

void CILInstPrinter::printImmHex(const MCInst *MI, unsigned OpNo,
                                     const MCSubtargetInfo &STI,
                                     raw_ostream &O) {
}

void CILInstPrinter::printPostIncOperand(const MCInst *MI, unsigned OpNo,
                                             unsigned Imm, raw_ostream &O) {
}

void CILInstPrinter::printVRegOperand(const MCInst *MI, unsigned OpNo,
                                          const MCSubtargetInfo &STI,
                                          raw_ostream &O) {
}

void CILInstPrinter::printSysCROperand(const MCInst *MI, unsigned OpNo,
                                           const MCSubtargetInfo &STI,
                                           raw_ostream &O) {
}

void CILInstPrinter::printAddSubImm(const MCInst *MI, unsigned OpNum,
                                        const MCSubtargetInfo &STI,
                                        raw_ostream &O) {
}

void CILInstPrinter::printLogicalImm32(const MCInst *MI, unsigned OpNum,
                                           const MCSubtargetInfo &STI,
                                           raw_ostream &O) {
}

void CILInstPrinter::printLogicalImm64(const MCInst *MI, unsigned OpNum,
                                           const MCSubtargetInfo &STI,
                                           raw_ostream &O) {
}

void CILInstPrinter::printShifter(const MCInst *MI, unsigned OpNum,
                                      const MCSubtargetInfo &STI,
                                      raw_ostream &O) {
}

void CILInstPrinter::printShiftedRegister(const MCInst *MI, unsigned OpNum,
                                              const MCSubtargetInfo &STI,
                                              raw_ostream &O) {
}

void CILInstPrinter::printExtendedRegister(const MCInst *MI, unsigned OpNum,
                                               const MCSubtargetInfo &STI,
                                               raw_ostream &O) {
}

void CILInstPrinter::printArithExtend(const MCInst *MI, unsigned OpNum,
                                          const MCSubtargetInfo &STI,
                                          raw_ostream &O) {
}

void CILInstPrinter::printMemExtend(const MCInst *MI, unsigned OpNum,
                                        raw_ostream &O, char SrcRegKind,
                                        unsigned Width) {
}

void CILInstPrinter::printCondCode(const MCInst *MI, unsigned OpNum,
                                       const MCSubtargetInfo &STI,
                                       raw_ostream &O) {
}

void CILInstPrinter::printInverseCondCode(const MCInst *MI, unsigned OpNum,
                                              const MCSubtargetInfo &STI,
                                              raw_ostream &O) {
}

void CILInstPrinter::printAMNoIndex(const MCInst *MI, unsigned OpNum,
                                        const MCSubtargetInfo &STI,
                                        raw_ostream &O) {
}

template<int Scale>
void CILInstPrinter::printImmScale(const MCInst *MI, unsigned OpNum,
                                       const MCSubtargetInfo &STI,
                                       raw_ostream &O) {
}

void CILInstPrinter::printUImm12Offset(const MCInst *MI, unsigned OpNum,
                                           unsigned Scale, raw_ostream &O) {
}

void CILInstPrinter::printAMIndexedWB(const MCInst *MI, unsigned OpNum,
                                          unsigned Scale, raw_ostream &O) {
}

void CILInstPrinter::printPrefetchOp(const MCInst *MI, unsigned OpNum,
                                         const MCSubtargetInfo &STI,
                                         raw_ostream &O) {
}

void CILInstPrinter::printPSBHintOp(const MCInst *MI, unsigned OpNum,
                                        const MCSubtargetInfo &STI,
                                        raw_ostream &O) {
}

void CILInstPrinter::printFPImmOperand(const MCInst *MI, unsigned OpNum,
                                           const MCSubtargetInfo &STI,
                                           raw_ostream &O) {
}

static unsigned getNextVectorRegister(unsigned Reg, unsigned Stride = 1) {
  return 0;
}

template<unsigned size>
void CILInstPrinter::printGPRSeqPairsClassOperand(const MCInst *MI,
                                                   unsigned OpNum,
                                                   const MCSubtargetInfo &STI,
                                                   raw_ostream &O) {
}

void CILInstPrinter::printVectorList(const MCInst *MI, unsigned OpNum,
                                         const MCSubtargetInfo &STI,
                                         raw_ostream &O,
                                         StringRef LayoutSuffix) {
}

void
CILInstPrinter::printImplicitlyTypedVectorList(const MCInst *MI,
                                                   unsigned OpNum,
                                                   const MCSubtargetInfo &STI,
                                                   raw_ostream &O) {
}

template <unsigned NumLanes, char LaneKind>
void CILInstPrinter::printTypedVectorList(const MCInst *MI, unsigned OpNum,
                                              const MCSubtargetInfo &STI,
                                              raw_ostream &O) {
}

void CILInstPrinter::printVectorIndex(const MCInst *MI, unsigned OpNum,
                                          const MCSubtargetInfo &STI,
                                          raw_ostream &O) {
}

void CILInstPrinter::printAlignedLabel(const MCInst *MI, unsigned OpNum,
                                           const MCSubtargetInfo &STI,
                                           raw_ostream &O) {
}

void CILInstPrinter::printAdrpLabel(const MCInst *MI, unsigned OpNum,
                                        const MCSubtargetInfo &STI,
                                        raw_ostream &O) {
}

void CILInstPrinter::printBarrierOption(const MCInst *MI, unsigned OpNo,
                                            const MCSubtargetInfo &STI,
                                            raw_ostream &O) {
}

void CILInstPrinter::printMRSSystemRegister(const MCInst *MI, unsigned OpNo,
                                                const MCSubtargetInfo &STI,
                                                raw_ostream &O) {
}

void CILInstPrinter::printMSRSystemRegister(const MCInst *MI, unsigned OpNo,
                                                const MCSubtargetInfo &STI,
                                                raw_ostream &O) {
}

void CILInstPrinter::printSystemPStateField(const MCInst *MI, unsigned OpNo,
                                                const MCSubtargetInfo &STI,
                                                raw_ostream &O) {
}

void CILInstPrinter::printSIMDType10Operand(const MCInst *MI, unsigned OpNo,
                                                const MCSubtargetInfo &STI,
                                                raw_ostream &O) {
}
