#include "semaphore.hpp"
#include <iostream>

Semaphore::Semaphore(unsigned char value) {
    this->value = value;
    pthread_mutex_init(&this->mutex, nullptr);
}

Semaphore::~Semaphore() {
    this->value = 0;
    pthread_mutex_destroy(&mutex);
}

void Semaphore::acquire_semaphore() {
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

    pthread_mutex_lock(&mutex);
    // wait
    if (this->value == 0) {
        this->thr_wait.push(&cond);

        pthread_cond_wait(&cond, &this->mutex);
    }
    --this->value;
    pthread_mutex_unlock(&mutex);
    pthread_cond_destroy(&cond);
}

void Semaphore::release_semaphore() {
    pthread_mutex_lock(&mutex);

    ++this->value;
    if (this->thr_wait.size()) {
        pthread_cond_signal(this->thr_wait.front());
        this->thr_wait.pop();
    }
    pthread_mutex_unlock(&mutex);
}

unsigned char Semaphore::get_semaphore_value() { return this->value; }
