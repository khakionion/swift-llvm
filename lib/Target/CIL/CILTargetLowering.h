#ifndef LLVM_LIB_TARGET_CIL_CILTARGETLOWERING_H
#define LLVM_LIB_TARGET_CIL_CILTARGETLOWERING_H

#include "llvm/Target/TargetLowering.h"

namespace llvm {
 class CILTargetLowering final : public TargetLowering {
  public:
    explicit CILTargetLowering(const TargetMachine &TM, const CILSubtarget &STI);
 };
}

#endif
