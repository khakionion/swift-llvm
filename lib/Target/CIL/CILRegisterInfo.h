//===-- CILRegisterInfo.h - CIL Register Information Impl ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the CIL implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CIL_CILREGISTERINFO_H
#define LLVM_LIB_TARGET_CIL_CILREGISTERINFO_H

#include "llvm/ADT/BitVector.h"
#include "llvm/Target/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "CILGenRegisterInfo.inc"

namespace llvm {
struct CILRegisterInfo : public CILGenRegisterInfo {
  CILRegisterInfo();

  /// Code Generation virtual methods...
  const MCPhysReg *getCalleeSavedRegs(const MachineFunction *MF) const override
  {
    return nullptr;
  }
  const uint32_t *getCallPreservedMask(const MachineFunction &MF,
                                       CallingConv::ID CC) const override
  {
    return nullptr;
  }

  const uint32_t* getRTCallPreservedMask(CallingConv::ID CC) const
  {
    return nullptr;
  }

  BitVector getReservedRegs(const MachineFunction &MF) const override
  {
    BitVector Reserved(getNumRegs());
    return Reserved;
  }

  const TargetRegisterClass *getPointerRegClass(const MachineFunction &MF,
                                                unsigned Kind) const override
  {
    return &CIL::GPRRegClass;
  }

  void eliminateFrameIndex(MachineBasicBlock::iterator II,
                           int SPAdj, unsigned FIOperandNum,
                           RegScavenger *RS = nullptr) const override
  {

  }

  unsigned getFrameRegister(const MachineFunction &MF) const override
  {
    return 0;
  }

  bool canRealignStack(const MachineFunction &MF) const override
  {
    return false;
  }

};

} // end namespace llvm

#endif
