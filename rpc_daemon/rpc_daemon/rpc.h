#include <pthread.h>
#include <sys/select.h>

#ifndef RPC_H
#define RPC_H

#define MAX_USER 1024

typedef struct{
	struct addrinfo *addr_inf;
	int user_fd;
	char root_dir[20];
	pthread_t user_thread_id ;
	pthread_mutex_t user_mutex ;
	int fd[2];
}rpc_user;

int NUMBER_OF_USER;

rpc_user *user_list;

int thread_handler(rpc_user *user_list){
};

int root_changer(char *root_dir){
};

int sigaction_handler(){
};




int total_user ;


int user_connection[MAX_USER];
fd_set readfds ;
fd_set writefds;

#endif
