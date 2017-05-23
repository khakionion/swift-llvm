//===-- CILFixupKinds.h - CIL Specific Fixup Entries --------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CIL_MCTARGETDESC_CILFIXUPKINDS_H
#define LLVM_LIB_TARGET_CIL_MCTARGETDESC_CILFIXUPKINDS_H

#include "llvm/MC/MCFixup.h"

namespace llvm {
  namespace CIL {
    enum Fixups {
      // Marker
      FirstTargetFixupKind,
      LastTargetFixupKind = FirstTargetFixupKind,
      NumTargetFixupKinds = LastTargetFixupKind - FirstTargetFixupKind
    };
  }
}

#endif
