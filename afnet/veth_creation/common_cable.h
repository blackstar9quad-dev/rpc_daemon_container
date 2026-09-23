#ifndef COMMON_CABLE_H

#define CONTAINER_BRIDGE_SIG 7
#define

struct interface_message{
	struct nlmsghdr *nlh ;
	struct ifinfomsg *inf_msg;
	char buffer[988];
};

struct address_message{
	struct nlmsghdr *nlh;
	struct ifaddrmsg *inf_addr ;
	char buffer[1000]
};

struct route_message{
	struct nlmsghdr *nlh;
	struct rtmsg    *rt;
	char buffer[996];
};

char interface_message_buffer[1024];
char address_message_buffer_host[1024];
char address_message_buffer_guest[1024];
char routing_message_buffer_host[1024];
char routing_message_buffer_guest[1024];

#endif
