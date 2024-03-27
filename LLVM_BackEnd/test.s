	.text
	.file	"test.ll"
	.globl	main                            ; -- Begin function main
	.type	main,@function
main:                                   ; @main
; %bb.0:
	MOVli r9 12
	BR r0
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
                                        ; -- End function
	.section	".note.GNU-stack","",@progbits
