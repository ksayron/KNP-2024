.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ../Debug/TDS-2022LIB.lib
	ExitProcess PROTO :DWORD


outputuint PROTO :DWORD
outputchar PROTO :BYTE
outputstr PROTO :DWORD

.stack 4096
.const
divideOnZeroExeption BYTE "������� ������� �� ����.", 0  ;STR, ��� ������ ������ ��� ������� �� ����
	counter$LEX1 DWORD 0 ;INT
	counter$LEX2 DWORD 1 ;INT
	main$LEX3 DWORD 11 ;INT
	main$LEX4 DWORD 5 ;INT
	main$LEX5 BYTE "If works", 0  ;STR
	main$LEX7 BYTE 'q' ;CHR
	main$LEX8 BYTE "Symbol", 0  ;STR
	main$LEX9 BYTE "is new", 0  ;STR
	main$LEX10 BYTE "Hello, World!", 0  ;STR
	main$LEX11 DWORD 0 ;INT
.data
	mainnumber DWORD 0 ;INT
	mainsymbol BYTE 0 ;CHR
	mainline DWORD 0 ;STR

.code
$counter PROC uses ebx ecx edi esi ,	countercount: DWORD 
While9Start: 
mov eax, countercount
mov ebx, counter$LEX1
cmp eax, ebx
jl While9End

push countercount
CALL outputuint

; String #4 :ivilv
push countercount
push counter$LEX2
pop ebx
pop eax
sub eax, ebx
push eax
pop countercount
jmp While9Start
While9End: 

mov eax, countercount
ret
$counter ENDP

main PROC

; String #13 :ivl
push main$LEX3
pop mainnumber

push mainnumber
CALL outputuint

If45Start: 
mov eax, mainnumber
mov ebx, main$LEX4
cmp eax, ebx
jl If45End

push mainnumber
CALL outputuint

push offset main$LEX5
CALL outputstr
If45End: 

; String #19 :ivil@1
invoke $counter, main$LEX4
push eax ;��������� �������
pop mainnumber

; String #21 :ivl
movzx eax, main$LEX7
push eax 
pop eax
mov mainsymbol, al

push offset main$LEX8
CALL outputstr
push eax
movzx eax, mainsymbol
push eax
CALL outputchar
pop eax


push offset main$LEX9
CALL outputstr

; String #28 :ivl
push offset main$LEX10
pop mainline

push mainline
CALL outputstr

mov eax, main$LEX11
	jmp endPoint
	div_by_0:
	push offset divideOnZeroExeption
CALL outputstr
endPoint:
	invoke		ExitProcess, eax
main ENDP
end main