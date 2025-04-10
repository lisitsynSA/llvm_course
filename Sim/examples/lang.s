	.file	"top"
	.text
	.globl	app                             ; -- Begin function app
	.type	app,@function
app:                                    ; @app
; %bb.0:                                ; %entry
	MOVli r2 0
.LBB0_1:                                ; %loopY.preheader
                                        ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB0_2 Depth 2
                                        ;       Child Loop BB0_5 Depth 3
	MOVli r4 0
	MOVli r9 0
.LBB0_2:                                ; %loopX.preheader
                                        ;   Parent Loop BB0_1 Depth=1
                                        ; =>  This Loop Header: Depth=2
                                        ;       Child Loop BB0_5 Depth 3
	MOVli r10 0
	MOVhi r11 65280
	B .LBB0_5
.LBB0_5:                                ; %iterX
                                        ;   Parent Loop BB0_1 Depth=1
                                        ;     Parent Loop BB0_2 Depth=2
                                        ; =>    This Inner Loop Header: Depth=3
	PUTPIXEL r10 r9 r11
	INC_NEi r12 r10 512
	ADD r11 r11 r4
	BR_COND r12 .LBB0_5
	B .LBB0_6
.LBB0_6:                                ; %loopX_end
                                        ;   in Loop: Header=BB0_2 Depth=2
	INC_EQi r10 r9 256
	ADD r4 r4 r2
	BR_COND r10 .LBB0_4
	B .LBB0_2
.LBB0_4:                                ; %loopY_end
                                        ;   in Loop: Header=BB0_1 Depth=1
	INC_EQi r4 r2 1000
	FLUSH
	BR_COND r4 .LBB0_3
	B .LBB0_1
.LBB0_3:                                ; %loopStep_end
	BR r0
.Lfunc_end0:
	.size	app, .Lfunc_end0-app
                                        ; -- End function
	.section	".note.GNU-stack","",@progbits
