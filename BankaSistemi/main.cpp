#include <iostream>
#include <string>
#include <limits>
#include "Banka.h"
#include "VadesizHesap.h"
#include "VadeliHesap.h"
#include "BankaExceptions.h"

using namespace std;

void menuGoster() {
    cout << "\n================ BANKA HESAP YONETIM SISTEMI ================" << endl;
    cout << "1. Vadesiz Hesap Ac" << endl;
    cout << "2. Vadeli Hesap Ac" << endl;
    cout << "3. Para Yatir" << endl;
    cout << "4. Para Cek" << endl;
    cout << "5. Tum Hesaplari Listele" << endl;
    cout << "6. Tum Hesaplara Faiz Uygula (Donem Sonu)" << endl;
    cout << "7. En Yuksek Bakiyeli Hesabi Goster" << endl;
    cout << "8. Vadeli Hesaba Gun Ekle (Simulasyon)" << endl;
    cout << "9. Hesap Islem Gecmisini Goster" << endl; // YENİ
    cout << "0. Cikis" << endl;
    cout << "===============================================================" << endl;
    cout << "Seciminiz: ";
}

double sayiOku() {
    double deger;
    while (!(cin >> deger)) {
        cout << "Gecersiz giris! Tekrar deneyin: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return deger;
}

int main() {
    // Veriler artık Banka'nın Constructor'ı içinde otomatik dosyadan yüklenecek
    Banka banka("Cpp Bankasi");
    int secim;

    do {
        menuGoster();
        secim = (int) sayiOku();

        try {
            switch (secim) {
                case 1: {
                    string ad, soyad, tc, no;
                    double bakiye;
                    // DÜZELTME: cin >> ad yerine getline kullanılarak boşluklu isim girilmesi sağlandı
                    cout << "Ad: "; cin >> ws; getline(cin, ad);
                    cout << "Soyad: "; cin >> ws; getline(cin, soyad);
                    cout << "TC No: "; cin >> tc;
                    cout << "Hesap No: "; cin >> no;
                    cout << "Baslangic Bakiyesi: "; bakiye = sayiOku();

                    Musteri m(ad, soyad, tc);
                    Hesap* yeni = new VadesizHesap(no, bakiye, m);
                    yeni->islemEkle("Hesap olusturuldu. Baslangic: " + to_string(bakiye) + " TL");
                    banka.hesapEkle(yeni);
                    break;
                }
                case 2: {
                    string ad, soyad, tc, no;
                    double bakiye;
                    int vadeGun;
                    cout << "Ad: "; cin >> ws; getline(cin, ad);
                    cout << "Soyad: "; cin >> ws; getline(cin, soyad);
                    cout << "TC No: "; cin >> tc;
                    cout << "Hesap No: "; cin >> no;
                    cout << "Baslangic Bakiyesi: "; bakiye = sayiOku();
                    cout << "Vade Suresi (gun): "; vadeGun = (int) sayiOku();

                    Musteri m(ad, soyad, tc);
                    Hesap* yeni = new VadeliHesap(no, bakiye, m, vadeGun);
                    yeni->islemEkle("Vadeli Hesap olusturuldu. Baslangic: " + to_string(bakiye) + " TL");
                    banka.hesapEkle(yeni);
                    break;
                }
                case 3: {
                    string no;
                    double tutar;
                    cout << "Hesap No: "; cin >> no;
                    cout << "Yatirilacak Tutar: "; tutar = sayiOku();

                    Hesap* h = banka.hesapBul(no);
                    *h += tutar;
                    cout << ">> Islem basarili! Yeni bakiye: " << h->getBakiye() << " TL" << endl;
                    break;
                }
                case 4: {
                    string no;
                    double tutar;
                    cout << "Hesap No: "; cin >> no;
                    cout << "Cekilecek Tutar: "; tutar = sayiOku();

                    Hesap* h = banka.hesapBul(no);
                    *h -= tutar;
                    cout << ">> Islem basarili! Yeni bakiye: " << h->getBakiye() << " TL" << endl;
                    break;
                }
                case 5:
                    banka.tumHesaplariListele();
                    break;
                case 6:
                    banka.tumHesaplaraFaizUygula();
                    break;
                case 7: {
                    Hesap* en = banka.enYuksekBakiyeliHesap();
                    if (en) {
                        cout << "\nEn yuksek bakiyeli hesap:" << endl;
                        cout << *en;
                    } else {
                        cout << "Sistemde hesap bulunmuyor." << endl;
                    }
                    break;
                }
                case 8: {
                    string no;
                    int gun;
                    cout << "Hesap No: "; cin >> no;
                    cout << "Eklenecek gun sayisi: "; gun = (int) sayiOku();

                    Hesap* h = banka.hesapBul(no);
                    VadeliHesap* vh = dynamic_cast<VadeliHesap*>(h);
                    if (vh) {
                        vh->gunEkle(gun);
                        cout << ">> " << gun << " gun eklendi. Kalan vade: "
                             << vh->kalanGun() << " gun" << endl;
                    } else {
                        cout << ">> Bu hesap vadeli hesap degil!" << endl;
                    }
                    break;
                }
                case 9: { // YENİ MENÜ SEÇENEĞİ
                    string no;
                    cout << "Gecmisi goruntulenecek Hesap No: "; cin >> no;
                    Hesap* h = banka.hesapBul(no);
                    h->gecmisGoster();
                    break;
                }
                case 0:
                    cout << "Sistemden cikiliyor..." << endl;
                    break;
                default:
                    cout << "Gecersiz secim! Lutfen tekrar deneyin." << endl;
            }
        }
        catch (const BankaException& e) {
            cout << "\n!!! HATA: " << e.what() << " !!!\n" << endl;
        }
        catch (const exception& e) {
            cout << "\n!!! Beklenmeyen hata: " << e.what() << " !!!\n" << endl;
        }

    } while (secim != 0);

    return 0;
}