//===-- CILMCAsmInfo.cpp - CIL asm properties -----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the CILMCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "CILMCAsmInfo.h"
#include "CILMCExpr.h"
#include "llvm/ADT/Triple.h"
#include "llvm/MC/MCStreamer.h"

using namespace llvm;

void CILMCAsmInfo::anchor() {}

CILMCAsmInfo::CILMCAsmInfo(const Triple &TheTriple) {
  UseIntegratedAssembler = false;
}


const MCExpr*
CILMCAsmInfo::getExprForPersonalitySymbol(const MCSymbol *Sym,
                                               unsigned Encoding,
                                               MCStreamer &Streamer) const {
  return 0;
}

const MCExpr*
CILMCAsmInfo::getExprForFDESymbol(const MCSymbol *Sym,
                                       unsigned Encoding,
                                       MCStreamer &Streamer) const {
  return 0;
}
