#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include  "common.h"
#include <linux/netlink.h>
#include <sys/socket.h>


int main(){
	int sockfds;
	struct sockaddr_nl *client_socket; 
	struct  nlmsghdr *header ; 
	char buffer[1024];

	header =  (struct nlmsghdr *)malloc(sizeof(struct nlmsghdr));
	client_socket  =  (struct sockaddr_nl *)malloc(sizeof(struct sockaddr_nl));

	memset(client_socket , 0 , sizeof(struct sockaddr_nl));

	printf("pid : %d \n",getpid());

	client_socket->nl_family  = AF_NETLINK ;
	client_socket->nl_pid     = getpid();
	client_socket->nl_groups   = COMMON_GROUP ;

	sockfds =  socket(AF_NETLINK , SOCK_RAW , NETLINK_USERSOCK);
	if(sockfds <0){
		printf("ERROR IN CREATING THE SOCKET \n");
		return -1;
	};

	if(bind(sockfds,(struct sockaddr *)client_socket,sizeof(*client_socket))<0){
		printf("ERROR IN BINDING THE SOCKET TO ITSELF \n");
			return -1;
	};

	printf("recving the message ...... \n");

        if(recv(sockfds , buffer ,sizeof(buffer),0)<0){
		printf("ERROR IN RECIVE \n");
		return -1;
	};

	header =  (struct nlmsghdr *)buffer;

	printf("--- NETLINK HEADER ---\n");
        printf("Length: %u bytes\n", header->nlmsg_len);
        printf("Type:   %u\n", header->nlmsg_type);
        printf("Flags:  %u\n", header->nlmsg_flags);
        printf("Seq:    %u\n", header->nlmsg_seq);
        printf("PID:    %u\n", header->nlmsg_pid);
        printf("----------------------\n");
	printf("Payload received: %s \n", (char *)NLMSG_DATA(header));

	return 1;
};	
