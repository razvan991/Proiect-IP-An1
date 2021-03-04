#include "allFunctions.h"

void informatiiEng()
{
    printLabel(2,15,"RULES AND INFORMATION");
    printLabel(5,2,"1.Pe tabla jocului se afla pioni identici , in fiecare casuta cate unul , lasand una sau mai multe casute libere.");
    printLabel(6,2,"2.Fiecare pion poate sari peste un pion vecin ,orizontal sau vertical,deci nu si diagonal,cu conditia ca in spatele");
    printLabel(7,3,"acestuia sa existe o cauta libera. ");
    printLabel(8,2,"3.Pionul peste care se sare este eliminat.");
    printLabel(9,2,"4.Jocul se termina atunci cand au fost eliminati toti pionii infara de unul singur care trebuie sa ajunga in centrul tablei,");
    printLabel(10,3,"acolo unde la inceputul jocului era o casuta libera.");
    printLabel(11,2,"5.Deoarece avem de eliminat 31 de piese , iar la fiecare saritura se elimina cate una , jocul poate fi terminat in exact");
    printLabel(12,3,"31 de mutari elementare");
    printButton(30,30,"EXIT");
    printButton(30,3,"BACK");
    printButton(30,15,"ROMANA");
    selectPosition();
    if ((selectedPosition.i>=30 && selectedPosition.i<=31) && (selectedPosition.j>=30 && selectedPosition.j<=31))
    {
        exit(0);
    }
    if ((selectedPosition.i>=30 && selectedPosition.i<=31) && (selectedPosition.j>=3 && selectedPosition.j<=4))
    {
        cleardevice();
        selectOption();
        clearmouseclick(WM_LBUTTONDOWN);
    }
    if ((selectedPosition.i>=30 && selectedPosition.i<=31) && (selectedPosition.j>=15 && selectedPosition.j<=16))
    {
        cleardevice();
        informatii();
        clearmouseclick(WM_LBUTTONDOWN);
    }

}

