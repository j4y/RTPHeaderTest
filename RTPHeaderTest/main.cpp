//
//  main.cpp
//  RTPHeaderTest
//

#include <iostream>
#include "RtpHeaders.h"
#include <inttypes.h>

using namespace std;


//    0                   1                   2                   3
//    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |V=2|P|X|  CC   |M|     PT      |       sequence number         |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |                           timestamp                           |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |           synchronization source (SSRC) identifier            |
//   +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
//   |            contributing source (CSRC) identifiers             |
//   |                             ....                              |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

using byte = unsigned char;

int main(int argc, const char * argv[]) {

    // data setup
    uint32_t first = 0xFFFF | 0x1FFFFFFF;
    uint32_t timestamp = 0x0128;
    uint32_t ssrc = 0x01 | 0x02 | 0x04 | 0x08 | 0x256;

    
    int somedata[4];
    //    The htonl() function converts the unsigned integer hostlong from host byte order to network byte order.
    // on the other side:
    //    The ntohl() function converts the unsigned integer netlong from network byte order to host byte order.
    somedata[0] = htonl(first);
    somedata[1] = htonl(timestamp);
    somedata[2] = htonl(ssrc);
    somedata[2] = htonl(ssrc);
    somedata[3] = htonl(ssrc);
    
    RtpHeader* head = reinterpret_cast<RtpHeader*>(somedata);
    
    printf("version: %" PRIu8 "\n", head->getVersion());
    printf("padding: %" PRIu8 "\n", head->hasPadding());
    printf("extension: %" PRIu8 "\n", head->getExtension());
    printf("marker: %" PRIu8 "\n", head->getMarker());
    printf("payload type: %" PRIu8 "\n", head->getPayloadType());
    printf("sequence number: %" PRIu16 "\n", head->getSeqNumber());
    printf("timestamp %" PRIu32 "\n", head->getTimestamp());
    printf("ssrc %" PRIu32 "\n", head->getSSRC());
    printf("header length: %u\n", head->getHeaderLength());
    
    return 0;
}
