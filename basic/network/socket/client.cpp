#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <thread>

using namespace std;

void send_read_to(const char* ip, const char* port, const char* msg){
  
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(port));
  inet_pton(AF_INET, ip, &addr.sin_addr.s_addr);
  socklen_t len = sizeof(addr);
  
  if (connect(sockfd, (struct sockaddr*)&addr, len) < 0) {
    cerr << "connect error" << strerror(errno) << endl;
    exit(0);
  }
  
  char buffer[1024];
  memset(buffer, 0, sizeof(buffer));
  strcpy(buffer, msg);
  send(sockfd, buffer, 1024, 0);

  memset(buffer, 0, sizeof(buffer));
  int length = 0;
  length = recv(sockfd, buffer, 1024, 0);
  if (length < 0) {
      cerr << "recv data error" << strerror(errno) << endl;
      exit(1);
  }
  cout << "result: " << buffer << endl;   
}

int main(int argc, char **argv){
  if(argc < 3){
    cerr << "useage:" << argv[0] << " ip port" << endl;
    exit(0);
  }
  thread clients[100];
  for(int i = 0; i < 100; i++){
    cout << i << endl;
    // stringstream ss("...");
    // ss << "Hi server, I am client" << i;
    clients[i] = thread(send_read_to, argv[1], argv[2], "Hi server,");
  }
  for(int i = 0; i < 100; i++){
   clients[i].join();
  }
  return 0;
}
