//===- CILRegisterInfo.cpp - CIL Register Information -------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the CIL implementation of the TargetRegisterInfo
// class.
//
//===----------------------------------------------------------------------===//

#include "CIL.h"
#include "CILRegisterInfo.h"
#include "CILSubtarget.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/Triple.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetFrameLowering.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

#define GET_REGINFO_TARGET_DESC
#include "CILGenRegisterInfo.inc"

CILRegisterInfo::CILRegisterInfo()
    : CILGenRegisterInfo(CIL::GPRRegClassID) {}

