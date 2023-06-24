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

#ifndef x86_Sincless_Mutex
#define x86_Sincless_Mutex

#define OPEN_VALUE 0
#define CLOSE_VALUE 1

/**
 * @brief Basic mutex.
 */
class Mutex {
private:
    volatile unsigned char value;
public:
    /**
     * @brief Construct a new Mutex object.
     */
    Mutex();

    /**
     * @brief Destroy the Mutex object opening the mutex value.
     */
    ~Mutex();

    /**
     * @brief Lock the mutex making that only one thread can
     * execute at the same time the section between lock and unlock.
     */
    void lock();

    /**
     * @brief Unlock the mutex.
     */
    void unlock();

private:
    /**
     * @brief Make an atomic write of 1 to the mutex value.
     *
     * @return Previous mutex value.
     */
    int test_and_set();
};

#endif /* x86_Sincless_Mutex */