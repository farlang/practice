#include <errno.h>
#include <iostream>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

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
 
  while(1) {
    struct sockaddr_in clientaddr;
    unsigned int c_len = sizeof(clientaddr);
    int fd = accept(sockfd, (struct sockaddr*)&clientaddr, &c_len); 
   
    if (fd < 0)
    {
     cerr << "accept error" << strerror(errno) << endl;
     exit(0);
    }
    
    cout << fd << endl;
  }
}
