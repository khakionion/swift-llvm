set(LLVM_TARGET_DEFINITIONS CIL.td)

tablegen(LLVM CILGenAsmMatcher.inc -gen-asm-matcher)
tablegen(LLVM CILGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM CILGenCallingConv.inc -gen-callingconv)
add_public_tablegen_target(CILCommonTableGen)

add_llvm_target(CILCodeGen
  CILTargetMachine.cpp
  CILTargetLowering.cpp
  CILTargetObjectFile.cpp
  )

#tablegen(LLVM CILGenAsmMatcher.inc -gen-asm-matcher)
#tablegen(LLVM CILGenDAGISel.inc -gen-dag-isel)
#tablegen(LLVM CILGenDisassemblerTables.inc -gen-disassembler)
#tablegen(LLVM CILGenInstrInfo.inc -gen-instr-info)
#tablegen(LLVM CILGenMCCodeEmitter.inc -gen-emitter)
#tablegen(LLVM CILGenRegisterInfo.inc -gen-register-info)
#tablegen(LLVM CILGenSubtargetInfo.inc -gen-subtarget)
#add_public_tablegen_target(CILCommonTableGen)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
add_subdirectory(InstPrinter)
