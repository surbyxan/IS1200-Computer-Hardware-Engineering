  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #

.global hexasc
hexasc:
	andi $t1,$a0,0xf
	ble $t1,9,number
	
	addi $v0,$a0,0x37
	jr $ra
	nop 
number:
	addi $v0,$a0, 0x30
	jr $ra
	nop

.global delay
delay:
	li $t0, 0 #int i
	li $t1, 4711 #konstanten
	nop
	
while:
	blez $a0, exitloop
	nop
	sub $a0, $a0, 1
	li $t0, 0

for:
	ble $t1, $t0, while
	nop
	addi $t0, $t0, 1
	j for
	nop 
	

exitloop:	
	jr $ra
	nop

.global time2string
time2string:
	PUSH    $ra
	PUSH    $s0
	PUSH    $s1
	move    $s1, $a1
	move    $s0, $a0
	#1 digit
	andi $t1,$s1,0xF000
	srl $a0,$t1,12
	jal hexasc
	nop
	sb $v0, ($s0)
	# 2 digit
	andi $t1,$s1,0x0F00
	srl $a0,$t1,8
	jal hexasc
	nop
	sb $v0, 1($s0)
	# colon
	li $t1,0x3A
	nop
	sb $t1, 2($s0)
	# 3 digit
	andi $t1,$s1,0x00F0
	srl $a0,$t1,4
	jal hexasc
	nop
	sb $v0, 3($s0)
	# 4 digit
	andi $t1,$s1,0x000F
	move $a0, $t1
	jal hexasc
	nop
	sb $v0, 4($s0)
	#null
	li $t1,0x00
	nop
	sb $t1, 5($s0)
	 
	POP    $s1
	POP    $s0
	POP    $ra
	jr    $ra
   	nop

.global enable_interrupt
enable_interrupt:
	ei
	jr $ra 