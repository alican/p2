
#include "SensorConfiguration.h"

void CSensorConfiguration::setAddr(std::string addr){
    this->addr = addr;
}

std::string CSensorConfiguration::getAddr(){
    return this->addr;
}


int CSensorConfiguration::enableNotification(){

if(true){
    return 0;
}
return -1;
}


int CSensorConfiguration::disableNotification(){
    if(true){
    return 0;
}
return -1;

}
