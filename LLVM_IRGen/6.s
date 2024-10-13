ENTRY
    read x2
    addi x3 x3 1
    b LOOP
EXIT
    exit
LOOP
    addi x1 x1 1
    mul x3 x3 x1
    dump x3
    bne x2 x1 LOOP
preEXIT
    sort
    b EXIT
