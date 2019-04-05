# SoalShift_modul3_C08

## Soal 1
Buat fungi untuk menghitung faktorial.
```
void* hit(void* arg){
    ll value=1;
    ll a = (ll) arg;
    for(ll i=2;i<=a;i++) value*=i;
    printf("Result of %lld! = %lld\n",a,value);
    return NULL;
}
```

Setelah itu buatlah fungi untuk mensorting angka, baik dari terkecil maupun terbesar, disini kami menggunakan Selection Sort secara ascending. 
```
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
```

Lalu buatlah thread untuk menjalankan fungsi faktorial.

## Soal 2
Untuk menyelesaikan soal nomer 2 ini, maka kami membuat 4 program, yaitu untuk Client Pembeli, Client Penjual, Server Pembeli dan Server Penjual. Agar antara client pembeli dan server pembeli maupun antara client penjual dan server penjual dapat terhubung, maka digunakan socket. Antara client pembeli dan server pembeli kami menggunakan port 7000, sementara antara client penjual dan server penjual menggunakan port 8080. Sehingga client penjual pasti akan terkonek ke server penjual begitupun pada client pembeli dan server pembeli. Selain itu, digunakan juga *Shared Memory* agar nilai stok yang berada di server pembeli dan penjual selalu sama, meskipun hanya dilakukan perubahan di salah satu server saja yaitu penjual saja atau hanya di pembeli. Syntax shared memorynya seperti di bawah ini.
```
key_t kode = 1234;    
int shmid = shmget(kode, sizeof(int), IPC_CREAT | 0666);
stok = shmat(shmid, NULL, 0);
```
*kode* yang bertipe *key_t* tersebut adalah semacam kode penghubung antara server pembeli dan server penjual yaitu di variabel pointer *stok*. 

Pada program Client Pembeli sendiri hanya digunakan sebagai input untuk mengurangi stok ketika ada perintah *beli*, sehingga perintah ini akan dikirim ke server pembeli untuk melakukan pengecekan apakah stok masih ada atau tidak dengan menggunakan syntax ```send(sock , perintah , strlen(perintah) , 0 );``` dan selain itu pada client pembeli akan menampilkan status apakah transaksi yang dilakukan berhasil yaitu ketika kita ingin *beli* dan stok masih lebih dari 0 atau transaksi yang dilakukan gagal yaitu ketika kita ingin *beli* namun stok telah bernilai 0. Untuk mengetahui status tersebut maka nantinya akan ada pesan yang dikirim dari server pembeli melalui socket dengan menggunakan syntax seperti berikut ```valread = read( sock , buffer, 1024);``` dan diterima di client pembeli ke dalam array of char *buffer*, indeks dari *buffer* ke 0 bernilai 1 jika transaksi berhasil dan bernilai 0 jika gagal. Syntaxnya seperti di bawah ini, sementara untuk syntax proses pembuatan socket mirip seperti di modul 3. 
```
while(1){
    printf("perintah pembeli : ");	scanf("%s", perintah);
    send(sock , perintah , strlen(perintah) , 0 );
    valread = read( sock , buffer, 1024);
    if(buffer[0] == '1'){
    	printf("transaksi berhasil\n");
    }
    else if(buffer[0] == '0'){
    	printf("transaksi gagal\n");
   }
}
```

Pada program server pembeli akan dilakukan proses pengurangan stok jika menerima perintah *beli* dari client pembeli dengan menggunakan socket ```valread = read( new_socket , buffer, 1024);```. Kemudian, di program ini terdapat thread untuk melakukan pengurangan stok tersebut. Prosesnya adalah melakukan pengecekan terlebih dahulu apakah perintahnya berupa *beli* atau tidak dengan menggunakan strcmp ```strcmp(buffer, "beli") == 0```, setelah itu jika nilai stok masih lebih dari 0, maka akan dilakukan pengurangan stok dan mengubah status menjadi 1 yang berarti transaksi berhasil dilakukan dan status tersebut yang nantinya akan dikirim ke client pembeli. Tetapi, jika stok telah bernilai 0 sebelum dilakukan pengurangan, maka tidak akan ada proses pengurangan stok, yang terjadi hanyalah membuat status menjadi 0 yang berarti transaksi gagal dilakukan. Syntaxnya seperti di bawah ini.
```
pthread_create(&(tid1),NULL,&ser_pem,NULL);
pthread_join(tid1,NULL);

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
```
Pada syntax di atas digunakan juga *pthread_join* untuk menunggu agar proses pada thread untuk melakukan pengurangan stok benar-benar telah selesai dilakukan.

Lalu, status yang dihasilkan dari proses pengurangan stok akan dikirim ke client pembeli dengan menggunakan syntax berikut ```send(new_socket , status , strlen(status) , 0 );```.

Pada program Client Penjual sendiri hanya digunakan sebagai input untuk menambah stok ketika ada perintah *tambah*, sehingga perintah ini akan dikirim ke server penjual untuk melakukan penambahan stok dengan menggunakan syntax ```send(sock , perintah , strlen(perintah) , 0 );``` Syntaxnya seperti di bawah ini, sementara untuk syntax proses pembuatan socket mirip seperti di modul 3. 
```
while(1){
    printf("perintah penjual : ");	scanf("%s", perintah);
    send(sock , perintah , strlen(perintah) , 0 );
}
```

Pada program server penjual akan dilakukan proses penambahan stok jika menerima perintah *tambah* dari client penjual dengan menggunakan socket ```valread = read(new_socket , buffer, 1024);```. Kemudian, prosesnya adalah melakukan pengecekan terlebih dahulu apakah perintahnya berupa *tambah* atau tidak dengan menggunakan strcmp ```strcmp(buffer, "tambah") == 0```. Syntaxnya seperti di bawah ini.
```
valread = read( new_socket , buffer, 1024);
if(strcmp(buffer, "tambah") == 0){
    *stok = *stok + 1;	   
}  
```

Selain itu, pada server penjual ini terdapat thread yang selalu berjalan yang bertujuan untuk mencetak jumlah *stok* yang ada sekarang baik setelah dilakukan *beli* maupun *tambah* setiap 5 second. Syntaxnya seperti di bawah ini.
```
void* cetak(void *arg){
    while(1){	
	printf("Stock sekarang : %d\n", *stok);
	sleep(5);
    }
}
```

## Soal 3
```
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
```
Untuk menyelesaikan soal nomer 3 ini, maka perlu dibuat tiga thread yaitu untuk *Agmal_Bangun*, *Iraj_Tidur*, dan *Cetak_Status*. 

Untuk *Agmal_Bangun* berfungsi untuk melakukan proses penambahan *WakeUp_Status* sebanyak 15 jika ada input berupa _Agmal Ayo Bangun_ dan disini saya ganti dengan input berupa bilangan 1. Namun, penambahan *WakeUp_Status* tidak akan terjadi jika thread ini dalam posisi disable selama 10s yaitu ketika perintah _Iraj Ayo Tidur_ telah dipanggil sebanyak 3x. Selain itu, program ini akan berhenti jika *WakeUp_Status* telah lebih dari atau sama dengan 100. Syntax untuk thread *Agmal_Bangun* seperti di bawah ini.
```
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
```

Untuk *Iraj_Tidur* berfungsi untuk melakukan proses pengurangan *Spirit_Status* sebanyak 20 jika ada input berupa _Iraj Ayo Tidur_ dan disini saya ganti dengan input berupa bilangan 2. Namun, pengurangan *Spirit_Status* tidak akan terjadi jika thread ini dalam posisi disable selama 10s yaitu ketika perintah _Agmal Ayo Bangun_ telah dipanggil sebanyak 3x. Selain itu, program ini akan berhenti jika *Spirit_Status* telah kurang dari atau sama dengan 0. Syntax untuk thread *Iraj_Tidur*  seperti di bawah ini.
```
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
```

Untuk *Cetak_Status* berfungsi untuk menampilkan kondisi terkini mengenai nilai dari *WakeUp_Status* dan *Spirit_Status* dan thread ini akan berjalan ketika terdapat perintah *All Status* dan disini kami ganti dengan bilangan 0. Syntaxnya seperti di bawah ini.
```
void *Cetak_Status(void *argv){
    printf("Agmal WakeUp_Status = %d\nIraj Spirit_Status = %d\n", WakeUp_Status, Spirit_Status);
    perintah = -1;
}
```

Untuk semua perintah akan diganti dengan -1 setelah menjalankan proses yang diminta oleh perintah tersebut sehingga setiap thread akan melakukan prosesnya baik untuk melakukan penambahan, pengurangan maupun menampilkan status-status yang ada hanya dilakukan sekali. 

Variabel *Agmal* dan *Iraj* ini digunakan sebagai counter perintah masing-masing mengenai *Agmal Ayo Bangun* dan *Iraj Ayo Tidur* dan setelah mencapai 3 kali, misalnya *Agmal Ayo Bangun* telah 3x dipanggil maka thread *Iraj_Tidur* akan terdisable selama 10second dan setelah disablenya berakhir maka counter *Agmal* yang sudah bernilai tiga akan kembali bernilai 0, begitupun pada counter *Iraj*.


## Soal 4
Langkah - langkah untuk menyelesaikan soal nomer 4 ini, maka yang pertama dilakukan adalah membuat directory *Document* dengan syntax ```mkdir``` dengan lokasi sesuai ketentuan di soal yaitu ```/home/adam/Document``` seperti di bawah ini.
```system("mkdir /home/adam/Document");```

Setelah itu menyimpan 10 list proses yang sedang berjalan dengan syntax ```ps -aux``` untuk menampilkan semua proses yang sedang berjalan, lalu agar hanya terambil 10 proses maka output dari syntax sebelumnya perlu di filter lagi agar hanya terambil maksimal 10 proses dengan menggunakan pipe dan menggunakan syntax  ```head -n 10```. Setelah itu barulah menyimpan hasil output dari syntax yang terakhir ke sebuah file dengan menggunakan tanda ```>``` diikuti dengan nama file untuk menyimpan 10 proses. Syntax-syntax ini dijalankan di *system*. Proses ini dijalankan di dua thread untuk menyimpan 10 proses tadi ke dua file dengan nama berbeda (satu thread satu file). Syntaxnya seperti di bawah ini.
```
pthread_create(&(tid_ps1), NULL, Simpan_Proses1, NULL);
pthread_create(&(tid_ps2), NULL, Simpan_Proses2, NULL);

void *Simpan_Proses1(void *argv){
    system("mkdir /home/adam/Document/FolderProses1");
    system("ps -aux | head -n 10 > /home/adam/Document/FolderProses1/SimpanProses1.txt");
}

void *Simpan_Proses2(void *argv){
    system("mkdir /home/adam/Document/FolderProses2");
    system("ps -aux | head -n 10 > /home/adam/Document/FolderProses2/SimpanProses2.txt");
}
```

Agar dalam hal menyimpan 10 proses tadi ke dua file tersebut dilakukan bersamaan maka perlu diberi ```pthread_join```, syntaxnya seperti di bawah ini.
```
pthread_join(tid_ps1,NULL);
pthread_join(tid_ps2,NULL);
```

Setelah itu melakukan kompress terhadap masing-masing file menjadi zip dengan menggunakan syntax ```zip -r``` diikuti dengan nama file sekaligus letak file zip tersebut yaitu ```/home/adam/Document/FolderProses1/KompresProses1.zip```dan juga letak file hasil kompress tadi ```/home/adam/Document/FolderProses1``` kemudian ada -j agar yang di kompress ke dalam zip hanya file .txt saja. Kemudian file .txt yang telah ke kompress ke dalam zip masih ada file .txt lagi di luar zip, agar menghilangkan file tersebut maka perlu dihapus dengan menggunakan syntax ```-rm``` diikuti file yang akan dihapus dengan menggunakan absolute path yaitu ```/home/adam/Document/FolderProses1/SimpanProses1.txt");```. Jika yang di zip adalah SimpanProses2.txt maka cukup mengganti *1* dengan *2* di proses yang lain. Syntax keseluruhannya seperti di bawah ini.
```
pthread_create(&(tid_zip1), NULL, Proses_Zip1, NULL);
pthread_create(&(tid_zip2), NULL, Proses_Zip2, NULL);

void *Proses_Zip1(void *argv){
    system("zip -r /home/adam/Document/FolderProses1/KompresProses1.zip /home/adam/Document/FolderProses1 -j -rm /home/adam/Document/FolderProses1/SimpanProses1.txt");
}

void *Proses_Zip2(void *argv){
    system("zip -r /home/adam/Document/FolderProses2/KompresProses2.zip /home/adam/Document/FolderProses2 -j -rm /home/adam/Document/FolderProses2/SimpanProses2.txt");
}
```
Agar proses kompres dua file tadi ke dalam zip dilakukan berbarengan maka perlu menggunakan ```pthread_join``` setelah memanggil thread untuk melakukan kompres dua file tadi ke dalam zip.
```
pthread_join(tid_zip1,NULL);
pthread_join(tid_zip2,NULL);
```

Terakhir adalah melakukan ekstrak file yang telah di zip sebelumnya. Namun, sebelum itu ada jeda 15 detik. Untuk melakukan jeda tersebut digunakan syntax ```sleep(15);```. Setelah itu, baru dilakukan proses ekstrak dengan syntax ```unzip``` diikuti file zip yang akan di ekstrak, disini  kami menggunakan absolute path, kemudian diikuti dengan letak menyimpan file hasil ekstrak yaitu dengan menggunakan syntax ```-d``` diikuti file lokasi yang diinginkan. Seperti di bawah ini.
```
pthread_create(&(tid_unzip1), NULL, Proses_Unzip1, NULL);  
pthread_create(&(tid_unzip2), NULL, Proses_Unzip2, NULL);

void *Proses_Unzip1(void *argv){
    system("unzip /home/adam/Document/FolderProses1/KompresProses1.zip -d /home/adam/Document/FolderProses1");
}

void *Proses_Unzip2(void *argv){
    system("unzip /home/adam/Document/FolderProses2/KompresProses2.zip -d /home/adam/Document/FolderProses2");
}
```

Agar proses ekstrak dua file tadi dilakukan berbarengan maka perlu menggunakan ```pthread_join``` setelah memanggil thread untuk melakukan ekstrak dua file zip tadi. Syntaxnya seperti di bawah ini.
```
pthread_join(tid_unzip1,NULL);
pthread_join(tid_unzip2,NULL);
```

## Soal 5



