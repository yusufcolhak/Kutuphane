#include <stdio.h>
#include <string.h>

#define MAX 100
//STRUCT verileri gruplar
//TYPDEF mevcut tipe yeni isim verme
typedef struct {
	int id;
	char ad[50];
	char yazar[50];
	int yil;
	char durum[50];
} Kitap;

Kitap kitaplar[MAX];
int kitapSayisi = 0;

void ornekVeriYukle() {
	static const Kitap veri[] = {
	{1, "BENIM ADIM KIRMIZI", "ORHAN PAMUK", 1998, "Mevcut"},
	{2, "SUC VE CEZA", "FYODOR DOSTOYEVSKI", 1866, "Mevcut"},
	{3, "KURK MANTOLU MADONNA", "SABAHATTIN ALI", 1943, "Mevcut"},
	{4, "FARELER VE INSANLAR", "JHON STEINBECK", 1937, "Mevcut"},
	{5, "HUZUR", "AHMET HAMDI TANPINAR", 1949, "Mevcut"},
	{6, "DONUSUM", "FRANZ KAFKA", 1915, "Mevcut"},
	{7, "ASK", "ELIF SAFAK", 2009, "Mevcut"},
	{8, "YABANCI", "ALBERT CAMUS", 1942, "Mevcut"},
	{9, "INCE MEMED", "YASAR KEMAL", 1955, "Mevcut"},
	{10, "HARRY POTTER VE FELSEFE TASI", "J.K. ROWLING", 1997, "Mevcut"},
	};
	//sizeof diziyi otomatik günceller bellekte kaç byte yer kaplar onu söyler
	int veriSayisi = sizeof(veri) / sizeof(veri[0]);
	int eklenen = 0;
	int i, j;

	if (kitapSayisi + veriSayisi > MAX) {// kitap sayýsýný aþarsa 100'den fazla kitap eklenmez aþþaðýdaki hatayý verir
		printf("\nTanzanya Kutuphanesi dolu! Daha fazla kitap eklenemez.\n");
		return;
	}
	for (i = 0; i < veriSayisi; i++) { //veri dizisindeki her kitabý dolaþýr
		int ayniIdVar = 0; // 0 ayný id yok 1 ayný id var
		for (j = 0; j < kitapSayisi; j++) {//veri dizisindeki mevcut kitablarý dolaþýr
			if (kitaplar[j].id == veri[i].id) { // kitabýn idsi ile eklenmek istenen kitabýn idsi ayný mý kontrol eder
				ayniIdVar = 1; 
				break;
			}
		}
		if (ayniIdVar == 0) { // ayný id yoksa bu satýra geçer
			kitaplar[kitapSayisi++] = veri[i]; //kitabý kütüphaneye ekler kitap sayýsýný 1 arttýrýr
			eklenen++;
		}
	}
	printf("\n%d kitap eklendi.\n", eklenen);
}

void kitapEkle() {
	if (kitapSayisi >= MAX) {// kitap sayisi 100 aþarsa kitap eklenmez
		printf("\nTanzanya Kutuphanesi dolu! Daha fazla kitap eklenemez.\n");
		return;
	}

	Kitap yeni;
	printf("\nYeni Kitap Bilgilerini Giriniz:\n");
	printf("ID: ");
	scanf("%d", &yeni.id);
	getchar(); // enter\n karakterini temizler

	int i;
	for (i = 0; i < kitapSayisi; i++) {// verileri dolaþýr ayný id ile kitap bulursa aþþaðýdaki çýktýyý verir yok ise kitap bilgilerini almaya devam eder
		if (kitaplar[i].id == yeni.id) {
			printf("Bu ID ile zaten bir kitap bulunmaktadir!\n");
			return;
		}
	}

	printf("Ad: ");
	scanf(" %49[^\n]", yeni.ad);// dizi boyutu 50 olduðu için 49 sýnýrý 
	printf("Yazar: ");
	scanf(" %49[^\n]", yeni.yazar);
	printf("Basim Yili: ");
	scanf("%d", &yeni.yil);
	strcpy(yeni.durum, "Mevcut"); //bir stringi baþka bir stringe kopyalar

	kitaplar[kitapSayisi] = yeni;
	kitapSayisi++;
	printf("\nYeni kitap eklendi!\n");
}

void kitapSil() {
	int id;
	int bulundu = 0;
	int i, j;
	printf("Silinecek kitap ID'sini girin: ");
	scanf("%d", &id);

	for (i = 0; i < kitapSayisi; i++) {//verilerde ayný id ye ait kitap bulunamazsa en aþþaðýdaki çýktýyý verir
		if (kitaplar[i].id == id) {
			for (j = i; j < kitapSayisi - 1; j++) {
				kitaplar[j] = kitaplar[j + 1]; 
			}
			kitapSayisi--;
			bulundu = 1;// kitap id si bulunursa kitabý siler
			printf("\nKitap silindi.\n");
			break;
		}
	}
	if (bulundu == 0)
		printf("Bu ID'ye sahip kitap bulunamadi.\n");
}

void kitapOduncVer() {
	int id;
	int i;
	int bulundu = 0;
	printf("\nOdunc verilecek kitap ID'sini giriniz: ");
	scanf("%d", &id);

	for (i = 0; i < kitapSayisi; i++) {// üstteki döngülerle ayný iþlevi görür döngü içinde ayný id bulunmazsa kitap bulunamadý çýktýsýný verir
		if (kitaplar[i].id == id) {
			bulundu = 1;
			if (strcmp(kitaplar[i].durum, "Mevcut") == 0) { // durum eþit mi diye kontrol eder
				strcpy(kitaplar[i].durum, "Odunc");// mevcut ödünç yerini deðiþtirir
				printf("Kitap odunc verildi.\n");
			} else {
				printf("Kitap zaten odunc verildi.\n");//kitap önceden ödünç verildiyse bu çýktýyý verir
			}
			break;
		}
	}
	if (bulundu == 0)
		printf("Kitap bulunamadi.\n");
}

void kitapIadeEt() {
	int id;
	int bulundu = 0;
	int i;
	printf("\nIade edilecek kitap ID'si giriniz: ");
	scanf("%d", &id);

	for (i = 0; i < kitapSayisi; i++) {
		if (kitaplar[i].id == id) {
			bulundu = 1;// ödünç ver döngüsü ile ayný iþlev sadece ödünç olan kitabý iade eder ve mevcut durumuna çevirir
			if (strcmp(kitaplar[i].durum, "Odunc") == 0) {
				strcpy(kitaplar[i].durum, "Mevcut");
				printf("Kitap iade edildi.\n");
			} else {
				printf("Kitap zaten mevcut.\n");
			}
			break;
		}
	}
	if (bulundu == 0)
		printf("Kitap bulunamadi.\n");
}

void kitapAra() {
	char aranan[50];
	int bulundu = 0;
	int i;
	int id;
	int atil;

	printf("\nKitap arama turu seciniz:\n");
	printf("1-ID ile arama\n");
	printf("2-Kitap ismi ile arama\n");
	printf("Seciminiz: ");
	scanf("%d", &atil);

	if (atil == 1) {
		printf("\nAranacak ID: ");
		scanf("%d", &id);

		for (i = 0; i < kitapSayisi; i++) {
			if (kitaplar[i].id == id) {
				printf("ID: %d | Isim: %s | Yazar: %s | Yil: %d | Durum: %s\n", // ýd den baþlayarak durumuna kadar kitap hakkýndaki bilgileri sýralar id doðru ise
					kitaplar[i].id, kitaplar[i].ad, kitaplar[i].yazar,
					kitaplar[i].yil, kitaplar[i].durum);
				bulundu = 1;
				break;
			}
		}
		if (bulundu == 0)
			printf("Aradiginiz ID'ye sahip kitap bulunamadi.\n");
	} else if (atil == 2) {
		printf("\nAramak istediginiz kitabin adini giriniz: ");
		scanf(" %49[^\n]", aranan); // taþmayý önlemek için geniþlik verir

		for (i = 0; i < kitapSayisi; i++) {
			if (strstr(kitaplar[i].ad, aranan) != NULL) { //strstr kitaplarýn içinden kitabýn adýný arar
				printf("ID: %d | Isim: %s | Yazar: %s | Yil: %d | Durum: %s\n", //null geçersiz hiç bir geçerli adres olmadýðýný ifade eder
					kitaplar[i].id, kitaplar[i].ad, kitaplar[i].yazar,
					kitaplar[i].yil, kitaplar[i].durum);
				bulundu = 1;
			}
		}
		if (bulundu == 0)
			printf("Aradiginiz kitap bulunamadi.\n");
	} else {
		printf("\nGecersiz secim!\n");
	}
}

void kitaplariListele() {
	if (kitapSayisi == 0) {
		printf("\nTanzanya kütüphanesinde kitap bulunamadý.\n");
		return;
	}
	printf("\n||| Tanzanya Kutuphanesindeki Kitaplar(Alfabetik sirali) |||\n");
	int i, j;
	Kitap alfabetik[MAX]; // geçici diziyi bozmamak için kopyasýný aldýðýmýz dizi
	for (i = 0; i < kitapSayisi; i++) {
		alfabetik[i] = kitaplar[i];
	}
//EN KOLAY A DAN Z YE SIRALAMA YÖNTEMÝ(BUBBLE SORT)

	for (i = 0; i < kitapSayisi - 1; i++) {
		for (j = 0; j < kitapSayisi - 1 - i; j++) {
			if (strcmp(alfabetik[j].ad, alfabetik[j + 1].ad) > 0) { // karþýlaþtýrma yapar soldaki ad alfabetik olarak saðdakinden büyüktür
				Kitap temp = alfabetik[j];
				alfabetik[j] = alfabetik[j + 1];
				alfabetik[j + 1] = temp; // iki elemaný yer deðiþtirmek için tutucu görevi görür temp 
			}
		}
	}

	for (i = 0; i < kitapSayisi; i++) {// kitaplarý sýrasýyla yazdýrýr dögüden alýp
		printf("ID: %d | Isim: %s | Yazar: %s | Yil: %d | Durum: %s\n",
			alfabetik[i].id, alfabetik[i].ad, alfabetik[i].yazar,
			alfabetik[i].yil, alfabetik[i].durum);
	}
}

int main() {
	int tuyaa;

	ornekVeriYukle();

	do {
		printf("\n|||| TANZANYA KUTUPHANESI ||||\n");
		printf("1- Kitap ekle\n");
		printf("2- Kitap sil\n");
		printf("3- Kitap odunc ver\n");
		printf("4- Kitap iade et\n");
		printf("5- Kitap ara\n");
		printf("6- Kitaplari listele\n");
		printf("7- Cikis\n");
		printf("Seciminiz: ");
		scanf("%d", &tuyaa);

		switch (tuyaa) {
			case 1:
				kitapEkle();
				break;
			case 2:
				kitapSil();
				break;
			case 3:
				kitapOduncVer();
				break;
			case 4:
				kitapIadeEt();
				break;
			case 5:
				kitapAra();
				break;
			case 6:
				kitaplariListele();
				break;
			case 7:
				printf("\nTanzanya kutuphanesinden cikis yapiliyor...\n");
				break;
			default:
				printf("\nGecersiz secim! Tekrar deneyiniz!\n");
		}
	} while (tuyaa != 7);

	return 0;
}
