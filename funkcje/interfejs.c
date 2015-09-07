#include "../lista.h"
#include "../interfejs.h"
#include "../operacje_na_plikach.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
int ROZMIAR_BUF_KOPIOWANIA=250;
void gotoxy(int x, int y)//ustawia kursor w odpowiedzie miejsce
{
    COORD cord;
    cord.X = x;
    cord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}

int WysrodkujTekst(char *tekst)//wysrodkowuje tekst
{
    return (SZEROKOSC_KONSOLI-strlen(tekst))/2;
}

void gprintf(char *tekst,int x, int y)//wypisuje dany tekst w odpowiednim miejscu
{
    gotoxy(x,y);
    printf(tekst);
}
void OpcjeWOperacjach()//wypisuje informacje w zakladce operacje
{
    PasekOpcjiGorny();
    gprintf("Tryb: OPERACJI",WysrodkujTekst("Tryb: OPERACJE"),5);
    gprintf("Zanzaczenie/anulowanie zaznaczenia - +/-, Kopiuj- c, Wklej- v, Wytnij- x,       Wyczysc bufor- f",0,WYSOKOSC_MENU_GORNEGO-3);
}
void OpcjeWEdycji()//wypisuje informacje w zakladce edycji
{
    PasekOpcjiGorny();
    gprintf("Tryb: EDYCJI",WysrodkujTekst("Tryb: EDYCJI"),5);
    gprintf("Sterowanie - strzalki gora/dol, nowa linia - ENTER, Usuniece znaku - Backspace, wyscie do menu - ESC",0,WYSOKOSC_MENU_GORNEGO-3);
}
void PasekOpcjiGorny()//wypisuje pasek górny
{

    gprintf(NAZWAPROGRAMU,WysrodkujTekst(NAZWAPROGRAMU),1);
    gprintf(AUTORZY,WysrodkujTekst(AUTORZY),2);
    gprintf(WERSJA,WysrodkujTekst(WERSJA),3);
    gprintf(KRESKA,0,4);
    gprintf(KRESKA,0,WYSOKOSC_MENU_GORNEGO-1);
}

void ekranPowitalny()//wypisuje ekran powitalny
{
    gotoxy(0,7);
    printf("         #######   #######    #       #   #######   #######   #######\n"
           "         #         #      #    #     #       #      #     #   #     #\n"
           "         #         #      #     #   #        #      #     #   #    #\n"
           "         #######   #      #      # #         #      #     #   #  ##\n"
           "         #         #      #       #          #      #     #   #    #\n"
           "         #         #      #       #          #      #     #   #     #\n"
           "         #######   #######        #          #      #######   #      #\n"
           "\n\n"
           "                            #####  #####  ##  #####     \n"
           "                                #  #   #   #  #   \n"
           "                            #####  #   #   #  #####\n"
           "                            #      #   #   #      #\n"
           "                            #####  #####   #  ##### \n");
    gprintf(NAZWAPROGRAMU,WysrodkujTekst(NAZWAPROGRAMU),30);
    gprintf(AUTORZY,WysrodkujTekst(AUTORZY),31);
    gprintf("Wcisnij dowolny klawisz aby kontynulowac...",WysrodkujTekst("Wcisnij dowolny klawisz aby kontynulowac..."),33);
    getch();
    system("cls");
    PasekOpcjiGorny();
}

void wybierz(wezel *wsk,unsigned int *znakNumer,unsigned int *wierszNumer, int wybor,char *zapis,char *odczyt,int *flaga)
//przechodzimy do funcji która wskaże jaka opcja w menu została wybrana
//argumenty funkcji to adres listy,licznik kolumn-znakNumer, licznik wierszy,sciezka zapisu pliku, odczytu pliku i flaga określająca zmianae tekstu z nowy plik na kontynułuj edycje
{
    wezel *adresPrzejsciaDoWybranejListy,*AdresPomocniczy=wsk;
    int nrWiersza;
    int nrKol=0,znaleziono=0;//znaleziono- licznik do wypisywania wyników w kolejnym wierszu przy wyszukiwaniu
    char tekstWyszukaj[30],znakWybor=80,pozycjaStrz=-1;//pozycjaStr wykorzystywane w menu opcji
    CONSOLE_CURSOR_INFO ci;//urywanie kursora
    HANDLE hC=GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hC, &ci);
    ci.bVisible=0;
    SetConsoleCursorInfo(hC, &ci);
    switch(wybor)
    {
    case 0://EDYCJA
    {
        nrWiersza=-1;//przejscie do ostatniej lini
        /* AdresPomocniczy=wsk->glowa;
         while(AdresPomocniczy->nast!=NULL)
             AdresPomocniczy=AdresPomocniczy->nast;*/
        adresPrzejsciaDoWybranejListy=przejdDoWiersza(wsk,nrWiersza,znakNumer,wierszNumer);
        //nr wierszza okresla do którego wiersza ma przejść -1 oznacza przejscie do ostatniego wiersza, reszta to polozenie kursora
        system("cls");
        OpcjeWEdycji();
        pobierzZnakWsrodkuListy(wsk,adresPrzejsciaDoWybranejListy,znakNumer,wierszNumer,flaga);//pobiera znaki
        break;
    }
    case 1://ZAPIS
    {
        PasekOpcjiGorny();
        if(zapiszPlik(zapis,wsk))
            gprintf("Plik zapisany poprawnie!",WysrodkujTekst("Plik zapisany poprawnie!"),7);
        else
            gprintf("Plik nie zostal zapisany!",WysrodkujTekst("Plik nie zostal zapisany!"),7);
        break;
    }
    case 2://WCZYTANIE
    {
        if ((wsk->nast!=NULL)||(wsk->nrKolumny!=0))
        {
            gprintf("Nie mozna wczytywac pliku podczas edycji!",WysrodkujTekst("Nie mozna wczytywac pliku podczas edycji!"),7);
            break;
        }
        else   if(odczytZpliku(odczyt,wsk,znakNumer,wierszNumer))
            gprintf("Plik wczytany poprawnie!",WysrodkujTekst("Plik wczytany poprawnie!"),7);
        else
            gprintf("Plik nie zostal wczytany!",WysrodkujTekst("Plik nie zostal wczytany!"),7);
        break;
    }
    case 3://USUNIECIE
    {
        zapiszPlik("temp.txt",wsk);//zapisanie do pliku tymczasowego
        gprintf("Edycje zakonczono, praca zostala usunieta!",WysrodkujTekst("Edycje zakonczono, praca zostala usunieta!"),7);
        wyczyscListe(wsk,znakNumer,wierszNumer,flaga);//czyszczenie listy
        break;
    }
    case 4://PRZEJDZ DO WIERSZA
    {
        ci.bVisible=1;//widocznosc kursora
        SetConsoleCursorInfo(hC, &ci);
        gprintf("PRZEJDZ DO WIERSZA",WysrodkujTekst("Przejd do wiersza"),5);
        gprintf("Zatwierdz - ENTER",0,WYSOKOSC_MENU_GORNEGO-2);
        AdresPomocniczy=wsk->glowa;
        gprintf("Zakres wierszy ",WysrodkujTekst("Zakres wierszy: od %i do %i     "),7);
        while(AdresPomocniczy->nast!=NULL)//liczy ile wierszow sie znajduje na liscie
            AdresPomocniczy=AdresPomocniczy->nast;
        printf("od 1 do %i",AdresPomocniczy->nrWiersza+1);
        gprintf("Ustaw kurosor na koniec wiersza nr: ",WysrodkujTekst("Ustaw kurosor na koniec wiersza i wcisnij ENTER: "),8);
        scanf("%i",&nrWiersza);
        nrWiersza--;//zmiejszamy o 1 bo indeksowanie jest od 0
        if ((nrWiersza>AdresPomocniczy->nrWiersza)||(0==AdresPomocniczy->nrWiersza)) //wlaczenie zwyklej edycji
        {
            if (AdresPomocniczy->nrWiersza!=nrWiersza+1) //brak wyswietlania komunikatu przy ostatni wersie
            {
                gotoxy(WysrodkujTekst("Brak wiersza nr: %i za 3 sek przejscie do ostatniego wiersza"),21);
                printf("Brak wiersza nr: %i za 3 sek przejscie do ostatniego wiersza!!!",nrWiersza+1);
                Sleep(3000);
            }
            system("cls");
            OpcjeWEdycji();
            adresPrzejsciaDoWybranejListy=przejdDoWiersza(wsk,nrWiersza,znakNumer,wierszNumer);
            pobierzZnakWsrodkuListy(wsk,adresPrzejsciaDoWybranejListy,znakNumer,wierszNumer,flaga);
            break;
        }
        else
        {
            adresPrzejsciaDoWybranejListy=przejdDoWiersza(wsk,nrWiersza,znakNumer,wierszNumer);
            system("cls");
            PasekOpcjiGorny();
            OpcjeWEdycji();
            pobierzZnakWsrodkuListy(wsk,adresPrzejsciaDoWybranejListy,znakNumer,wierszNumer,flaga);
        }
        break;
    }
    case 5://WYSUKAJ
    {
        ci.bVisible=1;
        SetConsoleCursorInfo(hC, &ci);
        gprintf("WYSUKAJ",WysrodkujTekst("WYSZUKAJ"),5);
        gprintf("Zatwierdz - ENTER",0,WYSOKOSC_MENU_GORNEGO-2);
        gotoxy(WysrodkujTekst("Podaj tekst jaki chcesz wyszukac max 30 znakow: "),7);
        printf("Podaj tekst jaki chcesz wyszukac max 30 znakow: ");
       // fscanf(stdin,"%s",tekstWyszukaj);
        gets(tekstWyszukaj);//pobieranie ze spacja
        wsk=wsk->glowa;
        nrWiersza=0;
        gotoxy(0,WYSOKOSC_MENU_GORNEGO);
        while (wsk!=NULL)
        {
            nrKol=wyszukaj(wsk->tabZnak,tekstWyszukaj,30);

            if (nrKol>-1)
            {
                printf("Znaleziony wyraz znajduje sie w kolumnie: %i w wierszu: %i\n",nrKol,wsk->nrWiersza);
                znaleziono++;
            }
            wsk=wsk->nast;
        }
        if (znaleziono==0)
            gprintf("Nie znaleziono frazy!",WysrodkujTekst("Nie znaleziono frazy!"),14+znaleziono);
        gprintf("Wcisnij jakis klawisz...",WysrodkujTekst("Wcisnij jakis klawisz..."),16+znaleziono);
        getch();//przytrzymuje widok wyików
        system("cls");
        break;
    }
    case 6://OPERACJE
    {
        system("cls");
        ruchKursorOperacje(wsk,znakNumer,wierszNumer);//ruch kursorem przy operacjach
        break;
    }
    case 7://OPCJE
    {
        system("cls");
        PasekOpcjiGorny();
        gprintf("OPCJE",WysrodkujTekst("OPCJE"),5);
        MENU_OPCJE
        while (znakWybor!=27)
        {
            gprintf("    ",31,21+pozycjaStrz);
            switch(znakWybor)
            {
            case 80:
            {
                if (pozycjaStrz<ROZMIAR_MENU_OPCJE-1)
                    pozycjaStrz++;//zmiana pozyji w menu na dół
                break;
            }//end 80:
            case 72:
            {
                if (pozycjaStrz>0)
                    pozycjaStrz--;//zmiana pozycji w menu na górę
                break;
            }//end 72:
            case 13:
            {
                system("cls");
                PasekOpcjiGorny();
                gprintf("OPCJE",WysrodkujTekst("OPCJE"),5);
                gprintf("Zatwierdz i wyjdz - ENTER",0,WYSOKOSC_MENU_GORNEGO-2);
                switch(pozycjaStrz)
                {
                case 0:
                {
                    ci.bVisible=1;
                    SetConsoleCursorInfo(hC, &ci);
                    gprintf("Bierzaca sciezka zapisu: ",WysrodkujTekst("Bierzaca sciezka zapisu                               "),7);
                    printf("%s",zapis);
                    gprintf("Podaj nowa sciezke: ",WysrodkujTekst("Podaj nowa sciezke                                "),WYSOKOSC_MENU_GORNEGO+7);
                    gets(zapis);
                    system("cls");
                    PasekOpcjiGorny();
                    gprintf("OPCJE",WysrodkujTekst("OPCJE"),5);
                    ci.bVisible=0;
                    SetConsoleCursorInfo(hC, &ci);
                    MENU_OPCJE//wypisanie tekstu przez makrodefinicje
                    break;
                }
                case 1:
                {
                    ci.bVisible=1;
                    SetConsoleCursorInfo(hC, &ci);
                    gprintf("Bierzaca sciezka odczytu: ",WysrodkujTekst("Bierzaca sciezka odczytu                               "),7);
                    printf("%s",odczyt);
                    gprintf("Podaj nowa sciezke: ",WysrodkujTekst("Podaj nowa sciezke                                "),WYSOKOSC_MENU_GORNEGO+7);
                    gets(odczyt);
                    system("cls");
                    PasekOpcjiGorny();
                    gprintf("OPCJE",WysrodkujTekst("OPCJE"),5);
                    ci.bVisible=0;
                    SetConsoleCursorInfo(hC, &ci);
                    MENU_OPCJE//wypisanie tekstu przez makrodefinicje
                    break;
                }
                case 2:
                {
                    ci.bVisible=1;
                    SetConsoleCursorInfo(hC, &ci);
                    gprintf("Bierzacy rozmiar bufora: ",WysrodkujTekst("Bierzacy rozmiar bufora:"),7);
                    printf("%i",ROZMIAR_BUF_KOPIOWANIA);
                    gprintf("Podaj nowa rozmiar bufora: ",WysrodkujTekst("Podaj nowa rozmiar bufora:"),WYSOKOSC_MENU_GORNEGO+7);
                    scanf("%i",&ROZMIAR_BUF_KOPIOWANIA);
                    fflush(stdin);
                    system("cls");
                    PasekOpcjiGorny();
                    gprintf("OPCJE",WysrodkujTekst("OPCJE"),5);
                    ci.bVisible=0;
                    SetConsoleCursorInfo(hC, &ci);
                    MENU_OPCJE//wypisanie tekstu przez makrodefinicje
                }//end case 2

                }//end switch
                break;
            }//end 13:
            }//end switch
            gotoxy(0,7);
            printf(ZAMARZTESKST);
            gotoxy(0,8);
            printf(ZAMARZTESKST);
            gprintf("Bierzaca sciezka zapisu: ",WysrodkujTekst("Bierzaca sciezka zapisu                               "),7);
            printf("%s",zapis);
            gprintf("Bierzaca sciezka zapisu: ",WysrodkujTekst("Bierzaca sciezka zapisu                               "),8);
            printf("%s",odczyt);
            gprintf(STEROWANIE_MENU_OPIS,0,WYSOKOSC_MENU_GORNEGO-2);
            gprintf("===>",31,21+pozycjaStrz);
            znakWybor=getch();
        }//end while
        gprintf("    ",31,21+pozycjaStrz);
        gprintf(ZAMARZTESKST,0,7);
        gprintf(ZAMARZTESKST,0,8);
        gprintf(ZAMARZTESKST,0,5);
        gprintf(ZAMARZTESKST,0,21+0);
        gprintf(ZAMARZTESKST,0,21+1);
        break;
    }
    case 8:
    {
        gprintf("Dziekujemy za korzystanie z naszego programu.",WysrodkujTekst("Dziekujemy za korzystanie z naszego programu."),15);
        Sleep(1500);
        exit(0);
        break;
    }
    default:
    {
        break;
    }
    }//end switch
}//end wybierz

void pobierzZnakWsrodkuListy(wezel *adresListy,wezel *adresListyWybranegoWiersza,unsigned int *kolumnaAdres,unsigned int *wierszAdres,int *Edycja)
{
    CONSOLE_CURSOR_INFO ci;//urywanie kursora
    HANDLE hC=GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hC, &ci);
    ci.bVisible=1;//wyswietlenie kurosra
    SetConsoleCursorInfo(hC, &ci);
    char znakPobrany;
    wezel *adresListyTymczasowy;
    int i;
    unsigned int wiersz=*wierszAdres,kolumna=*kolumnaAdres;
    wypiszTekst(adresListy,kolumnaAdres,wierszAdres);
    adresListy=adresListyWybranegoWiersza;
    kolumna=*kolumnaAdres;
    gotoxy(kolumna,WYSOKOSC_MENU_GORNEGO+adresListy->nrWiersza);
    int znakSpec=0;
    while ((znakPobrany=getch())!=27)
    {
        if (znakPobrany==-32)//znak specjalny np strzalki przekirowanie do obslugi ich
        {
            kolumna=kolumna;
            wiersz=wiersz;
            znakSpec=1;
            continue;
        }//end if
        if (znakSpec==1)
        {
            switch(znakPobrany)
            {
            case 72:
            {
                if (wiersz>0)
                {
                    wiersz--;
                    adresListy->nrKolumny=kolumna;
                    adresListy->tabZnak[kolumna]='\0';//przypisanie konca tekstu zeby nie wypisywalo smieci w ostatnim wierszu
                    adresListy=adresListy->poprz;
                    kolumna=adresListy->nrKolumny;
                }
                break;

            }//end case 72
            case 80:
            {
                if (adresListy->nast!=NULL)
                {
                    wiersz++;
                    adresListy->nrKolumny=kolumna;
                    adresListy->tabZnak[kolumna]='\0';
                    adresListy=adresListy->nast;
                    kolumna=adresListy->nrKolumny;
                }
                break;

            }//end case 72
            }//end switch
            gotoxy(kolumna,wiersz+WYSOKOSC_MENU_GORNEGO);
            znakSpec=0;
            continue;


        }//end if

        switch(znakPobrany)
        {
        case 8://usuwanie znaku
        {
            i=0;
            if(kolumna>0) //jak są 2 linie puste
            {
                kolumna--;
            }
            adresListy->tabZnak[kolumna]='\0';
            printf("\r%s",adresListy->tabZnak);
            printf(" ");
            printf("\r%s",adresListy->tabZnak);
            if (wiersz<0)
                break;//zabezpieczenie przed usuwaniem nieistniejacych elementow listy mniejszych od 0
            if(kolumna==0)
            {

                if ((adresListy->nast==NULL)&&(adresListy->nrWiersza!=0)) //jezeli kursor jest na ostatnim elemncie w ostatnim wierszu
                {
                    adresListy=adresListy->poprz;
                    kolumna=adresListy->nrKolumny;
                    wiersz--;
                    gotoxy(kolumna,WYSOKOSC_MENU_GORNEGO+wiersz);
                    free(adresListy->nast);
                    adresListy->nast=NULL;
                }
                else if ((adresListy->nrWiersza>0)) //jezeli kurosr nie jest na glowie listy usuwanie wezla
                {
                    adresListy=adresListy->poprz;
                    adresListyTymczasowy=adresListy;
                    adresListyTymczasowy=adresListyTymczasowy->nast;
                    adresListy->nast=adresListyTymczasowy->nast;
                    adresListy=adresListy->nast;
                    adresListy->poprz=adresListyTymczasowy->poprz;
                    free(adresListyTymczasowy);
                    adresListyTymczasowy=NULL;
                    adresListy=adresListy->poprz;//powrod na wczesniejszy elemnt
                    wiersz--;
                    kolumna=adresListy->nrKolumny;
                    gotoxy(adresListy->nrKolumny,wiersz);
                }

                adresListyTymczasowy=adresListy;
                i=adresListy->nrWiersza;
                while(adresListyTymczasowy->nast!=NULL)//przesuniecie tekstu w gore i usuniecie
                {
                    adresListyTymczasowy->nrWiersza=i;
                    gotoxy(0,WYSOKOSC_MENU_GORNEGO+adresListyTymczasowy->nrWiersza);//gdzie zmazac
                    printf(ZAMARZTESKST);//zmazanie tekstu
                    gotoxy(0,WYSOKOSC_MENU_GORNEGO+adresListyTymczasowy->nrWiersza);//gdzie napisac
                    printf("%s",adresListyTymczasowy->tabZnak);//napisanie na nowo
                    i++;
                    adresListyTymczasowy=adresListyTymczasowy->nast;
                }
                adresListyTymczasowy->nrWiersza=i;//ostatni element listy pominiety w petli
                gotoxy(0,WYSOKOSC_MENU_GORNEGO+adresListyTymczasowy->nrWiersza);//gdzie zmazac
                printf(ZAMARZTESKST);//zmazanie tekstu
                gotoxy(0,WYSOKOSC_MENU_GORNEGO+adresListyTymczasowy->nrWiersza);//gdzie napisac
                printf("%s",adresListyTymczasowy->tabZnak);//napisanie na nowo
                gotoxy(0,WYSOKOSC_MENU_GORNEGO+adresListyTymczasowy->nrWiersza+1);//gdzie zmazać
                printf(ZAMARZTESKST);
            }//end if
            break;
        }//end case 8:
        default:
        {

            if(kolumna<ROZMIAR_STRONY-1)
            {
                adresListy->tabZnak[kolumna]=znakPobrany;
                printf("%c",adresListy->tabZnak[kolumna]);
                kolumna++;
                if(kolumna<ROZMIAR_STRONY-1)//je¿eli nie przekroczymy wartosc tablicy, przejscie do nowej lini po wpisaniu ostatnigo znaku
                    break;
            }

        }
        case 13://przejscie do nowej lini
        {
            if (adresListy->nast==NULL)//jezeli jest ostatni element listy
            {

                adresListy->tabZnak[kolumna]='\0';
                adresListy->nrKolumny=kolumna;
                *kolumnaAdres=kolumna;
                adresListy=DodajWiersz(adresListy);//dodaje wiersz
                kolumna=0;
                wiersz++;
                printf("\n");
                // break;
            }//end if
            else//jezeli jest w srodku listy
            {
                adresListy->tabZnak[kolumna]='\0';//przypisanie konca tekstu
                adresListy->nrKolumny=kolumna;// przypisanie ile liter jest w wierszu
                *kolumnaAdres=kolumna;//orzekazanie przez wskaźnik wartosci
                adresListy=DodajWierszWsrodekListy(adresListy);//dodanie wiersza
                kolumna=0;//wyzerowanie kolumny - ilosc znakow jest równa 0
                adresListy->tabZnak[kolumna]='\0';//znak jako zabezpieczenie jezeli odrazu sie wcisnie enter
                wiersz++;
                adresListyTymczasowy=adresListy;
                gotoxy(0,WYSOKOSC_MENU_GORNEGO+adresListy->nrWiersza);
                printf(ZAMARZTESKST);
                printf("%s",adresListyTymczasowy->tabZnak);
                while(adresListyTymczasowy!=NULL)//przypiuje tekst po zmianie
                {
                    gotoxy(0,WYSOKOSC_MENU_GORNEGO+adresListyTymczasowy->nrWiersza);
                    printf(ZAMARZTESKST);
                    gotoxy(0,WYSOKOSC_MENU_GORNEGO+adresListyTymczasowy->nrWiersza);
                    printf("%s",adresListyTymczasowy->tabZnak);
                    adresListyTymczasowy=adresListyTymczasowy->nast;
                }//end while
                gotoxy(0,adresListy->nrWiersza);//wraca do polozenia kursora
                //break;
            }
            zapiszPlik("temp1.txt",adresListy);//zapisanie do pliku tymczasowego jako zabezpieczenie przed utratą danych po bledzie programu
            break;
        }//end case 13

        }//end switch
        gotoxy(kolumna,WYSOKOSC_MENU_GORNEGO+adresListy->nrWiersza);
        if (wiersz==0&&kolumna==0&&adresListy->nast!=NULL)// sprawdza czy są dalsze elementy listy jezeli są to ustawia flage na 1 zeby pisało dalej kontynułowanie edycji
        {
            *Edycja=1;
        }
    }//end while
    adresListy->tabZnak[kolumna]='\0';
    adresListy->nrKolumny=kolumna;
    system("cls");
    PasekOpcjiGorny();
    *kolumnaAdres=kolumna;
    *wierszAdres=wiersz;

}

void wypiszTekst(wezel *adresListy,unsigned int *kolumnaAdres,unsigned int *wierszAdres)
{
    unsigned int kolumna=*kolumnaAdres,wiersz=*wierszAdres;
    if ((kolumna!=0)||(wiersz!=0))//{//jeeli nie jest pierwszym elementem wykonuje wypisanie tekstu obecnego w liscie
    {
        adresListy=adresListy->glowa;
        while (adresListy->nast!=NULL)
        {
            gotoxy(0,WYSOKOSC_MENU_GORNEGO+adresListy->nrWiersza);
            printf("%s",adresListy->tabZnak);
            adresListy=adresListy->nast;
        }//end while
        gotoxy(0,WYSOKOSC_MENU_GORNEGO+adresListy->nrWiersza);//wypisuje ostatni wiersz
        printf("%s",adresListy->tabZnak);
    }//end if
}

void ruchKursorOperacje(wezel *adresListy,unsigned int *kolumnaAdres,unsigned int *wierszAdres)// ruch kursora podczas operacji kopiuj wklej
{

    char znak,buf[ROZMIAR_BUF_KOPIOWANIA];
    unsigned int kolumna,wiersz,licznikKopiowaniaStartX=0,licznikKopiowaniaStartY=0;
    int znakSpec=0,flaga=1,flagaWartoscBuf=0,licznikKopiowania=0; //flaga -> pokazuje czy kursor zostal zablokowany:0/nie zablokowany: 1
    char z=219;//przypisanie kodu ASCII całej zamalowanej komórki konsoli
    CONSOLE_CURSOR_INFO ci;//urywanie kursora
    HANDLE hC=GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hC, &ci);
    ci.bVisible=1;//wyswietlenie kurosra
    SetConsoleCursorInfo(hC, &ci);
    OpcjeWOperacjach();
    wypiszTekst(adresListy,kolumnaAdres,wierszAdres);
    adresListy=adresListy->glowa;
    adresListy=przejdDoWiersza(adresListy,-1,kolumnaAdres,wierszAdres);
    kolumna=*kolumnaAdres;
    wiersz=*wierszAdres;
    buf[licznikKopiowania]='\0';
    while ((znak=getch())!=27)
    {
        gotoxy(0,7);
        printf(ZAMARZTESKST);
        gotoxy(0,7);
        printf("Status bufora: ");
        if (flagaWartoscBuf==0)//wypisanie stanu bufora
            printf("PUSTY");
        else if(licznikKopiowania<ROZMIAR_BUF_KOPIOWANIA-1)
            printf("CZESCIOWO ZAPELNIONY");
        else
            printf("PELNY");
        if (znak==-32)//znak specjalny np strzalki przekirowanie do obslugi ich
        {

            znakSpec=1;
            continue;
        }//end if
        if (znakSpec==1&&flaga==1)//mozliwosc ruchu kursorem jezeli nie zaczeto zaznaczania i jezeli jest potwierdzenie wcisniecia znaku specjalnego(strzalki)
        {
            switch(znak)
            {
            case 72:
            {
                if (wiersz>0)
                {
                    wiersz--;
                    adresListy=adresListy->poprz;
                    kolumna=adresListy->nrKolumny;
                }
                break;

            }//end case 72
            case 80:
            {
                if (adresListy->nast!=NULL)
                {
                    wiersz++;
                    adresListy=adresListy->nast;
                    kolumna=adresListy->nrKolumny;
                }
                break;

            }//end case 80
            case 75:
            {
                if(kolumna>0)
                    kolumna--;
                else if(adresListy->poprz!=NULL)
                {
                    wiersz--;
                    adresListy=adresListy->poprz;
                    kolumna=adresListy->nrKolumny;
                }
                break;
            }
            case 77:
            {
                if(kolumna<adresListy->nrKolumny)
                    kolumna++;
                else if(adresListy->nast!=NULL)
                {
                    wiersz++;
                    adresListy=adresListy->nast;
                    kolumna=0;
                }
                break;
            }

            }//end switch
            licznikKopiowaniaStartX=kolumna;//poczatek zaznaczania kolumna
            licznikKopiowaniaStartY=wiersz;//poczatek zaznaczania wiersz
            gotoxy(kolumna,wiersz+WYSOKOSC_MENU_GORNEGO);
            znakSpec=0;
            // continue;
        }//end if
        else
        {
            do
            {
                if (flaga==0)
                    znak=getch();
                switch(znak)
                {
                case '+':
                {
                    if (licznikKopiowania<ROZMIAR_BUF_KOPIOWANIA-1)// zeby nie przekroczyc tablicy przechowujaca przekopiowany tekst
                    {
                        gotoxy(kolumna,WYSOKOSC_MENU_GORNEGO+wiersz);
                        printf("%c",z);
                        if (adresListy->tabZnak[kolumna]!='\0')
                        {
                            kopiuj(buf,licznikKopiowania,adresListy->tabZnak[kolumna]);
                            licznikKopiowania++;
                        }
                        else if(adresListy->nast!=NULL)
                        {
                            kopiuj(buf,licznikKopiowania,' ');
                            licznikKopiowania++;
                        }

                        if(kolumna<adresListy->nrKolumny)
                            kolumna++;
                        else if(adresListy->nast!=NULL)
                        {
                            wiersz++;
                            adresListy=adresListy->nast;
                            kolumna=0;
                        }
                        flaga=0;
                        flagaWartoscBuf=1;
                    }
                    break;
                }//end case +
                case '-':
                {

                    if(kolumna>0)
                    {
                        licznikKopiowania--;
                        kolumna--;
                    }

                    else if(adresListy->poprz!=NULL)
                    {
                        licznikKopiowania--;
                        wiersz--;
                        adresListy=adresListy->poprz;
                        kolumna=adresListy->nrKolumny;
                    }//end else if
                    if (licznikKopiowania<0)
                    {
                        flaga=1;
                        flagaWartoscBuf=0;
                        //licznikKopiowania=0;
                    }
                    buf[licznikKopiowania]='\0';
                    gotoxy(kolumna,WYSOKOSC_MENU_GORNEGO+wiersz);
                    printf("%c",adresListy->tabZnak[kolumna]);
                    break;
                }//end case -
                case 'v':
                {
                    if(flaga==1)
                    {
                        wklej(adresListy,buf,kolumna,wiersz);
                        system("cls");
                        OpcjeWOperacjach();
                        wypiszTekst(adresListy,kolumnaAdres,wierszAdres);
                        gotoxy(kolumna,WYSOKOSC_MENU_GORNEGO+wiersz);
                    }
                    break;
                }
                case 'c':
                {
                    flaga=1;
                    break;
                }
                case 'f':
                {
                    system("cls");
                    OpcjeWOperacjach();
                    licznikKopiowania=0;
                    buf[licznikKopiowania]='\0';
                    flagaWartoscBuf=0;
                    wypiszTekst(adresListy,kolumnaAdres,wierszAdres);
                    gotoxy(kolumna,WYSOKOSC_MENU_GORNEGO+wiersz);
                    flaga=1;
                    break;
                }
                case 'x':
                {
                    wytnij(adresListy,buf,licznikKopiowaniaStartX,licznikKopiowaniaStartY,licznikKopiowania);
                    system("cls");
                    OpcjeWOperacjach();
                    wypiszTekst(adresListy,kolumnaAdres,wierszAdres);
                    gotoxy(kolumna,WYSOKOSC_MENU_GORNEGO+wiersz);
                    flaga=1;
                    break;
                }
                }//end switch
            }
            while(flaga==0);
        }//end else
    }//end while
    system("cls");
    PasekOpcjiGorny();
}
