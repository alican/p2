#include "SensorCommunication.h"
#include "SensorTag.h"
#include <iostream>
#include <memory>

#define ACC_RANGE_2G      0
#define ACC_RANGE_4G      1
#define ACC_RANGE_8G      2
#define ACC_RANGE_16G     3


float sensorMpu9250GyroConvert(int16_t data)
{
  //-- calculate rotation, unit deg/s, range -250, +250
  return (data * 1.0) / (65536 / 500);
}

float sensorMpu9250AccConvert(int16_t rawData)
{
  float v;
int accRange = 0;
  switch (accRange)
  {
  case ACC_RANGE_2G:
    //-- calculate acceleration, unit G, range -2, +2
    v = (rawData * 1.0) / (32768/2);
    break;

  case ACC_RANGE_4G:
    //-- calculate acceleration, unit G, range -4, +4
    v = (rawData * 1.0) / (32768/4);
    break;

  case ACC_RANGE_8G:
    //-- calculate acceleration, unit G, range -8, +8
    v = (rawData * 1.0) / (32768/8);
    break;

  case ACC_RANGE_16G:
    //-- calculate acceleration, unit G, range -16, +16
    v = (rawData * 1.0) / (32768/16);
    break;
  }

  return v;
}


int CSensorCommunication::readMotion(CSensorConfiguration config, char* buffer){



}

Motion_t CSensorCommunication::getMotion(CSensorConfiguration conf)
{

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

    readMotion(conf, testdaten);


    /*
        Reads the motion sensor from the SensorTag specified by the given SensorTag
        confoguration, converts the raw data and returns it as Motion_t.
        @param[in] conf Configuration of the SensorTag
        @return Motion values
    */

    Motion_t motion;


    return convertMotion(testdaten);
}

Motion_t CSensorCommunication::convertMotion(char* rawData)
{
    Motion_t mt;
    int16_t* data = (int16_t*)rawData;

    mt.gyro.x = sensorMpu9250GyroConvert(data[0]);
    mt.gyro.y = sensorMpu9250GyroConvert(data[1]);
    mt.gyro.z = sensorMpu9250GyroConvert(data[2]);
    mt.acc.x = sensorMpu9250AccConvert(data[3]);
    mt.acc.y = sensorMpu9250AccConvert(data[4]);
    mt.acc.z = sensorMpu9250AccConvert(data[5]);
    return mt;
}
