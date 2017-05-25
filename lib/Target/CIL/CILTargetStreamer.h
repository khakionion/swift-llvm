//===-- CILTargetStreamer.h - CIL Target Streamer ----------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CIL_CILTARGETSTREAMER_H
#define LLVM_LIB_TARGET_CIL_CILTARGETSTREAMER_H

#include "llvm/MC/MCStreamer.h"

namespace llvm {
class CILTargetStreamer : public MCTargetStreamer {
  virtual void anchor();

public:
  CILTargetStreamer(MCStreamer &S);
};

// This part is for ascii assembly output
class CILTargetAsmStreamer : public CILTargetStreamer {
  formatted_raw_ostream &OS;

public:
  CILTargetAsmStreamer(MCStreamer &S, formatted_raw_ostream &OS);
  void emitCILRegisterIgnore(unsigned reg);
  void emitCILRegisterScratch(unsigned reg);

};

} // end namespace llvm

#endif
