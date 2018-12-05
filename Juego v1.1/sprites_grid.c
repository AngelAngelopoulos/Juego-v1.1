#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "GRID.h"
#include "LIB01.h"
#include <cstdlib>
#include <time.h>
#include "MENU.h"
void initStages(NODE_STAGE *actualStage)  /*Esta funcion, se encaraga de inicalizar los escenarios, poniendo su apuntador a NULL*/
{
    *actualStage = NULL;
}


int createNodeStage(NODE_STAGE *newStage, char name[])  /*Esta funcion, crea un nodo nuevo para el escenario donde se van a cargar los datos*/
{
    int res = 0;
    *newStage = (NODE_STAGE)malloc(sizeof(struct nodeStage));  //obtiene memoria para el nuevo escenario

    if (newStage)
    {
        (*newStage)->nextStage = NULL;  //siguiente escenario a NULL, hasta que se cargue
        (*newStage)->listSprites = NULL;  //cabecera de lista de sprites, a NULL, hasta que se carguen
        strcpy((*newStage)->nameStage, name);  //asignacion del nombre del stage, sin la extension
        (*newStage)->tamX = SIZE_STAGE_X;  //Tamaño del actual stage en X
        (*newStage)->tamY = SIZE_STAGE_Y;  //Tamaño del actual stage en Y
        (*newStage)->puntaje = 0;
        (*newStage)->vidas = 3;
        res = 1;
    }
    return (res);
}



int createNodeSprite(GRID_SPRITE *newSprite, int x, int y, int xGrid, int yGrid, int size, char name[])
{
    int res = 0;
    *newSprite = (GRID_SPRITE)malloc(sizeof(struct nodeSprite));

    if (newSprite)
    {
        (*newSprite)->down = NULL;
        (*newSprite)->up = NULL;
        (*newSprite)->left = NULL;
        (*newSprite)->right = NULL;

        (*newSprite)->sVisible = 1;
        (*newSprite)->GridCoorx = xGrid;
        (*newSprite)->GridCoory = yGrid;
        (*newSprite)->sCorx = x;
        (*newSprite)->sCory = y;
        (*newSprite)->sizeSprite = size;  //Tamaño de sprite en pixeles de Malla

        (*newSprite)->headSprite = NULL;

        strcpy((*newSprite)->nameSprite, name);

        res = 1;
    }
    return (res);
}



void loadGridStage(GRID_SPRITE *headSprite, NODE_STAGE Astage)
{
    setvisualpage(0);
    settextstyle(4, HORIZ_DIR, 4);
    outtextxy(400, 300, "CARGANDO...");
    setactivepage(1);
    cleardevice();
    char nameFile[30];
    int res, res2 = 0;
    GRID_SPRITE aux1, auxUp, auxLft, aux2;
    aux1 = auxUp = auxLft = aux2 = NULL;
    FILE *stage;
    char num, nombre[20];
    sprintf(nombre, "%s.txt", Astage->nameStage);
    stage = fopen(nombre, "r");
    int i = 0,j = 0,x = 0,y = -96;

    for(i = 0; i < 7; i++)
    {

        for(j = 0; j < 11; j++)
        {
            if(!feof(stage))
                num = fgetc(stage);
            if (num != 10)
            {
                printf("%c\n", num);
                sprintf(nameFile, "%c.dat", num);  //nombre del actual nodo
                printf(nameFile);
                res = createNodeSprite(&aux1, x, y, j, i, 24, nameFile);
                asignaMem(&(aux1->headSprite), 24, 24);


                if (res)
                {
                    res2 = loadFileSprite(nameFile, aux1->headSprite);
                    if (res2){
                        impMini(aux1->headSprite, 24, 24, x, y);
                        printf("Llega aqui\n");
                    }
                }

                if(res)
                {

                    if(!auxLft)
                        aux2 = aux1;

                    if(!*headSprite)
                        *headSprite = aux1;

                    if(auxLft)
                    {
                        auxLft->right = aux1;
                        aux1->left = auxLft;
                    }

                    if(auxUp)
                    {
                        aux1->up = auxUp;
                        auxUp->down = aux1;
                    }

                    if(auxUp)
                        auxUp = auxUp->right;


                    auxLft = aux1;
                    x += SIZE_SPRITE_X;
                }
            }
        }
        y += SIZE_SPRITE_Y;
        x = 0;
        auxUp = aux2;
        auxLft = NULL;
    }
    fclose(stage);
    setvisualpage(1);
}

void recorreGrid(GRID_SPRITE cab, int x, int y)
{
    GRID_SPRITE aux1, aux2;
    aux1 = cab;
    aux2 = cab;


}




int loadFileSprite(char fileName[], SPRITE **sprite)
{
    int res, n, m;
    FILE *file;

    res = loadSizeSprite(fileName, &n, &m);

    if (res)
    {
        file = fopen(fileName, "rb+");

        if (file)
        {
            for (int i = 0; i < 24; i++)
            {
                for(int j = 0; j < 24; j++)
                {
                    fread(&(*(sprite+i)+j)->sNumRow, sizeof(int), 1, file);
                    fread(&(*(sprite+i)+j)->sNumCol, sizeof(int), 1, file);
                    fread(&(*(sprite+i)+j)->sCorX, sizeof(int), 1, file);
                    //printf("X: %d ", (*(sprite+i)+j)->sCorX);
                    fread(&(*(sprite+i)+j)->sCorY, sizeof(int), 1, file);
                    //printf("Y: %d ", (*(sprite+i)+j)->sCorY);
                    fread(&(*(sprite+i)+j)->sColor, sizeof(int), 1, file);
                    //printf("Color: %d \n", (*(sprite+i)+j)->sColor);
                }
            }
            res = 1;
        }
        fclose(file);
    }
    else
    {
        printf("El archivo no se encuentra\n");
        res = 0;
    }
    return(res);
}


int loadSizeSprite(char name[], int *sizex, int *sizey)
{
    FILE *file;
    int res = 0;
    file = fopen(name, "rb+");

    if (file)
    {
        fread(sizex, sizeof(int), 1, file);
        fread(sizey, sizeof(int), 1, file);
        res = 1;
    }
    else
    {
        res = 0;
        printf("AAAA\n");
    }
    fclose(file);
    return(res);
}

int Juega(NODE_STAGE stage[])
{
    int retP = 1;
    char tecla;
        int noStage = 0;
        GRID_SPRITE aux = stage[noStage]->listSprites;
        GRID_SPRITE ant = stage[noStage]->listSprites;
        GRID_SPRITE up = stage[noStage]->listSprites;
        GRID_SPRITE down = up->right;
        GRID_SPRITE right =down->right;
        GRID_SPRITE left = right->right;
        GRID_SPRITE enemy = left->right;
        GRID_SPRITE enemy_ant = up;
        GRID_SPRITE enemy_mov = up;
        printf("Llega Aqui********************");
        GRID_SPRITE pers = stage[noStage]->listSprites;
        GRID_SPRITE ini = left->right->right;

        clock_t t,ts;
        ts = clock()+CLOCKS_PER_SEC;
        char dir;
        int direnem = 0;
        int sum = 0;
        int mult = 0;
        //int acum = stage[noStage]->listSprites->GridCoory;
        int band = 1;
        aux = aux->down->down->right->down->right;  //asignamos su posicion incial
        enemy_mov = stage[noStage]->listSprites->down->down->down->right->right;
        do
        {
            t = clock();
            switch(noStage)
            {
                case 0:
                    mult = 3;
                    break;
                case 1:
                    mult = 6;
                    break;
                case 2:
                    mult = 9;
                    break;
                case 3:
                    mult = 12;
                    break;
            }
            t = t * mult;
            if(t >= ts)
                {
                    if (noStage != sum)
                        enemy_mov = stage[noStage]->listSprites->right->right->right->down->down;

                    sum = noStage;
                    srand(time(NULL));
                    direnem = rand() % 3;

                    switch (direnem)
                    {
                        case 0:

                            if (enemy_mov->down->GridCoory < 6)
                            {
                                enemy_ant = enemy_mov;
                                enemy_ant->headSprite = enemy_mov->headSprite;
                                enemy_mov = enemy_mov->down;
                            }
                            break;
                        case 1:
                        if (enemy_mov->right->GridCoorx < 9)
                            {
                                enemy_ant = enemy_mov;
                                enemy_ant->headSprite = enemy_mov->headSprite;
                                enemy_mov = enemy_mov->right;
                            }
                            break;
                        case 2:
                            if (enemy_mov->left->GridCoorx > 0)
                            {
                                enemy_ant = enemy_mov;
                                enemy_ant->headSprite = enemy_mov->headSprite;
                                enemy_mov = enemy_mov->left;
                            }
                            break;
                        case 3:
                            if (enemy_mov->up->GridCoory > 1)
                            {
                                enemy_ant = enemy_mov;
                                enemy_ant->headSprite = enemy_mov->headSprite;
                                enemy_mov = enemy_mov->up;
                            }
                            break;
                    }

                    impItem(enemy->headSprite, 24, 24, enemy_mov->sCorx, enemy_mov->sCory);
                    impItem(enemy_ant->headSprite, 24, 24, enemy_ant->sCorx, enemy_ant->sCory);

                    if (enemy_mov->GridCoorx == aux->GridCoorx && enemy_mov->GridCoory == aux->GridCoory)
                    {
                        stage[0]->vidas -= 1;
                    }

                    ts=t+CLOCKS_PER_SEC;
                }

                if (aux && band)
                {
                    if (strcmp(aux->nameSprite, "B.dat") == 0)
                    {
                        stage[0]->puntaje -= 10;
                    }
                    if (strcmp(aux->nameSprite, "I.dat") == 0)
                    {
                        stage[0]->puntaje += 10;
                        aux->headSprite = ini->headSprite;
                        strcpy(aux->nameSprite, "A.dat");
                    }

                    impBarraEstado(stage[0], noStage);

                    switch(band)
                    {
                        case 1:
                            if (aux->right->GridCoorx == 9 && aux->down->GridCoory == 5  && noStage == 0)
                                {
                                    noStage = 1;
                                    loadGridStage(&stage[1]->listSprites, stage[1]);
                                    aux = stage[noStage]->listSprites->down->down->down->right;
                                    impItem(pers->headSprite, 24, 24, aux->sCorx, aux->sCory);
                                }
                                break;
                        case 2:
                            if (aux->right->GridCoorx == 5 && aux->up->GridCoory == 1 && noStage == 1)
                                {
                                    noStage = 2;
                                    loadGridStage(&stage[2]->listSprites, stage[2]);
                                    aux = stage[noStage]->listSprites->down->down->down->down->down->right->right->right;
                                    impItem(pers->headSprite, 24, 24, aux->sCorx, aux->sCory);
                                }
                                break;
                        case 3:
                            if (aux->left->GridCoorx == 0 && aux->down->GridCoory == 6 && noStage == 2)
                                {
                                    noStage = 3;
                                    loadGridStage(&stage[3]->listSprites, stage[3]);
                                    aux = stage[noStage]->listSprites->right->right->right->right->right->right->right->right->down->down->down->down;
                                    impItem(pers->headSprite, 24, 24, aux->sCorx, aux->sCory);
                                }
                                break;
                        default:
                            impItem(ant->headSprite, 24, 24, ant->sCorx, ant->sCory);
                            impItem(pers->headSprite, 24, 24, aux->sCorx, aux->sCory);
                            break;
                    }

                    band = 0;
                }

                if (kbhit())
                {
                    dir = getch();
                    setcolor(15);
                    ant = aux;
                    ant->headSprite = aux->headSprite;

                    switch (dir)
                    {
                        case 77:
                            pers->headSprite = right->headSprite;
                            band = 1;

                            if (aux->right->GridCoorx < 9)
                            {
                                aux = aux->right;
                                band = 5;
                            }
                            break;
                        case 75:
                            pers->headSprite = left->headSprite;
                            band = 3;

                            if (aux->left->GridCoorx > 0)
                            {
                                aux = aux->left;
                                band = 5;
                            }
                            break;
                        case 72:
                            pers->headSprite = up->headSprite;
                            band =2;

                            if (aux->up->GridCoory > 1)
                            {
                                aux = aux->up;
                                band = 5;
                            }
                            break;
                        case 80:
                            pers->headSprite = down->headSprite;
                            band = 4;

                            if (aux->down->GridCoory < 6)
                            {
                                aux = aux->down;
                                band = 5;
                            }
                            break;
                        }
                }
        }while(stage[0]->vidas > 0 && stage[0]->puntaje < 100);
        settextstyle(3, HORIZ_DIR, 4);

        if (stage[0]->vidas <= 0)
        {
            cleardevice();
            outtextxy(150, 300, "GAME OVER :(");
            outtextxy(150, 400, "Presiona cualquier tecla para reiniciar");
            outtextxy(150, 500, "Presiona ESC para salir");
            tecla = getch();
            if (tecla == 32)
            {
                retP = 1;
                cleardevice();
            }
            else if(tecla == 27)
                retP = 0;
        }
        if (stage[0]->puntaje >= 100)
        {
            cleardevice();
            pideNombre(stage[0]->nombreJug);
            cleardevice();
            setcolor(15);
            outtextxy(150, 300, "Felicidades, has pasado el juego con exito UwU");
            outtextxy(150, 400, "Presiona SPACE para reiniciar");
            outtextxy(150, 500, "Presiona ESC para salir");

            tecla = getch();
            if (tecla == 32)
            {
                retP = 1;
                cleardevice();
            }
            else if (tecla == 27)
                retP = 0;
        }
        return (retP);
}


void escribeRecords(int puntaje, char nombre[])
{
    RECORD rec[5];
    int pos = 0, i = 0;
    FILE *file;
    FILE *ofile;

    file = fopen("scores.dat", "rb+");

    if (file)
    {
        for( i= 0; i < 5; i++);
        {
            fread(&rec[i].nombre, sizeof(char), 20, file);
            fread(&rec[i].puntaje, sizeof(int), 1, file);
            if (rec[i].puntaje < puntaje)
                pos = i;
        }
    }
    else
    {
        printf("Archivo no encontrado\n");
    }
    fclose(file);

    if (pos > 0)
    {
        rec[pos].puntaje = puntaje;
        strcpy(rec[pos].nombre, nombre);
        printf("Aqui llega bien");
    }

    ofile = fopen("scores.dat", "wb+");
        if (ofile)
        {
            for(int i = 0; i < 5; i++)
            {
                fwrite(&rec[i].nombre, sizeof(char), 20, ofile);
                fwrite(&rec[i].nombre, sizeof(int), 1, ofile);
            }
        }
        else{
            printf("El archivo no existe");
        }
        fclose(ofile);
}

void escRec()
{
    RECORD rec[5];
    strcpy(rec[0].nombre, "Luis");
    rec[0].puntaje = 88;
    strcpy(rec[1].nombre, "Miguel");
    rec[1].puntaje = 85;
    strcpy(rec[2].nombre, "Jesus");
    rec[2].puntaje = 74;
    strcpy(rec[3].nombre, "Beto");
    rec[3].puntaje = 65;
    strcpy(rec[4].nombre, "Daniel");
    rec[4].puntaje = 50;
    FILE *arch;

    arch = fopen("scores.dat", "wb+");

    if (arch)
    {
        for(int i = 0; i < 5; i++)
        {
            fwrite(&rec[i].nombre, sizeof(char), 20, arch);
            fwrite(&rec[i].puntaje, sizeof(int), 1, arch);
        }
    }
    else
    {
        printf("El archivo no existe");
    }

    fclose(arch);
}

void pideNombre(char cadena[])
{
    int borrar = 0;
    do {
        setbkcolor(15);
        outtextxy(260, 300, "Escriba su nombre:");
        setbkcolor(0);
        borrar = ponletras(cadena, 260, 330, 25, 15, 0);
    } while(borrar != 0);
}


int ponletras(char cadena[],int iXx,int iYy,int iTam,int iColorL,int iColorF){
     char tecla='0',auxLetras[30];
     int iBand1,iCont=0,iConta=0, borrar = 0;
     strncpy(cadena,"\0",iTam);
     strncpy(auxLetras,"\0",30);
     tecla='0';
     setcolor(iColorL);
     outtextxy(iXx,iYy,auxLetras);
     while(tecla!=13){
        iBand1=-1;
        do
		  {
		    while(!kbhit() && (iConta++ < 700));
		    setcolor(iColorL);
		    //(10+8)/2 es el tamaño de las letras modificar aqui si se cambia el tamaño de letra
		    outtextxy(iXx+(strlen(auxLetras)*(int)((10+8)/2)),iYy,"_");
		    iConta = 0;
		    while(!kbhit() && (iConta++ < 700));
		    setcolor(iColorF);
		    outtextxy(iXx+(strlen(auxLetras)*(int)((10+8)/2)),iYy,"_");
		    iConta=0;
		    if(kbhit()){
			   tecla=getch();
			   iBand1=-1;
			   if(tecla == 8)
                return 1;
			   if((tecla==0)||(tecla==27)){
				     tecla=getch();
				     iBand1=0;
               }
			   if(iBand1!=0)
				 iBand1=1;
		     }
		}while(iBand1!=1);
		if(tecla!=13){
		   setcolor(iColorF);
		   outtextxy(iXx,iYy,auxLetras);
		   setcolor(iColorL);
    	   cadena[iCont]   = tecla;
           cadena[iCont+1] = '\0';
           auxLetras[iCont]   = tecla;
           auxLetras[iCont+1] = '\0';
           outtextxy(iXx,iYy,auxLetras);
           iCont++;
		   }
		}
		return (borrar);
}

void impBarraEstado(NODE_STAGE stage, int noStage)
{
    settextstyle(4, HORIZ_DIR, 2);
    setbkcolor(7);
    setcolor(0);
    char puntaje[10];
    char vidas[2];
    char nivel[2];
    sprintf(puntaje, "%d", stage->puntaje);
    sprintf(vidas, "%d", stage->vidas);
    sprintf(nivel, "%d", noStage+1);
    exterior(0, 576, 960, 672,8);
    interior(5, 581, 955, 667, 7);
    bar(960,0, 1152, 672);
    exterior(960, 0, 1152, 667, 8);
    interior(965, 5, 1147, 662, 7);
    rectangle(96-3, 96, 864+3, 480+3);
    outtextxy(1000, 50, "Puntaje:");
    outtextxy(1000, 70, puntaje);
    outtextxy(1000, 100, "Vidas:");
    outtextxy(1000, 120, vidas);
    outtextxy(1000, 150, "Nivel:");
    outtextxy(1000, 170, nivel);
}


int asignaMem(SPRITE ***ptrArr, int n, int m)
{
    int res = 0, i = 0;

    *ptrArr = (SPRITE**)malloc(sizeof(SPRITE*)*m);

    if (*ptrArr != NULL)
    {
        res = 1;

        for (i = 0; i < n; i++)
        {
            *(*ptrArr+i) = (SPRITE*)malloc(sizeof(SPRITE)*m);

            if (*(*ptrArr+i) == NULL)
            {
                while (--i > 0)
                {
                    free(*(*ptrArr+i));
                }
                free(*ptrArr);
                res = 0;
            }
        }
    }
    return(res);
}

void liberaMem(SPRITE **ptrArr, int n, int m)
{
    int i;
    for(i = m; i > m; i--)
    {
        free((*ptrArr+i));
    }
    free(*ptrArr);
}

void leerArch(SPRITE **ptrPixel, int n, int m, char Name[])
{
    FILE *arch;
    arch = fopen(Name, "rb+");

    if (arch)
    {
        for (int i = 0; i < n; i ++)
        {
            for(int j = 0; j < m; j++)
            {
                fread(&(*(ptrPixel+i)+j)->sNumRow, sizeof(int), 1, arch);
                fread(&(*(ptrPixel+i)+j)->sNumCol, sizeof(int), 1, arch);
                fread(&(*(ptrPixel+i)+j)->sCorX, sizeof(int), 1, arch);
                //printf("X: %d ", (*(ptrPixel+i)+j)->ix);
                fread(&(*(ptrPixel+i)+j)->sCorY, sizeof(int), 1, arch);
                //printf("Y: %d ", (*(ptrPixel+i)+j)->iy);
                fread(&(*(ptrPixel+i)+j)->sColor, sizeof(int), 1, arch);
                //printf("Color: %d \n", (*(ptrPixel+i)+j)->iColor);
            }
        }
    }
    fclose(arch);
}


void impMini(SPRITE **ptrArr, int n, int m, int x1, int aux)
{
    int noPag = 0;
    int tamDispx = 96;
    int tamDispy = 96;
    int i, j, x2 = 0, y2 = 0, y1 = 0;
    x2 = x1 + (tamDispx/n) , y2 = y1 + (tamDispy/m)+aux;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            y1 = y2;
            y2 = y1+(tamDispy/m);
            if ((*(ptrArr+i)+j)->sColor != 15)
            {
                setfillstyle(1,(*(ptrArr+i)+j)->sColor);
                bar(x1, y1, x2, y2);
            }
        }
        x1 = x2;
        x2 = x1+ (tamDispx/n);
        y1 = aux;
        y2 = y1 +(tamDispy/m);
        }
        if(noPag == 1)
        {
            noPag = 0;
        }
        else
            noPag = 1;
}


void impItem(SPRITE **ptrArr, int n, int m, int x1, int aux)
{
    int tamDispx = 96;
    int tamDispy = 96;
    int i, j, x2 = 0, y2 = 0, y1 = 0;
    x2 = x1 + (tamDispx/n) , y2 = y1 + (tamDispy/m)+aux;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            y1 = y2;
            y2 = y1+(tamDispy/m);
            if ((*(ptrArr+i)+j)->sColor != 15)
            {
                setfillstyle(1,(*(ptrArr+i)+j)->sColor);
                bar(x1, y1, x2, y2);
            }
        }
        x1 = x2;
        x2 = x1+ (tamDispx/n);
        y1 = aux;
        y2 = y1 +(tamDispy/m);
        }
}
