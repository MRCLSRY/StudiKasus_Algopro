/*Nama : Marcelius Surya Wijaya
NIM : 2502001164*/
//Library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//struct
struct history{
    int tanggal;
    int bulan;
    int tahun;
    int nilai;
    char kreditdebit[7];
    char keterangan[20];
};

//Functiton declaration
void menu();
/*Fungsi untuk mengeprint halaman menu*/

void menambahkan();
/*Fungsi untuk menambahkan transaksi*/

void menampilkan();
/*Fungsi untuk membaca history transaksi yang sudah ditulis*/

void cari();
/*Fungsi untuk membaca history transaksi yang sudah ditulis*/

//File Processing
FILE *file;

//global Var.
int pilih;
int kredit;
int debit;

//NIM : 2502001164
//code
int main(){
    /*melakukan do...while dimana 
    looping minimal dijalankan 1x*/    
    do{
        //Menjalankan fungsi menu
        menu();
        //Menerima input pilih
        scanf("%d", &pilih);
        getchar();

        switch (pilih)
        {
        //jika input user = 1
        case 1:
            menambahkan();
            break;

        //jika input user = 2
        case 2:
            menampilkan();
            break;
        
        //jika input user = 3
        case 3:
            cari();
            break;
        }
    //dilakukan selama pilih tidak sama dengan 0
    }while (pilih != 0);
    return 0;
}

//NIM : 2502001164
//Menu
void menu(){
    //Mencetak menu program
    system("cls");
    printf("Buku Catatan Transaksi\n");
    printf("======================\n");
    printf("Menu : \n");
    printf("1. Tambah Transaksi\n");
    printf("2. Print Transaksi\n");
    printf("3. Cari Transaksi\n");
    printf("0. Exit\n");
    printf("Silahkan pilih : ");
}

//Add
void menambahkan(){
    system("cls");
    
    //Mendeclare struct
    struct history transaksi[1];

    //File Processing, append
    file = fopen ("transaksi.txt", "a");

    ubahTanggal:   //label nama untuk jumping statement.
    printf("Masukkan tanggal (dd-mm-yyyy) : ");
    //Input tanggal transaksi
    scanf("%d-%d-%d", &transaksi[0].tanggal,&transaksi[0].bulan,&transaksi[0].tahun);
    getchar();

    //Jika tanggal yang diinput melebihi 31 dan bulan melebihi 12
    if (transaksi[0].tanggal > 31 || transaksi[0].bulan > 12){
        printf("Masukkan tanggal dengan benar!\n");
        goto ubahTanggal;
    }

    //Input nama transaksi
    printf("Nama Transaksi : ");
    scanf("%[^\n]",transaksi[0].keterangan);
    getchar();
    
    //Input besar transaksi
    printf("Besar Transaksi : ");
    scanf("%d", &transaksi[0].nilai);
    getchar();

    //Input jenis transaksi
    printf("Kredit/Debit : ");
    scanf("%s",transaksi[0].kreditdebit);
    getchar();

    /*File Processing, melakukan print 
    sesuai format ke dalam file*/
    fprintf(file,"%d/%d/%d.%s#%d#%s\n",
    transaksi[0].tanggal,
    transaksi[0].bulan,
    transaksi[0].tahun,
    transaksi[0].keterangan,
    transaksi[0].nilai,
    transaksi[0].kreditdebit);

    fclose(file);
    printf("Press enter to continue\n");
    getchar();
}

//NIM : 2502001164
void menampilkan(){
    system("cls");

    //Mendeclare struct
    struct history transaksi[5000];
    struct history buffer;

    //Local variabel
    int banyakData = 0;

    //File Processing, read 
    file = fopen ("transaksi.txt", "r");

    //Jika file tidak tersedia
    if(file == NULL){
        printf("Error, Tidak ada data tersedia\n");
        printf("Press enter to continue\n");
        getchar();        
    }

    else{
        //Dilakukan hingga end of file transaksi.txt
        while (!feof(file))
        {
            /*File Processing, melakukan scan sesuai format
            lalu disimpan di dalam struct*/
            fscanf(file, "%d/%d/%d.%[^#]#%d#%[^\n]\n", 
            &transaksi[banyakData].tanggal,
            &transaksi[banyakData].bulan,
            &transaksi[banyakData].tahun,
            transaksi[banyakData].keterangan,
            &transaksi[banyakData].nilai,
            transaksi[banyakData].kreditdebit);

            //Menjumlahkan transaksi debit
            if (strcmp(transaksi[banyakData].kreditdebit, "Debit") == 0){
                debit += transaksi[banyakData].nilai;
            }

            //Menjumlahkan transaksi kredit
            else if(strcmp(transaksi[banyakData].kreditdebit, "Kredit") == 0){
                kredit += transaksi[banyakData].nilai;
            }
            banyakData++;
        }
    
        //Melakukan Sorting Data
        for (int data1 = 0; data1 < banyakData; data1++)
        {
            for (int data2 = 0; data2 < banyakData; data2++){
                //Jika tahun sama
                if(transaksi[data1].tahun == transaksi[data2].tahun){
                    //Jika tahun dan bulan sama
                    if(transaksi[data1].bulan == transaksi[data2].bulan){
                        if(transaksi[data1].tanggal < transaksi[data2].tanggal){
                            buffer = transaksi[data1];
                            transaksi[data1] = transaksi[data2];
                            transaksi[data2] = buffer;
                        } 
                    }
                    //Jika tahun sama dan bulan berbeda
                    else if(transaksi[data1].bulan < transaksi[data2].bulan){
                        buffer = transaksi[data1];
                        transaksi[data1] = transaksi[data2];
                        transaksi[data2] = buffer;
                    }
                }
                //Jika tahun berbeda
                else if(transaksi[data1].tahun < transaksi[data2].tahun){
                    buffer = transaksi[data1];
                    transaksi[data1] = transaksi[data2];
                    transaksi[data2] = buffer;
                }
            }
        }

        //Header
        printf("======================Buku Catatan Transaksi=======================\n");
        printf("===================================================================\n");
        printf("| No |    Nama Transaksi    |  Tanggal  | Jenis | Nilai Transaksi |\n");
        printf("===================================================================\n");
        //Melakukan output
        for (int j = 0; j < banyakData; j++){
            printf("|%-3d | %-20s |%-2d/%-2d/%-4d |%-6s | %-15d |\n",
            j+1,
            transaksi[j].keterangan,
            transaksi[j].tanggal,
            transaksi[j].bulan,
            transaksi[j].tahun,
            transaksi[j].kreditdebit,
            transaksi[j].nilai );
        }
        printf("===================================================================\n");
        printf("Total Debit :%d\n", debit);
        printf("Total Kredit :%d\n", kredit);

        //Jika debit dikurang kredit hasilnya minus
        if (debit-kredit < 0){
            printf("Selisih dari transaksi Kredit dan Debit :%d\n", kredit-debit);
        }
        else{
            printf("Selisih dari transaksi Debit dan Kredit :%d\n", debit-kredit);
        }

        fclose(file);

        printf("Press enter to continue\n");
        getchar();
    }
}

//NIM : 2502001164
void cari(){
    system("cls");

    //Mendeclare struct
    struct history transaksi[5000];

    //Local variabel
    int tanggal;
    int bulan;
    int tahun;
    int banyakData=0;

    //File Processing, read 
    file = fopen ("transaksi.txt", "r");
    
    //Jika file tidak tersedia
    if(file == NULL){
        printf("Error, Tidak ada data tersedia\n");     
    }

    else{
        //Input tanggal yang dicari
        printf("Masukkan tanggal yang ingin dicari : (dd-mm-yyyy)\n>>");
        scanf("%d-%d-%d", &tanggal, &bulan, &tahun);
        getchar();

        printf("Transaksi pada tanggal :%d/%d/%d :\n",tanggal,bulan,tahun);
        
        //Dilakukan hingga end of file transaksi.txt
        while (!feof(file))
        {
            fscanf(file, "%d/%d/%d.%[^#]#%d#%[^\n]\n", 
            &transaksi[banyakData].tanggal,
            &transaksi[banyakData].bulan,
            &transaksi[banyakData].tahun,
            transaksi[banyakData].keterangan,
            &transaksi[banyakData].nilai,
            transaksi[banyakData].kreditdebit);
            
            //Jika transaksi yang di scan sama dengan yang dicari
            if(transaksi[banyakData].tanggal == tanggal && transaksi[banyakData].bulan == bulan && transaksi[banyakData].tahun == tahun){
            printf("Transaksi %s, %s sebesar: %d\n",transaksi[banyakData].kreditdebit,transaksi[banyakData].keterangan,transaksi[banyakData].nilai);
            }
            banyakData++;
        }
    }
    fclose(file);
    printf("\nPress enter to continue\n");
    getchar();

}
//NIM : 2502001164