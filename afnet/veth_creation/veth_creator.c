#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>

int nlmsghdr_creator(struct interface_message *interface_msg){

	struct nlmsghdr *nlh;

	interface_msg->nlh  = (struct nlmsghdr *)malloc(sizeof(struct nlmsghdr));
	nlh = interface_msg->nlh;
	if(!nlh){
		printf("ERROR IN ALLOCATION SPACE : INTERFACE HEADER \n");
		return -1;
	};

	nlh->nl_len   = NLMSG_LENGTH(sizeof(struct ifinfomsg));
	nlh->nl_type  = RTM_NEWLINK ;
	nlh->nl_flags = NLM_F_REQUEST | NLM_F_ECHO | NLM_F_CREATE | NLM_F_EXCL ;
	nlh->nl_seq   = 1 ;
	nlh->nl_pid   = getpid();

	printf("OPERATION COMPLETE : INTERFACE HEADER \n");

	return 1;
};

int nlmsg_ip_creator(struct address_message *address_msg){

	struct nlmsghdr *nlh ;

	address_msg->nlh = (struct nlmsghdr *)malloc(sizeof(struct nlmsghdr));
	nlh = address_msg->nlh ;
	if(!nlh){
		printf("ERROR IN ALLOCATING SPACE : INTERFACE IP HEADER \n");
		return -1;
	};

	nlh->nl_len   = NLMSG_LENGTH(sizeof(struct ifinfoaddr));
	nlh->nl_type  = RTM_NEWADDR ;
	nlh->nl_flags = NLM_F_REQUEST | NLM_F_ECHO | NLM_F_CREATE | NLM_F_EXCL ;
	nlh->nl_seq   = 2
	nlh->nl_pid   = getpid();

	printf("OPERATION COMPLETE : INTERFACE IP HEADER \n");
	return 1;
};

int nlsmsg_route_creator(struct route_message *route_msg){

	struct nlmsghdr *nlh;

	route_msg->nlh = (struct nlmsghdr *)malloc(sizeof(struct nlmsghdr));
	nlh =  route_msg->nlh ;
	if(!nlh){
		printf("ERROR IN ALLOCATING THE SPACE : INTERFACE ROUTE HEADER \n");
		return -1;
	};

	nlh->nl_len   = NLMSG_LENGTH(sizeof(struct rtmsg)); 
	nlh->nl_type  = RTM_NEWROUTE ;
	nlh->nl_flags = NLM_F_REQUEST | NLM_F_ECHO | NLM_F_CREATE | NLM_F_EXCL ;
	nlh->nl_seq   = 3
	nlh->nl_pid   = getpid();

};

int ifinfomsg_creator(struct interface_message *interface_msg){
	struct ifinfomsg *ifn;
 
	uint32_t flags ;
	flags =  IFF_UP | IFF_BROADCAST | IFF_MULTICAST ;

	interface_msg->inf_msg = (struct ifinfomsg *)malloc(sizeof(struct ifinfomsg));
	ifn = interface_msg->inf_msg ;
	if(!ifn){
		printf("ERROR IN ALLOCATING SPACE : INTERFACE PROTOCOL \n");
		return -1;
	};
	
	ifn->ifi_family  = AF_UNSPEC ; 
	ifn->ifi_type    = ARPHRD_ETHER ;
	ifn->ifi_index   = 13
	ifn->ifi_flags   = flags; 
	ifn->ifi_change  = flags; 

	printf("OPERATION COMPLETE : INTERFACE PROTOCOL \n");
	return 1;
};

int ifinfoaddr_creator_host(struct address_message *address_msg_host){

	struct ifaddrmsg *inf;

	address_msg_host->inf_addr = (struct ifaddrmsg *)malloc(sizeof(struct ifaddrmsg));
	inf = address_msg->inf_addr ;
	if(!inf){
		printf("ERROR IN ALLOCATING SPACE : INTERFACE IP HOST PROTOCOL \n");
		return -1;
	};

	inf->ifa_family    =  AF_INET;
	inf->ifa_prefixlen =  24;
	inf->ifa_flags     =  IFA_F_NOPREFIXROUTE ; 
	inf->ifa_scope     =  RT_SCOPE_LINK ;
	inf->ifa_index     =  14 ;

	printf("OPERATION COMPLETE : INTERFACE IP HOST PROTOCOL \n");
	return 1;
};

int ifinfoaddr_creator_guest(struct address_message *address_msg_guest){
	struct ifaddrmsg *inf;

	address_msg_guest->inf_addr  = (struct ifaddrmsg *)malloc(sizeof(struct ifaddrmsg));
	inf = address_msg_guest->inf_addr ; 
	inf(!inf){
		printf("ERROR IN ALLOCATING THE SPACE : INTERFACE IP GUEST PROTOCOL \n");
		return -1;
	};

	inf->ifa_family    = AF_INET ;
	inf->ifa_prefixlen = 24 ;
	inf->flags         = IFA_F_NOPREFIXROUTE ;
	inf->ifa_scope     = RT_SCOPE_LINK ;
	inf->ifa_index     = 13;

	printf("OPERATION COMPLETE : INTERFACE IP GUEST PROTOCOL \n");
	return 1;
};

int rtmsg_creator(struct route_message *route_msg){

	struct rtmsg *rt;

	route_msg->rt = (struct rtmsg *)malloc(sizeof(struct rtmsg));
	rt = route_msg->rt ;
	if(!rt){
		printf("ERROR IN ALLOCATING THE SPACE : INTERFACE ROUTING PROTOCOL \n");
		return -1;
	};

	rt->rtm_family   = AF_INET ;
	rt->rtm_dest_len = 24 ;
	rt->rtm_tos      = 0;
	rt->rtm_table    = 254 ;
	rt->rtm_protocol = CONTAINER_BRIDGE_SIG ;
	rt->rtm_scope    = RT_SCOPE_LINK ;
	rt->rtm_type     = RTN_UNICAST ;
	rt->rtm_flags    = 0;

	printf("OPERATION SUCCESSFUL : INTERFACE ROUTING PROTOCOL \n");
	return 1;

};

int rtattr_interface(struct interface_message *interface_msg){

	int offset = 0 ;

	struct rtattr *rt ; 
	rt = (struct rtattr *)interface_msg->buffer  ; 

	                         //INTERFACE NAME 
	char *name = "veth_guest";
	rt->rt_len  = RTA_LENGTH(strlen(name));
	rt->rt_type = IFLA_NAME ;
	memcpy(RTA_DATA(rt),name,strlen(name));
	offset += RTA_ALIGN(rt->rt_len);

	                         //INTERFACE BROADCAST 
	struct rtattr *rt1;
	rt1 = (struct rtattr *)(rt + offset);

	unsigned char broadcast[6]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	rt1->rt_len  = RTA_LENGTH(6);
	rt1->rt_type = IFLA_BROADCAST ;
	memcpy(RTA_DATA(rt1),broadcast,6);
	offset += RTA_ALIGN(rt1->rt_len);

	                          //INTERFACE PID_CHANGE 
	struct rtattrr *rt2;
	rt2 = (struct rtattr *)(buffer+offset);

	pid_t container_pid = //pid of the container after clone(CLONE_NEWNET)
	rt2->rt_len  = RTA_LENGTH(sizeof(container_pid));
	rt2->rt_type = IFLA_F_NS_PID;
	memcpy(RTA_DATA(rt2),&container_pid,sizeof(container_pid));
	offset += RTA_ALIGN(rt2->rt_len);

	                          //Matryoshka doll
	
	                          //ILFA_LINKINFO 
				  
	int linkinfo_offset = RTA_LENGTH(0);
	struct rtattr *rt3;
	rt3 = (struct rtattr *)(buffer + offset);

	rt3->rt_type = IFLA_LINKINFO;
	offset += RTA_LENGTH(0);

	                          //ILFA_INFO_KIND
	struct rtattr *rt4;
	rt4 = (struct rtattr *)(buffer + offset);

	char *type = "veth";
	rt4->rt_len  = RTA_LENGTH(strlen(type));
	rt4->rt_type = IFLA_INFO_KIND ;
	memcpy(RTA_DATA(rt4),type,strlen(type));
	offset += RTA_ALIGN(rt4->rt_len);
	linkinfo_offset += RTA_ALIGN(rt4->rt_len);

	                          //IFLA_INFO_DATA 
				  
	int data_offset = RTA_LENGTH(0);

	struct rtattr *rt5 ;
	rt5 = (struct rtattr *)(buffer + offset);

	rt5->rt_type = IFLA_INFO_DATA;
	offset += RTA_LENGTH(0);
	linkinfo_offset += RTA_LENGTH(0);



                                 //VETH_INFO_PEER 
	struct rtattr *rt6 ;
	rt6 = (struct rtattr *)(buffer + offset);

	rt6->rt_type = VETH_INFO_PEER ; 

	int current_offset  = RTA_LENGTH(0);

	struct ifinfomsg *peer_interface ;
	peer_interface = (struct ifinfomsg *)(buffer + (offset + current_offset));
	uint32_t flags  = IFF_UP | IFF_BROADCAST | IFF_MULTICAST ;

	peer_interface->ifa_family    = AF_UNSPEC ;
	peer_interface->ifa_type      = ARPHRD_ETHER ;
	peer_interface->ifa_index     = 14;
	peer_interface->ifa_flags     = flags;
	peer_interface->ifa_change    = flags;

	current_offset += NLMSG_ALIGN(sizeof(struct ifinfomsg));

	struct rtattr *rt7;
	rt7 = (struct rtattr *)(buffer + (offset + current_offset));

	char *peer_name = "veth_host";
	rt7->rt_len  = RTA_LENGTH(strlen(peer_name));
	rt7->rt_type = IFLA_IFNAME ;
	memcpy(RTA_DATA(rt7),peer_name,strlen(peer_name));
	current_offset += RTA_ALIGN(rt7->rt_len);
	linkinfo_offset += current_offset;
	data_offset += current_offset ;


	rt7->rt_len  = current_offset ;
	rt5->rt_len  = data_offset ;
	rt3->rt_len  = linkinfo_offset ;

	offset += current_offset ;


};

int rtattr_ip_host(struct address_message *address_msg_host){
};

int rtattr_ip_guest(struct address_message *address_msg_guest){
};

int rtattr_route(struct route_message *route_msg){
};


int sockaddr_creation(struct sockaddr_nl *sock_info){
	
};

int main(){
	struct interface_message interface_msg;
	struct address_message address_msg_host ;
	struct address_message address_msg_guest ;
	struct route_message route_msg_host ;
	struct route_message route_msg_guest;

	if(nlmsg_creator(interface_msg)<0){
		printf("OPERATION FAILED : CREATION OF THE INTERFACE HEADER \n");
		return -1;
	};

	if(ifinfomsg_creator(interface_msg)<0){
		printf("OPERATION FAILED : CREATION OF THE INTERFACE PROTOCOLS \n");
		return -1;
	};

	if(rtattr_interface(interface_msg)<0){
		printf("OPERATION FAILED : CREATION OF THE INTERFACE RULES  \n");
		return -1;
	};

	if(nlmsg_ip_creator(address_msg)<0){
		printf("OPERATION FAILED : CREATION OF THE INTERFACE IP HEADER \n");
		return -1;
	};

	if(ifinfoaddr_creator(address_msg)<0){
		printf("OPERATION FAILED : CREATION OF THE INTERFACE IP PROTOCOLS \n");
		return -1;
	};

	if(rtattr_ip(address_msg)<0){
		printf("OPERATION FAILED : CREATION OF THE INTERFACE IP RULES \n");
		return -1;
	};

	if(nlmsg_route_creator(route_msg)<0){
		printf("OPERATION FAILED : CREATION OF THE INTERFACE ROUTING HEADER \n");
		return -1;
	};

	if(rtmsg_creator(route_msg)<0){
		printf("OPERATION FAILED : CREATION OF THE INTERFACE ROUTING PROTOCOLS \n");
		return -1;
	};

	if(rtattr_route(route_msg)<0){
		printf("OPERATION FAILED : CREATION OF THE INTERFACE ROUTING RULES \n");
		return -1;
	};


};
