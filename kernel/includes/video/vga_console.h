#ifndef VIDEO_VGA_CONSOLE_H_
#define VIDEO_VGA_CONSOLE_H_

#include "lib/fxsint.h"
#include "lib/memory.h"
#include "video/vga_types.h"

// ugly hack
namespace vga {
    template <typename T>
    struct is_integral { static constexpr bool value = false; };

    template <> struct is_integral<char> { static constexpr bool value = true; };
    template <> struct is_integral<signed char> { static constexpr bool value = true; };
    template <> struct is_integral<unsigned char> { static constexpr bool value = true; };
    template <> struct is_integral<short> { static constexpr bool value = true; };
    template <> struct is_integral<unsigned short> { static constexpr bool value = true; };
    template <> struct is_integral<int> { static constexpr bool value = true; };
    template <> struct is_integral<unsigned int> { static constexpr bool value = true; };
    template <> struct is_integral<long> { static constexpr bool value = true; };
    template <> struct is_integral<unsigned long> { static constexpr bool value = true; };
    template <> struct is_integral<long long> { static constexpr bool value = true; };
    template <> struct is_integral<unsigned long long> { static constexpr bool value = true; };

    template <typename T>
    concept integral = is_integral<T>::value;

    template <typename T>
    inline constexpr bool is_signed_v = (T(-1) < T(0));
} // namespace vga

class VGAConsole {
public:
    /* Print text to screen */
    VGAConsole& operator<<(char character);
    VGAConsole& operator<<(const char* string);

    /* Print numbers to screen */
    template <vga::integral T>
    VGAConsole& operator<<(T number);

    /* Special actions */
    VGAConsole& operator<<(vga::Action action);
    VGAConsole& operator<<(vga::Color color);

    VGAConsole& operator=(const VGAConsole& other);

    /* Getters */
    vga::Color GetBackground() const;
    vga::Color GetForeground() const;
    uint16_t MakeAttribute(char character) const;

    void Scroll(uint8_t rows);
    void CursorUpdate();

private:
    uint8_t row_{0};
    uint8_t col_{0};
    vga::Color bg_{vga::Color::kBgBlack};
    vga::Color fg_{vga::Color::kWhite};

    uint16_t* const kVgaMemory{reinterpret_cast<uint16_t*>(0xb8000)};
    const uint8_t kMaxRows{25};
    const uint8_t kMaxColumns{80};
    const uint16_t kCrtcCtrlAddrReg{0x3D4};
    const uint16_t kCrtcCtrlDataReg{0x3D5};
    const uint8_t kCursorLocLow{0xF};
    const uint8_t kCursorLocHigh{0xE};

    /* Helpers for printing signed/unsigned numbers */
    void PrintSigned(int64_t number);
    void PrintUnsigned(uint64_t number);

    /* Main functions used for actually printing */
    void PrintCharNoCursorUpdate(char character);
    void PrintChar(char character);
} __attribute__((packed));

template <vga::integral T>
inline VGAConsole& VGAConsole::operator<<(T number) {
    if constexpr (vga::is_signed_v<T>) {
        PrintSigned(static_cast<int64_t>(number));
    } else {
        PrintUnsigned(static_cast<uint64_t>(number));
    }
    return *this;
}

#endif  // VIDEO_VGA_CONSOLE_H_