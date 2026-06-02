//
// Created by Antonie Gabriel Belu on 02/06/2026.
//

extern "C" {
    // 64bits division
    unsigned long long __udivmoddi4(unsigned long long num, unsigned long long den, unsigned long long* rem) {
        if (den == 0) {
            if (rem) *rem = 0;
            return 0;
        }

        unsigned long long quot = 0;
        unsigned long long qbit = 1;

        while ((den < num) && ((den & (1ULL << 63)) == 0)) {
            den <<= 1;
            qbit <<= 1;
        }

        while (qbit > 0) {
            if (num >= den) {
                num -= den;
                quot |= qbit;
            }
            den >>= 1;
            qbit >>= 1;
        }

        if (rem) {
            *rem = num;
        }

        return quot;
    }
    unsigned long long __udivdi3(unsigned long long num, unsigned long long den) {
        return __udivmoddi4(num, den, nullptr);
    }
    unsigned long long __umoddi3(unsigned long long num, unsigned long long den) {
        unsigned long long rem = 0;
        __udivmoddi4(num, den, &rem);
        return rem;
    }

    __attribute__((noreturn)) void kernel_panic(const char* message);
    unsigned int __stack_chk_guard = 0xDEADC0DE;
    __attribute__((noreturn)) void __stack_chk_fail(void) {
        void kernel_panic(const char* message);
        kernel_panic("STACK SMASHING DETECTED");
    }
}