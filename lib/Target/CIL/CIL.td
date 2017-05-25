include "llvm/Target/Target.td"

include "CILRegisterInfo.td"

include "CILCallingConv.td"

include "CILInstrInfo.td"
def CILInstrInfo : InstrInfo;

def : Processor<"generic", NoItineraries,      []>;

include "CILAsmWriter.td"

def CILAsmParser : AsmParser {
  bit ShouldEmitMatchRegisterName = 0;
}

def CIL : Target {
  // Pull in Instruction Info:
  let InstructionSet = CILInstrInfo;
  let AssemblyParsers  = [CILAsmParser];
  let AssemblyWriters = [CILAsmWriter];
}

