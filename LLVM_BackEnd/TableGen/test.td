class SimReg<bits<4> Enc = 0, string n> {
    bits<4> HWEncoding = Enc;
    string Name = n;
    string purpose;
}

class SimRegGPR<bits<4> Enc, string n> : SimReg<Enc, n> {
    let purpose = "GPR";
}

foreach I = 0-3 in {
    def R#I : SimRegGPR<!add(I,2), "r"#I>;
}

class SimRegVEC<bits<4> Enc, string n, int s> : SimReg<Enc, n> {
    let purpose = "VEC";
    int size = s;
}

multiclass SimRegVEC<bits<4> Enc, string n> {
    def D#NAME : SimRegVEC<!add(Enc, 6), "d"#n, 64>;
    def Q#NAME : SimRegVEC<!add(Enc,10), "q"#n, 128>;
}

foreach I = 0-3 in {
    defm ""#I : SimRegVEC<I, ""#I>;
}

/*
class SimGPReg<bits<4> Enc, string n> : SimReg<Enc, n> {
    int size;
}

let purpose = "GPR", size = 32  in {
    foreach I = 1-4 in {
        def R#I : SimGPReg<I, "r"#I>;
    }
}


class SimVecReg<bits<4> Enc, string n, int size> : SimReg<Enc, n> {
    int Size = size;
    let purpose = "Vec";
    bits<2> part = Enc{1...0};
}

multiclass SimDQReg<bits<4> Enc, string n> {
    def D#NAME : SimVecReg<Enc, "d"#n, 64>;
    def Q#NAME : SimVecReg<Enc, "q"#n, 128>;
}

foreach I = 1-4 in {
    defm ""#I : SimDQReg<I, ""#I>;
}





let purpose = "GPR" in {
    foreach I = 1-15 in {
        def R#I : SimGPReg<I, "r"#I>;
    }
}

class SimVecReg<bits<4> Enc, string n, int size> : SimReg<Enc, n> {
    int Size = size;
    let purpose = "Vec";
    bits<2> part = Enc{1...0};
}

multiclass SimDQReg<bits<4> Enc, string n> {
    def D#NAME : SimVecReg<Enc, "d"#n, 64>;
    def Q#NAME : SimVecReg<Enc, "q"#n, 128>;
}

foreach I = 1-4 in {
    defm ""#I : SimDQReg<I, ""#I>;
}
*/
