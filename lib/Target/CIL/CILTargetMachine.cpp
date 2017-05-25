//===-- CILTargetMachine.cpp - Define TargetMachine for CIL     -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
#include "CIL.h"
#include "CILSubtarget.h"
#include "CILTargetMachine.h"
#include "CILTargetLowering.h"
#include "CILTargetObjectFile.h"
#include "CILTargetTransformInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

extern "C" void LLVMInitializeCILTarget() {
  // Register the target.
  RegisterTargetMachine<CILTargetMachine> X(getTheCILTarget());
}

static std::string computeDataLayout(const Triple &T, bool is64Bit) {
  std::string Ret = "e";
  Ret += "-m:e";

  // Alignments for 64 bit integers.
  Ret += "-i64:64";
  Ret += "-n32:64";
  Ret += "-S128";

  return Ret;
}

static Reloc::Model getEffectiveRelocModel(Optional<Reloc::Model> RM) {
  if (!RM.hasValue())
    return Reloc::Static;
  return *RM;
}

/// Create an CIL architecture model
CILTargetMachine::CILTargetMachine(const Target &T, const Triple &TT,
                                       StringRef CPU, StringRef FS,
                                       const TargetOptions &Options,
                                       Optional<Reloc::Model> RM,
                                       CodeModel::Model CM,
                                       CodeGenOpt::Level OL)
    : LLVMTargetMachine(T, computeDataLayout(TT, true), TT, CPU, FS, Options,
                        getEffectiveRelocModel(RM), CM, OL), 
                        TLOF(make_unique<CILTargetObjectFile>()), 
                        Subtarget(TT, CPU, FS, *this) {
  initAsmInfo();
}

CILTargetMachine::~CILTargetMachine() {}

namespace {
/// CIL Code Generator Pass Configuration Options.
class CILPassConfig : public TargetPassConfig {
public:
  CILPassConfig(CILTargetMachine *TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

  CILTargetMachine &getCILTargetMachine() const {
    return getTM<CILTargetMachine>();
  }

  void addIRPasses() override;
  bool addInstSelector() override;
  void addPreEmitPass() override;
};
} // namespace

TargetPassConfig *CILTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new CILPassConfig(this, PM);
}
void CILPassConfig::addIRPasses() {
  //addPass(createAtomicExpandPass(&getCILTargetMachine()));

  // TargetPassConfig::addIRPasses();
}

bool CILPassConfig::addInstSelector() {
  //addPass(createCILISelDag(getCILTargetMachine()));
  return false;
}

void CILPassConfig::addPreEmitPass(){
  /*
  addPass(createCILDelaySlotFillerPass(getCILTargetMachine()));

  if (this->getCILTargetMachine().getSubtargetImpl()->insertNOPLoad())
  {
    addPass(new InsertNOPLoad(getCILTargetMachine()));
  }
  if (this->getCILTargetMachine().getSubtargetImpl()->fixFSMULD())
  {
    addPass(new FixFSMULD(getCILTargetMachine()));
  }
  if (this->getCILTargetMachine().getSubtargetImpl()->replaceFMULS())
  {
    addPass(new ReplaceFMULS(getCILTargetMachine()));
  }
  if (this->getCILTargetMachine().getSubtargetImpl()->detectRoundChange()) {
    addPass(new DetectRoundChange(getCILTargetMachine()));
  }
  if (this->getCILTargetMachine().getSubtargetImpl()->fixAllFDIVSQRT())
  {
    addPass(new FixAllFDIVSQRT(getCILTargetMachine()));
  }
  */
}

TargetIRAnalysis CILTargetMachine::getTargetIRAnalysis() {
  return TargetIRAnalysis([this](const Function &F) {
    return TargetTransformInfo(CILTTIImpl(this, F));
  });
}
