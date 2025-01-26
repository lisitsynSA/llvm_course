def add;
def mul;
def GPR;
def Imm;

class Inst <int opc, string asmstr, dag pattern> {
    int Opcode = opc;
    string AsmString = asmstr;
    dag Pattern = pattern;
}

class Inst_A <int opc, string asmstr, dag op> : 
    Inst<opc, !strconcat(asmstr, " $dst, $src1, $src2"), (op GPR:$dst, GPR:$src1, GPR:$src2)>;

def ADD : Inst_A <0b111, "add", (add)>;

def MADD : Inst <0b100000, "madd $src1, $src2, $src3",
                 (add GPR:$dst, GPR:$src1, (mul GPR:$dst2, GPR:$src2, GPR:$src3))>;




                 
