//// TEN PROGRAM POWIEN BYC NAPISANY ZNACZNIE PROSCIEJ (WYSTARCZY JEDNA PETLA) 
//// CELEM JEST UTWORZENIE SYMULACJI ODPOWIADAJACEJ BLISKO RZECZYWISTOSCI (DLA PARANOIKOW)
//// GDYBYM CHCIAL NAPISAC KROTKI PROGRAM ZWROCILBYM WYNIK, KTORY OBLICZYLEM NA KARTCE (4 linijki)

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define LICZBA_CZEKOLADEK 28
#define LICZBA_WYBIERANYCH_CZEKOLADEK 3
#define PROG_TRAFIEN 2
#define WYPISUJ_W_TRAKCIE 0
#define FUNKCJA_TRAFIENIA >=

#define GAMES_TOTAL_COUNT (int) pow(LICZBA_CZEKOLADEK, LICZBA_WYBIERANYCH_CZEKOLADEK)

int czekoladki[LICZBA_CZEKOLADEK][2];

struct wyniki {
	int sumaTrafien;
	int liczbaWystapienZjawiska;
	int gryOdrzucone;
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
		czekoladki[i][0] = 1 + i;
	}
}

int getDigit(int digitIndex, int number) {
	return (number % (int) pow(LICZBA_CZEKOLADEK, digitIndex+1)) / (int) pow(LICZBA_CZEKOLADEK, digitIndex);
}

int hasDuplicatedDigits(int number) {
	int usedDigits[LICZBA_CZEKOLADEK];
	for(int i = 0; i < LICZBA_CZEKOLADEK; i++) usedDigits[i] = 0;
	for(int i = 0; i < LICZBA_WYBIERANYCH_CZEKOLADEK; i++) {
		int d = getDigit(i, number);
		//printf("\ngetDigit(%d, %d): %d\n", i, number, d);
		if (usedDigits[d] == 1) return 1;
		//for(int j = 0; j < LICZBA_CZEKOLADEK; j++) printf("%d ", usedDigits[j]);
		usedDigits[d] = 1;
	}

	return 0;
}

void zgadnijCzekoladki(int s) {
	///28 28 28, 28 26 26 itd sa odsiewane wczesniej
	for(int i = 0; i < LICZBA_WYBIERANYCH_CZEKOLADEK; i++) {
		czekoladki[getDigit(i, s)][1] = 1 + i;
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
	int liczbaLosowan = GAMES_TOTAL_COUNT - wyniki.gryOdrzucone;
	printf("liczba losowan: %d\n", liczbaLosowan);
	printf("suma trafien: %d\n", wyniki.sumaTrafien);
	printf("wystapienia zjawiska: %d\n", wyniki.liczbaWystapienZjawiska); 
	printf("udzial wystapien: %.30f\n", wyniki.liczbaWystapienZjawiska/((double)liczbaLosowan));
}

void wypiszTrafienia(int trafienia) {
	printf("trafienia: %d\n", trafienia);
}

int main() {
	for(int i = 0; i < GAMES_TOTAL_COUNT; i++) if (!hasDuplicatedDigits(i)) {
		wyczyscCzekoladki();
		wybierzCzekoladki();
		zgadnijCzekoladki(i);

		int trafienia = policzTrafienia();
		wyniki.sumaTrafien += trafienia; 
		if (trafienia FUNKCJA_TRAFIENIA PROG_TRAFIEN) {
			wyniki.liczbaWystapienZjawiska++;
			if (WYPISUJ_W_TRAKCIE)
				printf("zjawisko\n");
		}

		if(WYPISUJ_W_TRAKCIE) {
			wypiszCzekoladki();
			wypiszTrafienia(trafienia);
			printf("\n");
		}
	} else wyniki.gryOdrzucone++;
	wypiszWyniki();
}
