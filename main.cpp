#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include "SensorConfiguration.h"
#include "SensorCommunication.h"
#include "SensorTag.h"

#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

// maximilian.repp@hotmail.de


using namespace std;

int loops = 1000;


pthread_attr_t* create_p_attr(){

    pthread_attr_t* tattr = new pthread_attr_t();
    sched_param param;
    int ret;
    ret = pthread_attr_init(tattr);
    ret = pthread_attr_getschedparam(tattr, &param);
    ret = pthread_attr_setschedpolicy(tattr, SCHED_RR);
    param.sched_priority=20;
    ret = pthread_attr_setschedparam(tattr, &param);

    return tattr;
}


// the function being executed as thread 2
void* main_thread2(void* parameterPtr) {
    // explicit cast of parameterPtr into a pointer to int
    int *xPtr = (int *) parameterPtr;
    // increment x up to 10
    while ( ++(*xPtr) < 10 ) {
        cout << "(x=" << *xPtr << ")" << flush;
        sleep(1); // wait a second
    }
    cout << endl << "reached end of incrementing x" << endl;
    // return NULL as function demands for a return value
    return NULL;
}

void* thread1(void* motion_t) {
    Motion_t *motion = (Motion_t *) motion_t;

    int i = 0;
    while (i < loops){
        i++;

        motion->acc.x = 0;
        motion->acc.y = 0;
        motion->acc.z = 0;
        motion->gyro.x = 0;
        motion->gyro.y = 0;
        motion->gyro.z = 0;

        cout << "acc:  x: "  << motion->acc.x << " | y: " << motion->acc.y << " | z: " << motion->acc.z  << endl << flush;
        cout << "gyro:  x: "  << motion->gyro.x << " | y: " << motion->gyro.y << " | z: " << motion->gyro.z  << endl << flush;

    }

}

void* thread2(void* motion_t) {
    // explicit cast of parameterPtr into a pointer to int
    Motion_t *motion = (Motion_t *) motion_t;
    // increment x up to 10

    CSensorTag tag;

    int i = 0;
    while (i < loops){
        struct timeval start, end;
        i++;


        CSensorConfiguration configuration;
        CSensorCommunication communication;

        Motion_t m = communication.getMotion(configuration);

        motion->acc.x = m.acc.x;
        motion->acc.y = m.acc.y;
        motion->acc.z = m.acc.z;

        motion->gyro.x = m.gyro.x;
        motion->gyro.y = m.gyro.y;
        motion->gyro.z= m.gyro.z;

        cout << "acc:  x: "  << motion->acc.x << " | y: " << motion->acc.y << " | z: " << motion->acc.z  << endl << flush;
        cout << "gyro:  x: "  << motion->gyro.x << " | y: " << motion->gyro.y << " | z: " << motion->gyro.z  << endl << flush;


    }


    // return NULL as function demands for a return value
    return NULL;
}

int main() {

    char* testdaten = new char[12];

    testdaten[0]= 0x0d;
    testdaten[1]= 0x01;
    testdaten[2]=  0x6c;
    testdaten[3]=  0xfc;
    testdaten[4]= 0xd9;
    testdaten[5]=  0xfc;
    testdaten[6]=  0xf4;
    testdaten[7]=  0xfd;
    testdaten[8]=  0x85;
    testdaten[9]=  0x00;
    testdaten[10]=  0xd2;
    testdaten[11]=  0x0f;

    CSensorConfiguration configuration;
    CSensorCommunication communication;


    Motion_t motion = communication.getMotion(configuration);



    pthread_t thread1_id;
    if(pthread_create(&thread1_id, create_p_attr(), thread1, &motion)) {
        cerr << "Error: thread 1 not created" << endl;
        return 1;
    }

    pthread_t thread2_id;
    if(pthread_create(&thread2_id, create_p_attr(), thread2, &motion)) {
        cerr << "Error: thread 2 not created" << endl;
        return 1;
    }




    if (pthread_join(thread2_id, NULL) && pthread_join(thread1_id, NULL)) {
        cerr << "Error: thread not joined" << endl;
        return 2;
    }
    return 0;
}




// main runs thread 1
int main_old() {
    // variables we modify in two threads
    int x = 0, y = 0;
    // show the initial values of x and y
    cout << "start count x=" << x << ", y=" << y << endl;
    // thread ID for second thread
    pthread_t thread2_id;
    // create second thread executing function thread2_main */
    if(pthread_create(&thread2_id, NULL, main_thread2, &x)) {
        cerr << "Error: thread not created" << endl;
        return 1;
    }
    // sleep 2 seconds, then start incrementing y up to 5
    sleep(2);
    while ( ++y < 5 ) {
        cout << "(y=" << y << ")" << flush;
        sleep(1); // wait a second
    }
    cout << endl << "reached end of incrementing y" << endl;
    /* wait for the second thread to finish */
    if ( pthread_join(thread2_id, NULL) ) {
        cerr << "Error: thread not joined" << endl;
        return 2;
    }
    /* show the results - x is now 10, thanks to the second thread */
    cout << endl << "end count x=" << x << ", y=" << y << endl;
    return 0;
}

int main2(){
    char* testdaten = new char[12];

    testdaten[0]= 0x0d;
    testdaten[1]= 0x01;
    testdaten[2]=  0x6c;
    testdaten[3]=  0xfc;
    testdaten[4]= 0xd9;
    testdaten[5]=  0xfc;
    testdaten[6]=  0xf4;
    testdaten[7]=  0xfd;
    testdaten[8]=  0x85;
    testdaten[9]=  0x00;
    testdaten[10]=  0xd2;
    testdaten[11]=  0x0f;

    CSensorConfiguration test;
    CSensorCommunication mysens;
    mysens.convertMotion(testdaten);

    CSensorTag tag;



/*std::cout << sizeof(CSensorConfiguration) << std::endl;
std::cout << "test " << sizeof(int16_t) << std::endl;
*/

    return 0;
}