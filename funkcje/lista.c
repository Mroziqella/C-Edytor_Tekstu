#include "../lista.h"
#include "../operacje_na_plikach.h"
#include "../interfejs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int ROZMIAR_BUF_KOPIOWANIA;
void ZerujL (wezel *lista)
{
    lista->nast=NULL;
    lista->poprz=NULL;
    lista->nrWiersza=0;
    lista->nrKolumny=0;
    lista->glowa=lista;
}

wezel* DodajWiersz (wezel *lista)
{
    wezel *wsk,*nowy;
    wsk=lista;
    while (wsk->nast!=NULL)
    {
        wsk=wsk->nast;
    }
    nowy=(wezel*)malloc(sizeof(wezel));
    if (nowy==NULL)
    {
        printf("Brak pamieci!!!");
        return NULL;
    }
    nowy->nrWiersza=wsk->nrWiersza+1;
    nowy->nast=NULL;
    nowy->poprz=wsk;
    nowy->glowa=wsk->glowa;
    wsk->nast=nowy;
    return nowy;
}

wezel* DodajWierszWsrodekListy (wezel *lista)
{
    wezel *wsk,*nowy;
    wsk=lista;
    nowy=(wezel*)malloc(sizeof(wezel));
    if (nowy==NULL)
    {
        printf("Brak pamieci!!!");
        return NULL;
    }
    nowy->nrWiersza=wsk->nrWiersza+1;
    nowy->nast=wsk->nast;
    nowy->poprz=wsk;
    nowy->glowa=wsk->glowa;
    wsk->nast=nowy;
    wsk=nowy->nast;
    wsk->poprz=nowy;


    while(wsk!=NULL)
    {
        wsk->nrWiersza=wsk->nrWiersza+1;
        wsk=wsk->nast;
    }
    return nowy;
}

int wyczyscListe(wezel *adres,unsigned int *kolumnaAdres,unsigned int *wierszAdres,int *flaga)
{
    while(adres->nast!=NULL)//ustawia na koniec listy
    {
        adres=adres->nast;
    }//end while

    while (adres!=adres->glowa)//idzie przez wszystkie elementy listy od konca i usuwa
    {
        adres=adres->poprz;
        free(adres->nast);
        adres->nast=NULL;
    }
    adres->nrKolumny=0;
    adres->nrWiersza=0;
    *kolumnaAdres=adres->nrKolumny;
    *wierszAdres=adres->nrWiersza;
    *flaga=0;
    return 0;
}
wezel* przejdDoWiersza(wezel *adres,int nrWierszaPodanego,unsigned int *kolumnaAdres,unsigned int *wierszAdres )
{
    if (nrWierszaPodanego>=0)//przechodzi do wiersza o podnanym numerze
        while ((adres->nrWiersza!=nrWierszaPodanego)&&(adres->nast!=NULL))
            adres=adres->nast;

    else//przechodzi na koniec listy
        while (adres->nast!=NULL)
            adres=adres->nast;
    *kolumnaAdres=adres->nrKolumny;
    *wierszAdres=adres->nrWiersza;
    return adres;
}

int wyszukaj(char *tab, char *buf2,int rozmiarBuf2)
{
    char buf1[ROZMIAR_STRONY];//przechowuje dane
    strcpy(buf1,tab);//kopiuje dane do bufora z tablicy podanej jako argument
    int i=0;
    if(strlen(buf1)<strlen(buf2)) return -1;//jeeli wyraz podany jest mniejszy od wiersza
    for(i = 0; i<strlen(buf1)-strlen(buf2)+1; i++)
    {
        if (buf1[i]==buf2[0])
        {
            int x;
            for (x=1; x<strlen(buf2); x++)
            {
                if (buf1[i+x] != buf2[x]) break;
            }
            if (x==strlen(buf2)) return i;
        }
    }
    return -1;
}

int kopiuj(char *buf,unsigned int licznik,char znak)
{
    buf[licznik]=znak;
    buf[licznik+1]='\0';

    return 0;
}

void wklej(wezel *adres,char *buf, int kolumna,int wiersz)
{
    unsigned int i,j,rozmiarBuf=strlen(buf);
    char buf2[ROZMIAR_BUF_KOPIOWANIA+ROZMIAR_STRONY];
    int dopelnienie;//zm mówi ile znaków sie zmiesci w wierszy
    strcpy(buf2,buf);//przechowanie buf kopowania zeby moc go przywrocic
    if (kolumna==adres->nrKolumny)// mówi czy wklejamy na końcu wiersza(zaczynamy klejać w miejscu znaku konca tekstu
    {
        if (adres->nrKolumny+rozmiarBuf<ROZMIAR_STRONY)//mówi czy się zmiesci tekst po wklejenu we wierszu jęzeli tak wykonuje kopiowanie
        {
            for(i=0,kolumna; buf[i]!='\0'; i++,kolumna++)
            {
                adres->tabZnak[kolumna]=buf[i];//kopiujemy do konca w buforze od miejsca znaku konca tekstu w wierszu
            }
            adres->tabZnak[kolumna]=buf[i];
            adres->nrKolumny=strlen(adres->tabZnak);//liczy długosc wiersza po skopiowaniu

        }//end if
        else
        {
            dopelnienie=ROZMIAR_STRONY-(adres->nrKolumny+rozmiarBuf);// liczy ile zmiesci sie znakow w wersie
            dopelnienie--;//znak konca lini
            if (dopelnienie<0)//jezeli się nie zmieści tekst w wierszu
            {
                for(i=0,kolumna; i<rozmiarBuf+dopelnienie; i++,kolumna++) //+dopelnienie bo dopelnienie bedzie zawsze <0
                //wklejamy ilość znaków jaka nam się zmiesci w wierszu
                {
                    adres->tabZnak[kolumna]=buf[i];
                }
                adres->tabZnak[kolumna]='\0';
                adres->nrKolumny=strlen(adres->tabZnak);
                j=i;//pozycja w buforze
                for(i=0; j<rozmiarBuf; j++,i++)// przesuniecie danych w buforze o ilosc elementow zapisanych do wiersza
                {
                    buf[i]=buf[j];
                }
                buf[i]='\0';
            }
            if(adres->nast!=NULL)//dodawanie wiersza
                adres=DodajWierszWsrodekListy(adres);
            else
                adres=DodajWiersz(adres);
            kolumna=0;//ustaiwnie na początek wiersza
            adres->tabZnak[kolumna]='\0';//przypisanie znaku konca lini
            adres->nrKolumny=0;//przypisanie dlugosci wiersza
            wiersz++;//zwiekszenie zmiennej na kolejny wiersz
            wklej(adres,buf,kolumna,wiersz);
            strcpy(buf,buf2);//przywrocienie wartosci w buf kopiowania

        }//end else
    }//end if
    else//jezlei wkeljamy  w srodku wiersza
    {
        strncpy(buf2,adres->tabZnak,kolumna);//kopiowanie calego tekstu do bufora od numeru kolumny w tablicy
        buf2[kolumna]='\0';
        strcat(buf2,buf);//łaczenie buf z buf2
        strcat(buf2,adres->tabZnak+kolumna);//kopiowanie reszty tekstu
        gotoxy(kolumna,wiersz+WYSOKOSC_MENU_GORNEGO);
        kolumna=0;
        adres->nrKolumny=kolumna;
        wklej(adres,buf2,kolumna,wiersz);// rekurencyja wklejenie od nowa calego wiersza
    }


}

int wytnij(wezel* adresListy,char* buf,unsigned int licznikStartX,unsigned int licznikStartY,int licznik)
{
    int i,j,licznikTmp,licznikStartXTmp,wynik; //licznikTmp-licznik tymczasowy
    wezel *adresTymczasowy,*adres;
    adres=adresListy;
    adres=adres->glowa;
    while(adres->nrWiersza<licznikStartY)//przejscie do wiersza z ktorego zaczeto kopiowanie
    {
        adres=adres->nast;
    }
    if (licznik<=strlen(adres->tabZnak)-licznikStartX)//sprawdzenie czy wycinamy tylko z jednego wiersza
    {
        if(adres->tabZnak[licznikStartX+licznik-1]!='\0')//czy wycinanie konczy sie na koncu wiersza jezeli tak wycinamy
        {
            strcpy(adres->tabZnak+licznikStartX,adres->tabZnak+licznikStartX+licznik);
            adres->nrKolumny=strlen(adres->tabZnak);
            return -1;
        }
        else //jezeli nie wycinamy z dopisaniem konca znaku
        {
            strcpy(adres->tabZnak+licznikStartX,adres->tabZnak+licznikStartX+licznik);
            adres->tabZnak[licznikStartX]='\0';
            adres->nrKolumny=strlen(adres->tabZnak);
        }
        return -1;
    }
    else//jezeli wycinamy z wielu wierszy
    {
        adresTymczasowy=adres;
        licznikTmp=licznik;
        licznikStartXTmp=licznikStartX;
        for(i=0; licznik>0; i++)
        {
            wynik=licznik;
            licznik=licznik-(adres->nrKolumny+1-licznikStartXTmp);//odejmujemy od licznika ilość
            // kolum znajdujacych sie w wierszu(wirtualnie pozbywamy sie wiersza w celu obliczenia ile wierszy potrzebujemy wyciac)
            licznikStartXTmp=0;
            adres=adres->nast;
        }
        licznik=licznikTmp;//przywracamy wartosci poczatkowe
        adres=adresTymczasowy;
        for(j=0; j<i; j++)//wykonujemy do konca wierszy do wyciecia (i-ilosc wierszy)
        {
            licznikTmp=adres->nrKolumny-licznikStartX;//ustalamy liczbe znakow do wyciecia z pierwszego kopiowanego wiersza, a później całe wiersze
            if(j==i-1)//przy ostatnim wierszu kopiujemy tylko ilość znaków jaka została
                licznikTmp=wynik;
            wytnij(adres,buf,licznikStartX,licznikStartY,licznikTmp);//wywołanie rekurencyje kopiowania
            licznik=licznik-(adres->nrKolumny+1-licznikStartX);//zmiejszenie licznika o ilosc skopiowanych
            licznikStartX=0;
            licznikStartY++;//przechodzimy wiersz nizej
            adres=adres->nast;
        }
    }
    return 0;
}






