//
// Created by Antonie Gabriel Belu on 02/06/2026.
//

#include "lib/fxsint.h"

extern "C" {
    __attribute__((noreturn)) void kernel_panic(const char* message) {
        uint16_t* const vga_memory = reinterpret_cast<uint16_t*>(0xb8000);

        const int kMaxRows = 25;
        const int kMaxColumns = 80;

        const uint16_t attribute = 0x4F00;

        for (int i = 0; i < kMaxColumns * kMaxRows; ++i) {
            vga_memory[i] = attribute | ' ';
        }

        const char* header = "!!! KERNEL PANIC !!!";
        int offset = (80 * 2) + 5;
        for (int i = 0; header[i] != '\0'; ++i) {
            vga_memory[offset++] = attribute | header[i];
        }

        const char* separator = "--------------------";
        offset = (80 * 3) + 5;
        for (int i = 0; separator[i] != '\0'; ++i) {
            vga_memory[offset++] = attribute | separator[i];
        }

        offset = (80 * 5) + 5;
        for (int i = 0; message[i] != '\0'; ++i) {
            vga_memory[offset++] = attribute | message[i];
        }

        while (true) {
            __asm__ __volatile__("cli; hlt");
        }
    }
}