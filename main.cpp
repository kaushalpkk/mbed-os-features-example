/*
program to demonstrate Thread and Mutex on the DISCO-L4S5I
Mbed OS 6.15.1. 
*/

#include "mbed.h"

DigitalOut led1(LED1);
Thread t1;
Thread t2;
Thread t3;
Mutex m1;

int randon_array[5];


// thread populates random numbers to an array
void populate_aray(){
    while(1){
        printf(".");
        m1.lock();
        for(int i=0;i<5; i++){
            randon_array[i] = rand() % 10;
            printf("%d-",randon_array[i]);

        }
        printf("\r\n");
        m1.unlock();
    }
}

// thread calculates total of the numbers in the array
void calculate_total(){
    while(1){
        m1.lock();
        int total = 0;
        printf("[ ");
        for(int i=0;i<5; i++){
            printf("%d, ", randon_array[i]);
            total += randon_array[i];
        }
        printf("] \r\ntotal is %d \r\n", total);
        ThisThread::sleep_for(1s);
        m1.unlock();
    }
}


// independent thread no mutex implementation
void blink_led(){
    while(1){
        led1 =! led1;
        ThisThread::sleep_for(1s);
    }
}

int main()
{
    printf("This is the bare metal blinky example running on Mbed OS %d.%d.%d. \r\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    t1.start(calculate_total);
    t2.start(populate_aray);
    t3.start(blink_led);

    while (true)
    {
        ThisThread::sleep_for(5s);
    }
}
