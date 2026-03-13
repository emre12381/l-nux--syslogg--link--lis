#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* TEKNIK ACIKLAMA (Video Sunumu Icin Notlar):
   1. Syslog Nedir?: Sistem olaylarinin kronolojik kaydidir.
   2. Neden Bagli Liste?: Log sayisi belirsizdir, dinamik bellek yonetimi gerekir.
   3. Neden Cift Yonlu (Doubly)?: En son hataya (tail) hizli erismek ve 
      loglar arasinda ileri-geri kolayca gezinebilmek icin.
*/

typedef struct LogNode {
    int logID;
    char timestamp[30];
    char level[15];
    char message[200];
    struct LogNode* next;
    struct LogNode* prev;
} LogNode;

LogNode* head = NULL;
LogNode* tail = NULL;
int globalLogCounter = 1;

// Fonksiyon: Yeni bir Syslog kaydi olusturur ve listenin sonuna ekler.
void logEkle(const char* level, const char* msg) {
    LogNode* yeniLog = (LogNode*)malloc(sizeof(LogNode));
    if (yeniLog == NULL) return;

    yeniLog->logID = globalLogCounter++;
    strcpy(yeniLog->level, level);
    strcpy(yeniLog->message, msg);

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(yeniLog->timestamp, 30, "%Y-%m-%d %H:%M:%S", tm_info);

    yeniLog->next = NULL;

    if (head == NULL) {
        yeniLog->prev = NULL;
        head = yeniLog;
        tail = yeniLog;
    } else {
        yeniLog->prev = tail;
        tail->next = yeniLog;
        tail = yeniLog;
    }
}

void loglariListele() {
    LogNode* temp = head;
    printf("\n>>> SISTEM GUNLUKLERI (ESKIDEN YENIYE) <<<\n");
    printf("--------------------------------------------------\n");
    if (temp == NULL) printf("Liste bos!\n");
    while (temp != NULL) {
        printf("[%s] ID:%d | %-8s | %s\n", temp->timestamp, temp->logID, temp->level, temp->message);
        temp = temp->next;
    }
}

void loglariTersListele() {
    LogNode* temp = tail;
    printf("\n>>> SISTEM GUNLUKLERI (SONDAN BASA / EN YENILER) <<<\n");
    printf("--------------------------------------------------\n");
    while (temp != NULL) {
        printf("[%s] ID:%d | %-8s | %s\n", temp->timestamp, temp->logID, temp->level, temp->message);
        temp = temp->prev;
    }
}

int main() {
    // 1. Ornek Verilerin Girilmesi
    logEkle("INFO", "Cekirdek (Kernel) yuklendi.");
    logEkle("WARNING", "Islemci sicakligi yukseldi: 75C");
    logEkle("ERROR", "Disk yazma hatasi olustu (Sector 0x45).");
    logEkle("INFO", "Aga baglanildi: eth0 aktif.");

    // 2. Fonksiyonlarin Cagrilmasi
    loglariListele();
    loglariTersListele();

    printf("\n--------------------------------------------------\n");
    printf("ANALIZ TAMAMLANDI.\n");
    
    // 3. BELLEK TEMIZLEME
    LogNode* current = head;
    while (current != NULL) {
        LogNode* next = current->next;
        free(current);
        current = next;
    }

    // 4. EKRANI DURDURMA (Dev-C++ kapanmamasi icin kritik kisim)
    printf("\nProgram sonlandi. Cikmak icin ENTER tusuna basin...");
    
    fflush(stdin); // Giris tamponunu temizle
    getchar();     // Bir karakter bekler, ekran boylece kapanmaz
    
    return 0;
}
