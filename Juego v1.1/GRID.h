#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED
#define SIZE_STRINGS 30

#define SIZE_STAGE_X 22
#define SIZE_STAGE_Y 16

#define SIZE_SREAL_X 960
#define SIZE_SREAL_Y 576
#define VISIBLE_X 960

#define SIZE_SPRITE_X 96
#define SIZE_SPRITE_Y 96


/*Estructura de tipo Sprite que es el archivo binario que lo representa*/
typedef struct
{
    int sNumRow;  //numero de filas del sprite
    int sNumCol;  //numero de columnas del sprite
    int sCorX;  //coordenada en x del pixel
    int sCorY;  //coordenda en y del pixel
    int sColor;  //color del pixel
}SPRITE;

typedef struct nodeSprite
{
    int sCorx;  //coordenada en x del sprite en la ventana
    int sCory;  //coordenada en y del sprite en la ventana
    int GridCoorx; //Coordenada de Sprite en la malla
    int GridCoory;  //Coordenada de Sprite en la malla
    int sizeSprite; //Tamaño de sprite
    char nameSprite[SIZE_STRINGS];
    int sVisible;

    struct nodeSprite *right;  //Liga al siguiente sprite
    struct nodeSprite *left;  //liga al anterior sprite
    struct nodeSprite *up;
    struct nodeSprite *down;

    /*struct nodeSprite *diagUR;
    struct nodeSprite *diagUL;
    struct nodeSprite *diagDR;   //estos apuntadores son, por si en un futuro se agregan mas cosas
    struct nodeSprite *diagDL;*/

    SPRITE **headSprite;  //cabecera sel sprite (bidimensional de tipo SPRITE)
}*GRID_SPRITE;

/*Estructuras de tipo Escenario, son representados como vertices de un grafo enlazado*/
typedef struct nodeStage
{
    struct nodeStage *nextStage;  //apuntador de tipo struct que apunta al siguiente escenario
    GRID_SPRITE listSprites;  //Lista dinamica de sprites
    char nameStage[SIZE_STRINGS];
    int tamX;
    int tamY;
    int puntaje;
    int vidas;
    char nombreJug[10];
}*NODE_STAGE;

void initStages(NODE_STAGE *actualStage);  /*Esta funcion, se encaraga de inicalizar los escenarios, poniendo su apuntador a NULL*/
int createNodeStage(NODE_STAGE *newStage, char name[]);  /*Esta funcion, crea un nodo nuevo para el escenario donde se van a cargar los datos*/
int createNodeSprite(GRID_SPRITE *newSprite, int x, int y, int xGrid, int yGrid, int size, char name[]);
int Juega(NODE_STAGE stage[]);
int loadFileSprite(char fileName[], SPRITE **sprite);
int loadSizeSprite(char name[], int *sizex, int *sizey);
void impMini(SPRITE **ptrArr, int n, int m, int x1, int aux);
void leerArch(SPRITE **ptrPixel, int n, int m, char Name[]);
void liberaMem(SPRITE **ptrArr, int n, int m);
int asignaMem(SPRITE ***ptrArr, int n, int m);
void impItem(SPRITE **ptrArr, int n, int m, int x1, int aux);
void impBarraEstado(NODE_STAGE stage, int noStage);
void loadGridStage(GRID_SPRITE *headSprite, NODE_STAGE stage);
void escribeRecords(int puntaje, char nombre[]);
void escRec();
int ponletras(char cadena[],int iXx,int iYy,int iTam,int iColorL,int iColorF);
void pideNombre(char cadena[]);









#endif // GRID_H_INCLUDED
