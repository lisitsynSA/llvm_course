label_0:
    XOR x1 x1 x1                    // step = 0
label_1:                            // main loop start
    XOR x2 x2 x2                    // y = 0
label_4:                            // loop y start
    XOR x5 x5 x5                    // x = 0
    MUL x3 x2 x1                    // step*y
label_13:                           // loop x
    MUL x6 x3 x5                    // step*y*x
    SUB x6 x6 16777216              // argb
    PUT_PIXEL x5 x2 x6
    INC_NE x4 x5 512
    BR_COND x4 label_13
label_10:                           // increment y
    INC_NE x4 x2 256
    BR_COND x4 label_4
label_7:                            // loop y end
    FLUSH
    INC_NE x4 x1 1000
    BR_COND x4 label_1
label_3:                            // main loop end
    EXIT
