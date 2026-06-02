# bost, a minimal operating system ![C](https://img.shields.io/badge/Language-CPP-blue) ![NASM](https://img.shields.io/badge/Assembler-NASM-blue) 

bost, x86 Operating System, built upon:
* bost-boot - Fast and ligtweight bootloader, built in Assembly. The bootloader prepares the hardware and switches to the kernel in under 1024 bytes. For reference, an 1920x1080 png picture uses 2MB. The entire bootloader is smaller than the picture by ~1950 times.
* bost-kernel - Minimal, with focus on code readability and scalability.

![Preview](https://github.com/user-attachments/assets/76e4205c-0d23-4fac-a7d8-2e6a80c71ef5)


## Build and usage
```make run``` will build the image and run it using qemu-system-i386.
## Dependencies
* gcc i386 cross-compiler
* nasm compiler
* linker

## Upcoming
- Keyboard driver

## Resources I am currently using or used
* [Intel® 64 and IA-32 Architectures Software Developer Manuals](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
* [OSDev Wiki](https://wiki.osdev.org/)
* [x86 Instruction Set](https://www.felixcloutier.com/x86/)
* [osdever](http://www.osdever.net/FreeVGA/vga/portidx.htm)
* [ctyme/intr/](https://www.ctyme.com/intr/) ; rb-1338,1337,1336

## bost-boot error format
Errors will be printed on the screen with the following format: ```bER{error number}``` 
(example: ```bER20```)
| Error Number   | Description |
| :----------:   | :---------- |
| 1              | Sector load func failed/did not read all sectors |
| 20             | Could not open A20 Line |

## License
This repository is licensed under the ```MIT License```.
