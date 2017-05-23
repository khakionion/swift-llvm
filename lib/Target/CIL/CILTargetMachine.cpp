//===-- CILTargetMachine.cpp - Define TargetMachine for CIL     -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "CILTargetMachine.h"
//#include "CILTargetObjectFile.h"
//#include "CIL.h"
#include "LeonPasses.h"
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
                                       CodeGenOpt::Level OL, bool is64bit)
    : LLVMTargetMachine(T, computeDataLayout(TT, true), TT, CPU, FS, Options,
                        getEffectiveRelocModel(RM), CM, OL),
      TLOF(make_unique<CILTargetObjectFile>()),
      Subtarget(TT, CPU, FS, *this, is64bit), is64Bit(is64bit) {
  initAsmInfo();
}

CILTargetMachine::~CILTargetMachine() {}

const CILSubtarget * 
CILTargetMachine::getSubtargetImpl(const Function &F) const {
  Attribute CPUAttr = F.getFnAttribute("target-cpu");
  Attribute FSAttr = F.getFnAttribute("target-features");

  std::string CPU = !CPUAttr.hasAttribute(Attribute::None)
                        ? CPUAttr.getValueAsString().str()
                        : TargetCPU;
  std::string FS = !FSAttr.hasAttribute(Attribute::None)
                       ? FSAttr.getValueAsString().str()
                       : TargetFS;

  // FIXME: This is related to the code below to reset the target options,
  // we need to know whether or not the soft float flag is set on the
  // function, so we can enable it as a subtarget feature.
  bool softFloat =
      F.hasFnAttribute("use-soft-float") &&
      F.getFnAttribute("use-soft-float").getValueAsString() == "true";

  if (softFloat)         
    FS += FS.empty() ? "+soft-float" : ",+soft-float";

  auto &I = SubtargetMap[CPU + FS];
  if (!I) {
    // This needs to be done before we create a new subtarget since any
    // creation will depend on the TM and the code generation flags on the
    // function that reside in TargetOptions.
    resetTargetOptions(F);
    I = llvm::make_unique<CILSubtarget>(TargetTriple, CPU, FS, *this,
                                          this->is64Bit);
  }
  return I.get();
}

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
  addPass(createAtomicExpandPass(&getCILTargetMachine()));

  TargetPassConfig::addIRPasses();
}

bool CILPassConfig::addInstSelector() {
  addPass(createCILISelDag(getCILTargetMachine()));
  return false;
}

void CILPassConfig::addPreEmitPass(){
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
}

