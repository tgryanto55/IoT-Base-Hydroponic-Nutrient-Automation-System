#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleESP32.h>
#include <HTTPClient.h>

#define BLYNK_TEMPLATE_ID "TMPL6T3veYVj1"
#define BLYNK_TEMPLATE_NAME "IoT hydroponic system"
#define BLYNK_AUTH_TOKEN "8gZna1PktNqockZ15gnFvf7TS2BsHkw1"

#define TDS_PIN 32
#define PH_PIN 34
#define RELAY_PUPUK_A 4
#define RELAY_PUPUK_B 2
#define RELAY_AIR_BERSIH 15
#define RELAY_TDS_POWER 16

char ssid[] = ""; // SSID
char pass[] = ""; // PASdWORD

const char* GAS_URL = ""; // put the google script URL here

BlynkTimer timer;
unsigned long idleStart = 0;
bool idle = false;
int mainTimerID;
unsigned long lastNotifTime = 0;
const unsigned long notifInterval = 10000;

void relayWrite(int pin, bool on) {
digitalWrite(pin, on ? LOW : HIGH);
}

void kirimKeGoogleSheets(float tds, float ph) {
if (WiFi.status() == WL_CONNECTED) {
HTTPClient http;
String url = String(GAS_URL) + "?tds=" + String(tds, 2) + "&ph=" + String(ph, 2);
http.begin(url);
int httpCode = http.GET();
if (httpCode > 0) {
Serial.println("✅ Data terkirim ke Google Sheets");
} else {
Serial.println("❌ Gagal kirim ke Google Sheets. Kode: " + String(httpCode));
}
http.end();
} else {
Serial.println("❌ Tidak terkoneksi ke WiFi!");
}
}

float bacaTDS() {
relayWrite(RELAY_TDS_POWER, true);
delay(5000);
int raw = analogRead(TDS_PIN);
float voltage = raw * (3.3 / 4095.0);
float tds = (133.42 * voltage * voltage * voltage - 255.86 * voltage * voltage + 857.39 * voltage) * 0.5;
relayWrite(RELAY_TDS_POWER, false);
if (raw < 100) {
Serial.println("⚠️ Sensor TDS belum terhubung atau belum terendam air!");
Blynk.logEvent("tds_invalid", "⚠️ Sensor TDS tidak valid atau belum terhubung!");
tds = 0.0;
}
Serial.printf("TDS: %.2f ppm\n", tds);
Blynk.virtualWrite(V1, tds);
return tds;
}

float bacaPH() {
float totalPH = 0;
for (int i = 0; i < 10; i++) {
int adc = analogRead(PH_PIN);
float voltage = adc * (3.3 / 4095.0);
float ph = -4.933 * voltage + 19.536;
totalPH += ph;
delay(50);
}
float avgPH = totalPH / 10.0;
Serial.printf("pH: %.2f\n", avgPH);
Blynk.virtualWrite(V0, avgPH);
return avgPH;
}

void cekNutrisiDanPH() {
if (idle && millis() - idleStart < 600000) return;
idle = false;
float tds = bacaTDS();
bool sensorTdsValid = tds > 0.0;
delay(5000);
float ph = bacaPH();
kirimKeGoogleSheets(tds, ph);
if (sensorTdsValid) {
if (tds < 560) {
relayWrite(RELAY_PUPUK_A, true); delay(2000);
relayWrite(RELAY_PUPUK_A, false);
delay(5000);
relayWrite(RELAY_PUPUK_B, true); delay(2000);
relayWrite(RELAY_PUPUK_B, false);
} else if (tds > 840) {
relayWrite(RELAY_AIR_BERSIH, true); delay(5000);
relayWrite(RELAY_AIR_BERSIH, false);
}
} else {
Serial.println("⏸️ Kontrol pompa dilewati karena TDS tidak valid.");
}
unsigned long now = millis();
if (ph < 5.5 || ph > 6.5) {
String pesan = (ph < 5.5) ? "⚠️ pH terlalu rendah: " + String(ph, 2) : "⚠️ pH terlalu tinggi: " + String(ph, 2);
if (now - lastNotifTime >= notifInterval) {
Blynk.logEvent("ph_alert", pesan);
lastNotifTime = now;
}
timer.changeInterval(mainTimerID, 10000L);
idle = false;
} else {
lastNotifTime = 0;
if (!idle) {
idle = true;
idleStart = millis();
Blynk.logEvent("idle_mode", "✅ Sistem masuk mode idle (pH & TDS ideal)");
timer.changeInterval(mainTimerID, 600000L);
}
}
}

BLYNK_WRITE(V2) {
if (param.asInt() == 1) {
Serial.println("Tombol V2 ditekan: Nutrisi AB Manual");
relayWrite(RELAY_PUPUK_A, true); delay(2000);
relayWrite(RELAY_PUPUK_A, false);
delay(5000);
relayWrite(RELAY_PUPUK_B, true); delay(2000);
relayWrite(RELAY_PUPUK_B, false);
}
}

BLYNK_WRITE(V3) {
if (param.asInt() == 1) {
Serial.println("Tombol V3 ditekan: Air Bersih Manual");
relayWrite(RELAY_AIR_BERSIH, true); delay(5000);
relayWrite(RELAY_AIR_BERSIH, false);
}
}

void setup() {
Serial.begin(115200);
Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
pinMode(RELAY_PUPUK_A, OUTPUT);
pinMode(RELAY_PUPUK_B, OUTPUT);
pinMode(RELAY_AIR_BERSIH, OUTPUT);
pinMode(RELAY_TDS_POWER, OUTPUT);
relayWrite(RELAY_PUPUK_A, false);
relayWrite(RELAY_PUPUK_B, false);
relayWrite(RELAY_AIR_BERSIH, false);
relayWrite(RELAY_TDS_POWER, false);
mainTimerID = timer.setInterval(10000L, cekNutrisiDanPH);
}

void loop() {
Blynk.run();
timer.run();
}

