#ifndef UDPRECEIVER
#define UDPRECEIVER

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>

#include <WPILib.h>

#define BUFFSIZE 1024

class UdpReceiver: public Subsystem {
    public:
        int port;
        UdpReceiver(int init_port, const char* name);
        ~UdpReceiver();
        bool isBroadcastable();
    private:
        int sock;
        bool broadcastable; // true if the socket is ready and we cajn broadcast
        void receivePacket();
        void socketInit();
        virtual int parsePacket(char* recv_buffer, int received_bytes) = 0; // int is error code return
};
#endif
