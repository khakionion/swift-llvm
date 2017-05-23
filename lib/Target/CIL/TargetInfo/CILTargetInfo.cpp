//===-- CILTargetInfo.cpp - CIL Target Implementation -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "CIL.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

Target &llvm::getTheCILTarget() {
  static Target TheCILTarget;
  return TheCILTarget;
}

extern "C" void LLVMInitializeCILTargetInfo() {
  RegisterTarget<Triple::cil, /*HasJIT=*/false> X(getTheCILTarget(), "cil",
                                                   "CIL");
}
