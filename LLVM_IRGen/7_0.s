ENTRY
    read x1
    addi x3 x3 1
LOOP
    addi x2 x2 1
    mul x3 x3 x2
    bne x1 x2 LOOP
EXIT
    write x3
    exit