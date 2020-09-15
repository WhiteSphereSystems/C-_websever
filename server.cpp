#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <string.h>

const int HTTP_TCP_PORT = 80;
const int CR = 13;
const int LF =10;

void httpd(int sockfd);

int send_msg(int fd, char *msg);


int main(int argc, char* argv[]){

    int socked, new_sockfd;
    int writer_len;
    struct sockaddr_in reader_addr, writer_addr;
    unsigned short servPort;

    if(argc != 2){
        fprintf(stderr, "argument count mismatch error.\n");
        exit(EXIT_FAILURE);
    }

    if((servPort = (unsigned short) atoi(argv[1])) == 0){
        fprintf(stderr, "invalid port number.\n");
        exit(EXIT_FAILURE);
    }

    if((servPort = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 ){
        perror("bind() failed");
        exit(EXIT_FAILURE);
    }

    memset((char*)&reader_addr, 0, sizeof(reader_addr));

   reader_addr.sin_family = AF_INET;
   reader_addr.sin_addr.s_addr = htonl(INADDR_ANY);
   reader_addr.sin_port = htons(servPort);

    
    
}