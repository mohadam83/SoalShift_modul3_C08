# SoalShift_modul3_C08

## Soal 1

## Soal 2
Untuk menyelesai

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



