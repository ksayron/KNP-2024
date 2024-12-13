.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ../Debug/KNP-2024LIB.lib
	ExitProcess PROTO :DWORD


outputuint PROTO :DWORD
outputchar PROTO :BYTE
outputstr PROTO :DWORD

.stack 4096
.const
divideOnZeroExeption BYTE "Попытка деления на ноль.", 0  ;STR, для вывода ошибки при делении на ноль
	main$LEX1 SDWORD 4294967285 ;INT
	main$LEX2 SDWORD 0 ;INT
.data
	mainnumber SDWORD 0 ;INT

.code
main PROC

; expression #5 :ivl
push main$LEX1
pop mainnumber

push mainnumber
CALL outputuint

mov eax, main$LEX2
	jmp endPoint
	div_by_0:
	push offset divideOnZeroExeption
CALL outputstr
endPoint:
	invoke		ExitProcess, eax
main ENDP
end main