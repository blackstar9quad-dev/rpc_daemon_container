#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <


void  *thread_handler(void *user_list){

	pthread_t user_thread;
	struct addrinfo *client_info ; 
	int user_fd ; 
	struct sockaddr_in *client ;
	char client_addr[12];
	char client_port[5];
	char root_dir[100];



	if(data_extraction(client_addr,client_port,(struct sockaddr *)client) < 0){
		printf("OPERATION FAILED : CLIENT DATA EXTRACTION \n");
		return -1;
	};

	if(addrinfo_creator(&client_info, client_addr ,  client_port , client)<0){
		printf("OPERATION FAILED :  ADDRINFO CREATION ERROR \n");
		return  -1;
	};

	if(root_creator(root_dir)<0){
		printf("OPERATION FAILED : CREATION OF THE ROOT DIRECTORY \n");
		return -1;
	};

	if(entry_filler(client_info ,  root_dir , (rpc_user *)user_client)<0){
		printf("OPERATION FAILED : FILLING THE USER DATA \n");
		return -1;
	};
//--------------------------------------------------------------------------------------------------//

	                        //clone code    


//--------------------------------------------------------------------------------------------------//

}

int sigaction_handler(sigset_t signal ){
};

int addrinfo_creator(struct addrinfo **client_info ,  char *client_addr , char * client_port , struct sockaddr *client){
	struct addrinfo *buffer_info  ; 

	buffer_info->ai_family = client->sa_family ; 
	buffer_info->ai_flags  = AI_PASSIVE ; 
	buffer_info->socktype  = SOCK_STREAM ;

	if(getaddrinfo(client_addr,client_port,buffer_info,client_info) !=){
		printf("CLIENT GETADDR CREATION ERROR \n");
		return -1;
	};

	return 1;
};

int data_extraction(char *client_addr ,  char *client_port , struct sockaddr *client_info){
	struct sockaddr_in temp;
	uint16_t port ; 
	uint32_t address ;

	size_t addr_size =  sizeof(temp->sin_addr);

	if(!memcpy(client_port , client_info[0] , sizeof(port))){
		return -1;
	};

	if(!memcpy(client_addr , client_info[sizeof(port) + 1] , sizeof(address))){
		return -1;
	};

	printf("OPEARATION COMPLETE :  DATA EXTRACTION \n");

	return 0;
};

int root_creator(char *root_dir){

	char dir_name[10];

	printf("ENTER THE NAME OF THE DIRECTORY FOR YOUR DEVICE \n");

	if(!fgets(dir_name,sizeof(root_dir),stdin)){
		printf("INPUT ROOT DIRECTORY ERROR \n");
		return -1;
	};

	root_dir = getenv("HOME");

	strcat(root_dir,dir_name);

	if(!root_dir){
		printf("CAN'T GET THE HOME DIR \n");
		return -1;
	};


	if(mkdir(root_dir , 0777)){
		if(errno == EEXIST){
			printf("directory already exist \n");
			return -1;
		}else {
			printf("failed in creating the dir \n");
			return -1;
		};
	};
	
	printf("ROOT DIRECTORY CREATED AT %s \n",root_dir);

	return 1;
};

//--------------------------------------------------------------------------------------------------//
               //to be added in the clone() code 
int root_setter(char *root_dir){

	char *sources[] = { "/bin" , "/usr" , "/lib" , "/lib64" , "/etc" } ;

	if(mount()<0){
		printf("");
	};

	int flag = 0 ;

	for(int i = 0 ;  i<5; i++){
		if(mount(sources[i],root_dir,NULL,MS_RDONLY|MS_BIND,NULL)<0){
			printf("ERROR IN MOUNTING DIR %s \n",sources[i]);
			flag = -1;
		};
	};

	if(flag<0){
		return -1;
	};

	printf("ROOT DIRECTORY HAS BEEN SET \n");
	return 1;
};
