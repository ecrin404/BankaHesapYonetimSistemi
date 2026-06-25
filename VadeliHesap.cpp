#ifndef VADELI_HESAP_H
#define VADELI_HESAP_H

#include "Hesap.h"

class VadeliHesap : public Hesap {
private:
    static constexpr double FAIZ_ORANI = 0.05;
    int vadeGunSayisi;
    int geçenGunSayisi;

public:
    VadeliHesap(string no, double baslangicBakiye, const Musteri& s, int vadeGun)
        : Hesap(no, baslangicBakiye, s), vadeGunSayisi(vadeGun), geçenGunSayisi(0) {
        cout << "[Constructor] VadeliHesap olusturuldu (Vade: " << vadeGun << " gun)" << endl;
    }

    ~VadeliHesap() override {
        cout << "[Destructor] VadeliHesap kapatildi" << endl;
    }

    void gunEkle(int gun) {
        geçenGunSayisi += gun;
        islemEkle("Gun eklendi: +" + to_string(gun) + " gun."); // YENİ
    }
    
    // YENİ: Dosyadan veri okurken geçen günü ayarlamak için
    void setGecenGun(int gun) {
        geçenGunSayisi = gun;
    }

    int kalanGun() const {
        int kalan = vadeGunSayisi - geçenGunSayisi;
        return kalan > 0 ? kalan : 0;
    }

    void faizUygula() override {
        double faizMiktari = bakiye * FAIZ_ORANI;
        bakiye += faizMiktari;
        islemEkle("Faiz uygulandi: +" + to_string(faizMiktari) + " TL (%5 Vadeli)"); // YENİ
        cout << hesapNo << " hesabina " << faizMiktari << " TL faiz eklendi (Vadeli, %5)" << endl;
    }

    string hesapTuru() const override {
        return "Vadeli Hesap";
    }

    void paraCek(double tutar) override {
        if (kalanGun() > 0)
            throw VadeSuresiDolmamisException(kalanGun());

        Hesap::paraCek(tutar);
    }

    void bilgiGoster() const override {
        Hesap::bilgiGoster();
        cout << "Vade Durumu: " << kalanGun() << " gun kaldi" << endl;
    }

    // YENİ: Dosyaya yazılacak Vadeli format
    string serialize() const override {
        return "Vadeli," + hesapNo + "," + to_string(bakiye) + "," + 
               sahip.ad + "," + sahip.soyad + "," + sahip.tcNo + "," + 
               to_string(vadeGunSayisi) + "," + to_string(geçenGunSayisi);
    }
};

#endif