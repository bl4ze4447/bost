// TODO: Check the screen type

#include "video/vga_console.h"
#include "port/io.h"
#include "video/vga_types.h"

VGAConsole& VGAConsole::operator<<(char character) {
    PrintChar(character);
    return *this;
}

VGAConsole& VGAConsole::operator<<(const char* string) {
    for (; *string != '\0'; ++string) {
        PrintCharNoCursorUpdate(*string);
    }
    CursorUpdate();
    return *this;
}

VGAConsole& VGAConsole::operator<<(vga::Action action) {
    switch (action) {
        case vga::Action::kResetConsole: {
            VGAConsole tmp;
            *this = tmp;
            break;
        }

        case vga::Action::kClearConsole: {
            uint8_t row{0};
            uint16_t attribute{MakeAttribute(' ')};
            for (; row < kMaxRows; ++row) {
                for (uint8_t col = 0; col < kMaxColumns; ++col) {
                    kVgaMemory[(row * kMaxColumns) + col] = attribute;
                }
            }
            row_ = 0;
            col_ = 0;
            CursorUpdate();
            break;
        }
    }
    return *this;
}

VGAConsole& VGAConsole::operator<<(vga::Color color) {
    if (color < vga::Color::kBgBlack) {
        fg_ = color;
        return *this;
    }

    bg_ = color;
    return *this;
}

VGAConsole& VGAConsole::operator=(const VGAConsole& other) {
    row_ = other.row_;
    col_ = other.col_;
    bg_ = other.bg_;
    fg_ = other.fg_;
    return *this;
}

vga::Color VGAConsole::GetBackground() const {
    return bg_;
}

vga::Color VGAConsole::GetForeground() const {
    return fg_;
}

uint16_t VGAConsole::MakeAttribute(char character) const {
    return character |
           ((static_cast<uint8_t>(fg_) | (static_cast<uint8_t>(bg_) << 4)) << 8);
}

void VGAConsole::Scroll(uint8_t rows) {
    uint8_t row{0};
    for (; row < kMaxRows - rows; ++row) {
        memcpy(&kVgaMemory[row * kMaxColumns],
               &kVgaMemory[(row + rows) * kMaxColumns],
               kMaxColumns * sizeof(uint16_t));
    }

    uint16_t attribute{MakeAttribute(' ')};
    for (; row < kMaxRows; ++row) {
        for (uint8_t col = 0; col < kMaxColumns; ++col) {
            kVgaMemory[(row * kMaxColumns) + col] = attribute;
        }
    }

    row_ -= rows;
    CursorUpdate();
}

void VGAConsole::CursorUpdate() {
    uint16_t offset{static_cast<uint16_t>(row_ * kMaxColumns + col_)};
    uint8_t crtc_address{riob(kCrtcCtrlAddrReg)};

    wiob(kCrtcCtrlAddrReg, kCursorLocHigh);
    wiob(kCrtcCtrlDataReg, offset >> 8);
    wiob(kCrtcCtrlAddrReg, kCursorLocLow);
    wiob(kCrtcCtrlDataReg, offset);
    wiob(kCrtcCtrlAddrReg, crtc_address);
}

void VGAConsole::PrintUnsigned(uint64_t number) {
    if (number == 0) {
        PrintCharNoCursorUpdate('0');
        return;
    }

    char buffer[21];
    int i = 20;
    buffer[i] = '\0';

    while (number > 0) {
        buffer[--i] = '0' + (number % 10);
        number /= 10;
    }

    for (int j = i; buffer[j] != '\0'; ++j) {
        PrintCharNoCursorUpdate(buffer[j]);
    }
}

void VGAConsole::PrintSigned(int64_t number) {
    if (number < 0) {
        PrintCharNoCursorUpdate('-');
        if (number == -9223372036854775807LL - 1LL) {
            PrintUnsigned(9223372036854775808ULL);
            return;
        }
        PrintUnsigned(static_cast<uint64_t>(-number));
    } else {
        PrintUnsigned(static_cast<uint64_t>(number));
    }
}

void VGAConsole::PrintCharNoCursorUpdate(char character) {
    bool new_line = (character == '\n' || character == 13);

    if (new_line || col_ >= kMaxColumns) {
        ++row_;
        col_ = 0;

        if (row_ >= kMaxRows) {
            Scroll(row_ - kMaxRows + 1);
        }

        if (new_line) {
            return;
        }
    }

    kVgaMemory[(row_ * kMaxColumns) + col_] = MakeAttribute(character);
    ++col_;
}

void VGAConsole::PrintChar(char character) {
    PrintCharNoCursorUpdate(character);
    CursorUpdate();
}