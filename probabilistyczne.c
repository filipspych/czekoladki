/// TEN PROGRAM POWIIEN BYC NAPISANY ZNACZNIE PROSCIEJ (WYSTARCZY JEDNA PETLA) 
//// CELEM JEST UTWORZENIE SYMULACJI ODPOWIADAJACEJ BLISKO RZECZYWISTOSCI (DLA PARANOIKOW)
//// GDYBYM CHCIAL NAPISAC KROTKI PROGRAM ZWROCILBYM WYNIK, KTORY OBLICZYLEM NA KARTCE (4 linijki)

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define LICZBA_CZEKOLADEK 28
#define LICZBA_WYBIERANYCH_CZEKOLADEK 3
#define LICZBA_LOSOWAN 10000000
#define PROG_TRAFIEN 2
#define WYPISUJ_W_TRAKCIE 0

int czekoladki[LICZBA_CZEKOLADEK][2];

struct wyniki {
	int sumaTrafien;
	int liczbaWystapienZjawiska;
} wyniki;

void wyczyscCzekoladki() {
	for(int i = 0; i < LICZBA_CZEKOLADEK; i++) {
		czekoladki[i][0] = 0;
		czekoladki[i][1] = 0;
	}
}

void wypiszCzekoladki() {
	for(int i = 0; i < LICZBA_CZEKOLADEK; i++) {
		if(czekoladki[i][0]) printf("%d ", czekoladki[i][0]);
		else printf("_ ");
	}
	printf("\n");
        for(int i = 0; i < LICZBA_CZEKOLADEK; i++) {
                if(czekoladki[i][1]) printf("%d ", czekoladki[i][1]);
                else printf("_ ");
        }
	printf("\n");
}

void wybierzCzekoladki() {
	for(int i = 0; i < LICZBA_WYBIERANYCH_CZEKOLADEK; i++) {
		int r = rand();
		while(czekoladki[r % LICZBA_CZEKOLADEK][0] != 0) r = rand();
		czekoladki[rand() % LICZBA_CZEKOLADEK][0] = 1 + i;
	}
}

void zgadnijCzekoladki() {
	for(int i = 0; i < LICZBA_WYBIERANYCH_CZEKOLADEK; i++) {
		int r = rand();
		while(czekoladki[r % LICZBA_CZEKOLADEK][1] != 0) r = rand();
		czekoladki[rand() % LICZBA_CZEKOLADEK][1] = 1 + i;
	}
}

int policzTrafienia() {
	int trafienia = 0;
	for(int j = 0; j < LICZBA_CZEKOLADEK; j++)
		if((czekoladki[j][0] != 0) && (czekoladki[j][0] == czekoladki[j][1]))
			trafienia++;	
	return trafienia;
}

void wypiszWyniki() {
	printf("liczba losowan: %d\n", LICZBA_LOSOWAN);
	printf("suma trafien: %d\n", wyniki.sumaTrafien);
	printf("wystapienia zjawiska: %d\n", wyniki.liczbaWystapienZjawiska); 
	printf("udzial wystapien: %f\n", wyniki.liczbaWystapienZjawiska/((double)LICZBA_LOSOWAN));
}

void wypiszTrafienia(int trafienia) {
	printf("trafienia: %d\n", trafienia);
}

int main() {
	srand(time(NULL)); 
	for(int i = 0; i < LICZBA_LOSOWAN; i++) {
		wyczyscCzekoladki();
		wybierzCzekoladki();
		zgadnijCzekoladki();

		int trafienia = policzTrafienia();
		wyniki.sumaTrafien += trafienia; 
		if (trafienia >= PROG_TRAFIEN) {
			wyniki.liczbaWystapienZjawiska++;
			if (WYPISUJ_W_TRAKCIE)
				printf("zjawisko\n");
		}

		if(WYPISUJ_W_TRAKCIE) {
			wypiszCzekoladki();
			wypiszTrafienia(trafienia);
			printf("\n");
		}
	}
	wypiszWyniki();
}
