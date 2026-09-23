#include <stdio.h>
#include <stdlib.h>
#include <fnctl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sched.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <signal.h>
#include <dirent.h>
#include <./rpc.h>

#define BACKLOGS 5 

char ip_address[] = "127.0.0.1";
char *port = "4533";
NUMBER_OF_USERS = 1;
int NUMBER_OF_ENTRIES = 0  ; 

int entry_filler(struct addrinfo *addr_info , int fd ,  char root_dir[20] , pthread_t user_thread_id ,rpc_user *user_list){

	user_list->entry_numnber  =  NUMBER_OF_ENTIRES ;
	user_list->addr_inf = addr_info ;
	user_list->user_fd  = fd ; 
	user_list->root_dir = root_dir ; 
	user_list->user_thread_id = user_thread_id ;
	pipe(user_list->fd);

	printf("entry for user number %d \n",NUMBER_OF_ENTIRES);

	return 1;

};


int user_creation(rpc_user *user_list){
	pthread_t user_thread;
	struct addrinfo client_info ; 
	char root_dir[20];
	int user_fd ; 
	struct sockaddr_in *client_info ;
	char client_addr[12];
	char client_port[5];


	user_fd =  accept(fd,(struct sockaddr *)client_info,sizeof(struct sockaddr_in));

	if(data_extraction(client_addr,client_port,(struct sockaddr *)client_info) < 0){
		printf("OPERATION FAILED : CLIENT DATA EXTRACTION \n");
		return -1;
	};

	if(!fgets(root_dir,sizeof(root_dir),stdin)){
		printf("INPUT ROOT DIRECTORY ERROR \n");
		return -1;
	};

	


};

int user_entry(rpc_user *user_list){
	NUMBER_OF_ENTIRES += 1;
	NUMBER_OF_USER += 1;
	
	user_list = (rpc_user *)realloc(sizeof(rpc_user)*NUMBER_OF_USER);
	if(!user_list){
		printf("OPERTION FAILED : REALLOC ERROR \n");
		return -1;
	};

	if(thread_creation(user_list)<0){
	};
};

int server_setter(struct addrinfo *server , struct addrinfo **server_info, int *fd){
	int result;

	server->ai_flags = AI_PASSIVE;
	server->ai_family = AF_INET ; 
	server->ai_socktype = SOCK_STREAM ;

	result = getaddrinfo(ip_address,port,server,server_info);

	if(result != 0){
		return -1;
	};

	*fd  =  socket((*server_info)->ai_family,(*server_info)->ai_socktype,(*server_info)->ai_protocol);

	if(*fd <0){
		return -1;
	};


	result =  bind(*fd,(*server)->ai_addr,(*server)->ai_addrlen);
	if(result<0){
		return -1;
	};


	printf("OPERATION COMPLETE : SERVER INFO ESTABLISED \n");
	return 1;
};


int main(){

	struct addrinfo *server , *server_info;
	int result;
	int fd;


	rpc_user *user_list =  (rpc_user *)malloc(sizeof(rpc_user) * NUMBER_OF_USER);
	if(!rpc_user){
		printf("OPERATION FAILED : ALLOCATION ERRROR \n");
		return -1;
	};

	result = server_setter(server, &server_info , &fd);
	if(result<0){
		printf("OPERATION FAILED: SETTING SERVER INFO \n");
		return -1;
	};

	result = entry_filler(server_info , *fd,NULL,NULL,user_list);
	while(){
		if(listen(*fd,BACKLOGS)<0){
			perror("OPERATION FAILED : LISTENINF ERROR \n");
			return -1;
		};


	};
};
