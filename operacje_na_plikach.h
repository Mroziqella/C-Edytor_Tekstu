#ifndef OPERACJE_NA_PLIKACH_H_INCLUDED
#define OPERACJE_NA_PLIKACH_H_INCLUDED

int odczytZpliku(char* sciezkaZapisu, wezel* adres,unsigned int *kolumnaAdres,unsigned int *wierszAdres);
int zapiszPlik(char* sciezkaZapisu, wezel* adres);

#endif // OPERACJE_NA_PLIKACH_H_INCLUDED
