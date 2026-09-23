#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include "common.h"
#include <linux/netlink.h>
#include <sys/socket.h>
#include <linux/rtnetlink.h>
#include <errno.h>


int main(){
	struct sockaddr_nl  *sender_client  ; 
	struct nlmsghdr     *sender_header  ; 
	int sockfds ;

	char *payload = "THE MESSAGE HAVE BEEN RECIVED";
	int len = strlen(payload) + 1 ;

        pid_t sender_pid =  getpid();
	sender_header = (struct nlmsghdr *)malloc(NLMSG_SPACE(len));
	sender_client = (struct sockaddr_nl *)malloc(sizeof(struct sockaddr_nl));

	memset(sender_client,0,sizeof(struct sockaddr_nl));

	sender_client->nl_family = AF_NETLINK ;
	sender_client->nl_pid  =  0 ;
	sender_client->nl_groups  = COMMON_GROUP | GROUP_1 ;


        sockfds = socket(AF_NETLINK , SOCK_RAW , NETLINK_USERSOCK);
	if(sockfds<0){
		printf("SOCKET CREATION ERROR \n");
		return -1;
	};

	sender_header->nlmsg_len   =  NLMSG_SPACE(len);
	sender_header->nlmsg_type  =  RTM_NEWLINK  ;
	sender_header->nlmsg_flags =  NLM_F_REQUEST |  NLM_F_CREATE ;
	sender_header->nlmsg_seq   =  3 ;
	sender_header->nlmsg_pid   =  sender_pid ;

	strcpy(NLMSG_DATA(sender_header),payload);

	if(sendto(sockfds,sender_header,sender_header->nlmsg_len,0,(struct sockaddr *)sender_client,sizeof(*sender_client))<0){
		if(errno == ECONNREFUSED){
			printf("Broadcast sent successfully (Ignored kernel unicast fallback)\n");
		}else{
			perror("ERROR IN SENDING TO KERNEL \n");
		        return -1;
		};
	};

	return 1;

};



