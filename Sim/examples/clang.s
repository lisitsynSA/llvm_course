	.file	"app.c"
	.text
	.globl	app                             ; -- Begin function app
	.type	app,@function
app:                                    ; @app
; %bb.0:                                ; %entry
	MOVli r2 0
.LBB0_1:                                ; %for.cond1.preheader
                                        ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB0_3 Depth 2
                                        ;       Child Loop BB0_6 Depth 3
	MOVli r4 0
	MOVli r9 0
	B .LBB0_3
.LBB0_3:                                ; %for.cond5.preheader
                                        ;   Parent Loop BB0_1 Depth=1
                                        ; =>  This Loop Header: Depth=2
                                        ;       Child Loop BB0_6 Depth 3
	MOVli r10 0
	MOVhi r11 65280
	B .LBB0_6
.LBB0_6:                                ; %for.body8
                                        ;   Parent Loop BB0_1 Depth=1
                                        ;     Parent Loop BB0_3 Depth=2
                                        ; =>    This Inner Loop Header: Depth=3
	PUTPIXEL r10 r9 r11
	INC_EQi r12 r10 512
	ADD r11 r11 r4
	BR_COND r12 .LBB0_5
	B .LBB0_6
.LBB0_5:                                ; %for.cond.cleanup7
                                        ;   in Loop: Header=BB0_3 Depth=2
	INC_EQi r10 r9 256
	ADD r4 r4 r2
	BR_COND r10 .LBB0_4
	B .LBB0_3
.LBB0_4:                                ; %for.cond.cleanup3
                                        ;   in Loop: Header=BB0_1 Depth=1
	INC_EQi r4 r2 1000
	FLUSH
	BR_COND r4 .LBB0_2
	B .LBB0_1
.LBB0_2:                                ; %for.cond.cleanup
	BR r0
.Lfunc_end0:
	.size	app, .Lfunc_end0-app
                                        ; -- End function
	.ident	"clang version 20.1.0 (https://github.com/lisitsynSA/llvm-add-backend.git 0c2e205d16d270e0f5100d8ff81a7fbae0d2bbce)"
	.section	".note.GNU-stack","",@progbits
