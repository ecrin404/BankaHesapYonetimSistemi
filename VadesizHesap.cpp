#ifndef VADESIZ_HESAP_H
#define VADESIZ_HESAP_H

#include "Hesap.h"

class VadesizHesap : public Hesap {
private:
    static constexpr double FAIZ_ORANI = 0.01;

public:
    VadesizHesap(string no, double baslangicBakiye, const Musteri& s)
        : Hesap(no, baslangicBakiye, s) {
        cout << "[Constructor] VadesizHesap olusturuldu" << endl;
    }

    ~VadesizHesap() override {
        cout << "[Destructor] VadesizHesap kapatildi" << endl;
    }

    void faizUygula() override {
        double faizMiktari = bakiye * FAIZ_ORANI;
        bakiye += faizMiktari;
        islemEkle("Faiz uygulandi: +" + to_string(faizMiktari) + " TL (%1 Vadesiz)"); // YENİ
        cout << hesapNo << " hesabina " << faizMiktari << " TL faiz eklendi (Vadesiz, %1)" << endl;
    }

    string hesapTuru() const override {
        return "Vadesiz Hesap";
    }

    // YENİ: Dosyaya yazılacak Vadesiz format
    string serialize() const override {
        return "Vadesiz," + hesapNo + "," + to_string(bakiye) + "," + 
               sahip.ad + "," + sahip.soyad + "," + sahip.tcNo;
    }
};

#endif