.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ../Debug/KNP-2024LIB.lib
	ExitProcess PROTO :DWORD


	Random PROTO :SDWORD 
	Compare PROTO :DWORD, :DWORD
	GetSize PROTO :DWORD
	Copy PROTO :DWORD
	ctn PROTO :BYTE
	ntc PROTO :SDWORD 
outputuint PROTO :SDWORD
outputchar PROTO :BYTE
outputstr PROTO :DWORD

.stack 4096
.const
divideOnZeroExeption BYTE "Попытка деления на ноль.", 0  ;STR, для вывода ошибки при делении на ноль
	main$LEX1 SDWORD -11 ;INT
	main$LEX2 SDWORD 5 ;INT
	main$LEX3 BYTE "If works", 0  ;STR
	main$LEX5 BYTE "If doesn't work", 0  ;STR
	main$LEX6 BYTE "Random:", 0  ;STR
	main$LEX7 SDWORD 10 ;INT
	main$LEX8 SDWORD 0 ;INT
	main$LEX10 SDWORD 1 ;INT
	main$LEX12 SDWORD 4 ;INT
	main$LEX13 SDWORD 69 ;INT
	main$LEX14 SDWORD 50 ;INT
	main$LEX15 BYTE "Hello, World!", 0  ;STR
	main$LEX16 BYTE "Длина:", 0  ;STR
	main$LEX18 BYTE "Строки одинаковы", 0  ;STR
	main$LEX20 BYTE "Первая строка больше", 0  ;STR
	main$LEX21 SDWORD 2 ;INT
	main$LEX22 BYTE "Вторая строка больше", 0  ;STR
	main$LEX23 SDWORD 0 ;INT
.data
	sumresult SDWORD 0 ;INT
	mainnumber SDWORD 0 ;INT
	mainline DWORD 0 ;STR
	mainmassiv SDWORD  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ;ARR
	maini SDWORD 0 ;INT
	maingreet DWORD 0 ;STR
	maincomp SDWORD 0 ;INT
	maingreet2 DWORD 0 ;STR

.code
$sum PROC uses ebx ecx edi esi ,	sumfirst: SDWORD ,	sumsecond: SDWORD 
; expression #3 :iviiv
push sumfirst
push sumsecond
pop ebx
pop eax
add eax, ebx 
push eax
pop sumresult

mov eax, sumresult
ret
$sum ENDP

main PROC

; expression #17 :ivl
push main$LEX1
pop mainnumber

If94Start: 
mov eax, mainnumber
mov ebx, main$LEX2
cmp eax, ebx
je If94End

push offset main$LEX3
CALL outputstr
If94End: 

If106Start: 
mov eax, mainnumber
mov ebx, main$LEX2
cmp eax, ebx
jne If106End

push offset main$LEX5
CALL outputstr
If106End: 

; expression #26 :ivl
push offset main$LEX6
pop mainline

push mainline
CALL outputstr

; expression #30 :ivl
push main$LEX8
pop maini

While144Start: 
mov eax, maini
mov ebx, main$LEX7
cmp eax, ebx
je While144End

; expression #32 :i[i]vi
push maini
push maini
pop eax
pop mainmassiv[eax]
push maini
pop eax

push mainmassiv[eax]
CALL outputuint

; expression #34 :ivilv
push maini
push main$LEX10
pop ebx
pop eax
add eax, ebx 
push eax
pop maini
jmp While144Start
While144End: 

; expression #37 :ivill@2!
invoke $sum, main$LEX2, main$LEX12
mov mainnumber, eax ;результат функции

push mainnumber
CALL outputuint

; expression #39 :ivl
push main$LEX13
pop mainnumber

push mainnumber
CALL outputuint

; expression #41 :ivil@1
invoke Random, main$LEX14
mov mainnumber, eax ;результат функции

push mainnumber
CALL outputuint

; expression #45 :ivl
push offset main$LEX15
pop maingreet

push maingreet
CALL outputstr

push offset main$LEX16
CALL outputstr

; expression #50 :ivii@1
invoke GetSize, maingreet
mov maincomp, eax ;результат функции

push maincomp
CALL outputuint

push maingreet
CALL outputstr

; expression #56 :ivii@1
invoke Copy, maingreet
mov maingreet2, eax ;результат функции

push maingreet2
CALL outputstr

; expression #60 :iviii@2!
invoke Compare, maingreet, maingreet2
mov maincomp, eax ;результат функции

If255Start: 
mov eax, maincomp
mov ebx, main$LEX8
cmp eax, ebx
jne If255End

push offset main$LEX18
CALL outputstr
If255End: 

If267Start: 
mov eax, maincomp
mov ebx, main$LEX10
cmp eax, ebx
jne If267End

push offset main$LEX20
CALL outputstr
If267End: 

If279Start: 
mov eax, maincomp
mov ebx, main$LEX21
cmp eax, ebx
jne If279End

push offset main$LEX22
CALL outputstr
If279End: 

mov eax, main$LEX23
	jmp endPoint
	div_by_0:
	push offset divideOnZeroExeption
CALL outputstr
endPoint:
	invoke		ExitProcess, eax
main ENDP
end main