/**************************************************************************************************
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
}*NODE_LEVEL;

/*Estructuras de tipo Escenario, son representados como vertices de un grafo enlazado*/
typedef struct nodeStage
{
    struct nodeStage *nextStage;  //apuntador de tipo struct que apunta al siguiente escenario
    LIST_SPRITE listSprites;  //Lista dinamica de sprites
    NODE_LEVEL headLevel;  //cabecera de tipo NODE_LEVEL anidada dentro de el grafo
}*NODE_STAGE;

void initStages(NODE_STAGE *stageAct);

int main()
{

}

void initStages(NODE_STAGE *actualStage)
{
    *actualStage = NULL;
}

int createNodeStage(NODE_STAGE *newStage)
{
    int res = 0;
    *newStage = (NODE_STAGE)malloc(sizeof(struct nodeStage));

    if (newStage)
    {
        (*newStage)->nextStage = NULL;
        (*newStage)->listSprites = NULL;
        (*newStage)->headLevel = NULL;
        res = 1;
    }
    return (res);
}











