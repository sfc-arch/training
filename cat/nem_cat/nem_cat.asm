section .data
	cant db "open error", 10
	length equ $- cant
	errnum equ 0xFFFFFFFE

	sys_open equ 2
	sys_write equ 1
	sys_read equ 0
	sys_close equ 3
	sys_lseek equ 8

	seek_start equ 0
	seek_end equ 2

section .bss
	msg resb 1

section .text
	global _start

_write:
	mov rax, sys_write
	mov rdi, 1 ;標準出力
	syscall
	ret

_start:
	pop rcx ;コマンドライン引数の数
	pop rbx ;./n_cat
	push rcx

argloop:
	pop rcx
	pop rbx ;コマンドライン引数
	dec rcx
	push rcx
	cmp rcx, 0
	je end

	;open
	mov rax, sys_open
	mov rdi, rbx
	xor rsi, rsi
	xor rdx, rdx
	syscall

	;これ以降rdiに変更なし
	push rax
	cmp rax, errnum
	je op_error

	;lseek
	mov rax, sys_lseek
	pop rdi
	xor rsi, rsi
	mov rdx, seek_end
	syscall

	push rax

	mov rax, sys_lseek
	xor rsi, rsi
	mov rdx, seek_start
	syscall
	
	;read
	mov rax, sys_read
	mov rsi, msg ;書き込み先
	pop rdx ;読み込む文字数
	syscall
	
	;write
	mov rsi, msg ;読み込み先
	call _write

	close:
	mov rax, sys_close
	xor rdi, rdi
	syscall
jmp argloop

op_error:
	mov rsi, cant
	mov rdx, length
	call _write

end:
	;exit
	mov rax, 60
	xor rdi, rdi
	syscall
