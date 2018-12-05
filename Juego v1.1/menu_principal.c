#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "MENU.h"

int Menu()
{
    BACK arrImg[6];
    int res = 0;
    initwindow(960, 672, "Menu");
    loadBackground(arrImg);
//    PlaySound("C:\\Users\\Angel Alvarado\\Documents\\GitHub\\Juego-v1.1\\Juego v1.1\\musica.wma", NULL, SND_FILENAME);﻿
    res = printBackground(arrImg);
    return (res);
}

void loadBackground(BACK arr[])
{
    setactivepage(1);
    int i;
    char name[20];
    for (i = 0; i < 6; i++)
    {
        sprintf(name, "%d.jpg", i+1);
        readimagefile(name, 0, 0, 960, 672);
        arr[i].bitmap = malloc(imagesize(0,0,960,672));
        getimage(0,0,960, 672, (arr[i].bitmap));
        delay(50);
        cleardevice();
    }
}


void guardamem(void *bitmap)
{
    bitmap = (void*)malloc(imagesize(0, 0, 960, 672));
    getimage(0, 0, 960, 672, &bitmap);
}

int printBackground(BACK arr[])
{
    setvisualpage(1);
    clock_t t,ts;
    int res = 0;
    ts=clock()+CLOCKS_PER_SEC;
    int i = 0;

    do
    {
        do
        {
            t = clock();
            t = t*8;
            if(t >= ts)
            {
                cleardevice();
                putimage(0, 0, (arr[i].bitmap), COPY_PUT);
                generaBotones();
                i++;
                ts = t+CLOCKS_PER_SEC;
            }
            res = obtieneboton();
        }while(i < 6 && res == 0);
        i = 0;
    }while(res == 0 || res == 1 || res == 2 || res == 4);
    return(res);
}

void generaBotones()
{
    setcolor(15);
    bar3d(75, 250, 250, 300, 10, 1);  //Ayuda
    bar3d(75, 350, 250, 400, 10, 1);  //Acerca de
    bar3d(75, 450, 250, 500, 10, 1);

    bar3d(710, 250, 885, 300, 10, 1);
    bar3d(710, 350, 885, 400, 10, 1);
    bar3d(710, 450, 885, 500, 10, 1);

    setcolor(0);
    setbkcolor(15);
    settextstyle(2, HORIZ_DIR, -7);
    settextjustify(0,1);
    outtextxy(87, 275, "Ayuda");
    outtextxy(80, 375, "Acerca de");
    outtextxy(87, 475, "Salir");
    outtextxy(730, 275, "Scores");
    outtextxy(730, 475, "Jugar->");
}

int obtieneboton()
{
    int res = 0, x = 0, y = 0;

    if (ismouseclick(WM_LBUTTONDOWN))
    {
        getmouseclick(WM_LBUTTONDOWN, x, y);

        if (x < 250 && x > 75 && y < 300 && y > 250)
        {
            res = 1;
            cleardevice();
            Ayuda();
        }
        if (x < 250 && x > 75 && y < 400 && y > 350)
        {
            cleardevice();
            About();
            res = 2;
        }
        if (x < 250 && x > 75 && y < 500 && y > 450)
        {
            cleardevice();
            outtextxy(10, 10, "Salir");
            exit(1);
            res = 3;
        }
        if (x < 885 && x > 710 && y < 300 && y > 250)
        {
            cleardevice();
            Scores();
            res = 4;
        }
        if (x < 885 && x > 710 && y < 400 && y > 350)
        {
            res = 5;
        }
        if (x < 885 && x > 710 && y < 500 && y > 450)
        {
            res = 6;
            closegraph();
        }
    }
    return(res);
}


void Ayuda()
{
    FILE *arch;
    char txt[50];
    int  y = 100;
    arch = fopen("Ayuda.txt", "r");
    outtextxy(100, 50, "Ayuda");
    settextstyle(4, HORIZ_DIR, 2);

    do
    {
        do
        {
            fgets(txt, 50,arch);
            outtextxy(100, y, txt);
            printf("%s", txt);
            y +=20 ;
        }while(!feof(arch));
    }while(getch() != 27);
    fclose(arch);
}

void About()
{
    FILE *arch;
    char txt[50];
    int y = 200;
    arch = fopen("About.txt", "r");
    outtextxy(300, 50, "Acerca de");
    settextstyle(4, HORIZ_DIR, 3);

    do
    {
        do
        {
            fgets(txt, 50,arch);
            outtextxy(100, y, txt);
            printf("%s", txt);
            y +=40 ;
        }while(!feof(arch));
    }while(getch() != 27);
    fclose(arch);
}


void Scores()
{
    RECORD rec[5];
    FILE *arch;
    char puntaje[10];
    arch = fopen("scores.dat", "rb");
    int y = 70, x = 100;

    if (arch)
    {
        for ( int i = 0; i < 5; i++)
        {
            fread(&rec[i].nombre, sizeof(char), 20, arch);
            fread(&rec[i].puntaje, sizeof(int), 1, arch);
        }
    }
    else{
        printf("No se encuentra el archivo\n");
    }
    fclose(arch);
    for (int i = 0; i < 5; i++)
        {
            outtextxy(x, y, rec[i].nombre);
            sprintf(puntaje, "%d", rec[i].puntaje);
            outtextxy(x + 300, y, puntaje);
            y += 100;
        }
    outtextxy(150, 600, "Presiona alguna tecla para regresar al menu");
    getch();
}

