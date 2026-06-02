[bits 32]
global kernel_entry

kernel_entry:
    [extern kmain]
    call kmain
jmp $