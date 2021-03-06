//===-- CILInstrFormats.td - CIL Instruction Formats ---*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//
//  These instruction format definitions are copied from the RISC-V
//  implementation. CIL doesn't use registers, so we probably don't 
//  actually need these. 
//
//===----------------------------------------------------------------------===//

class CILInst<dag outs, dag ins, string asmstr, list<dag> pattern>
    : Instruction {
  field bits<32> Inst;
  let Size = 4;

  bits<7> Opcode = 0;

  let Inst{6-0} = Opcode;

  let Namespace = "CIL";

  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString = asmstr;
  let Pattern = pattern;
}

// Pseudo instructions
class Pseudo<dag outs, dag ins, string asmstr, list<dag> pattern>
    : CILInst<outs, ins, asmstr, pattern> {
  let isPseudo = 1;
}

class FR<bits<7> funct7, bits<3> funct3, bits<7> opcode, dag outs, dag ins,
         string asmstr, list<dag> pattern> : CILInst<outs, ins, asmstr, pattern>
{
  bits<5> rs2;
  bits<5> rs1;
  bits<5> rd;

  let Inst{31-25} = funct7;
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
  let Opcode = opcode;
}

class FI<bits<3> funct3, bits<7> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
    : CILInst<outs, ins, asmstr, pattern>
{
  bits<12> imm12;
  bits<5> rs1;
  bits<5> rd;

  let Inst{31-20} = imm12;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
  let Opcode = opcode;
}

class FI32Shift<bit arithshift, bits<3> funct3, bits<7> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
    : CILInst<outs, ins, asmstr, pattern>
{
  bits<5> shamt;
  bits<5> rs1;
  bits<5> rd;

  let Inst{31} = 0;
  let Inst{30} = arithshift;
  let Inst{29-25} = 0;
  let Inst{24-20} = shamt;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
  let Opcode = opcode;
}

class FS<bits<3> funct3, bits<7> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
    : CILInst<outs, ins, asmstr, pattern>
{
  bits<12> imm12;
  bits<5> rs2;
  bits<5> rs1;

  let Inst{31-25} = imm12{11-5};
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = imm12{4-0};
  let Opcode = opcode;
}

class FSB<bits<3> funct3, bits<7> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
    : CILInst<outs, ins, asmstr, pattern>
{
  bits<12> imm12;
  bits<5> rs2;
  bits<5> rs1;

  let Inst{31} = imm12{11};
  let Inst{30-25} = imm12{9-4};
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-8} = imm12{3-0};
  let Inst{7} = imm12{10};
  let Opcode = opcode;
}

class FU<bits<7> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
    : CILInst<outs, ins, asmstr, pattern>
{
  bits<20> imm20;
  bits<5> rd;

  let Inst{31-12} = imm20;
  let Inst{11-7} = rd;
  let Opcode = opcode;
}

class FUJ<bits<7> opcode, dag outs, dag ins, string asmstr, list<dag> pattern>
    : CILInst<outs, ins, asmstr, pattern>
{
  bits<20> imm20;
  bits<5> rd;

  let Inst{31} = imm20{19};
  let Inst{30-21} = imm20{9-0};
  let Inst{20} = imm20{10};
  let Inst{19-12} = imm20{18-11};
  let Inst{11-7} = rd;
  let Opcode = opcode;
}
