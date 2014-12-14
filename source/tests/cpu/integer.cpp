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
    unsigned int badflags = 0;

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

    // ADDS
    badflags = 0;
    rm = std::numeric_limits<unsigned int>::max() - 1;
    rn = 1;
    asm volatile ("ADDS  %[Rm], %[Rm], %[Rn]\n"
                  "ORRCS %[out], %[out], #1\n"
                  "ORRPL %[out], %[out], #2\n"
                  "ORRVS %[out], %[out], #4\n"
                  "ORREQ %[out], %[out], #8\n"
                  "ADDS  %[Rm], %[Rm], %[Rn]\n"
                  "ORRCC %[out], %[out], #1\n"
                  "ORRMI %[out], %[out], #2\n"
                  "ORRVS %[out], %[out], #4\n"
                  "ORRNE %[out], %[out], #8" : [out] "+r"(badflags), [Rm] "+r"(rm) : [Rn] "r"(rn));
    if (badflags != 0)
        return false; 

    // TODO: ADC, ADCS, ADDW variants.

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

// UQSUB8
static bool Uqsub8() {
    unsigned int output;
    unsigned int rm = 70;
    unsigned int rn = 50;

    // Regular subtraction
    asm volatile ("UQSUB8 %[out], %[Rm], %[Rn]" : [out] "=r"(output) : [Rm] "r"(rm), [Rn] "r"(rn));
    SoftAssert(output == 20);

    // Floor subtraction (50 - 70) == 0 with UQSUB8 (or any of the other UQSUB variants).
    rm = 50;
    rn = 70;
    asm volatile ("UQSUB8 %[out], %[Rm], %[Rn]" : [out] "=r"(output) : [Rm] "r"(rm), [Rn] "r"(rn));
    SoftAssert(output == 0);

    return true;
}

void TestAll() {
    const std::string tag = "Integer";

    Test(tag, "ADD", Add(), true);
    Test(tag, "SUB", Sub(), true);
    Test(tag, "MUL", Mul(), true);
    Test(tag, "SASX", Sasx(), true);
    Test(tag, "SSAX", Ssax(), true);
    Test(tag, "UQSUB8", Uqsub8(), true);
}

}
}
