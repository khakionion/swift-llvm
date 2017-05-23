//===-- llvm/Support/CIL.h - CIL constants and data structures --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This header contains common, non-processor-specific data structures and
// constants for the CIL file format.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_SUPPORT_CIL_H
#define LLVM_SUPPORT_CIL_H

#include "llvm/Support/Compiler.h"
#include "llvm/Support/DataTypes.h"
#include <cstring>

namespace llvm {

namespace CIL {

typedef uint32_t Elf32_Addr; // Program address

// Object file magic string.
static const char CilMagic[] = {0x7f, 'C', 'I', 'L', '\0'};


} // end namespace CIL

} // end namespace llvm

#endif
