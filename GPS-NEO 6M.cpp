#include <TinyGPS++.h>

// Defina os pinos RX e TX para o GPS
#define RXD2 17  // Pino TX do GPS -> RX2 do ESP32
#define TXD2 16  // Pino RX do GPS -> TX2 do ESP32

#define GPS_BAUD 9600

// O objeto TinyGPS++
TinyGPSPlus gps;

// Cria uma instância da classe HardwareSerial para Serial2
HardwareSerial gpsSerial(2);

void setup() {
  // Monitor Serial
  Serial.begin(115200);
  
  // Inicia o Serial2 com os pinos RXD2 e TXD2 e a taxa de 9600 bps
  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial 2 started at 9600 baud rate");
}

void loop() {
  // Exibe as informações do GPS sempre que houver dados atualizados
  unsigned long start = millis();

  while (millis() - start < 1000) {
    while (gpsSerial.available() > 0) {
      gps.encode(gpsSerial.read());
    }
    if (gps.location.isUpdated()) {
      Serial.print("LAT: ");
      Serial.println(gps.location.lat(), 6);
      Serial.print("LONG: "); 
      Serial.println(gps.location.lng(), 6);
      Serial.print("Velocidade (km/h) = "); 
      Serial.println(gps.speed.kmph()); 
      Serial.print("ALT (m)= "); 
      Serial.println(gps.altitude.meters());
      Serial.print("HDOP = "); 
      Serial.println(gps.hdop.value() / 100.0); 
      Serial.print("Satellites = "); 
      Serial.println(gps.satellites.value()); 
      Serial.print("Time em UTC: ");
      Serial.println(String(gps.date.year()) + "/" + String(gps.date.month()) + "/" + String(gps.date.day()) + "," + String(gps.time.hour()) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second()));
      Serial.println("");
    }
  }
}
