#include <SoftwareSerial.h>
#include <TinyGPS++.h>
SoftwareSerial GPRS(4, 5);
SoftwareSerial GPS(2,3);
TinyGPSPlus G;
#include <SPI.h>
#include <SD.h>
//#include "Timer.h"
//Timer t;
#define chipSelect 10
String sementara="";
String lati="";
String longi="";
void setup() {
  delay(5000);
  GPRS.begin(9600);
  GPS.begin(9600);
  Serial.begin(9600);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    digitalWrite(13,HIGH);
    // don't do anything more:
    return;
  }  
  Serial.println("Lewat");
  delay(10);
  GPRS.print("ATS0=3\r\n");
  delay(100);
  GPRS.print("AT+CMGF=1\r\n"); delay(1000);
  GPRS.print("AT+CNMI=2,2,0,0,0\r\n");
  delay(1000);
  sendSMS("+6285858938951", "Halo, ini pesan dari GPS TRACKER");
  //t.every(60000,tulis, (void*)2);
}

void loop() {
  //t.update();
  GPRS.listen();
  // put your main code here, to run repeatedly:
  while(GPRS.available()>0){
    String incoming=GPRS.readStringUntil('\n');
    incoming.trim();
    Serial.println("sms = "+incoming);
    if (incoming.startsWith("+CMT:")) {
      // Ekstrak nomor ponsel pengirim dari pesan SMS
      String senderNumber = extractPhoneNumber(incoming);
      sementara=senderNumber;
      // Tampilkan nomor ponsel pengirim
      Serial.println("Nomor Pengirim: " + senderNumber);
    }
    if(incoming.indexOf("LOKASI")>=0){ 
    // Turn on relay and save current state
    smartDelay(1000);
    
    String pesan="https://maps.google.com/?q="+lati+","+longi;
    sendSMS(sementara.c_str(), pesan.c_str());
    delay(100);
    GPRS.println("AT+CMGD=1,4");
    tulis();
    delay(1000);
  }
    if(incoming.indexOf("ON")>=0){ 
    sendSMS(sementara.c_str(), "Kendaraan dinyalakan");
    
    delay(100);
    GPRS.println("AT+CMGD=1,4");
  }
  if(incoming.indexOf("OFF")>=0){ 
    sendSMS(sementara.c_str(), "Kendaraan dimatikan");
    
    delay(100);
    GPRS.println("AT+CMGD=1,4");
  }
  }
  //smartDelay(1000);
}

void sendSMS(const char* phoneNumber, const char* message) {
  GPRS.println("AT+CMGF=1"); // Set mode teks untuk SMS
  delay(1000);

  GPRS.print("AT+CMGS=\"");
  GPRS.print(phoneNumber);
  GPRS.println("\"");
  delay(1000);

  GPRS.print(message);
  delay(1000);

  GPRS.write(26); // Mengirim karakter CTRL+Z untuk mengakhiri SMS
  delay(1000);

  Serial.println("SMS terkirim!");
}
String extractPhoneNumber(String sms) {
  // Cari posisi awal dan akhir nomor ponsel dalam pesan SMS
  int firstQuote = sms.indexOf('"') + 1;
  int secondQuote = sms.indexOf('"', firstQuote);

  // Ekstrak dan kembalikan nomor ponsel
  return sms.substring(firstQuote, secondQuote);
}
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    GPS.listen();
    delay(2);
    while (GPS.available())
      G.encode(GPS.read());
  } while (millis() - start < ms);
  lati=String(G.location.lat(),8);
  longi=String(G.location.lng(),6);
  Serial.println(lati);
  Serial.println(longi);
}
void tulis(){
  //smartDelay(1000);
  String data=lati+","+longi;
  writeFile("log.txt",data);
  Serial.println(data);
}
void writeFile(const char *filename, String data){
  File file=SD.open(filename,FILE_WRITE);
  if(file){
    
    file.println(data);
    file.close();
    Serial.println("Tersimpan");
  }
  else{
    Serial.println("Error");
  }
}
