entry
    XOR x1 x1 x1
main_loop
    XOR x2 x2 x2
loop_y
    XOR x5 x5 x5
    MUL x3 x2 x1
loop_x
    MUL x6 x3 x5
    SUBi x6 x6 16777216
    PUT_PIXEL x5 x2 x6
    INC_NEi x4 x5 512
    BR_COND x4 loop_x
inc_y
    INC_NEi x4 x2 256
    BR_COND x4 loop_y
inc_step
    FLUSH
    INC_NEi x4 x1 1000
    BR_COND x4 main_loop
exit
    EXIT
