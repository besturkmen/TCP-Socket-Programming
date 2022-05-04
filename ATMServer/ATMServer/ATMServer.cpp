#include<iostream>
#include <stdio.h>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <limits>
using namespace std;
typedef struct Musteri
{
	int musteriNo;
	char tc[20];
	char adSoyad[30];
	char dogumTarih[20];
	char cinsiyet;
	char adres[30];
	char telefon[20];
	char eposta[30];
	int  sifre;
	float bakiye;
	int sifreDurum; // tek kullanımlıkta = 0, yenilerse = 1 olacak 
	int hesapDurum; // hesap dondurulurs = 0, aktif hesap = 1 	
} musteri;

typedef struct Hareket {
	int musteriNo;
	char adSoyad[30];
	char sube[20];
	char islem[20];
	time_t tarih;
} hareket;

void musteriEkle()
{
	srand(time(0));

	system("cls");
	cout << ("Musteri ekleme ekrani \n\n");
	musteri m1;
	cout << ("TC           : "); cin >> m1.tc;
	cout << ("Ad-Soyad     : "); cin >> m1.adSoyad;
	cout << ("Dogum Tarih  : "); cin >> m1.dogumTarih;
	cout << ("Cinsiyet     : "); cin >> m1.cinsiyet;
	cout << ("Adres        : "); cin >> m1.adres;
	cout << ("Telefon      : "); cin >> m1.telefon;
	cout << ("E-Posta      : "); cin >> m1.eposta;

	m1.musteriNo = rand() % 1000 + 1000;
	m1.sifre = rand() % 10000 + 10000;
	m1.bakiye = 0.0;
	m1.sifreDurum = 0;
	m1.hesapDurum = 1;

	ofstream piton;
	piton.open("piton.txt", ios::app);
	piton << m1.tc << setw(10) << m1.adSoyad << setw(10) << m1.dogumTarih << setw(10) << m1.cinsiyet << setw(10) << m1.adres << setw(10) << m1.telefon << setw(10) << m1.eposta << m1.musteriNo << setw(10) << m1.sifre << setw(10) << m1.bakiye << setw(10) << m1.sifreDurum << setw(10) << m1.hesapDurum << endl;
	piton.close();
	cout << "Musteri kaydı tamamlandı\n\n" << endl;
	cout << "Tek kullanımlık şifre SMS olarak gönderildi \n\n";

}
void musteriSil() //tekrar bak ///////////////////////////////////////////////
{
	srand(time(0));

	system("cls");
	cout << ("Musteri silme ekrani \n\n");
	musteri m1;
	char tc_kontrol[20];
	cout << "TC Kimlik Numaranizi Giriniz...";
	cin >> tc_kontrol;
	ifstream Acma("piton.txt");
	ofstream Gecici("gecici.txt");
	while (!(Acma.eof()))
	{
		Acma >> m1.tc;
		if (tc_kontrol == m1.tc)
		{
			cout << "Kullanıcı silindi";

		}
		else
			Gecici << m1.tc << setw(10) << m1.adSoyad << setw(10) << m1.dogumTarih << setw(10) << m1.cinsiyet << setw(10) << m1.adres << setw(10) << m1.telefon << setw(10) << m1.eposta << m1.musteriNo << setw(10) << m1.sifre << setw(10) << m1.bakiye << setw(10) << m1.sifreDurum << setw(10) << m1.hesapDurum << endl;
	}

	cout << "Musteri kaydı tamamlandı\n\n" << endl;
	Acma.close();
	Gecici.close();
	remove("piton.txt");
	rename("gecici.txt", "piton.txt");


	}
int yetkiliMenu()
{
	int secim;
	cout << ("\t1-MUSTERI EKLE\n\n");
	cout << ("\t2-MUSTERI SIL\n\n");
	cout << ("\t3-HESAP DONDUR\n\n");
	cout << ("\t0-CIKIS\n\n");
	cout << ("Seciminiz   : "); cin >> secim;
	return secim;

}
void yetkili()
{
	system("cls");
	cout << ("Sayın Yetkili ---Hoşgeldiniz..\n\n");

	int secim = yetkiliMenu();
	while (secim != 0)
	{
		switch (secim)
		{
		case 1: musteriEkle(); break;
		case 2: musteriSil(); break;
		case 0: break;
		default: cout << ("Hatali secim ! \n"); break;
		}
		secim = yetkiliMenu();
	}
	system("cls");
	cout << ("Cikis yaptiniz... ");

}
void paraCek(musteri m1)
{
	system("cls");
	cout << ("Para Cekme Ekrani... \n\n ");
	float ucret;
	cout<<("Ucret   :  "); cin >> ucret;
	musteri m2;
	ofstream piton;
	piton.open("piton.txt", ios::app);
	while (!(piton.eof()))
	{
		if ((m1.tc == m2.tc))
			break;
	}
	piton.close();
	if (ucret > m2.bakiye)
		cout<<("Yetersiz Bakiye \n");
	else
	{
		bakiyeGuncelle(m2, -ucret);
		hareketKaydet(m2, "Para cekme");
		cout<<("Para cekme islemi tamam \n");
	}

}
void hareketKaydet(musteri m1, char* islemPtr)
{
	hareket h1;
	h1.musteriNo = m1.musteriNo;
	strcpy(h1.adSoyad, m1.adSoyad);
	strcpy(h1.islem, islemPtr);
	strcpy(h1.sube, "Ankara Şube");
	h1.tarih = time(0);
    char dosyaAdi[20];
	strcpy(dosyaAdi, m1.tc);
	strcat(dosyaAdi, ".txt");
	ofstream piton;
	piton.open("piton.txt", ios::app);
    piton.write((char*)&h1, sizeof(hareket));
	piton.close();
	cout<<("Hareket kaydi tamam \n\n"); 		

}
		

void bakiyeGuncelle(musteri m1, float para)
{

	ofstream piton;
	piton.open("piton.txt", ios::app);
	int sayac = 0;
	musteri m2;
	while (!(piton.eof()))
	{
		if (m1.tc == m2.tc)
			break;

		sayac++;
	}

	m2.bakiye += para;
	//piton.seekg(0);
	//piton.read((char*)&m2, sizeof(musteri));
	piton.write((char*)&m2, sizeof(musteri));
	cout << ("Bakiye guncellendi \n\n");
	piton.close();
}
		
void paraYatir(musteri m1)
{
	system("cls");
	printf("Para Yatirma Ekrani... \n\n ");
	float ucret;
	printf("Ucret   :  "); scanf("%f", &ucret);
	musteri m2;
	ofstream piton;
	piton.open("piton.txt", ios::app);
	while (fread(&m2, sizeof(musteri), 1, ptr) != NULL)
	{
		if (strcmp(m1.tc, m2.tc) == 0)
			break;
	}
	piton.close();
	bakiyeGuncelle(m2, ucret);
	hareketKaydet(m2, "Para yatirma");
	printf("Para yatirma islemi tamam \n");

}
void havaleEFT(musteri m1)
{
	system("cls");
	cout<<("Havale /EFT Ekrani... \n\n ");

	float ucret;
	int musteriNo;
	char adSoyad[20];
	cout<<("Hesap No   :  "); cin>>musteriNo;
	cout<<("Ad Soyad   :  "); cin>> adSoyad;
	cout<<("Ucret (TL) :  "); cin>>ucret;

	musteri m2;
	int sonuc = 0;
	ofstream piton;
	piton.open("piton.txt", ios::app);
	while (!(piton.eof()))
	{
		if (musteriNo == m2.musteriNo && strcmp(adSoyad, m2.adSoyad) == 0)
		{
			sonuc = 1;
			break;
		}
	}
	piton.close();
	piton.open("musteriler.txt");

	if (sonuc == 0)
	{
		cout<<("Alici hasep numarasi veya ad/soyad bilgilerinde hatali islem yaptaniz ! \n");
		return;
	}

	musteri m3;
	int sonuc2 = 0;
	while (!(piton.eof()))
	{
		if (m1.tc== m3.tc)
		{
			sonuc2 = 1;
			break;
		}
	}
	piton.close();
	if (ucret > m3.bakiye)
	{
		cout<<("Yetersiz bakiye ! \n");
	}
	else
	{
		bakiyeGuncelle(m3, -ucret);
		bakiyeGuncelle(m2, ucret);

		hareketKaydet(m3, "Havale gonderdi");
		hareketKaydet(m2, "Havale aldi ");

		cout<<("Havale islemi tamam \n");

	}


}
void bakiyeSorgula(musteri m1)
{
	system("cls");
	cout<<("Bakiye Sorgulama Ekrani... \n\n ");

	musteri m2;
	ofstream piton;
	piton.open("piton.txt", ios::app);
	while (!(piton.eof()))
	{
		if (m1.tc==m2.tc) 
			break;
	}
	piton.close();
	cout<<("\nBakiyeniz : %.2f TL \n\n", m2.bakiye);
	hareketKaydet(m2, "Bakiye sorgulama");

}

int musteriMenu()
{
	int secim;

	cout << ("\t1- PARA CEK \n\n");
	cout << ("\t2- PARA YATIR  \n\n");
	cout << ("\t3- HAVALE/ EFT  \n\n");
	cout << ("\t4- BAKIYE SORGULA  \n\n");
	cout << ("\t0- CIKIS   \n\n");
	cout << ("Seciminiz    :  ");
	cin >> secim;
	return secim;
}

void musterimiz(musteri m1)
{
	system("cls");
	cout << ("Sayin %s Hosgeldiniz... \n\n", m1.adSoyad);
	cout << ("Musteri No : %d \n", m1.musteriNo);
	int secim = musteriMenu();


	while (secim != 0)
	{
		switch (secim)
		{
		case 1: paraCek(m1); break;
		case 2: paraYatir(m1); break;
		case 3: havaleEFT(m1); break;
		case 4: bakiyeSorgula(m1); break;

		case 0: break;
		default: cout << ("Hatali secim ! \n"); break;
		}
		secim = musteriMenu();
	}

	system("cls");
	cout << ("\n%s cikis yaptiniz ... ", m1.adSoyad);

}
void sifreDegistirTek(musteri m1)
{
	system("cls");
	cout << ("%s Tek kullanimlik sifrenizi degistiriniz... \n\n", m1.adSoyad);
	int eskiSifre, yeni, sifreTekrar;

	cout << ("Eski Sifre        : "); cin >> eskiSifre;
	cout << ("Yeni Sifre        : "); cin >> yeni;
	cout << ("Yeni Sifre Tekrar : "); cin >> sifreTekrar;
	int sonuc = 0, sayac = 0;
	if (m1.sifre == eskiSifre && yeni == sifreTekrar)
	{
		musteri m2;
		ifstream piton;
		piton.open("musteriler.txt");
		while (!(piton.eof()))
		{
			if (strcmp(m1.tc, m2.tc) == 0)
			{
				sonuc = 1;
				break;
			}
			sayac++;
		}
		if (sonuc == 0)
		{
			cout << ("Sifre degistirme isleminde hata olustu ! \n");
			piton.close();
		}
		else
		{
			piton.seekg(0);
			piton.read((char*)&m2, sizeof(m2));
			m2.sifreDurum = 1;
			m2.sifre = yeni;
			//piton.write((char*)&m2, sizeof(m2));
			piton.close();
			cout << ("Sifre degistirme islemi basarili, yeni sifreniz ile giris yapabilirsiniz \n\n");
			piton.close();

		}

	}
	else
	{
		cout<<("Hatali sifre degistirme islemi ! \n");
	}



}
void musteriGiris()
{
	system("cls");
	cout << ("Musteri Giris Ekranı\n\n");
	char tc[20];
	int parola;
	cout << ("TC      :"); cin >> tc;
	cout << ("PAROLA  :"); cin >> parola;
	ifstream piton;
	piton.open("piton.txt");
	musteri m1;
	int sonuc = 1;
	while (!(piton.eof()))
	{
		if (strcmp(tc, m1.tc) == 0 && parola == m1.sifre)
		{
			sonuc = 1;
			break;
		}
	}

	piton.close();
	if (sonuc == 0)
	{
		cout << ("Hatali giris denemesi \n");
	}
	else
	{
		if (m1.sifreDurum == 0)
			sifreDegistirTek(m1);
		else if (m1.hesapDurum == 0)
		{
			cout << ("\nHesabiniz dondurulmustur, Lutfen banka subeniz ile gorusunuz... \n");
		}
		else
			musterimiz(m1);

	}



}
void yetkiliGiris()
{
	system("cls");
	cout << ("Yetkili Giris Ekranı\n\n");
	char admin[20];
	int parola;
	cout << ("ADMIN :"); cin >> admin;
	cout << ("PAROLA  :"); cin >> parola;

	if (strcmp(admin, "PITON") == 0 && parola == 123)
		yetkili();

	else
		cout << ("Hatalı Giris Denemesi !\n\n");


}

int menu()
{
	int secim;
	cout << ("\n\n\t BESTE'NIN BANKAMATIK OTOMASYONU \n\n");
	cout << ("\t1- MUSTERI GIRIS \n\n");
	cout << ("\t2- YETKILI GIRIS \n\n");
	cout << ("\t3- PROGRAMI KAPAT \n\n");
	cout << ("Seciminiz  :  ");
	cin >> secim;
	return secim;

}
int main()
{
	int secim = menu();
	while (secim != 0)
	{
		switch (secim)
		{
		case 1: musteriGiris(); break;
		case 2: yetkiliGiris(); break;
		case 0: break;
		default: cout << ("Hatali secim ! \n"); break;
		}
		secim = menu();
	}

	cout << ("Program kapatiliyor... ");
	return 0;
}
