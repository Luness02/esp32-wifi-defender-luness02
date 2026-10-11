#include <WiFi.h>
#include "esp_wifi.h"

// --- AYARLAR ---
// Tespit edilen saldırı sayacını takip etmek için değişkenler
unsigned int attackCount = 0;
unsigned long lastWarningTime = 0;

void wifi_promiscuous_cb(void* buf, wifi_promiscuous_pkt_type_t type) {
  if (type == WIFI_PKT_MGMT) {
    wifi_promiscuous_pkt_t *pkt = (wifi_promiscuous_pkt_t *)buf;
    uint8_t *payload = pkt->payload;
    
    // 802.11 Yönetim Çerçevesi alt tipleri kontrolü
    // Frame Control alanının ilk baytı: Deauth (0xC0) veya Disassociation (0xA0)
    if (payload[0] == 0xC0 || payload[0] == 0xA0) {
      attackCount++;
      
      // Seri porta ve ekrana uyarı bas (Saniyede bir spam olmasın diye cooldown)
      if (millis() - lastWarningTime > 2000) {
        Serial.println("==========================================");
        Serial.println("[!] UYARI: Wi-Fi Deauth / Bağlantı Koparma Saldırısı Tespit Edildi!");
        Serial.printf("[!] Toplam Yakalanan Saldırı Paketi: %u\n", attackCount);
        Serial.println("==========================================");
        lastWarningTime = millis();
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("[*] ESP32 Wi-Fi Defender (Saldırı Tespit Sistemi) Başlatılıyor...");

  // Wi-Fi'ı istasyon modunda başlat ve promiscuous (havayı dinleme) modunu aç
  WiFi.mode(WIFI_STA);
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_promiscuous_rx_cb(&wifi_promiscuous_cb);

  // Kanalda taramaya başla (Kanal 1)
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);
  Serial.println("[+] Havayı dinleme modu aktif. Saldırı bekleniyor...");
}

void loop() {
  // Çevredeki kanallar arasında tur atarak saldırı taramasını genişlet
  for (int ch = 1; ch <= 13; ch++) {
    esp_wifi_set_channel(ch, WIFI_SECOND_CHAN_NONE);
    delay(300); // Her kanalda 300ms dinleme
  }
}