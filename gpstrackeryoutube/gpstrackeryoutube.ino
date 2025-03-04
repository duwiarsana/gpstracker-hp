#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Deklarasi komunikasi serial untuk GPRS dan GPS
SoftwareSerial GPRS(5, 4);
SoftwareSerial GPS(3, 2);
TinyGPSPlus G;

// Variabel untuk menyimpan data sementara
String sementara = "";
String lati = "";
String longi = "";

void setup() {
  delay(5000); // Delay awal untuk memastikan perangkat siap
  
  // Memulai komunikasi serial dengan modul GPRS dan GPS
  GPRS.begin(9600);
  GPS.begin(9600);
  Serial.begin(9600);

  Serial.println("Lewat");
  delay(10);
  
  // Mengatur parameter GPRS
  GPRS.print("ATS0=3\r\n");
  delay(100);
  GPRS.print("AT+CMGF=1\r\n"); // Mengatur mode teks untuk SMS
  delay(1000);
  GPRS.print("AT+CNMI=2,2,0,0,0\r\n"); // Mengatur notifikasi pesan masuk
  delay(1000);
}

void loop() {
  GPRS.listen(); // Mengaktifkan komunikasi dengan GPRS
  
  while (GPRS.available() > 0) {
    String incoming = GPRS.readStringUntil('\n'); // Membaca pesan dari GPRS
    incoming.trim();
    Serial.println("sms = " + incoming);
    
    // Mengekstrak nomor pengirim jika ada pesan masuk
    if (incoming.startsWith("+CMT:")) {
      String senderNumber = extractPhoneNumber(incoming);
      sementara = senderNumber;
      Serial.println("Nomor Pengirim: " + senderNumber);
    }
    
    // Jika pesan mengandung kata "LOKASI", kirim koordinat GPS
    if (incoming.indexOf("LOKASI") >= 0) {
      smartDelay(5000); // Mengambil data GPS terbaru
      
      String pesan = "https://maps.google.com/?q=" + lati + "," + longi;
      sendSMS(sementara.c_str(), pesan.c_str()); // Mengirim SMS dengan lokasi
      delay(100);
      GPRS.println("AT+CMGD=1,4"); // Menghapus semua SMS di modul GPRS
      delay(1000);
    }
  }
}

// Fungsi untuk mengirim SMS
void sendSMS(const char* phoneNumber, const char* message) {
  GPRS.println("AT+CMGF=1"); // Mengatur SMS ke mode teks
  delay(2000);

  GPRS.print("AT+CMGS=\"");
  GPRS.print(phoneNumber);
  GPRS.println("\"");
  delay(1000);

  GPRS.print(message);
  delay(1000);

  GPRS.write(26); // Mengirim karakter CTRL+Z untuk mengakhiri SMS
  delay(5000);

  Serial.println(message);
}

// Fungsi untuk mengekstrak nomor telepon dari pesan SMS
String extractPhoneNumber(String sms) {
  int firstQuote = sms.indexOf('"') + 1;
  int secondQuote = sms.indexOf('"', firstQuote);
  return sms.substring(firstQuote, secondQuote);
}

// Fungsi untuk menunggu dan membaca data GPS dalam waktu tertentu
static void smartDelay(unsigned long ms) {
  unsigned long start = millis();
  do {
    GPS.listen();
    delay(2);
    while (GPS.available()) {
      G.encode(GPS.read());
    }
  } while (millis() - start < ms);
  
  lati = String(G.location.lat(), 8); // Mengambil data latitude
  longi = String(G.location.lng(), 6); // Mengambil data longitude
  
  Serial.println(lati);
  Serial.println(longi);
}
