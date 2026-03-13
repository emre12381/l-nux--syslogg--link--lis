# l-nux--syslogg--link--lis
linux ödev# Linux Syslog Management with Doubly Linked List

Bu proje, Linux sistem günlüklerinin (Syslog) dinamik bir veri yapısı olan **Çift Yönlü Bağlı Liste** kullanılarak yönetilmesini simüle eder.

## 🛠 Kullanılan Teknolojiler
* Dil: C
* Veri Yapısı: Doubly Linked List (Çift Yönlü Bağlı Liste)
* Ortam: Dev-C++ / GCC

## 🚀 Çalıştırma
1. `main.c` dosyasını indirin.
2. Dev-C++ veya herhangi bir C derleyicisi ile açın.
3. `F11` tuşuna basarak derleyin ve çalıştırın.

## 📌 Teknik Özellikler
* **Dinamik Bellek:** Loglar çalışma zamanında `malloc` ile oluşturulur.
* **Zaman Damgası:** `time.h` kütüphanesi ile loglara gerçek zamanlı tarih eklenir.
* **Çift Yönlü Erişim:** Loglar hem ileriye hem geriye doğru taranabilir.

## 📂 Proje Yapısı
* `LogNode`: Veri yapısı şablonu.
* `logEkle()`: Yeni günlük ekleme fonksiyonu.
* `loglariListele()`: Kronolojik listeleme.
* `loglariTersListele()`: Tersten (en yeni) listeleme.
