//===-- MipsTargetMachine.cpp - Define TargetMachine for Mips -------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Implements the info about Mips target spec.
//
//===----------------------------------------------------------------------===//

/*
#include "MipsTargetMachine.h"
#include "Mips.h"
#include "Mips16FrameLowering.h"
#include "Mips16ISelDAGToDAG.h"
#include "Mips16ISelLowering.h"
#include "Mips16InstrInfo.h"
#include "MipsFrameLowering.h"
#include "MipsInstrInfo.h"
#include "MipsSEFrameLowering.h"
#include "MipsSEISelDAGToDAG.h"
#include "MipsSEISelLowering.h"
#include "MipsSEInstrInfo.h"
#include "MipsTargetObjectFile.h"
*/
#include "CILTargetMachine.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Scalar.h"

using namespace llvm;

extern "C" void LLVMInitializeCILTarget() {
  // Register the target.
  RegisterTargetMachine<CILTargetMachine> X(getTheCILTarget());
}

void CILTargetMachine::anchor() { }

CILTargetMachine::CILTargetMachine(const Target &T, const Triple &TT,
                                     StringRef CPU, StringRef FS,
                                     const TargetOptions &Options,
                                     Optional<Reloc::Model> RM, CodeModel::Model CM,
                                     CodeGenOpt::Level OL)
    : LLVMTargetMachine(T, "insert-data-layout", TT, CPU, FS, Options,
                        Reloc::Static, CM, OL) {}
CILTargetMachine::~CILTargetMachine() {}
