#ifndef BANKA_EXCEPTIONS_H
#define BANKA_EXCEPTIONS_H

#include <exception>
#include <string>

using namespace std;

class BankaException : public exception {
protected:
    string mesaj;
public:
    BankaException(const string& m) : mesaj(m) {}
    virtual const char* what() const noexcept override {
        return mesaj.c_str();
    }
    virtual ~BankaException() {}
};

class YetersizBakiyeException : public BankaException {
public:
    YetersizBakiyeException(double bakiye, double cekilmekIstenen)
        : BankaException("Yetersiz bakiye! Mevcut: " + to_string(bakiye) +
                          " TL, Cekilmek istenen: " + to_string(cekilmekIstenen) + " TL") {}
};

class GecersizTutarException : public BankaException {
public:
    GecersizTutarException(double tutar)
        : BankaException("Gecersiz tutar girdiniz: " + to_string(tutar) +
                          " TL (Tutar pozitif olmalidir)") {}
};

class HesapBulunamadiException : public BankaException {
public:
    HesapBulunamadiException(const string& hesapNo)
        : BankaException("Hesap bulunamadi! Hesap No: " + hesapNo) {}
};

class VadeSuresiDolmamisException : public BankaException {
public:
    VadeSuresiDolmamisException(int kalanGun)
        : BankaException("Vade suresi henuz dolmadi! Kalan gun: " + to_string(kalanGun)) {}
};

#endif