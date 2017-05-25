//===-- CILAsmPrinter.cpp - CIL LLVM assembly writer --------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains a printer that converts from our internal representation
// of machine-dependent LLVM code to the CIL assembly language.
//
//===----------------------------------------------------------------------===//

#include "CIL.h"
#include "CILRegisterInfo.h"
#include "InstPrinter/CILInstPrinter.h"
#include "MCTargetDesc/CILMCExpr.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/ADT/Twine.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineModuleInfoImpls.h"
#include "llvm/CodeGen/StackMaps.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstBuilder.h"
#include "llvm/MC/MCLinkerOptimizationHint.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MCSymbolELF.h"
#include "llvm/MC/MCSectionELF.h"
#include "llvm/MC/MCSectionMachO.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define DEBUG_TYPE "asm-printer"

namespace {

class CILAsmPrinter : public AsmPrinter {

public:
  CILAsmPrinter(TargetMachine &TM, std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)) {}

  bool PrintAsmOperand(const MachineInstr *MI, unsigned OpNum,
                       unsigned AsmVariant, const char *ExtraCode,
                       raw_ostream &O) override;

  StringRef getPassName() const override { return "CIL Assembly Printer"; }
};

bool CILAsmPrinter::PrintAsmOperand(const MachineInstr *MI, unsigned OpNum,
                       unsigned AsmVariant, const char *ExtraCode,
                       raw_ostream &O) {
  O << "\tHi";
  return false;
}

} // end of anonymous namespace

//===----------------------------------------------------------------------===//

// Force static initialization.
extern "C" void LLVMInitializeCILAsmPrinter() {
  RegisterAsmPrinter<CILAsmPrinter> X(getTheCILTarget());
}
