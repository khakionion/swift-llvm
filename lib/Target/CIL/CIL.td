include "llvm/Target/Target.td"

include "CILCallingConv.td"
include "CILGenMCCodeEmitter.td"

def CILAsmParser : AsmParser {
  bit ShouldEmitMatchRegisterName = 0;
}

def CILAsmWriter : AsmWriter {
  string AsmWriterClassName  = "InstPrinter";
  int PassSubtarget = 1;
  int Variant = 0;
}

def Sparc : Target {
  // Pull in Instruction Info:
  // let InstructionSet = CILInstrInfo;
  let AssemblyParsers  = [CILAsmParser];
  let AssemblyWriters = [CILAsmWriter];
}

