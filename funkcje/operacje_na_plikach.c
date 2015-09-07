#include "../lista.h"
#include "../interfejs.h"
#include <stdio.h>
#include <string.h>
int zapiszPlik(char* sciezkaZapisu, wezel* adres)
{
    FILE *plik;
    adres=adres->glowa;
    if ((plik=fopen(sciezkaZapisu,"w"))==NULL)
    {
        printf("Nie moge otworzyc pliku!\n");
        return 0;
    }//end if
    while(adres!=NULL)
    {
        fprintf(plik,"%s\n",adres->tabZnak);
        adres=adres->nast;
    }//end while
    if (fclose(plik))
    {
        printf("Nie moge zamknac pliku!\n");
        return 0;
    }//end if
    return 1;
}
int odczytZpliku(char* sciezkaZapisu, wezel* adres,unsigned int *kolumnaAdres,unsigned int *wierszAdres)
{
    FILE *plik;
    adres=adres->glowa;
    char znak;
    int i=-1;
    if ((adres->nast!=NULL)||(adres->nrKolumny!=0))//zabezpieczenie przed wczytaniem jezeli plik jest edytowany lub zostal juz wczytany
    {
        return 2;
    }//end if
    if ((plik=fopen(sciezkaZapisu,"r"))==NULL)
    {
        printf("Nie moge otworzyc pliku!\n");
        return 0;
    }//end if
    printf("\n");
    while (znak!=EOF)
    {
        znak=fgetc(plik);//pobranie znaku
        i++;
        adres->nrKolumny=i;//przypisanie do kolejnej kolumny
        if ((znak=='\n')||(i>ROZMIAR_STRONY-3))//jezeli trafi na koniec wiersza lub znak konca lini tworzy nowy element
        {
            adres->tabZnak[i]=znak;
            adres->tabZnak[i+1]='\0';
            adres=DodajWiersz(adres);
            i=-1;

        }
        else
        {
            adres->tabZnak[i]=znak;
        }
    }
    adres->tabZnak[i]='\0';
    *kolumnaAdres=adres->nrKolumny;
    *wierszAdres=adres->nrWiersza;
    if (fclose(plik))
    {
        printf("Nie moge zamknac pliku!\n");
        return 0;
    }
    return 1;
}
