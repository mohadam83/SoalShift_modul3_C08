# SoalShift_modul3_C08

## Soal 1

## Soal 2

## Soal 3

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



