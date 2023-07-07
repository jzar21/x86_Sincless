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

#ifndef x86_Sincless_Semaphore
#define x86_Sincless_Semaphore

#include "mutex.hpp"
#include <signal.h>
#include <pthread.h>
#include <queue>

/**
 * @brief A basic Semaphore that allows a define num of thread
 * to enter a section.
 *
 * This Semaphore **does not** guarantees any kind of order.
 */
class Semaphore {
private:
    unsigned char value;
    Mutex mutex;
    std::queue<pthread_t> thr_wait;
public:
    /**
     * @brief Construct a new Semaphore object.
     *
     * @param value The value of the Semaphore.
     */
    Semaphore(unsigned char value);

    /**
     * @brief Destroy the Semaphore object
     */
    ~Semaphore();

    /**
     * @brief Acquire the Semaphore.
     */
    void acquire_semaphore();

    /**
     * @brief Release the Semaphore.
     */
    void release_semaphore();

    /**
     * @brief Get the semaphore value.
     *
     * @return The Semaphore value.
     */
    unsigned char get_semaphore_value();
};

#endif /* x86_Sincless_Semaphore */