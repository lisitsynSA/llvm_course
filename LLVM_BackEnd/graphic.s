	.text
	.file	"graphic.ll"
	.globl	app                             ; -- Begin function app
	.type	app,@function
app:                                    ; @app
; %bb.0:                                ; %entry
	MOVhi r2 65535
	ORi r2 r2 65535
	MOVli r9 5
	PUTPIXEL r9 r9 r2
	FLUSH
	BR r0
.Lfunc_end0:
	.size	app, .Lfunc_end0-app
                                        ; -- End function
	.section	".note.GNU-stack","",@progbits
