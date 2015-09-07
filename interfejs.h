#ifndef INTERFEJS_H_INCLUDED
#define INTERFEJS_H_INCLUDED

#define WYSOKOSC_KONSOLI 49
#define SZEROKOSC_KONSOLI 79

#define WYSOKOSC_MENU_GORNEGO 12
#define WYSOKOSC_MENU_DOLNEGO 5


#define NAZWAPROGRAMU "EDYTOR TEKSTU"
#define AUTORZY "Mroz Kamil"
#define WERSJA "Wersja 1.0"

#define ZAMARZTESKST "                                                                                "
#define KRESKA       "--------------------------------------------------------------------------------"

#define ROZMIAR_MENU 9
#define MENU    gprintf("Zapisz Plik",35,21);\
                gprintf("Wczytaj Plik",35,22);\
                gprintf("Zakoncz edycje i wyczysc",35,23);\
                gprintf("Przejdz do wiersza",35,24);\
                gprintf("Wyszukaj",35,25);\
                gprintf("Operacje",35,26);\
                gprintf("Opcje",35,27);\
                gprintf("Wyjscie",35,28);

#define ROZMIAR_MENU_OPCJE 3
#define MENU_OPCJE      gprintf("Zamien sciezke zapisu",35,21);\
                        gprintf("Zamien sciezke wczytania",35,22);\
                        gprintf("Zamien rozmiar buforu",35,23);


#define OBRAMOWKA_MENU 40


#define MENUWYPISZNOWY  gprintf("Nowy Plik",35,20);\
                        MENU;
#define MENUWYPISZKONTYNULUJ    gprintf("Kontynuluj edycje pliku",35,20);\
                                MENU;


#define STEROWANIE_MENU_OPIS "Sterowanie - strzalki, zatwierdzenie wyboru - ENTER, wyjscie - ESC"
void gotoxy(int x, int y);
int WysrodkujTekst(char *tekst);
void gprintf(char *tekst,int x, int y);
void PasekOpcjiGorny();
void ekranPowitalny();
void pobierzZnakWsrodkuListy(wezel *adresListy,wezel *adresListyWybranegoWiersza,unsigned int *kolumnaAdres,unsigned int *wierszAdres,int *Edycja);
void wybierz(wezel *wsk,unsigned int *znakNumer,unsigned int *wierszNumer, int wybor,char *zapis,char *odczyt,int *flaga);
void wypiszTekst(wezel *adresListy,unsigned int *kolumnaAdres,unsigned int *wierszAdres);

#endif // INTERFEJS_H_INCLUDED
