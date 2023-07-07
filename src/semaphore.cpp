#include "semaphore.hpp"
#include <iostream>

Semaphore::Semaphore(unsigned char value) { this->value = value; }

Semaphore::~Semaphore() { this->value = 0; }

/**
 * @brief This is only used to allow to handle signals to wakeu up
 * the threads waiting the Semaphore.
 *
 * @param sig Signal to handle.
 */
static void sleep_thread(int sig) {}

void Semaphore::acquire_semaphore() {
    struct sigaction sa;
    sa.sa_handler = sleep_thread;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

    this->mutex.lock();
    // wait
    if (this->value == 0) {
        this->thr_wait.push(pthread_self());
        this->mutex.unlock();
        pause();
        this->mutex.lock();
    }
    --this->value;
    this->mutex.unlock();
}

void Semaphore::release_semaphore() {
    this->mutex.lock();
    ++this->value;
    int sig = SIGUSR1;

    if (this->thr_wait.size()) {
        pthread_kill(this->thr_wait.front(), sig);
        this->thr_wait.pop();
    }
    this->mutex.unlock();
}

unsigned char Semaphore::get_semaphore_value() { return this->value; }
