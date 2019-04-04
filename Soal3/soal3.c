#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>
int WakeUp_Status = 0;
int Spirit_Status = 100;
int Agmal = 0;
int perintah = -1;
int Iraj = 0;

void *Cetak_Status(void *argv){
    printf("Agmal WakeUp_Status = %d\nIraj Spirit_Status = %d\n", WakeUp_Status, Spirit_Status);
    perintah = -1;
}

void *Agmal_Bangun(void *argv){
    while(1){
	if(Iraj == 3){
	    printf("Agmal Ayo Bangun disabled 10 s\n");
	    sleep(10);
	    Iraj = 0;	   
	}
	if(perintah == 1){
	    WakeUp_Status += 15;
	    Agmal++;	     
	    perintah = -1;
    	}	
	if(WakeUp_Status >= 100){
	    printf("Agmal Terbangun,mereka bangun pagi dan berolahraga\n");
	    exit(0);
	}
    }   
}

void *Iraj_Tidur(void *argv){
    while(1){
	if(Agmal == 3){
	    printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
	    sleep(10);
	    Agmal = 0;
	}
	if(perintah == 2){
	    Spirit_Status -= 20;
	    Iraj++;	    
	    perintah = -1;
	}
	if(Spirit_Status <= 0){
	    printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
	    exit(0);
	}
    }   
}

int main(){
    pthread_t tid[3];
    pthread_create(&(tid[1]),NULL,Agmal_Bangun,NULL);
    pthread_create(&(tid[2]),NULL,Iraj_Tidur,NULL);
    while(1){
        scanf("%d", &perintah);
        if(perintah == 0){
            pthread_create(&(tid[0]),NULL,Cetak_Status,NULL);
        }		
    }
    return 0;
}
