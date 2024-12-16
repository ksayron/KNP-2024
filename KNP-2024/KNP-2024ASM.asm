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
	main$LEX6 SDWORD 10 ;INT
	main$LEX7 BYTE "Random:", 0  ;STR
	main$LEX8 SDWORD 0 ;INT
	main$LEX10 SDWORD 1 ;INT
	main$LEX11 BYTE "element", 0  ;STR
	main$LEX16 SDWORD 4 ;INT
	main$LEX17 SDWORD 69 ;INT
	main$LEX18 SDWORD 50 ;INT
	main$LEX19 BYTE "Hello, World!", 0  ;STR
	main$LEX20 BYTE "Длина:", 0  ;STR
	main$LEX22 BYTE "Строки одинаковы", 0  ;STR
	main$LEX24 BYTE "Первая строка больше", 0  ;STR
	main$LEX25 SDWORD 2 ;INT
	main$LEX26 BYTE "Вторая строка больше", 0  ;STR
	main$LEX27 SDWORD 0 ;INT
.data
	sumresult SDWORD 0 ;INT
	mainnumber SDWORD 0 ;INT
	mainmassiv SDWORD  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ;ARR
	mainline DWORD 0 ;STR
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
push offset main$LEX7
pop mainline

push mainline
CALL outputstr

; expression #30 :ivl
push main$LEX8
pop maini

While144Start: 
mov eax, maini
mov ebx, main$LEX6
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

push offset main$LEX11
CALL outputstr

; expression #38 :i[l]vl
push main$LEX2
pop mainmassiv[1]

push mainmassiv[1]
CALL outputuint

; expression #41 :ivill@2!
invoke $sum, main$LEX2, main$LEX16
mov mainnumber, eax ;результат функции

push mainnumber
CALL outputuint

; expression #43 :ivl
push main$LEX17
pop mainnumber

push mainnumber
CALL outputuint

; expression #45 :ivil@1
invoke Random, main$LEX18
mov mainnumber, eax ;результат функции

push mainnumber
CALL outputuint

; expression #49 :ivl
push offset main$LEX19
pop maingreet

push maingreet
CALL outputstr

push offset main$LEX20
CALL outputstr

; expression #54 :ivii@1
invoke GetSize, maingreet
mov maincomp, eax ;результат функции

push maincomp
CALL outputuint

push maingreet
CALL outputstr

; expression #60 :ivii@1
invoke Copy, maingreet
mov maingreet2, eax ;результат функции

push maingreet2
CALL outputstr

; expression #64 :iviii@2!
invoke Compare, maingreet, maingreet2
mov maincomp, eax ;результат функции

If271Start: 
mov eax, maincomp
mov ebx, main$LEX8
cmp eax, ebx
jne If271End

push offset main$LEX22
CALL outputstr
If271End: 

If283Start: 
mov eax, maincomp
mov ebx, main$LEX10
cmp eax, ebx
jne If283End

push offset main$LEX24
CALL outputstr
If283End: 

If295Start: 
mov eax, maincomp
mov ebx, main$LEX25
cmp eax, ebx
jne If295End

push offset main$LEX26
CALL outputstr
If295End: 

mov eax, main$LEX27
	jmp endPoint
	div_by_0:
	push offset divideOnZeroExeption
CALL outputstr
endPoint:
	invoke		ExitProcess, eax
main ENDP
end main