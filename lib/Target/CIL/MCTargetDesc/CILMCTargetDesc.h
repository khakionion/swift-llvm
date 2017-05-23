//===-- CILMCTargetDesc.h - CIL Target Descriptions -------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides CIL specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_CIL_MCTARGETDESC_CILMCTARGETDESC_H
#define LLVM_LIB_TARGET_CIL_MCTARGETDESC_CILMCTARGETDESC_H

#include "llvm/Support/DataTypes.h"

namespace llvm {
class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCObjectWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCTargetOptions;
class Target;
class Triple;
class StringRef;
class raw_pwrite_stream;
class raw_ostream;

Target &getTheCILTarget();

MCCodeEmitter *createCILMCCodeEmitter(const MCInstrInfo &MCII,
                                        const MCRegisterInfo &MRI,
                                        MCContext &Ctx);
MCAsmBackend *createCILAsmBackend(const Target &T, const MCRegisterInfo &MRI,
                                    const Triple &TT, StringRef CPU,
                                    const MCTargetOptions &Options);
MCObjectWriter *createCILObjectWriter(raw_pwrite_stream &OS, bool Is64Bit,
                                           bool IsLIttleEndian, uint8_t OSABI);
} // End llvm namespace

// Defines symbolic names for CIL registers.  This defines a mapping from
// register name to register number.
//
#define GET_REGINFO_ENUM
#include "CILGenRegisterInfo.inc"

// Defines symbolic names for the CIL instructions.
//
#define GET_INSTRINFO_ENUM
#include "CILGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "CILGenSubtargetInfo.inc"

#endif
