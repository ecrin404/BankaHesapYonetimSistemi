#ifndef BANKA_H
#define BANKA_H

#include "Hesap.h"
#include "VadesizHesap.h"
#include "VadeliHesap.h"
#include "BankaExceptions.h"
#include <vector>
#include <fstream>  // YENİ: Dosya işlemleri
#include <sstream>  // YENİ: String parçalama işlemleri

class Banka {
private:
    vector<Hesap*> hesaplar;
    string bankaAdi;
    const string DOSYA_ADI = "banka_verileri.txt"; // YENİ: Veritabanı dosyamız

    // YENİ: Verileri .txt dosyasına kaydeder
    void verileriKaydet() const {
        ofstream dosya(DOSYA_ADI);
        for(Hesap* h : hesaplar) {
            dosya << h->serialize() << "\n";
        }
        dosya.close();
    }

    // YENİ: Başlangıçta .txt dosyasındaki hesapları sisteme yükler
    void verileriYukle() {
        ifstream dosya(DOSYA_ADI);
        if (!dosya.is_open()) return; // Dosya yoksa ilk kurulum sayılır, boş başlar

        string satir;
        while(getline(dosya, satir)) {
            if(satir.empty()) continue;
            
            stringstream ss(satir);
            string tur, no, bakiyeStr, ad, soyad, tc;
            
            getline(ss, tur, ',');
            getline(ss, no, ',');
            getline(ss, bakiyeStr, ',');
            getline(ss, ad, ',');
            getline(ss, soyad, ',');
            getline(ss, tc, ',');

            Musteri m(ad, soyad, tc);
            double bakiye = stod(bakiyeStr);

            if (tur == "Vadesiz") {
                Hesap* h = new VadesizHesap(no, bakiye, m);
                h->islemEkle("Hesap dosyadan sisteme yuklendi.");
                hesaplar.push_back(h);
            } else if (tur == "Vadeli") {
                string vadeGunStr, gecenGunStr;
                getline(ss, vadeGunStr, ',');
                getline(ss, gecenGunStr, ',');
                
                Hesap* h = new VadeliHesap(no, bakiye, m, stoi(vadeGunStr));
                dynamic_cast<VadeliHesap*>(h)->setGecenGun(stoi(gecenGunStr));
                h->islemEkle("Hesap dosyadan sisteme yuklendi.");
                hesaplar.push_back(h);
            }
        }
        dosya.close();
        cout << "[Sistem] Onceki kayitlar basariyla yuklendi." << endl;
    }

public:
    Banka(string ad) : bankaAdi(ad) {
        cout << "[Constructor] " << bankaAdi << " bankasi sisteme baglandi." << endl;
        verileriYukle(); // YENİ: Başlangıçta kayıtları çek
    }

    ~Banka() {
        cout << "[Destructor] " << bankaAdi << " kapatiliyor..." << endl;
        verileriKaydet(); // YENİ: Kapanmadan hemen önce her şeyi kaydet
        cout << "[Sistem] Tum hesaplar " << DOSYA_ADI << " dosyasina kaydedildi." << endl;
        
        for (Hesap* h : hesaplar) {
            delete h;
        }
        hesaplar.clear();
    }

    void hesapEkle(Hesap* yeniHesap) {
        hesaplar.push_back(yeniHesap);
        cout << ">> Yeni hesap bankaya eklendi: " << yeniHesap->getHesapNo() << endl;
    }

    Hesap* hesapBul(const string& no) {
        for (Hesap* h : hesaplar) {
            if (h->getHesapNo() == no)
                return h;
        }
        throw HesapBulunamadiException(no);
    }

    void tumHesaplariListele() const {
        cout << "\n========== " << bankaAdi << " - Tum Hesaplar ==========" << endl;
        if (hesaplar.empty()) {
            cout << "Henuz kayitli hesap yok." << endl;
            return;
        }
        for (const Hesap* h : hesaplar) {
            cout << *h;
        }
        cout << "==========================================\n" << endl;
    }

    void tumHesaplaraFaizUygula() {
        cout << "\n--- Donem sonu faiz islemleri basliyor ---" << endl;
        for (Hesap* h : hesaplar) {
            h->faizUygula();
        }
        cout << "--- Faiz islemleri tamamlandi ---\n" << endl;
    }

    Hesap* enYuksekBakiyeliHesap() const {
        if (hesaplar.empty()) return nullptr;
        Hesap* enYuksek = hesaplar[0];
        for (Hesap* h : hesaplar) {
            if (*h > *enYuksek)
                enYuksek = h;
        }
        return enYuksek;
    }

    int hesapSayisi() const { return hesaplar.size(); }
};

#endif