//===------- CILTargetObjectFile.cpp - CIL Object Info Impl -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "CILTargetObjectFile.h"
#include "MCTargetDesc/CILMCExpr.h"
#include "llvm/CodeGen/MachineModuleInfoImpls.h"
#include "llvm/Support/Dwarf.h"
#include "llvm/Target/TargetLowering.h"

using namespace llvm;
CILTargetObjectFile::CILTargetObjectFile() {
}
/*
  void CILTargetObjectFile::emitPersonalityValue(MCStreamer &Streamer, const DataLayout &TM,
                            const MCSymbol *Sym) const  {
}
                            
  /// Given a constant with the SectionKind, return a section that it should be
  /// placed in.
  MCSection *CILTargetObjectFile::getSectionForConstant(const DataLayout &DL, SectionKind Kind,
                                   const Constant *C,
                                   unsigned &Align) const {
                                  
} 
*/
  MCSection *CILTargetObjectFile::getExplicitSectionGlobal(const GlobalObject *GO, SectionKind Kind,
                                      const TargetMachine &TM) const {
llvm_unreachable("Unhandled expression!");
}
                                      
  MCSection *CILTargetObjectFile::SelectSectionForGlobal(const GlobalObject *GO, SectionKind Kind,
                                    const TargetMachine &TM) const {
llvm_unreachable("Unhandled expression!");
}
/*
                                    
MCSection *CILTargetObjectFile::getSectionForJumpTable(const Function &F,
                                    const TargetMachine &TM) const {
}
                                    
bool CILTargetObjectFile::shouldPutJumpTableInFunctionSection(bool UsesLabelDifference,
                                           const Function &F) const {
  return false;
}
                                           
  // The symbol that gets passed to .cfi_personality.
MCSymbol *CILTargetObjectFile::getCFIPersonalitySymbol(const GlobalValue *GV,
                                    const TargetMachine &TM,
                                    MachineModuleInfo *MMI) const {
}
                                    
MCSection *CILTargetObjectFile::getStaticCtorSection(unsigned Priority,
                                  const MCSymbol *KeySym) const {
}
MCSection *CILTargetObjectFile::getStaticDtorSection(unsigned Priority,
                                  const MCSymbol *KeySym) const {
}
                                  
const MCExpr *CILTargetObjectFile::lowerRelativeReference(const GlobalValue *LHS,
                                       const GlobalValue *RHS,
                                       const TargetMachine &TM) const {
}
const MCExpr *CILTargetObjectFile::getTTypeGlobalReference(
    const GlobalValue *GV, unsigned Encoding, const TargetMachine &TM,
    MachineModuleInfo *MMI, MCStreamer &Streamer) const {

  if (Encoding & dwarf::DW_EH_PE_pcrel) {
    MachineModuleInfoELF &ELFMMI = MMI->getObjFileInfo<MachineModuleInfoELF>();

    MCSymbol *SSym = getSymbolWithGlobalValueBase(GV, ".DW.stub", TM);

    // Add information about the stub reference to ELFMMI so that the stub
    // gets emitted by the asmprinter.
    MachineModuleInfoImpl::StubValueTy &StubSym = ELFMMI.getGVStubEntry(SSym);
    if (!StubSym.getPointer()) {
      MCSymbol *Sym = TM.getSymbol(GV);
      StubSym = MachineModuleInfoImpl::StubValueTy(Sym, !GV->hasLocalLinkage());
    }

    MCContext &Ctx = getContext();
    return CILMCExpr::create(CILMCExpr::VK_Sparc_R_DISP32,
                               MCSymbolRefExpr::create(SSym, Ctx), Ctx);
  }

  return TargetLoweringObjectFileELF::getTTypeGlobalReference(GV, Encoding, TM,
                                                              MMI, Streamer);
}
*/
