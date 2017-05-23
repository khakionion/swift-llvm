//===-- CILTargetStreamer.cpp - CIL Target Streamer Methods ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides CIL specific target streamer methods.
//
//===----------------------------------------------------------------------===//

#include "CILTargetStreamer.h"
#include "InstPrinter/CILInstPrinter.h"
#include "llvm/Support/FormattedStream.h"

using namespace llvm;

// pin vtable to this file
CILTargetStreamer::CILTargetStreamer(MCStreamer &S) : MCTargetStreamer(S) {}

void CILTargetStreamer::anchor() {}

CILTargetAsmStreamer::CILTargetAsmStreamer(MCStreamer &S,
                                               formatted_raw_ostream &OS)
    : CILTargetStreamer(S), OS(OS) {}

void CILTargetAsmStreamer::emitCILRegisterIgnore(unsigned reg) {
  OS << "\t.register "
     << "%" << StringRef(CILInstPrinter::getRegisterName(reg)).lower()
     << ", #ignore\n";
}

void CILTargetAsmStreamer::emitCILRegisterScratch(unsigned reg) {
  OS << "\t.register "
     << "%" << StringRef(CILInstPrinter::getRegisterName(reg)).lower()
     << ", #scratch\n";
}
