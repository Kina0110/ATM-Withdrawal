#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Initial balance of the bank account
long account_balance = 1000;

// Function declarations
void debit(long tid, long amount);
void dispense(long tid, long amount);
void receipt(long tid, long amount);
void *withdraw(void *threadid);

int main() {
    pthread_t threads[10];
    long thread_ids[10];
    int rc;

    // Create 10 threads for withdrawing
    for (long i = 0; i < 10; i++) {
        thread_ids[i] = i;
        rc = pthread_create(&threads[i], NULL, withdraw, (void *)thread_ids[i]);
        if (rc) {
            printf("Error: unable to create thread %ld, return code: %d\n", i, rc);
            exit(-1);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

// Withdraw function (unsynchronized version)
void *withdraw(void *threadid) {
    long tid = (long)threadid;
    long amount = (tid + 1) * 10;

    // No protection here: different threads can run this code at the same time.
    // This can cause issues when they try to change account balance together.
    debit(tid, amount);      // Changes account balance and can be unsafe if multiple threads do it at once
    dispense(tid, amount);   // Just prints may overlap with other threads prints
    receipt(tid, amount);    // Reads account balance, which could change while it runs

    pthread_exit(NULL);
}

// Debit function subtracts money from the account balance
void debit(long tid, long amount) {
    // Multiple threads might change account balance  at the same time, causing wrong results
    account_balance -= amount;
    printf("In thread %ld: Debiting %ld dollars, balance after: %ld\n", tid, amount, account_balance);
}

// Dispense function simulates giving cash (no change to shared data)
void dispense(long tid, long amount) {
    // Prints may mix with prints from other threads if they run at the same time
    printf("In thread %ld: dispensing %ld dollars from ATM\n", tid, amount);
}

// Receipt function  prints a summary of the withdrawal (reads shared data)
void receipt(long tid, long amount) {
    // If another thread changes account balance while this runs, the "before" and "after" values may not match
    printf("In thread %ld: Receipt: Balance before: %ld, Amount withdrawn: %ld, Balance after: %ld\n", 
           tid, account_balance + amount, amount, account_balance);
}

