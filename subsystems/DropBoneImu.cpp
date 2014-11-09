#include "DropBoneImu.h"

#include <cstdlib>
#include <cmath>

DropBoneImu::DropBoneImu(int port): UdpReceiver(port, "DropBoneImu") {
    offset = 0;
}

DropBoneImu::~DropBoneImu() {
}

int DropBoneImu::parsePacket(char* recv_buffer, int received_bytes) {
    char* end = recv_buffer;
    double next;
    for(int i = 0; i < BONE_PARSEDLEN; i++){
        next=strtod(end+1,&end);
        parsed[i] = next;
    }
    return 0;
}

double* DropBoneImu::getEuler() {
    return parsed;
}

double* DropBoneImu::getGyro() {
    return parsed+3;
}

double* DropBoneImu::getAccel() {
    return parsed+6;
}

double* DropBoneImu::getQuat() {
    return parsed+9;
}

double DropBoneImu::getYawAngle() {
    return parsed[0];
}

double DropBoneImu::getYawRate() {
    double yaw_angle;
    yaw_angle = atan2(sin(parsed[0]-offset),cos(parsed[0]-offset));
    return yaw_angle;
}

double DropBoneImu::PIDGet() {
    return getYawAngle();
}

void DropBoneImu::resetYaw() {
    offset = parsed[0];
}
