add_llvm_target(CILCodeGen
  CILTargetMachine.cpp
  CILTargetLowering.cpp
  )

add_subdirectory(TargetInfo)
