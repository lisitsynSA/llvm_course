	.text
	.file	"app.ll"
	.globl	app                             ; -- Begin function app
	.type	app,@function
app:                                    ; @app
; %bb.0:                                ; %entry
	MOVli r2 0
	MOVli r9 512
	MOVli r10 256
	MOVli r11 1000
.LBB0_1:                                ; %for.cond1.preheader
                                        ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB0_2 Depth 2
                                        ;       Child Loop BB0_3 Depth 3
	MOVli r12 0
	MOVli r13 0
.LBB0_2:                                ; %for.cond5.preheader
                                        ;   Parent Loop BB0_1 Depth=1
                                        ; =>  This Loop Header: Depth=2
                                        ;       Child Loop BB0_3 Depth 3
	MOVli r14 0
	MOVhi r15 65280
.LBB0_3:                                ; %for.body8
                                        ;   Parent Loop BB0_1 Depth=1
                                        ;     Parent Loop BB0_2 Depth=2
                                        ; =>    This Inner Loop Header: Depth=3
	PUTPIXEL r14 r13 r15
	ADD r15 r15 r12
	ADDi r14 r14 1
	B.NE r14 r9 .LBB0_3
; %bb.4:                                ; %for.cond.cleanup7
                                        ;   in Loop: Header=BB0_2 Depth=2
	ADD r12 r12 r2
	ADDi r13 r13 1
	B.NE r13 r10 .LBB0_2
; %bb.5:                                ; %for.cond.cleanup3
                                        ;   in Loop: Header=BB0_1 Depth=1
	FLUSH
	ADDi r2 r2 1
	B.NE r2 r11 .LBB0_1
; %bb.6:                                ; %for.cond.cleanup
	BR r0
.Lfunc_end0:
	.size	app, .Lfunc_end0-app
                                        ; -- End function
	.section	".note.GNU-stack","",@progbits
