#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//KELOMPOK 3 TEMA HOTEL
// ANGGOTA :
// 1. Oliver Elvino Putra Pratama / 672022030
// 2. Marcellinus Ronan Narendra / 672022123
// 3. Benedictus Lanang Ido H. / 672022129
// 4. Cessa Christian Eka J. / 672022059

//Koordinat untuk menengahkan data
void gotoxy(int x, int y)
{
    COORD coord = {X:0, Y:0};
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

struct hotel
{
    int nomorKamar;
    char jenisKamar[20];
    int hargaKamar;
    int statusKamar;
    struct hotel *next;
};

typedef struct hotel Hotel;

//Fungsi untuk membuat data
Hotel *buatData(int nomorKamar, char jenisKamar[], int hargaKamar, int statusKamar)
{
    Hotel *newNode = (Hotel*)malloc(sizeof(Hotel));
    newNode->nomorKamar = nomorKamar;
    strcpy(newNode->jenisKamar, jenisKamar);
    newNode->hargaKamar = hargaKamar;
    newNode->statusKamar = statusKamar;
    newNode->next = NULL;
    return newNode;
}

//Fungsi uhtuk menambah data
void tambahData(Hotel **headRef, int nomorKamar, char jenisKamar[], int hargaKamar, int statusKamar)
{
    Hotel *newNode = buatData(nomorKamar, jenisKamar, hargaKamar, statusKamar);
    if (*headRef == NULL)
    {
        *headRef = newNode;
    }
    else
    {
        Hotel *temp = *headRef;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;

    }
}

//Fungsi untuk menampilkan data
void tampilkanData(Hotel* head)
{
    printf("=================================================================\n");
    printf("| Nomor Kamar |    Jenis Kamar     | Harga Kamar | Status Kamar |\n");
    printf("=================================================================\n");
    Hotel *temp = head;
    while (temp != NULL)
    {
        printf("| %11d | %18s | %11d | %12d |\n", temp->nomorKamar, temp->jenisKamar, temp->hargaKamar, temp->statusKamar);
        temp = temp->next;
    }
    printf("====================================================================\n");
}

//Fungsi untuk mengubah data
void ubahData(Hotel **headRef, int nomorKamar, char jenisKamar[], int hargaKamar, int statusKamar)
{
    Hotel *temp = *headRef;
    while (temp != NULL)
    {
        if (temp->nomorKamar == nomorKamar)
        {
            strcpy(temp->jenisKamar, jenisKamar);
            temp->hargaKamar = hargaKamar;
            temp->statusKamar = statusKamar;
        }
        temp = temp->next;
    }
}

//Fungsi untuk hapus data
void hapusData(Hotel **headRef, int nomorKamar)
{
    Hotel *current = *headRef;
    Hotel *previous = NULL;
    if (current != NULL && current->nomorKamar == nomorKamar)
    {
        *headRef = current->next;
        free(current);
        printf("\nData berhasil dihapus");
        return;
    }
    while (current != NULL && current->nomorKamar != nomorKamar)
    {
        previous = current;
        current = current->next;
    }
    if (current == NULL)
    {
        printf("Data nomor kamar tidak ditemukan\n");
        return;
    }
    previous->next = current->next;
    free(current);
}

//Fungsi untuk searcing data
Hotel *cariData(Hotel *head, int nomorKamar)
{
    Hotel *current = head;
    while (current != NULL)
    {
        if (current->nomorKamar == nomorKamar)
        {
            return current;
        }
        current = current->next;
    }
}

//Fungsi untuk menulis data ke file
void simpanFile(Hotel *head)
{
    FILE *file;
    file = fopen("hotel.txt", "w");
    Hotel *current = head;
    while (current != NULL)
    {
        fprintf(file, "%d %s %d %d\n", current->nomorKamar, current->jenisKamar, current->hargaKamar, current->statusKamar);
        current = current->next;
    }
    fclose(file);
    gotoxy(46,18);
    printf("Data berhasil disimpan ke file");
}

//Fungsi untuk membaca data dari file
void bacaFile(Hotel **headRef)
{
    FILE *file;
    file = fopen("hotel.txt", "r");
    if (file == NULL)
    {
        gotoxy(46,18);
        printf("File tidak ditemukan\n");
        return;
    }
    int nomorKamar, hargaKamar, statusKamar;
    char jenisKamar[20];
    while (fscanf(file, "%d %s %d %d", &nomorKamar, jenisKamar, &hargaKamar, &statusKamar)!=EOF)
    {
        tambahData(headRef, nomorKamar, jenisKamar, hargaKamar, statusKamar);
    }
    fclose(file);
    gotoxy(46,18);
    printf("Data berhasil dibaca");
}

//Fungsi untuk sorting
void sortingBubble(Hotel *head)
{
    int swapped;
    Hotel *current;
    Hotel *previous = NULL;

    if (head == NULL)
        return;

    do
    {
        swapped = 0;
        current = head;

        while (current->next != previous)
        {
            if (current->hargaKamar > current->next->hargaKamar)
            {
                Hotel temp;
                strcpy(temp.jenisKamar, current->jenisKamar);
                temp.nomorKamar = current->nomorKamar;
                temp.hargaKamar = current->hargaKamar;
                temp.statusKamar = current->statusKamar;
                strcpy(current->jenisKamar, current->next->jenisKamar);
                current->nomorKamar = current->next->nomorKamar;
                current->hargaKamar = current->next->hargaKamar;
                current->statusKamar = current->next->statusKamar;
                strcpy(current->next->jenisKamar, temp.jenisKamar);
                current->next->nomorKamar = temp.nomorKamar;
                current->next->hargaKamar = temp.hargaKamar;
                current->next->statusKamar = temp.statusKamar;
                swapped = 1;
            }
            current = current->next;
        }
        previous = current;
    } while (swapped);
}

//Fungsi untuk login
int Login()
{
    char username[20],pass[20],ch,a,verified;
    int i=0;
    system("cls");
    gotoxy(40,4);
    printf("*************************\n");
    gotoxy(48,5);
    printf("L O G I N\n");
    gotoxy(40,6);
    printf("*************************");
    gotoxy(40,8);
    printf("Username :");
    gets(username);
    gotoxy(40,10);
    printf("Password :");
    while((ch = getch())!=13)
    {
        if(ch == 8)
        {
            if(i>0)
            {
                printf("\b \b");
                pass[i-1];
                i--;
            }
            else
            {
                printf("");
            }
        }
        else
        {
            pass[i]=ch;
            i++;
            printf("*");
        }
    }
    pass[i]='\0';
    if(strcmp(username,"fti")== 0 && strcmp(pass,"fti") == 0)
    {
        return 1;
    }
    else
    {
        gotoxy(40,12);
        printf("EROR!");
        gotoxy(40,13);
        printf("Username dan Password salah\n");
        getch();
        if(a == 2)
        {
            gotoxy(40,15);
            printf("Maaf anda sudah memasukan username dan password sebanyak 3 kali!\n");
            getch();
            exit(0);
        }
        else
        {
            a++;
            i=0;
            return 0;
        }
    }
}


int main()
{
    Hotel *head = NULL;
    int pilihan, nomorKamar, hargaKamar, statusKamar,verified;
    char jenisKamar[20];

    system("color E0");
    gotoxy(50,3);
    printf("SABAR CUYYY....\n");
    gotoxy(40,5);
    for(int i=0; i<32; i++)
    {
        printf("%c",219);
        Sleep(100);
    }
    gotoxy(51,7);
    printf("KUYY LAH!");
    getch();

    while(verified == 0)
    {
        verified=Login();
    }

    do
    {
        system("color E0");
        system("cls");
        gotoxy(45,5);
        printf(" ===============================");
        gotoxy(45,6);
        printf(" |             MENU            |\n");
        gotoxy(45,7);
        printf(" ===============================");
        gotoxy(45,8);
        printf(" |1. Tampilkan data            |\n");
        gotoxy(45,9);
        printf(" |2. Tambah data               |\n");
        gotoxy(46,10);
        printf("|3. Ubah data                 |\n");
        gotoxy(46,11);
        printf("|4. Hapus data                |\n");
        gotoxy(46,12);
        printf("|5. Cari data                 |\n");
        gotoxy(46,13);
        printf("|6. Simpan file               |\n");
        gotoxy(46,14);
        printf("|7. Baca file                 |\n");
        gotoxy(46,15);
        printf("|8. Keluar                    |\n");
        gotoxy(46,16);
        printf("===============================");
        gotoxy(46,17);
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &pilihan);
        switch(pilihan)
        {
        case 1:
            system("cls");
            sortingBubble(head);
            tampilkanData(head);
            getch();
            break;
        case 2:
            system("cls");
            printf("Masukkan nomor kamar: ");
            scanf("%d", &nomorKamar);
            printf("Masukkan jenis kamar: ");
            scanf("%s", jenisKamar);
            printf("Masukkan harga kamar: ");
            scanf("%d", &hargaKamar);
            printf("Masukkan status kamar (0 untuk kosong, 1 untuk terisi): ");
            scanf("%d", &statusKamar);
            tambahData(&head, nomorKamar, jenisKamar, hargaKamar, statusKamar);
            break;
        case 3:
            system("cls");
            printf("Masukkan nomor kamar yang ingin diubah: ");
            scanf("%d", &nomorKamar);
            Hotel *foundData = cariData(head, nomorKamar);
            if (foundData == NULL)
            {
                printf("Data tidak ditemukan\n");
            }
            else
            {
                printf("Data ditemukan : | %d | %s | %d | %d |\n", foundData->nomorKamar, foundData->jenisKamar, foundData->hargaKamar, foundData->statusKamar);
                printf("Masukan nomor kamar baru: ");
                scanf("%d", &foundData->nomorKamar);
                printf("Masukkan jenis kamar baru: ");
                scanf("%s", foundData->jenisKamar);
                printf("Masukkan harga kamar baru: ");
                scanf("%d", &foundData->hargaKamar);
                printf("Masukkan status kamar baru (0 untuk kosong, 1 untuk terisi): ");
                scanf("%d", &foundData->statusKamar);
            }
            printf("\nData berhasil diubah");
            getch();
            break;
        case 4:
            system("cls");
            printf("Masukkan nomor kamar yang ingin dihapus: ");
            scanf("%d", &nomorKamar);
            hapusData(&head, nomorKamar);
            getch();
            break;
        case 5:
            system("cls");
            printf("Masukkan nomor kamar yang ingin dicari: ");
            scanf("%d", &nomorKamar);
            Hotel *searchData = cariData(head, nomorKamar);
            if (searchData == NULL)
            {
                printf("Data tidak ditemukan.\n");
            }
            else
            {
                printf("Data ditemukan: | %d | %s | %d | %d |\n", searchData->nomorKamar, searchData->jenisKamar, searchData->hargaKamar, searchData->statusKamar);
            }
            getch();
            break;
        case 6:
            simpanFile(head);
            getch();
            break;
        case 7:
            bacaFile(&head);
            getch();
            break;
        case 8:
            gotoxy(46,18);
            printf("Tengkyuu bangg.......");
            break;
        default:
            gotoxy(46,19);
            printf("Input tidak dikenali!");
            getch();
            break;
        }
    }
    while (pilihan != 8);
    return 0;
}
