# ESP32 Wi-Fi Defender (esp32-wifi-defender-luness02)

Bu proje, çevredeki kablosuz ağlara yönelik gerçekleştirilen **Deauthentication (bağlantı koparma)** ve gözetleme saldırılarını havada eşzamanlı olarak tespit edip raporlayan bir karşı-casusluk (counter-surveillance) ve savunma aracıdır.

## Özellikler
- **Promiscuous Mod Dinlemesi:** ESP32 çipinin düşük seviyeli paket yakalama yeteneğini kullanarak havadaki yönetim paketlerini analiz eder.
- **Anlık Saldırı Tespiti:** Çevrede birisi ağları düşürmeye çalıştığında (deauth flood) bunu anında yakalar ve seri port üzerinden raporlar.
- **Dinamik Kanal Tarama:** 1 ile 13 arasındaki kanalları tarayarak tüm frekans bandındaki saldırıları gözlemler.

## Yasal Uyarı (Disclaimer)
Bu araç tamamen savunma, ağ güvenliği analizi ve eğitim amaçlı geliştirilmiştir. Sadece kendi ağlarınızın güvenliğini test etmek için kullanın.

## Lisans
Bu proje MIT lisansı altında lisanslanmıştır. Detaylar için [LICENSE](LICENSE) dosyasına bakın.