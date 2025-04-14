//atm_withdraw
//Yakina Azza
//11/18/2024
//Purpose: Assignment 6 for CS3377
//Synchronized using mutex variable

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long account_balance = 1000;

// Variable for  synchronization
pthread_mutex_t mutex;

void debit(long tid, long amount);
void dispense(long tid, long amount);
void receipt(long tid, long amount);
void *withdraw(void *threadid);

int main() {
    pthread_t threads[10];
    long thread_ids[10];
    int rc;

    // Mutex initialization 
    pthread_mutex_init(&mutex, NULL);

    // Thread creation 
    for (long i = 0; i < 10; i++) {
        thread_ids[i] = i;
        rc = pthread_create(&threads[i], NULL, withdraw, (void *)thread_ids[i]);
        if (rc) {
            printf("Error: unable to create thread %ld, return code: %d\n", i, rc);
            exit(-1);
        }
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}

void *withdraw(void *threadid) {
    long tid = (long)threadid;
    long amount = (tid + 1) * 10;

    // Protected Critical section
    pthread_mutex_lock(&mutex);
    debit(tid, amount);
    dispense(tid, amount);
    receipt(tid, amount);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

// Reduces debit balance
void debit(long tid, long amount) {
    account_balance -= amount;
    printf("In thread %ld: Debiting %ld dollars, balance after: %ld\n", tid, amount, account_balance);
}

void dispense(long tid, long amount) {
    printf("In thread %ld: dispensing %ld dollars from ATM\n", tid, amount);
}

// for receipt printing purposes
void receipt(long tid, long amount) {
    printf("In thread %ld: Receipt: Balance before: %ld, Amount withdrawn: %ld, Balance after: %ld\n", 
           tid, account_balance + amount, amount, account_balance);
}

