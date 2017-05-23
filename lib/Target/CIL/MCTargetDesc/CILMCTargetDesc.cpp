//===-- CILMCTargetDesc.cpp - CIL Target Descriptions --------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides CIL specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "CILMCTargetDesc.h"
#include "InstPrinter/CILInstPrinter.h"
#include "CILMCAsmInfo.h"
// #include "CILTargetStreamer.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
// #include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "CILGenInstrInfo.inc"


#define GET_REGINFO_MC_DESC
#include "CILGenRegisterInfo.inc"

static MCAsmInfo *createCILMCAsmInfo(const MCRegisterInfo &MRI,
                                       const Triple &TT) {
  MCAsmInfo *MAI = new CILMCAsmInfo(TT);
  /*
  unsigned Reg = MRI.getDwarfRegNum(SP::O6, true);
  MCCFIInstruction Inst = MCCFIInstruction::createDefCfa(nullptr, Reg, 0);
  MAI->addInitialFrameState(Inst);
  */
  return MAI;
}

static MCInstrInfo *createCILMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  // InitCILMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createCILMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  // InitCILMCRegisterInfo(X, SP::O7);
  return X;
}

/*
static MCSubtargetInfo *
createCILMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  CPU = "cil";
  // return createCILMCSubtargetInfoImpl(TT, CPU, FS);
}
*/

// Code models. Some only make sense for 64-bit code.
//
// SunCC  Reloc   CodeModel  Constraints
// abs32  Static  Small      text+data+bss linked below 2^32 bytes
// abs44  Static  Medium     text+data+bss linked below 2^44 bytes
// abs64  Static  Large      text smaller than 2^31 bytes
// pic13  PIC_    Small      GOT < 2^13 bytes
// pic32  PIC_    Medium     GOT < 2^32 bytes
//
// All code models require that the text segment is smaller than 2GB.

static void adjustCodeGenOpts(const Triple &TT, Reloc::Model RM,
                              CodeModel::Model &CM) {
  // The default 32-bit code model is abs32/pic32 and the default 32-bit
  // code model for JIT is abs32.
  switch (CM) {
  default: break;
  case CodeModel::Default:
  case CodeModel::JITDefault: CM = CodeModel::Small; break;
  }
}

static void adjustCodeGenOptsV9(const Triple &TT, Reloc::Model RM,
                                CodeModel::Model &CM) {
  // The default 64-bit code model is abs44/pic32 and the default 64-bit
  // code model for JIT is abs64.
  switch (CM) {
  default:  break;
  case CodeModel::Default:
    CM = RM == Reloc::PIC_ ? CodeModel::Small : CodeModel::Medium;
    break;
  case CodeModel::JITDefault:
    CM = CodeModel::Large;
    break;
  }
}

static MCInstPrinter *createCILMCInstPrinter(const Triple &T,
                                               unsigned SyntaxVariant,
                                               const MCAsmInfo &MAI,
                                               const MCInstrInfo &MII,
                                               const MCRegisterInfo &MRI) {
  return new CILInstPrinter(MAI, MII, MRI);
}

extern "C" void LLVMInitializeCILTargetMC() {
  // Register the MC asm info.
  RegisterMCAsmInfoFn X(getTheCILTarget(), createCILMCAsmInfo);

  for (Target *T :
       {&getTheCILTarget()}) {
    // Register the MC instruction info.
    TargetRegistry::RegisterMCInstrInfo(*T, createCILMCInstrInfo);

    // Register the MC register info.
    TargetRegistry::RegisterMCRegInfo(*T, createCILMCRegisterInfo);

    // Register the MC subtarget info.
    // TargetRegistry::RegisterMCSubtargetInfo(*T, createCILMCSubtargetInfo);

    // Register the MC Code Emitter.
    TargetRegistry::RegisterMCCodeEmitter(*T, createCILMCCodeEmitter);

    // Register the asm backend.
    TargetRegistry::RegisterMCAsmBackend(*T, createCILAsmBackend);

    // Register the object target streamer.
    // TargetRegistry::RegisterObjectTargetStreamer(*T,
    //                                              createObjectTargetStreamer);

    // Register the asm streamer.
    // TargetRegistry::RegisterAsmTargetStreamer(*T, createTargetAsmStreamer);

    // Register the MCInstPrinter
    TargetRegistry::RegisterMCInstPrinter(*T, createCILMCInstPrinter);
  }

  // Register the MC codegen info.
  TargetRegistry::registerMCAdjustCodeGenOpts(getTheCILTarget(),
                                              adjustCodeGenOpts);

}
