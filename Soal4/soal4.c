#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>

void *Simpan_Proses1(void *argv){
    system("mkdir /home/adam/Document/FolderProses1");
    system("ps -aux | head -n 10 > /home/adam/Document/FolderProses1/SimpanProses1.txt");
}

void *Simpan_Proses2(void *argv){
    system("mkdir /home/adam/Document/FolderProses2");
    system("ps -aux | head -n 10 > /home/adam/Document/FolderProses2/SimpanProses2.txt");
}

void *Proses_Zip1(void *argv){
    system("zip -r /home/adam/Document/FolderProses1/KompresProses1.zip /home/adam/Document/FolderProses1 -j -rm /home/adam/Document/FolderProses1/SimpanProses1.txt");
}

void *Proses_Zip2(void *argv){
    system("zip -r /home/adam/Document/FolderProses2/KompresProses2.zip /home/adam/Document/FolderProses2 -j -rm /home/adam/Document/FolderProses2/SimpanProses2.txt");
}

void *Proses_Unzip1(void *argv){
    system("unzip /home/adam/Document/FolderProses1/KompresProses1.zip -d /home/adam/Document/FolderProses1");
}

void *Proses_Unzip2(void *argv){
    system("unzip /home/adam/Document/FolderProses2/KompresProses2.zip -d /home/adam/Document/FolderProses2");
}

int main() {
    pthread_t tid_ps1, tid_zip1, tid_unzip1, tid_ps2, tid_zip2, tid_unzip2;
    system("mkdir /home/adam/Document");

    pthread_create(&(tid_ps1), NULL, Simpan_Proses1, NULL);
    pthread_create(&(tid_ps2), NULL, Simpan_Proses2, NULL);

    pthread_join(tid_ps1,NULL);
    pthread_join(tid_ps2,NULL);

    pthread_create(&(tid_zip1), NULL, Proses_Zip1, NULL);
    pthread_create(&(tid_zip2), NULL, Proses_Zip2, NULL);

    pthread_join(tid_zip1,NULL);
    pthread_join(tid_zip2,NULL);
    
    sleep(15);
    pthread_create(&(tid_unzip1), NULL, Proses_Unzip1, NULL);  
    pthread_create(&(tid_unzip2), NULL, Proses_Unzip2, NULL);
  
    pthread_join(tid_unzip1,NULL);
    pthread_join(tid_unzip2,NULL);
}
