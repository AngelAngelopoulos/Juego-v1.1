#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

typedef struct
{
    int i;
    void *bitmap;
}BACK;

typedef struct
{
    int bCoorx;
    int bCoory;
    int nButton;
}BUTTON;

typedef struct
{
    int puntaje;
    char nombre[20];
}RECORD;

void loadBackground(BACK arr[]);
int printBackground(BACK arr[]);
void guardamem(void *bitmap);
void generaBotones();
int obtieneboton();
int Menu();
void Ayuda();
void About();
void Scores();





#endif // MENU_H_INCLUDED
