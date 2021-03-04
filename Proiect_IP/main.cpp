#include <iostream>
#include <fstream>
#include <graphics.h>
#include <winbgim.h>
#include <stdlib.h>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <mmsystem.h>
#include "allFunctions.h"
using namespace std;
int main()
{

    initwindow(dimFEREASTRA,dimFEREASTRA,"Solitarul");
    PlaySound(TEXT("background.wav"),NULL,SND_ASYNC);
    /*setcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    rectangle(0,0,dimFEREASTRA,dimFEREASTRA);
    floodfill(400,400,WHITE);*/

    selectOption();
    do{
        selectie();
    }while(gata==1);

    getch();
    closegraph();
    return 0;
}
