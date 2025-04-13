	.file	"app2.c"
	.text
	.globl	getAbsVelocity                  ; -- Begin function getAbsVelocity
	.type	getAbsVelocity,@function
getAbsVelocity:                         ; @getAbsVelocity
; %bb.0:                                ; %entry
	ABS r2 r9
	ABS r4 r10
	ADD r2 r4 r2
	ANDi r9 r2 255
	BR r0
.Lfunc_end0:
	.size	getAbsVelocity, .Lfunc_end0-getAbsVelocity
                                        ; -- End function
	.globl	drawLine                        ; -- Begin function drawLine
	.type	drawLine,@function
drawLine:                               ; @drawLine
; %bb.0:                                ; %entry
	ABS r2 r11
	ABS r4 r12
	ADD r2 r4 r2
	SHLi r2 r2 16
	MOVhi r4 65280
	ORi r4 r4 255
	OR r2 r2 r4
	PUTPIXEL r9 r10 r2
	DIVi r4 r12 50
	ADD r4 r4 r10
	DIVi r13 r11 50
	ADD r13 r13 r9
	PUTPIXEL r13 r4 r2
	DIVi r4 r12 25
	ADD r4 r4 r10
	DIVi r13 r11 25
	ADD r13 r13 r9
	PUTPIXEL r13 r4 r2
	DIVi r4 r12 5
	MULi r13 r4 3
	DIVi r13 r13 10
	ADD r14 r13 r10
	DIVi r13 r11 5
	MULi r15 r13 3
	DIVi r15 r15 10
	ADD r15 r15 r9
	PUTPIXEL r15 r14 r2
	SHLi r14 r4 2
	DIVi r14 r14 10
	ADD r14 r14 r10
	SHLi r15 r13 2
	DIVi r15 r15 10
	ADD r15 r15 r9
	PUTPIXEL r15 r14 r2
	DIVi r12 r12 10
	ADD r12 r12 r10
	DIVi r11 r11 10
	ADD r11 r11 r9
	PUTPIXEL r11 r12 r2
	MULi r11 r4 6
	DIVi r11 r11 10
	ADD r11 r11 r10
	MULi r12 r13 6
	DIVi r12 r12 10
	ADD r12 r12 r9
	PUTPIXEL r12 r11 r2
	MULi r11 r4 7
	DIVi r11 r11 10
	ADD r11 r11 r10
	MULi r12 r13 7
	DIVi r12 r12 10
	ADD r12 r12 r9
	PUTPIXEL r12 r11 r2
	SHLi r11 r4 3
	DIVi r11 r11 10
	ADD r11 r11 r10
	SHLi r12 r13 3
	DIVi r12 r12 10
	ADD r12 r12 r9
	PUTPIXEL r12 r11 r2
	MULi r4 r4 9
	DIVi r4 r4 10
	ADD r4 r4 r10
	MULi r10 r13 9
	DIVi r10 r10 10
	ADD r9 r10 r9
	PUTPIXEL r9 r4 r2
	BR r0
.Lfunc_end1:
	.size	drawLine, .Lfunc_end1-drawLine
                                        ; -- End function
	.globl	app                             ; -- Begin function app
	.type	app,@function
app:                                    ; @app
; %bb.0:                                ; %entry
	RAND r9
	RAND r10
	RAND r2
	UREMi r2 r2 10
	RAND r4
	UREMi r4 r4 10
	ANDi r9 r9 510
	ORi r9 r9 512
	MULi r9 r9 6554
	SRLi r9 r9 16
	ANDi r10 r10 254
	ORi r10 r10 256
	MULi r10 r10 6554
	SRLi r10 r10 16
	MOVhi r11 65280
	ORi r11 r11 255
	MOVli r12 128
	MOVli r13 256
.LBB2_1:                                ; %while.cond
                                        ; =>This Inner Loop Header: Depth=1
	ABS r14 r2
	ABS r15 r4
	ADD r14 r15 r14
	SHLi r14 r14 16
	OR r14 r14 r11
	PUTPIXEL r9 r10 r14
	DIVi r15 r4 50
	ADD r15 r15 r10
	DIVi r0 r2 50
	ADD r0 r0 r9
	PUTPIXEL r0 r15 r14
	DIVi r15 r4 25
	ADD r15 r15 r10
	DIVi r0 r2 25
	ADD r0 r0 r9
	PUTPIXEL r0 r15 r14
	DIVi r0 r4 5
	MULi r15 r0 3
	DIVi r15 r15 10
	ADD r3 r15 r10
	DIVi r15 r2 5
	MULi r5 r15 3
	DIVi r5 r5 10
	ADD r5 r5 r9
	PUTPIXEL r5 r3 r14
	SHLi r3 r0 2
	DIVi r3 r3 10
	ADD r3 r3 r10
	SHLi r5 r15 2
	DIVi r5 r5 10
	ADD r5 r5 r9
	PUTPIXEL r5 r3 r14
	DIVi r3 r4 10
	ADD r3 r3 r10
	DIVi r5 r2 10
	ADD r5 r5 r9
	PUTPIXEL r5 r3 r14
	MULi r3 r0 6
	DIVi r3 r3 10
	ADD r3 r3 r10
	MULi r5 r15 6
	DIVi r5 r5 10
	ADD r5 r5 r9
	PUTPIXEL r5 r3 r14
	MULi r3 r0 7
	DIVi r3 r3 10
	ADD r3 r3 r10
	MULi r5 r15 7
	DIVi r5 r5 10
	ADD r5 r5 r9
	PUTPIXEL r5 r3 r14
	SHLi r3 r0 3
	DIVi r3 r3 10
	ADD r3 r3 r10
	SHLi r5 r15 3
	DIVi r5 r5 10
	ADD r5 r5 r9
	PUTPIXEL r5 r3 r14
	MULi r3 r0 9
	DIVi r3 r3 10
	ADD r3 r3 r10
	MULi r5 r15 9
	DIVi r5 r5 10
	ADD r5 r5 r9
	PUTPIXEL r5 r3 r14
	ADD r10 r0 r10
	SUB r14 r12 r10
	MULi r14 r14 10
	SRAi r0 r14 31
	SRLi r0 r0 24
	ADD r14 r14 r0
	ADD r9 r15 r9
	SRAi r14 r14 8
	ADD r4 r14 r4
	SUB r14 r13 r9
	MULi r14 r14 10
	SRAi r15 r14 31
	SRLi r15 r15 23
	ADD r14 r14 r15
	SRAi r14 r14 9
	ADD r2 r14 r2
	FLUSH
	B .LBB2_1
.Lfunc_end2:
	.size	app, .Lfunc_end2-app
                                        ; -- End function
	.ident	"clang version 20.1.0 (https://github.com/lisitsynSA/llvm-add-backend.git 35713b455254b19f34e2bfaf423b5dfa6444bbb9)"
	.section	".note.GNU-stack","",@progbits
