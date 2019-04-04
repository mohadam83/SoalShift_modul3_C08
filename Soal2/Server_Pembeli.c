#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define PORT 7000

int *stok;
char buffer[1024] = {0};
char status[1];

void* ser_pem(void *arg){
    if(strcmp(buffer, "beli") == 0){
	if(*stok > 0){
	    *stok = *stok - 1;
	    status[0] = '1';
	} 
	else {
	    status[0] = '0';
	} 
    } 
}

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
        
    key_t kode = 1234;    
    int shmid = shmget(kode, sizeof(int), IPC_CREAT | 0666);
    stok = shmat(shmid, NULL, 0);

    *stok = 0;       
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    pthread_t tid1;
    while(1){
	valread = read( new_socket , buffer, 1024);
    	pthread_create(&(tid1),NULL,&ser_pem,NULL);
    	pthread_join(tid1,NULL);

    	send(new_socket , status , strlen(status) , 0 );
    }
     
    return 0;
}
