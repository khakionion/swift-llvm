//===-- CILTargetTransformInfo.h - CIL specific TTI ---------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file a TargetTransformInfo::Concept conforming object specific to the
// CIL target machine. It uses the target's detailed information to
// provide more precise answers to certain TTI queries, while letting the
// target independent and default TTI implementations handle the rest.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CIL_CILTARGETTRANSFORMINFO_H
#define LLVM_LIB_TARGET_CIL_CILTARGETTRANSFORMINFO_H

#include "CIL.h"
#include "CILTargetMachine.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/BasicTTIImpl.h"
#include "llvm/Target/TargetLowering.h"

namespace llvm {
class CILTTIImpl : public BasicTTIImplBase<CILTTIImpl> {
  typedef BasicTTIImplBase<CILTTIImpl> BaseT;
  typedef TargetTransformInfo TTI;
  friend BaseT;

public:
  explicit CILTTIImpl(const CILTargetMachine *TM, const Function &F)
      : BaseT(TM, F.getParent()->getDataLayout()) {}

  bool shouldBuildLookupTables() const { return false; }

/*
  TargetTransformInfo::PopcntSupportKind getPopcntSupport(unsigned TyWidth) {
    if (TyWidth == 32)
      return TTI::PSK_FastHardware;
    return TTI::PSK_Software;
  }
*/
/*
  unsigned getArithmeticInstrCost(
      unsigned Opcode, Type *Ty,
      TTI::OperandValueKind Opd1Info = TTI::OK_AnyValue,
      TTI::OperandValueKind Opd2Info = TTI::OK_AnyValue,
      TTI::OperandValueProperties Opd1PropInfo = TTI::OP_None,
      TTI::OperandValueProperties Opd2PropInfo = TTI::OP_None,
      ArrayRef<const Value *> Args = ArrayRef<const Value *>()) {
    int ISD = TLI->InstructionOpcodeToISD(Opcode);

    switch (ISD) {
    default:
      return BaseT::getArithmeticInstrCost(Opcode, Ty, Opd1Info, Opd2Info,
                                           Opd1PropInfo, Opd2PropInfo);
    case ISD::MUL:
    case ISD::SDIV:
    case ISD::UDIV:
    case ISD::UREM:
      // This increases the cost associated with multiplication and division
      // to 64 times what the baseline arithmetic cost is. The arithmetic
      // instruction cost was arbitrarily chosen to reduce the desirability
      // of emitting arithmetic instructions that are emulated in software.
      // TODO: Investigate the performance impact given specialized lowerings.
      return 64 * BaseT::getArithmeticInstrCost(Opcode, Ty, Opd1Info, Opd2Info,
                                                Opd1PropInfo, Opd2PropInfo);
    }
  }
*/
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_LANAI_LANAITARGETTRANSFORMINFO_H
