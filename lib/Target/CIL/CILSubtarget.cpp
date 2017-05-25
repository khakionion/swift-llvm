//===-- CILSubtarget.cpp - cIL Subtarget Information ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the CIL specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "CIL.h"
#include "CILSubtarget.h"
#include "CILTargetLowering.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "cil-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "CILGenSubtargetInfo.inc"

void CILSubtarget::anchor() { }

CILSubtarget::CILSubtarget(const Triple &TT, const std::string &CPU,
                               const std::string &FS, const TargetMachine &TM)
    : CILGenSubtargetInfo(TT, CPU, FS), FrameLowering(*this), TargetLowering(TM, *this), InstrInfo(*this) {}
