	.file	"valToBin.c"
	.text
	.p2align 4
	.globl	valueToBinary
	.type	valueToBinary, @function
valueToBinary:
.LFB11:
	.cfi_startproc
	movq	%rsi, %r8
	movq	%rdx, %rsi
	xorl	%ecx, %ecx
	leaq	-1(%rdx,%r8), %rdx
	testq	%rsi, %rsi
	je	.L1
	.p2align 4,,10
	.p2align 3
.L3:
	movq	%rdi, %rax
	subq	$1, %rdx
	shrq	%cl, %rax
	addq	$1, %rcx
	andl	$1, %eax
	movb	%al, 1(%rdx)
	cmpq	%rcx, %rsi
	jne	.L3
.L1:
	ret
	.cfi_endproc
.LFE11:
	.size	valueToBinary, .-valueToBinary
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB12:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	xorl	%ecx, %ecx
	movl	$50, %esi
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$48, %rsp
	.cfi_def_cfa_offset 80
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	leaq	35(%rsp), %rdx
	.p2align 4,,10
	.p2align 3
.L9:
	movq	%rsi, %rax
	subq	$1, %rdx
	shrq	%cl, %rax
	addq	$1, %rcx
	andl	$1, %eax
	movb	%al, 1(%rdx)
	cmpq	$36, %rcx
	jne	.L9
	movq	%rsp, %rbx
	leaq	36(%rsp), %r12
	leaq	.LC0(%rip), %rbp
	.p2align 4,,10
	.p2align 3
.L10:
	movsbl	(%rbx), %esi
	movq	%rbp, %rdi
	xorl	%eax, %eax
	addq	$1, %rbx
	call	printf@PLT
	cmpq	%r12, %rbx
	jne	.L10
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L15
	addq	$48, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L15:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE12:
	.size	main, .-main
	.ident	"GCC: (GNU) 10.2.0"
	.section	.note.GNU-stack,"",@progbits
