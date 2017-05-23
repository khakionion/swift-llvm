//===-- CILMCAsmInfo.h - CIL asm properties --------------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the CILMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CIL_MCTARGETDESC_CILMCASMINFO_H
#define LLVM_LIB_TARGET_CIL_MCTARGETDESC_CILMCASMINFO_H

#include "llvm/MC/MCAsmInfo.h"

namespace llvm {
class Triple;

class CILMCAsmInfo : public MCAsmInfo {
  void anchor();

public:
  explicit CILMCAsmInfo(const Triple &TheTriple);
  const MCExpr*
  getExprForPersonalitySymbol(const MCSymbol *Sym, unsigned Encoding,
                              MCStreamer &Streamer) const override;
  const MCExpr* getExprForFDESymbol(const MCSymbol *Sym,
                                    unsigned Encoding,
                                    MCStreamer &Streamer) const override;

};

} // namespace llvm

#endif
