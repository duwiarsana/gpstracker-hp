# GPS GPRS SMS Tracker - Arduino Code

Dokumentasi ini menjelaskan bagaimana menggunakan koding dalam folder ini untuk proyek **GPS GPRS SMS Tracker**. Koding ini dirancang untuk bekerja dengan **modul GPS dan GSM (GPRS) secara terpisah**, serta dibuat khusus untuk PCB yang sudah dirancang dalam proyek ini.

## 📌 Persyaratan Software

Untuk menjalankan koding ini, kamu memerlukan software berikut:

1. **[Arduino IDE](https://www.arduino.cc/en/software)** - Untuk mengedit dan mengupload kode ke mikrokontroler.
2. **Driver CH340/CP2102** (jika menggunakan Arduino clone) - Sesuaikan dengan jenis mikrokontroler yang digunakan.
3. **Library Arduino yang dibutuhkan**:
   - [TinyGPS++](https://github.com/mikalhart/TinyGPSPlus) → Untuk membaca data GPS.
   - SoftwareSerial (bawaan Arduino) → Untuk komunikasi serial dengan modul GSM & GPS.

## ⚙️ Cara Menggunakan Koding Ini

1. **Buka Arduino IDE** dan pastikan board yang digunakan sudah terdeteksi.
2. **Instal Library yang Dibutuhkan**
   - Buka **Sketch** > **Include Library** > **Manage Libraries**
   - Cari dan instal **TinyGPS++**
3. **Hubungkan Arduino ke PC** menggunakan kabel USB.
4. **Sesuaikan Koneksi Hardware** jika tidak menggunakan PCB custom (lihat tabel koneksi di README utama).
5. **Upload kode ke Arduino**:
   - Pilih board yang sesuai (**Tools > Board > Arduino Uno/Nano/etc**).
   - Pilih port serial yang sesuai (**Tools > Port > COMx**).
   - Klik tombol **Upload** (ikon panah kanan di Arduino IDE).
6. **Buka Serial Monitor** (Baudrate 9600) untuk melihat log proses komunikasi.
7. **Uji dengan SMS**
   - Kirim SMS berisi **"LOKASI"** ke nomor kartu SIM yang ada di modul GSM.
   - Jika berhasil, akan menerima SMS balasan berupa link Google Maps.
8. **Uji dengan Panggilan**
   - Lakukan panggilan ke nomor SIM dalam modul GSM.
   - Perangkat akan **mengangkat otomatis pada dering ketiga**.

## 🔥 Troubleshooting

- **GPS tidak mendapatkan sinyal?**
  - Pastikan antena GPS terpasang dengan benar.
  - Coba uji di area terbuka untuk mendapatkan sinyal lebih cepat.

- **GSM tidak mengirim atau menerima SMS?**
  - Cek apakah kartu SIM memiliki pulsa atau paket SMS aktif.
  - Pastikan koneksi antara Arduino dan modul GSM sudah benar.

- **Tidak bisa upload kode?**
  - Cek apakah driver CH340/CP2102 sudah terinstal.
  - Coba gunakan kabel USB yang berbeda.

## 📜 Lisensi

Kode ini menggunakan lisensi MIT, artinya bebas digunakan dan dimodifikasi. Jika kamu ingin menggunakan atau mengembangkan proyek ini lebih lanjut, silakan!

🚀 Selamat mencoba!

