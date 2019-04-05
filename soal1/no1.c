#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>

typedef long long int ll;

ll arr[100];
int b; //banyaknya input

void* hit(void* arg){
    ll value=1;
    ll a = (ll) arg;
    for(ll i=2;i<=a;i++) {
        value*=i;
    }
    printf("Result of %lld! = %lld\n",a,value);
    return NULL;
}

void swap(ll *xp, ll *yp) 
{ 
    ll temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
void selectionSort() 
{ 
    int i, j, min_idx; 
  
    for (i = 0; i < b-1; i++) 
    { 

        min_idx = i; 
        for (j = i+1; j < b; j++) 
          if (arr[j] < arr[min_idx]) 
            min_idx = j; 
  
        swap(&arr[min_idx], &arr[i]); 
    } 
} 

int main(int argc,char *argv[]){
    pthread_t tid[argc-1];
    b = argc-1;
    for(int i=0;i<argc-1;i++)
    {
        ll a=strtol((char *)argv[i+1],NULL,10);
        arr[i] = a;
    }
    selectionSort();
    for(int i=0;i<argc-1;i++){
        pthread_create(&(tid[i]),NULL,&hit,(void*)arr[i]);
        pthread_join(tid[i],NULL);
    }
    // for(int i=0;i<argc-1;i++){
    //     pthread_join(tid[i],NULL);
    // }
}
