#include <sys/shm.h>
#include <termios.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

char name[30], menu;
int *value, darah, makan, bersih, scene, musuh, makanan, mandi;

void* bgdarah(){
    while(1){
        if(scene == 0){
            sleep(10);
            darah += 5;
        }
    }
}

void* bgmakan(){
    while(1){
        if(scene == 0){
            sleep(10);
            makan -= 5;
        }
    }
}

void* bgbersih(){
    while(1){
        if(scene == 0){
            sleep(30);
            bersih -= 10;
        }
    }
}

void* standby(){
    if(menu == 1){
        if(makanan > 0){
            makan += 15;
            makanan--;
        } else {
            printf("You don't have enough food. Please buy it in the shop.\n");
        }
    }
    if(menu == 2){
        if(mandi <= 0){
            mandi = 20;
            bersih += 30;
        }else{
            printf("Bath is not ready");
        }
    }
    if(menu == 3){
        scene = 1;
    }
    if(menu == 4){
        scene = 2;
    }
    if(menu == 5){
        exit(0);
    }
}

void* battle(){
    if(menu == 1){
        darah -= 20;
        musuh -= 20;
        if(musuh <= 0){
            printf("%s win!\n", name);
            sleep(0.7);
            scene = 0;
            musuh = 100;
        }
    } else if(menu == 2){
        scene = 0;
    }
}

void* shop(){
    if(menu == 1){
        if(*value > 0){
            *value -= 1;
            makanan++;
        }else{
            printf("Sold out.\n");
        }
    } else if(menu == 2){
        scene = 0;
    }
}

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

void* mainmenu(){
    while(makan > 0 && bersih > 0  && darah > 0){
        if(makan<=0 || bersih <= 0 || darah <= 0) printf("%s RIP :(\n", name);
        if(scene == 0){
            printf("Standby scene\n\ndarah : %d\nmakan : %d\nbersih : %d\nmakanan left : %d\n", darah, makan, bersih, makanan);
            if(mandi <= 0){
                printf("Bath is ready");
            }else{
                printf("Bath will be ready in %ds\n", mandi);
            }
            printf("\nChoices\n1. Eat\n2. Bath\n3. Battle\n4. Shop\n5. Exit\n");
        }
        if(scene == 1){
            printf("Battle scene\n\n%s’s darah : %d\nmusuh’s darah : %d\n\nChoices\n1. Attack\n2. Run\n", name, darah, musuh);
        }
        if(scene == 2){
            printf("Shop scene\n\nShop makanan stock : %d\nYour makanan stock : %d\n\nChoices\n1. Buy\n2. Back\n", *value, makanan);
        }
        mandi--;
        sleep(1);
        system("clear");
    }

    exit(0);
}

int main(){
    darah = 300;
    makan = 200;
    bersih = 100;
    // darah=5;
    // makan=5;
    // bersih=5;
    scene = 0;
    musuh = 100;
    makanan = 0;
    mandi = 0;
    pthread_t thread;
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);

    printf("Masukkan nama monster : ");
    scanf("%s", name);
    
    pthread_create(&thread, NULL, mainmenu, NULL);
    pthread_create(&thread, NULL, bgmakan, NULL);
    pthread_create(&thread, NULL, bgbersih, NULL);
    pthread_create(&thread, NULL, bgdarah, NULL);
    pthread_create(&thread, NULL, standby, NULL);
    pthread_create(&thread, NULL, battle, NULL);
    pthread_create(&thread, NULL, shop, NULL);

    while(1){
        if(makan>200) makan = 200;
        menu = getch();

        switch(scene)
        {
            case 0:
                standby();
                break;

            case 1:
                battle();
                break;

            case 2:
                shop();
                break;
        }
        
    }
}
