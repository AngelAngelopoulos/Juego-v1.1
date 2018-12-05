#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "GRID.h"
#include "MENU.h"

int main()
{
    int res = 0, resp = 0;
    res = Menu();
    if (res == 6)
    {
        do{

            NODE_STAGE stages[4];
            initwindow(1152, 672, "Hola");

            initStages(&stages[0]);
            initStages(&stages[1]);
            initStages(&stages[2]);
            initStages(&stages[3]);

            createNodeStage(&stages[0], "stage1");
            createNodeStage(&stages[1], "stage2");
            createNodeStage(&stages[2], "stage3");
            createNodeStage(&stages[3], "stage4");

            loadGridStage(&stages[0]->listSprites, stages[0]);
            //loadGridStage(&stages[1]->listSprites, stages[1]);
            //loadGridStage(&stages[2]->listSprites, stages[2]);
            //loadGridStage(&stages[3]->listSprites, stages[3]);

            loadGridStage(&stages[0]->listSprites, stages[0]);
            impBarraEstado(stages[0], 0);
            resp = Juega(stages);
            //escRec();
        }while(resp == 1);
    }
    return 0;
}
