// Register classes.
//
// This is just a dummy register definition for now, copied from Sparc code.
// CIL doesn't have registers so it doesn't need it...I think.
//

class CILReg<bits<16> Enc, string n> : Register<n> {
  let HWEncoding = Enc;
  let Namespace = "CIL";
}

class SparcCtrlReg<bits<16> Enc, string n>: Register<n> {
  let HWEncoding = Enc;
  let Namespace = "CIL";
}

let Namespace = "CIL" in {
def sub_even : SubRegIndex<32>;
def sub_odd  : SubRegIndex<32, 32>;
def sub_even64 : SubRegIndex<64>;
def sub_odd64  : SubRegIndex<64, 64>;
}

// Registers are identified with 5-bit ID numbers.
// Ri - 32-bit integer registers
class Ri<bits<16> Enc, string n> : CILReg<Enc, n>;


def I0 : Ri<24, "I0">, DwarfRegNum<[24]>;
def I1 : Ri<25, "I1">, DwarfRegNum<[25]>;
def I2 : Ri<26, "I2">, DwarfRegNum<[26]>;
def I3 : Ri<27, "I3">, DwarfRegNum<[27]>;
def I4 : Ri<28, "I4">, DwarfRegNum<[28]>;
def I5 : Ri<29, "I5">, DwarfRegNum<[29]>;
def I6 : Ri<30, "FP">, DwarfRegNum<[30]>;
def I7 : Ri<31, "I7">, DwarfRegNum<[31]>;


def IntRegs : RegisterClass<"CIL", [i32, i64], 32, (add (sequence "I%u", 0, 7))>;