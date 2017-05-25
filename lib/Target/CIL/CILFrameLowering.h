#ifndef LLVM_LIB_TARGET_CIL_CILFRAMELOWERING_H
#define LLVM_LIB_TARGET_CIL_CILFRAMELOWERING_H

#include "llvm/Target/TargetFrameLowering.h"


namespace llvm {

class CILFrameLowering : public TargetFrameLowering {
public:
  explicit CILFrameLowering(const CILSubtarget &sti);
    public:
      CILFrameLowering();
      void emitPrologue(MachineFunction &MF,
                      MachineBasicBlock &MBB) const override;
      void emitEpilogue(MachineFunction &MF,
                      MachineBasicBlock &MBB) const override;
      bool hasFP(const MachineFunction &MF) const override;
  };
}

#endif
