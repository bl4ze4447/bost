/*
    Codename-TGV-Kernel
    Author: bl4ze4447
 */

#define RELEASE_DATE    "02/06/2026"
#define CNB_MAJOR       0
#define CNB_MINOR       0
#define CNB_BUILD       9

#include "video/vga_console.h"

extern "C" void kmain() {
    VGAConsole kout;

    kout << vga::Action::kClearConsole 
    << vga::Color::kBgCyan 
    << "* Succesfully running bost-kernel\n"
    << vga::Color::kBgBlack
    << "> Version: " << CNB_MAJOR << '.' << CNB_MINOR << '.' << CNB_BUILD << '\n'
    << "> Release date: " << RELEASE_DATE << '\n'
    << "> For more info see: "
    << vga::Color::kBgBrown
    << "https://github.com/bl4ze4447/bost\n\n"
    << vga::Color::kBgBlack
    << "[No user] > "; 
}