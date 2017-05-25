//===-- CIL.h - Top-level interface for CIL representation --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// CIL back-end.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CIL_CIL_H
#define LLVM_LIB_TARGET_CIL_CIL_H

#include "MCTargetDesc/CILMCTargetDesc.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
  //class FunctionPass;
  class CILTargetMachine;
  class CILSubtarget;
  //class formatted_raw_ostream;
  //class AsmPrinter;
  //class MCInst;
  //class MachineInstr;
  // Enums corresponding to Sparc condition codes, both icc's and fcc's.  These
  // values must be kept in sync with the ones in the .td file.
  namespace CILCC {
    enum CondCodes {
      ICC_A   =  8   ,  // Always
      ICC_N   =  0   ,  // Never
    };
  }

  inline static const char *CILCondCodeToString(CILCC::CondCodes CC) {
    switch (CC) {
    case CILCC::ICC_A:   return "a";
    case CILCC::ICC_N:   return "n";
    }
    llvm_unreachable("Invalid cond code");
  }

} // end namespace llvm;

#endif
