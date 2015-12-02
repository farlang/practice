#include <errno.h>
#include <iostream>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <thread>
#include <string.h>

#if __cplusplus <= 199711L
#error you need c++11 compiler!
#endif

using namespace std;

void read_socket(int sockfd){
    while(1){
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));   
        int len = recv(sockfd, buffer, 1024, 0);
        if (len < 0 ){
          cerr << "recv message error:" << endl;
        }
        buffer[len] = '\0';
        cout << "recvive message from " << sockfd << ":" << buffer << endl;
        memset(buffer, 0, sizeof(buffer));
        const char *str = "Hi client";
        strncpy(buffer, str, strlen(str));
        send(sockfd, buffer, 1024, 0);
    }
}

void write_socket(int sockfd){
     cout << "write thread start" << endl;
}


int main(int argc, char **argv){
    if (argc < 2) {
        cerr << "useage: " << argv[0] << "port" << endl;
        exit(0);
    }
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cerr << "can't create socket:" << strerror(errno) << endl;
        exit(0);
    }
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    addr.sin_addr.s_addr = INADDR_ANY;

    int len = sizeof(addr);
    if (bind(sockfd,(struct sockaddr*)&addr, len) < 0)
    {
        cerr << "bind fail:" << strerror(errno) << endl;
        exit(0);
    }

    if (listen(sockfd,3) < 0) {
        cerr << "listen fail:" << strerror(errno) << endl;
        exit(0);
    }
   
    int n = 0;

    while(1) {
        struct sockaddr_in clientaddr;
        unsigned int c_len = sizeof(clientaddr);
        int fd = accept(sockfd, (struct sockaddr*)&clientaddr, &c_len); 

        if (fd < 0)
        {
            cerr << "accept error" << strerror(errno) << endl;
            exit(0);
        }

        thread reads(read_socket, fd);
        // thread write(write_socket, fd;
        reads.detach();
        cout << "n:" << n++ << endl;
    }

}
