/******************************************************************************************
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <string.h>
#include <math.h>
#include <graphics.h>

#define SIZE_STRINGS 30

/*Estructura de tipo Sprite que es el archivo binario que lo representa*/
typedef struct
{
    int sNumRow;  //numero de filas del sprite
    int sNumCol;  //numero de columnas del sprite
    int sCorX;  //coordenada en x del pixel
    int sCory;  //coordenda en y del pixel
    int sColor;  //color del pixel
}**SPRITE;

/*Estrcutura de tipo Sprite, que es representado como el nodo de una lista*/
typedef struct nodeSprite
{
    int sCorx;  //coordenada en x del sprite dentro de la malla
    int sCory;  //coordenada en y del sprite dentro de la malla
    char nameSprite[SIZE_STRINGS];
    bool sVisible; /*en otro caso //Visiblidad dentro de la malla
    int sVisible;   */
    struct nodeSprite *nextSprite;  //Liga al siguiente sprite
    struct nodeSprite *fowSprite;  //liga al anterior sprite
    SPRITE headSprite;  //cabecera sel sprite (bidimensional de tipo SPRITE
}*LIST_SPRITE;

/*Estructuras de tipo Nivel, son representados como relaciones de un grafo enlazado*/
typedef struct nodeLevel
{
    struct nodeLevel *nextLevel;  //apuntador tipo struct que apunta a siguiente nivel
    struct nodeLevel *nextStage;  //apuntador tipo struct que apunta a siguiente escenario
    int numLevel;
}*NODE_LEVEL;

/*Estructuras de tipo Escenario, son representados como vertices de un grafo enlazado*/
typedef struct nodeStage
{
    struct nodeStage *nextStage;  //apuntador de tipo struct que apunta al siguiente
    //escenario
    LIST_SPRITE listSprites;  //Lista dinamica de sprites
    NODE_LEVEL headLevel;  //cabecera de tipo NODE_LEVEL anidada dentro de el grafo
    char nameStage[SIZE_STRINGS];
}*NODE_STAGE;

void initStages(NODE_STAGE *stageAct);

int main()
{

}

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
        (*newStage)->headLevel = NULL;  //cabecera de lista de niveles a NULL, hasta ser cargados
        strcpy((*newStage)->nameStage, name);  //asignacion del nombre del stage, sin la extension
        res = 1;
    }
    return (res);
}

int createNodeLevel(NODE_LEVEL *newLevel)
{
    int res = 0;
    *newLevel = (NODE_LEVEL)malloc(sizeof(struct nodeLevel));

    if (newLevel)
    {
        (*newLevel)->nextLevel = NULL;
        (*newLevel)->nextStage = NULL;
        res = 1;
    }
    return(res);
}

//****************************************************************

int createNodeSprite(LIST_SPRITE *newSprite, int x, int y, int visibility)  //funcion pendiente
{
    int res = 0;
    *newSprite = (LIST_SPRITE)malloc(sizeof(struct nodeSprite));

    if (newSprite)
    {
        (*newSprite)->fowSprite = NULL;
        (*newSprite)->nextSprite = NULL;
        (*newSprite)->sCorx = x;
        (*newSprite)->sCory = y;
        (*newSprite)->sVisible = visibility;
        res = 1;
    }
    return (res);
}

//**************************************************************

int searchArchive(char nameFile[], char message[])  //Esta funcion busca un archivo y verifica su existencia
{
    int res;
    FILE *file;
    *file = fopen(nameFile,"rb");

    if (file)
    {
        res = 1;
        strcpy(message, "Cargando...")
        fclose(file);
    }
    else
    {
        res = 0;
        strcpy(message, "Error 001: EL archivo no se encuentra o ha cambiado su nombre o extension");
    }
    return (res);
}

void loadStageArchive(char nameStageFile[])
{
    int res, i;
    char messageError[40];
    FILE *fileStage;
    res = searchArchive(nameStageFile, messageError);

    if (res)
    {
        *fileStage = fopen(nameStageFile, "rb");

        if (fileStage)
        {
            for ()
        }
    }
}









