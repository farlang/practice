#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <iostream>
#include <netdb.h>

using namespace std;


int main(int argc, char **argv){
  if(argc < 3){
    cerr << "useage:" << argv[0] << " ip port" << endl;
    exit(0);
  }
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr);
  addr.sin.family = AF_INET;
  addr.sin.port = htons(atoi(argv[2]))
  inet_pton(AF_INET, argv[1],addr.sin_addr.s_addr);
  socklen_t len = sizeof(addr);
  
  if (connect(sockfd, (struct sockaddr*)&addr, len) < 0) {
    cerr << "connect error" << strerror(errno) << endl;
    exit(0);
  }
  
  char buffer[1024];
  memset(buffer, 0, sizeof(buffer));
  sszie_t n;
  if (n = read()
  

}
