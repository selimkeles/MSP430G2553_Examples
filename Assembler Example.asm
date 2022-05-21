;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file
            
;-------------------------------------------------------------------------------
            .def    RESET                   ; Export program entry-point to
                                            ; make it known to linker.
;-------------------------------------------------------------------------------
            .text                           ; Assemble into program memory.
            .retain                         ; Override ELF conditional linking
                                            ; and retain current section.
            .retainrefs                     ; And retain any sections that have
                                            ; references to current section.

;-------------------------------------------------------------------------------
RESET       mov.w   #__STACK_END,SP         ; Initialize stackpointer
StopWDT     mov.w   #WDTPW|WDTHOLD,&WDTCTL  ; Stop watchdog timer


;-------------------------------------------------------------------------------
; Main loop here
;-------------------------------------------------------------------------------
				mov.w #0xffff,r6
				mov.w #0x000f,r7
loop1 			push r6
				dec r7
				jnz loop1
				mov.w #0x000f,r7
loop2 			pop r6
				dec r7
				jnz loop2
				mov.w #0x0004,r4
				mov.w #0x0005,r5
				mov.b #0xff06,r6
				call #subroutine1
				mov.w r4,&0x43f2
				jmp END
subroutine1 	push.w r4
				push.w r5
				push.b r6
				mov.w #0x4444,r4
				mov.w #0x5555,r5
				mov.w #0x6666,r6
				pop.b r6
				pop.w r4
				pop.w r5
				ret
                                            
END
;-------------------------------------------------------------------------------
; Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect   .stack
            
;-------------------------------------------------------------------------------
; Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  RESET
            


