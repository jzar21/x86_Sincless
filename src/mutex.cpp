/*
 * MIT License
 *
 * Copyright (c) 2023 Juan Francisco Montilla
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "mutex.hpp"

Mutex::Mutex() { this->value = OPEN_VALUE; }

Mutex::~Mutex() { this->value = OPEN_VALUE; }

void Mutex::lock() {
    // Busy wait

    // clang-format off
    asm volatile(
        "loop: \n\t"
            "mov $1, %%cl \n\t"
            "lock xchg %%cl, %0 \n\t"
            "test %%cl, %%cl \n\t"
            "jne loop\n\t"
        : "=m"(this->value) /* output */
        :                   /* input */
        : "%cl"             /* clobbered */
    );
    // clang-format on
}

void Mutex::unlock() { this->value = OPEN_VALUE; }

unsigned char Mutex::mutex_value() const { return this->value; }
