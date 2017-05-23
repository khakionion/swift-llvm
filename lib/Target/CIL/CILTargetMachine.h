//===-- CILTargetMachine.h - Define TargetMachine for Mips -----*- C++ -*-===//
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

/*
#include "MCTargetDesc/MipsABIInfo.h"
#include "MipsSubtarget.h"
*/
#include "llvm/CodeGen/BasicTTIImpl.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/Target/TargetFrameLowering.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class CILTargetMachine : public LLVMTargetMachine {
  virtual void anchor();
  // Selected ABI
/*
  MipsABIInfo ABI;
  MipsSubtarget *Subtarget;
  MipsSubtarget DefaultSubtarget;
  MipsSubtarget NoMips16Subtarget;
  MipsSubtarget Mips16Subtarget;

  mutable StringMap<std::unique_ptr<MipsSubtarget>> SubtargetMap;
*/
public:
  CILTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                    StringRef FS, const TargetOptions &Options,
                    Optional<Reloc::Model> RM, CodeModel::Model CM,
                     CodeGenOpt::Level OL);

  ~CILTargetMachine() override;
};

} // End llvm namespace

#endif
