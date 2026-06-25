#ifndef HESAP_H
#define HESAP_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "BankaExceptions.h"

using namespace std;

struct Musteri {
    string ad;
    string soyad;
    string tcNo;

    Musteri(string a = "", string s = "", string tc = "")
        : ad(a), soyad(s), tcNo(tc) {}

    string tamAd() const {
        return ad + " " + soyad;
    }
};

class Hesap {
protected:
    string hesapNo;
    double bakiye;
    Musteri sahip;
    vector<string> islemGecmisi; // YENİ: İşlem geçmişi listesi

public:
    // DÜZELTME: Musteri parametresi gereksiz kopyalamayı önlemek için 'const Musteri&' olarak güncellendi.
    Hesap(string no, double baslangicBakiye, const Musteri& s)
        : hesapNo(no), bakiye(baslangicBakiye), sahip(s) {
        cout << "[Constructor] Hesap olusturuldu -> No: " << hesapNo << endl;
    }

    virtual ~Hesap() {
        cout << "[Destructor] Hesap kapatildi -> No: " << hesapNo << endl;
    }

    string getHesapNo() const { return hesapNo; }
    double getBakiye() const { return bakiye; }
    Musteri getSahip() const { return sahip; }

    // YENİ: İşlem geçmişine veri ekleyen yardımcı fonksiyon
    void islemEkle(const string& islem) {
        islemGecmisi.push_back(islem);
    }

    virtual void paraYatir(double tutar) {
        if (tutar <= 0)
            throw GecersizTutarException(tutar);
        bakiye += tutar;
        islemEkle("Para yatirildi: +" + to_string(tutar) + " TL");
    }

    virtual void paraCek(double tutar) {
        if (tutar <= 0)
            throw GecersizTutarException(tutar);
        if (tutar > bakiye)
            throw YetersizBakiyeException(bakiye, tutar);
        bakiye -= tutar;
        islemEkle("Para cekildi: -" + to_string(tutar) + " TL");
    }

    Hesap& operator+=(double tutar) {
        paraYatir(tutar);
        return *this;
    }

    Hesap& operator-=(double tutar) {
        paraCek(tutar);
        return *this;
    }

    bool operator==(const Hesap& other) const {
        return this->hesapNo == other.hesapNo;
    }

    bool operator>(const Hesap& other) const {
        return this->bakiye > other.bakiye;
    }

    virtual void faizUygula() = 0;
    virtual string hesapTuru() const = 0;

    // YENİ: Dosyaya yazılacak formatı belirleyen soyut fonksiyon
    virtual string serialize() const = 0;

    // YENİ: İşlem geçmişini ekrana basar
    void gecmisGoster() const {
        cout << "\n--- Islem Gecmisi (" << hesapNo << ") ---" << endl;
        if (islemGecmisi.empty()) {
            cout << "Henuz islem yapilmamis." << endl;
        } else {
            for (const string& islem : islemGecmisi) {
                cout << ">> " << islem << endl;
            }
        }
        cout << "---------------------------------" << endl;
    }

    virtual void bilgiGoster() const {
        cout << fixed << setprecision(2);
        cout << "----------------------------------------" << endl;
        cout << "Hesap No   : " << hesapNo << endl;
        cout << "Hesap Turu : " << hesapTuru() << endl;
        cout << "Sahibi     : " << sahip.tamAd() << endl;
        cout << "Bakiye     : " << bakiye << " TL" << endl;
    }
};

ostream& operator<<(ostream& os, const Hesap& h) {
    h.bilgiGoster();
    return os;
}

#endif