//===- lib/Target/CIL/CILTargetLowering.h - Target lowering -*- C++ -*---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file describes how to lower LLVM calls to machine code calls.
///
//===----------------------------------------------------------------------===//
#include "CIL.h"
#include "CILSubtarget.h"
#include "CILTargetLowering.h"
#include "CILTargetMachine.h"
#include "llvm/CodeGen/MachineValueType.h"
#include "llvm/CodeGen/CallingConvLower.h"


using namespace llvm;

CILTargetLowering::CILTargetLowering(const TargetMachine &TM,
                                     const CILSubtarget &STI) : TargetLowering(TM) {
}
