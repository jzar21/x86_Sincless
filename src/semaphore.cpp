#include "semaphore.hpp"

Semaphore::Semaphore(unsigned char value) { this->value = value; }

Semaphore::~Semaphore() { this->value = 0; }

void Semaphore::acquire_semaphore() {
    this->mutex.lock();
    // wait
    while (this->value == 0) {
    }
    --this->value;
    this->mutex.unlock();
}

void Semaphore::release_semaphore() {
    if (this->value) {
        this->mutex.lock();
        ++this->value;
        this->mutex.unlock();
    } else {
        /*
         * If the value is 0 it means that there is a thread waiting
         * to acquire the Semaphore so it has the mutex, it we try to
         * lock the mutex it will produce a deadlock.
         */
        ++this->value;
    }
}

unsigned char Semaphore::get_semaphore_value() { return this->value; }
