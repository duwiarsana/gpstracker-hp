# GPS GPRS SMS Tracker

Proyek ini menggunakan **modul GPS dan GPRS (GSM)** secara terpisah untuk mengirimkan koordinat lokasi via SMS ketika menerima perintah dari pengguna. Koding ini dibuat khusus untuk PCB yang sudah dicetak dalam proyek ini.

## 📌 Deskripsi Proyek

Kode ini bekerja dengan membaca data dari modul **GPS** dan mengirimkan koordinat melalui **modul GPRS (GSM)** dalam bentuk link Google Maps. Saat perangkat menerima SMS dengan kata kunci **"LOKASI"**, maka akan membalas dengan tautan lokasi GPS terbaru.

## 🛠️ Hardware yang Digunakan

- **Mikrokontroler**: Arduino (contoh: Arduino Uno, Nano, atau lainnya)
- **Modul GPS**: Neo-6M atau kompatibel
- **Modul GSM/GPRS**: SIM800L atau SIM900
- **PCB Custom**: Koding ini dibuat untuk PCB khusus yang sudah dirancang agar sesuai dengan proyek ini
- **Kartu SIM** dengan pulsa untuk mengirim SMS

## 🖇️ **Koneksi Hardware** (Jika Menggunakan Arduino dengan Modul GPS & GSM Terpisah)

Jika kamu menggunakan Arduino tanpa PCB khusus, pastikan koneksi berikut:

### **Modul GPS (Neo-6M)**

| GPS Pin | Arduino Pin |
| ------- | ----------- |
| VCC     | 5V          |
| GND     | GND         |
| TX      | D3          |
| RX      | D2          |

### **Modul GSM (SIM800L/SIM900)**

| GSM Pin | Arduino Pin                            |
| ------- | -------------------------------------- |
| VCC     | 5V (Gunakan regulator 4.2V jika perlu) |
| GND     | GND                                    |
| TX      | D5                                     |
| RX      | D4                                     |

> **Catatan:** Jika menggunakan PCB khusus yang sudah dicetak, koneksi sudah diatur secara langsung dalam desain PCB, jadi tidak perlu kabel tambahan.

## 🔧 Library yang Digunakan

Sebelum meng-compile kode, pastikan kamu sudah menginstal library berikut di **Arduino IDE**:

- **[TinyGPS++](https://github.com/mikalhart/TinyGPSPlus)** → Untuk membaca data dari GPS
- **SoftwareSerial** (bawaan Arduino) → Untuk komunikasi serial dengan modul GSM & GPS

## ⚙️ Cara Kerja

1. **Perangkat menyala** dan mulai membaca data GPS.
2. Saat menerima SMS dengan isi **"LOKASI"**, perangkat akan mengambil data koordinat dari GPS.
3. Data latitude dan longitude akan diubah menjadi link Google Maps.
4. SMS akan dikirim kembali ke pengirim dengan format:
   ```
   https://maps.google.com/?q=latitude,longitude
   ```
5. Nomor pengirim SMS akan disimpan sementara untuk membalas otomatis.
6. Setelah mengirim SMS, perangkat menghapus pesan yang diterima agar memori tidak penuh.

## 📌 Cara Menggunakan

1. **Siapkan PCB yang sudah dirakit** dengan Arduino dan modul GPS/GSM.
2. **Masukkan kartu SIM ke modul GSM** (pastikan memiliki pulsa atau paket SMS).
3. **Upload kode ke Arduino** menggunakan Arduino IDE.
4. **Kirim SMS berisi "LOKASI"** ke nomor yang ada di modul GSM.
5. **Perangkat akan membalas dengan link lokasi** berdasarkan data dari modul GPS.

## 🔥 Troubleshooting

Jika tidak mendapatkan SMS balasan atau koordinat tidak muncul:

- **Cek power supply modul GSM** (SIM800L biasanya butuh minimal 2A agar stabil).
- **Pastikan modul GPS mendapatkan sinyal satelit** (gunakan di luar ruangan untuk tes awal).
- **Gunakan serial monitor** di Arduino IDE untuk melihat output debug.

## 📜 Lisensi

Proyek ini menggunakan lisensi MIT, yang berarti bebas digunakan, dimodifikasi, dan didistribusikan.

---

🚀 Selamat mencoba! Jika ada pertanyaan atau ingin menggunakan PCB khusus ini, silakan hubungi saya.

