//===- CILCallingConv.td - Calling Conventions for CIL -*- tablegen -*-----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// This describes the calling conventions for CIL architecture.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// CIL Return Value Calling Convention (Stack-based, so do nothing)
//===----------------------------------------------------------------------===//
def RetCC_CIL : CallingConv<[
  CCCustom<"customCILReturn">
]>;

//===----------------------------------------------------------------------===//
// CIL Argument Calling Conventions
//===----------------------------------------------------------------------===//
def CC_CIL : CallingConv<[
  CCCustom<"customCILArgument">
]>;
