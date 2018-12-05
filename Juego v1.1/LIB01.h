void interior (int x1, int y1, int x2, int y2, int color){
    setfillstyle(1, color);
    bar(x1, y1, x2, y2);
    setcolor(0);
    line(x1,y1,x2+2,y1);
    line(x1,y1,x1, y2+2);
    setcolor(15);
    line(x1,y2+2,x2+2,y2+2);
    line(x2+2,y2+2,x2+2,y1);
    setcolor(0);
    }
void exterior (int x1, int y1, int x2, int y2, int color){
    setfillstyle(1,color);
    bar(x1+1, y1+1, x2-1, y2-1);
    setcolor(15);setcolor(15);
    line(x1,y1,x2,y1);
    line(x1,y1,x1,y2);
    setcolor(0);
    line(x1,y2,x2,y2);
    line(x2,y2,x2,y1);
    setcolor(0);
    }
