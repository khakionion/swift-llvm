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

#include "llvm/IR/Function.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class CILTargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  CILSubtarget        Subtarget;

public:
  CILTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                     StringRef FS, const TargetOptions &Options,
                     Optional<Reloc::Model> RM, CodeModel::Model CM,
                     CodeGenOpt::Level OL);
  ~CILTargetMachine() override;

  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }

  /// \brief Get the TargetIRAnalysis for this target.
  TargetIRAnalysis getTargetIRAnalysis() override;

  const CILSubtarget *getSubtargetImpl() const { return &Subtarget; }
  const CILSubtarget *getSubtargetImpl(const Function &) const override {
    return &Subtarget;
  }

};


} // end namespace llvm

#endif
