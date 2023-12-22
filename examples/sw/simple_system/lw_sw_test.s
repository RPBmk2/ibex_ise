.section .text
.globl _start

_start:
    # rf[x2] = 1
    addi x2, x0, 1
    
    # mem[2] = 1
    sw x2, 1(x0)
    
    # rf[x5] = 3
    addi x5, x0, 3
    
    # mem[6] = 3
    sw x5, 6(x0)
    
    # rf[x3] = 2
    addi x3, x0, 2
    
    lw_sw x4, 3(x2)
