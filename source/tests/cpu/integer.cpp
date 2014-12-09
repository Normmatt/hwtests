#include <limits>
#include <string>
#include "output.h"
#include "tests/test.h"

namespace CPU {
namespace Integer {

// ADD variants
static bool Add() {
    unsigned int output = 0;
    unsigned int rm = 0;
    unsigned int rn = 0;

    // Generic addition
    asm volatile ("LDR r0, =420\n"
                  "LDR r1, =69\n"
                  "ADD %[out], r0, r1" : [out] "=r"(output));
    if (output != 489)
        return false;

    // ADD overflow (unsigned)
    rm = std::numeric_limits<unsigned int>::max();
    rn = 1;
    asm volatile ("ADD %[out], %[Rm], %[Rn]" : [out] "=r"(output) : [Rm] "r"(rm), [Rn] "r"(rn));
    if (output != 0)
        return false;

    // TODO: ADC, ADCS, ADDW, and ADDS variants.

    return true;
}

// SUB variants
static bool Sub() {
    unsigned int output;

    // Generic subtraction.
    asm volatile ("LDR r0, =489\n"
                  "SUB %[out], r0, #69" : [out] "=r"(output));
    if (output != 420)
        return false;

    // Subtract overflow (0 - 1).
    asm volatile ("MOV r0, #0\n"
                  "SUB %[out], r0, #1" : [out] "=r"(output));
    if (output != std::numeric_limits<unsigned int>::max())
        return false;

    // TODO: SUBS, etc.

    return true;
}

// MUL variants
static bool Mul() {
    unsigned int output;

    // Multiply by loaded registers.
    asm volatile ("MOV r0, #20\n"
                  "MOV r1, #21\n"
                  "MUL %[out], r0, r1" : [out] "=r"(output));
    if (output != 420)
        return false;

    // TODO: Other MUL variants.

    return true;
}

// SASX
static bool Sasx() {
    unsigned int output;
    unsigned int rm = std::numeric_limits<unsigned int>::max();
    unsigned int rn = rm - 4000;

    asm volatile ("SASX %[out], %[Rm], %[Rn]" : [out] "=r"(output) : [Rm] "r"(rm), [Rn] "r"(rn));

    return (output == 4032692224);
}

// SSAX
static bool Ssax() {
    unsigned int output;
    unsigned int rm = std::numeric_limits<unsigned int>::max();
    unsigned int rn = rm - 4000;

    asm volatile ("SSAX %[out], %[Rm], %[Rn]" : [out] "=r"(output) : [Rm] "r"(rm), [Rn] "r"(rn));

    return (output == 262209534);
}

void TestAll() {
    const std::string tag = "Integer";

    Test(tag, "ADD", &Add);
    Test(tag, "SUB", &Sub);
    Test(tag, "MUL", &Mul);
    Test(tag, "SASX", &Sasx);
    Test(tag, "SSAX", &Ssax);
}

}
}
