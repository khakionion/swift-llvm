#include "CIL.h"
#include "CILFrameLowering.h"
#include "CILTargetLowering.h"
#include "CILSubtarget.h"
// #include "CILInstrInfo.h"
// #include "CILMachineFunctionInfo.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetLowering.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Target/TargetFrameLowering.h"

using namespace llvm;

  CILFrameLowering::CILFrameLowering(const CILSubtarget &sti)
      : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, 8, 0) {
  }
  // Do nothing
  bool CILFrameLowering::hasFP(const MachineFunction &MF) const {
    return false;
  }

  void CILFrameLowering::emitPrologue(MachineFunction &MF,
                                      MachineBasicBlock &MBB) const {
  }

  void CILFrameLowering::emitEpilogue(MachineFunction &MF,
                                      MachineBasicBlock &MBB) const {
  
  }
