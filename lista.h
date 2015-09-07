#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#define ROZMIAR_STRONY 80

typedef struct wezel
{
    struct wezel *nast,*poprz,*glowa;
    char tabZnak[ROZMIAR_STRONY];
    unsigned int nrWiersza,nrKolumny;
}wezel;


void ZerujL (wezel *lista);

wezel* DodajWiersz (wezel *lista);
int wyczyscListe(wezel *adres,unsigned int *kolumnaAdres,unsigned int *wierszAdres,int *flaga);
wezel* DodajWierszWsrodekListy (wezel *lista);
wezel* przejdDoWiersza(wezel *adres,int nrWierszaPodanego,unsigned int *kolumnaAdres,unsigned int *wierszAdres );
int wyszukaj(char *adres, char *buf2,int rozmiarBuf2);
void ruchKursorOperacje(wezel *adresListy,unsigned int *kolumnaAdres,unsigned int *wierszAdres);// ruch kursora podczas operacji kopiuj wklej
int wytnij(wezel* adresListy,char* buf,unsigned int licznikStartX,unsigned int licznikStartY,int licznik);
int kopiuj(char *buf,unsigned int licznik,char znak);
void wklej(wezel *adres,char *buf, int kolumna,int wiersz);

#endif // LISTA_H_INCLUDED
