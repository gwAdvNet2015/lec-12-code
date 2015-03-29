#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include "../socket_helper.h"

/****************************************
        Author: Tim Wood
        with a little help from
        http://beej.us/guide/bgnet/
****************************************/

int client_main(int sockfd, char* message) {
        int rc;
        /* Send the message, plus the \0 string ending. Use 0 flags. */
        rc = send(sockfd, message, strlen(message)+1, 0);
        if(rc < 0) {
                perror("ERROR on send");
                exit(-1);
        }

        return rc;

}

int main(int argc, char ** argv)
{
        int o;
        char* server_port = "1234";
        char* server_ip = "127.0.0.1";
        char *message = "Hello World";
        int sockfd;

        /* Command line args:
                -p port
                -h host name or IP
        */
        while ((o = getopt (argc, argv, "p:h:m:")) != -1) {
                switch(o){
                case 'p':
                        server_port = optarg;
                        break;
                case 'h':
                        server_ip = optarg;
                        break;
                case 'm':
                        message = optarg;
                        break;
                case '?':
                        if(optopt == 'p' || optopt == 'h' ) {
                                fprintf (stderr, "Option %c requires an argument.\n", optopt);
                        }
                        else {
                                fprintf (stderr, "Unknown argument: %c.\n", optopt);
                        }
                        break;
                }
        }
        printf("server_ip: %s   port: %s\n", server_ip, server_port);

        sockfd = socket_connect_helper(server_ip, server_port);

        client_main(sockfd, message);
        client_main(sockfd, "message 2");
        client_main(sockfd, "message 3");

        out:
        close(sockfd);

        printf("Done.\n");
        return 0;
}
