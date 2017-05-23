//===-- CILTargetMachine.h - Define TargetMachine for CIL -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the CIL specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CIL_CILTARGETMACHINE_H
#define LLVM_LIB_TARGET_CIL_CILTARGETMACHINE_H

//#include "CILInstrInfo.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class CILTargetMachine : public LLVMTargetMachine {

public:
  CILTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                     StringRef FS, const TargetOptions &Options,
                     Optional<Reloc::Model> RM, CodeModel::Model CM,
                     CodeGenOpt::Level OL, bool is64bit);
  ~CILTargetMachine() override;

  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
};


} // end namespace llvm

#endif
