# BankaHesapYonetimSistemi - C++ Bankacılık Simülasyonu 🏦

BankaHesapYonetimSistemi; vadesiz ve vadeli hesap yönetiminden finansal işlemlere, dönem sonu faiz hesaplamalarından hesap geçmişi takibine kadar bankacılık süreçlerini modelleyen C++ tabanlı bir CLI uygulamasıdır. Proje, Nesne Yönelimli Programlama (OOP) prensiplerini kullanarak güvenli, modüler ve genişletilebilir bir mimari sunmayı amaçlar.

## 🚀 Öne Çıkan Özellikler

- **Kapsamlı Hesap Yönetimi:** İki ana kategoride dinamik hesap kontrolü:
  - 💳 **Vadesiz Hesap:** Esnek para yatırma/çekme imkanı sağlayan ve günlük işlemlere uygun yapı.
  - 📈 **Vadeli Hesap:** Belirli bir vade süresine bağlı, yüksek faiz getirili ve erken çekim kontrollü yatırım hesabı.
- **Veri Kalıcılığı (File I/O):** Program kapatıldığında tüm hesapların, müşteri bilgilerinin ve güncel bakiyelerin `banka_verileri.txt` dosyasına formatlı olarak kaydedilmesi ve açılışta otomatik olarak sisteme yüklenmesi.
- **Oturum Bazlı İşlem Geçmişi (Log):** Aktif oturum boyunca gerçekleştirilen para yatırma, çekme ve faiz uygulama gibi finansal hareketlerin hesap bazında arka planda kaydedilmesi ve istendiğinde dökümünün alınması.
- **Güvenli Finansal İşlemler:** Yetersiz bakiye, eksi tutar girilmesi veya erken vade bozumu gibi hatalı durumlarda işlemleri anında durduran ve kullanıcıyı uyaran güçlü Exception Handling (Hata Yakalama) mekanizması.

## 🛠️ Teknik Uygulama (OOP Prensipleri)

- **Kalıtım ve Polimorfizm (Inheritance & Polymorphism):** Farklı hesap türlerini ortak bir çatı altında yönetmek için soyut (abstract) `Hesap` temel sınıfı oluşturulmuş; `faizUygula()`, `hesapTuru()` ve `serialize()` gibi saf sanal (pure virtual) fonksiyonlar çok biçimlilik ile türetilmiş sınıflarda ezilmiştir (override).
- **Dinamik Bellek Yönetimi:** `Banka` sınıfı içerisinde hesaplar pointer (`Hesap*`) kullanılarak dinamik olarak oluşturulmuş, sanal yıkıcılar (`virtual ~Hesap()`) ve `Banka` sınıfının yıkıcısı ile bellek sızıntıları (memory leak) tamamen önlenmiştir.