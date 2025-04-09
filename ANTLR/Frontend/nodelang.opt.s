	.file	"top"
	.text
	.globl	PUT_PIXEL                       ; -- Begin function PUT_PIXEL
	.type	PUT_PIXEL,@function
PUT_PIXEL:                              ; @PUT_PIXEL
; %bb.0:                                ; %entry
	PUTPIXEL r9 r10 r11
	MOVli r9 0
	BR r0
.Lfunc_end0:
	.size	PUT_PIXEL, .Lfunc_end0-PUT_PIXEL
                                        ; -- End function
	.globl	FLUSH                           ; -- Begin function FLUSH
	.type	FLUSH,@function
FLUSH:                                  ; @FLUSH
; %bb.0:                                ; %entry
	FLUSH
	MOVli r9 0
	BR r0
.Lfunc_end1:
	.size	FLUSH, .Lfunc_end1-FLUSH
                                        ; -- End function
	.globl	color                           ; -- Begin function color
	.type	color,@function
color:                                  ; @color
; %bb.0:                                ; %entry
	MUL r2 r10 r9
	MUL r2 r2 r11
	MOVhi r4 65280
	ADD r9 r2 r4
	BR r0
.Lfunc_end2:
	.size	color, .Lfunc_end2-color
                                        ; -- End function
	.globl	app                             ; -- Begin function app
	.type	app,@function
app:                                    ; @app
; %bb.0:                                ; %entry
	MOVli r2 0
.LBB3_1:                                ; %.preheader2
                                        ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB3_3 Depth 2
                                        ;       Child Loop BB3_5 Depth 3
	MOVli r4 0
	MOVli r9 0
	B .LBB3_3
.LBB3_3:                                ; %.preheader
                                        ;   Parent Loop BB3_1 Depth=1
                                        ; =>  This Loop Header: Depth=2
                                        ;       Child Loop BB3_5 Depth 3
	MOVli r10 0
	MOVhi r11 65280
	B .LBB3_5
.LBB3_5:                                ;   Parent Loop BB3_1 Depth=1
                                        ;     Parent Loop BB3_3 Depth=2
                                        ; =>    This Inner Loop Header: Depth=3
	PUTPIXEL r10 r9 r11
	INC_NEi r12 r10 512
	ADD r11 r11 r4
	BR_COND r12 .LBB3_5
	B .LBB3_6
.LBB3_6:                                ;   in Loop: Header=BB3_3 Depth=2
	INC_EQi r10 r9 256
	ADD r4 r4 r2
	BR_COND r10 .LBB3_4
	B .LBB3_3
.LBB3_4:                                ;   in Loop: Header=BB3_1 Depth=1
	INC_EQi r4 r2 42
	FLUSH
	BR_COND r4 .LBB3_2
	B .LBB3_1
.LBB3_2:
	MOVli r9 42
	BR r0
.Lfunc_end3:
	.size	app, .Lfunc_end3-app
                                        ; -- End function
	.section	".note.GNU-stack","",@progbits
