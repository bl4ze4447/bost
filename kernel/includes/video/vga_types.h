#ifndef VGATYPES_H
#define VGATYPES_H

#include "lib/fxsint.h"

namespace vga {
    enum class Color {
        kBlack = 0,
        kBlue,
        kGreen,
        kCyan,
        kRed,
        kMagenta,
        kBrown,
        kLightGray,
        kDarkGray,
        kLightBlue,
        kLightGreen,
        kLightCyan,
        kLightRed,
        kLightMagenta,
        kYellow,
        kWhite,
        kBgBlack,
        kBgBlue,
        kBgGreen,
        kBgCyan,
        kBgRed,
        kBgMagenta,
        kBgBrown,
        kBgLightGray,
        kBgDarkGray,
        kBgLightBlue,
        kBgLightGreen,
        kBgLightCyan,
        kBgLightRed,
        kBgLightMagenta,
        kBgYellow,
        kBgWhite,
    };
    enum class Action {
        kClearConsole,
        kResetConsole
    };
} // namespace vga

#endif
