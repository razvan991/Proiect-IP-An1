#include <iostream>
#include <fstream>
#include <graphics.h>
#include <winbgim.h>
#include <stdlib.h>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include "MMsystem.h"
using namespace std;
ifstream f ("bileInceput.in");    //inceput cu bile initializate
ifstream g ("veciniBile.in");     //bilele care sunt la 2 casute distanta SUS,DREAPTA,JOS,STANGA
ifstream h ("veciniBileMici.in"); //bilele care sunt la 1 casuta distanta SUS,DREAPTA,JOS,STANGA
ifstream ff ("soldudeney.in"); //mutarile pentru solutia h.e.dudeney

/*Cod culori
  0 = Negru
  1 = Albastru
  2 = Verde
  3 = Aqua
  4 = Rosu
  5 = Purpuriu
  6 = Galben
  7 = Alb
  8 = Gri
  9 = Albastru deschis
  A = Verde deschis
  B = Aqua deschis
  C = Rosu deschis
  D = Purpuriu deschis
  E = Galben deschis
  F = Alb stralucito*/
/*COD PATRAT UMPLUT
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    rectangle(0,0,dimFEREASTRA,dimFEREASTRA);
    floodfill(400,400,WHITE);
*/
int terminat;
short culoareBila=9;
short culoareSelectatBila=13;
int boardMatrix[7][7] = {1};
int dimension=20,gata=1;
int borderDimension=2;
//DIMENSIUNEA FERESTREI
short dimFEREASTRA=900;
short bilaPrecedenta=-1;
//COORDONATE xCENTRU SI yCENTRU, LUNGIME PATRAT TABLA
int x1=dimFEREASTRA/2,y1=dimFEREASTRA/2,L=dimFEREASTRA/10;
//UMBRA TABLA
short umbra=L/4-3;
short culoareUmbra=8;
short culoareFundalSinglePlayer=7;
//SCOR
int x=0,y=0,aceeasiBila;
short scor=0;
short scorPlayer1=0,scorPlayer2=0;
//LIMBA
int limba=1;
//JOC
short tipJoc=0;
short runda=0;
short lost=1;

void printLabel();
void selectie();
struct Position
{
    int i;
    int j;

} selectedPosition;
struct bilele{//Adrian Rosu
    unsigned int x,y;//coordonate bila
    bool ocupat;     //ocupat=1, liber=0
    int culoare;     //culoare bila (1-14)
    int culoareFundal;
    bool sageti;
    short vecSus;
    short vecJos;
    short vecStanga;
    short vecDreapta;
    short vecMicSus;
    short vecMicJos;
    short vecMicStanga;
    short vecMicDreapta;
}bile[33];
void citireVecini()// Adrian Rosu & Razvan Cazacu
{
    int i;
    for(i=1;i<=33;i++)
    {
        g>>bile[i].vecSus>>bile[i].vecDreapta>>bile[i].vecJos>>bile[i].vecStanga;
        h>>bile[i].vecMicSus>>bile[i].vecMicDreapta>>bile[i].vecMicJos>>bile[i].vecMicStanga;
    }
}
void bileInitializare(int x,int y,int L)//Adrian Rosu
{
    short i;
    for(i=1;i<=33;i++)
    {
        f>>bile[i].ocupat;
        bile[i].culoare=culoareBila;
        bile[i].sageti=0;
    }
    //y-3*L (1-3)
    bile[1].x=x-L;
    bile[1].y=y-3*L;
    bile[2].x=x;
    bile[2].y=y-3*L;
    bile[3].x=x+L;
    bile[3].y=y-3*L;
    //y-2*L (4-6)
    bile[4].x=x-L;
    bile[4].y=y-2*L;
    bile[5].x=x;
    bile[5].y=y-2*L;
    bile[6].x=x+L;
    bile[6].y=y-2*L;
    //y-L (7-13)
    bile[7].x=x-3*L;
    bile[7].y=y-L;
    bile[8].x=x-2*L;
    bile[8].y=y-L;
    bile[9].x=x-L;
    bile[9].y=y-L;
    bile[10].x=x;
    bile[10].y=y-L;
    bile[11].x=x+L;
    bile[11].y=y-L;
    bile[12].x=x+2*L;
    bile[12].y=y-L;
    bile[13].x=x+3*L;
    bile[13].y=y-L;
    //y (14-20)
    bile[14].x=x-3*L;
    bile[14].y=y;
    bile[15].x=x-2*L;
    bile[15].y=y;
    bile[16].x=x-L;
    bile[16].y=y;
    bile[17].x=x;
    bile[17].y=y;
    bile[18].x=x+L;
    bile[18].y=y;
    bile[19].x=x+2*L;
    bile[19].y=y;
    bile[20].x=x+3*L;
    bile[20].y=y;
    //y+L (21-27)
    bile[21].x=x-3*L;
    bile[21].y=y+L;
    bile[22].x=x-2*L;
    bile[22].y=y+L;
    bile[23].x=x-L;
    bile[23].y=y+L;
    bile[24].x=x;
    bile[24].y=y+L;
    bile[25].x=x+L;
    bile[25].y=y+L;
    bile[26].x=x+2*L;
    bile[26].y=y+L;
    bile[27].x=x+3*L;
    bile[27].y=y+L;
    //y+2*L (28-30)
    bile[28].x=x-L;
    bile[28].y=y+2*L;
    bile[29].x=x;
    bile[29].y=y+2*L;
    bile[30].x=x+L;
    bile[30].y=y+2*L;
    //y+3*L (31-33)
    bile[31].x=x-L;
    bile[31].y=y+3*L;
    bile[32].x=x;
    bile[32].y=y+3*L;
    bile[33].x=x+L;
    bile[33].y=y+3*L;

    citireVecini();

}
int gasireBilaApasata(int x, int y)//Adrian Rosu
{
    //7,14,21
    if(x>x1-3*L-L/2&&x<x1-2*L-L/2)
    {
        if(y>y1-L-L/2&&y<y1-L/2)
            return 7;
        if(y>y1-L/2&&y<y1+L/2)
            return 14;
        if(y>y1+L/2&&y<y1+L+L/2)
            return 21;
    }
    //8,15,22
    if(x>x1-2*L-L/2&&x<x1-L-L/2)
    {
        if(y>y1-L-L/2&&y<y1-L/2)
            return 8;
        if(y>y1-L/2&&y<y1+L/2)
            return 15;
        if(y>y1+L/2&&y<y1+L+L/2)
            return 22;
    }
    //1,4,9,16,23,28,31
    if(x>x1-L-L/2&&x<x1-L/2)
    {
        if(y>y1-3*L-L/2&&y<y1-2*L-L/2)
            return 1;
        if(y>y1-2*L-L/2&&y<y1-L-L/2)
            return 4;
        if(y>y1-L-L/2&&y<y1-L/2)
            return 9;
        if(y>y1-L/2&&y<y1+L/2)
            return 16;
        if(y>y1+L/2&&y<y1+L+L/2)
            return 23;
        if(y>y1+L/2&&y<y1+2*L+L/2)
            return 28;
        if(y>y1+2*L/2&&y<y1+3*L+L/2)
            return 31;
    }
    //2,5,10,17,24,29,32
    if(x>x1-L/2&&x<x1+L/2)
    {
        if(y>y1-3*L-L/2&&y<y1-2*L-L/2)
            return 2;
        if(y>y1-2*L-L/2&&y<y1-L-L/2)
            return 5;
        if(y>y1-L-L/2&&y<y1-L/2)
            return 10;
        if(y>y1-L/2&&y<y1+L/2)
            return 17;
        if(y>y1+L/2&&y<y1+L+L/2)
            return 24;
        if(y>y1+L/2&&y<y1+2*L+L/2)
            return 29;
        if(y>y1+2*L/2&&y<y1+3*L+L/2)
            return 32;
    }
    //3,6,11,18,25,30,33
    if(x>x1+L/2&&x<x1+L+L/2)
    {
        if(y>y1-3*L-L/2&&y<y1-2*L-L/2)
            return 3;
        if(y>y1-2*L-L/2&&y<y1-L-L/2)
            return 6;
        if(y>y1-L-L/2&&y<y1-L/2)
            return 11;
        if(y>y1-L/2&&y<y1+L/2)
            return 18;
        if(y>y1+L/2&&y<y1+L+L/2)
            return 25;
        if(y>y1+L/2&&y<y1+2*L+L/2)
            return 30;
        if(y>y1+2*L/2&&y<y1+3*L+L/2)
            return 33;
    }
    //12,19,26
    if(x>x1+L+L/2&&x<x1+2*L+L/2)
    {
        if(y>y1-L-L/2&&y<y1-L/2)
            return 12;
        if(y>y1-L/2&&y<y1+L/2)
            return 19;
        if(y>y1+L/2&&y<y1+L+L/2)
            return 26;
    }
    //13,20,27
    if(x>x1+2*L+L/2&&x<x1+3*L+L/2)
    {
        if(y>y1-L-L/2&&y<y1-L/2)
            return 13;
        if(y>y1-L/2&&y<y1+L/2)
            return 20;
        if(y>y1+L/2&&y<y1+L+L/2)
            return 27;
    }
    return -1;
}
bool validBilaUrmatoare(int bilaPrecedenta,int bilaObtinuta)//Razvan Cazacu && Adrian Rosu
{

    if(bile[bilaObtinuta].vecSus==bilaPrecedenta&&bile[bile[bilaPrecedenta].vecMicJos].ocupat!=0&&bile[bile[bilaPrecedenta].vecJos].ocupat==0)
    {
        bile[bile[bilaPrecedenta].vecMicJos].ocupat=0;
        return 1;
    }
    if(bile[bilaObtinuta].vecJos==bilaPrecedenta&&bile[bile[bilaPrecedenta].vecMicSus].ocupat!=0&&bile[bile[bilaPrecedenta].vecSus].ocupat==0)
    {
        bile[bile[bilaPrecedenta].vecMicSus].ocupat=0;
        return 1;
    }
    if(bile[bilaObtinuta].vecDreapta==bilaPrecedenta&&bile[bile[bilaPrecedenta].vecMicStanga].ocupat!=0&&bile[bile[bilaPrecedenta].vecStanga].ocupat==0)
    {
        bile[bile[bilaPrecedenta].vecMicStanga].ocupat=0;
        return 1;
    }
    if(bile[bilaObtinuta].vecStanga==bilaPrecedenta&&bile[bile[bilaPrecedenta].vecMicDreapta].ocupat!=0&&bile[bile[bilaPrecedenta].vecDreapta].ocupat==0)
    {
        bile[bile[bilaPrecedenta].vecMicDreapta].ocupat=0;
        return 1;
    }

    return 0;
}
void selectareBila()//Adrian Rosu & Razvan Cazacu
{
    int x,y;
    int bilaObtinuta;
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        x=mousex();
        y=mousey();
        bilaObtinuta=gasireBilaApasata(x,y);
        if(bilaObtinuta!=-1)
        {
            bile[bilaObtinuta].culoare=culoareSelectatBila;

            if(bilaPrecedenta!=-1)
            {
                bile[bilaPrecedenta].culoare=culoareBila;
                if(aceeasiBila==-1)
                {
                    aceeasiBila=bilaObtinuta;
                }

            }
            if(bilaPrecedenta!=-1)
            {
                if(validBilaUrmatoare(bilaPrecedenta,bilaObtinuta)==1)
                {
                    if(aceeasiBila==bilaPrecedenta)
                    {
                        aceeasiBila=bilaObtinuta;
                    }
                    else
                    {
                        scor++;
                        aceeasiBila=bilaObtinuta;
                    }
                    bile[bilaObtinuta].ocupat=1;
                    bile[bilaPrecedenta].ocupat=0;
                }
                bilaPrecedenta=-1;
                bile[bilaObtinuta].culoare=culoareBila;
            }
            else
                bilaPrecedenta=bilaObtinuta;
        }
    }
}
//Afisare tabla joc
void tabla(int x,int y,int l)//Razvan Cazacu
{
    setcolor(2);
    line(x-l-l/2,y-3*l-l/2,x+l+l/2,y-3*l-l/2); //AB

    line(x+l+l/2,y-3*l-l/2,x+l+l/2,y-l-l/2); //BC

    line(x+l+l/2,y-l-l/2,x+3*l+l/2,y-l-l/2); //CD

    line(x+3*l+l/2,y-l-l/2,x+3*l+l/2,y+l+l/2); //DE

    line(x+3*l+l/2,y+l+l/2,x+l+l/2,y+l+l/2); //EF

    line(x+l+l/2,y+l+l/2,x+l+l/2,y+3*l+l/2); //FG

    line(x+l+l/2,y+3*l+l/2,x-l-l/2,y+3*l+l/2); //GH

    line(x-l-l/2,y+3*l+l/2,x-l-l/2,y+l+l/2); //HI

    line(x-l-l/2,y+l+l/2,x-3*l-l/2,y+l+l/2); //IJ

    line(x-3*l-l/2,y+l+l/2,x-3*l-l/2,y-l-l/2); //JK

    line (x-3*l-l/2,y-l-l/2,x-l-l/2,y-l-l/2); //KL

    line (x-l-l/2,y-l-l/2,x-l-l/2,y-3*l-l/2); //LA


    //PATRAT DIN TABLA
    //SUS PANA JOS
    line (x-l/2,y-3*l-l/2,x-l/2,y+3*l+l/2); //r1

    line (x+l/2,y-3*l-l/2,x+l/2,y+3*l+l/2); //r2
    //STANGA PANA DREAPTA
    line (x-3*l-l/2,y-l/2,x+3*l+l/2,y-l/2); //r8

    line (x-3*l-l/2,y+l/2,x+3*l+l/2,y+l/2); //r7

    line (x-l-l/2,y-l-l/2,x-l-l/2,y+l+l/2); //LI

    line (x+l+l/2,y-l-l/2,x+l+l/2,y+l+l/2); //CF

    line (x-l-l/2,y-l-l/2,x+l+l/2,y-l-l/2); //LC

    line (x-l-l/2,y+l+l/2,x+l+l/2,y+l+l/2); //IF

    line (x-l-l/2,y-2*l-l/2,x+l+l/2,y-2*l-l/2); //m1

    line (x-l-l/2,y+2*l+l/2,x+l+l/2,y+2*l+l/2); //m3

    line (x-2*l-l/2,y-l-l/2,x-2*l-l/2,y+l+l/2); //m4

    line (x+2*l+l/2,y-l-l/2,x+2*l+l/2,y+l+l/2); //m2


}
// Scriere text
void printLabel(int i, int j,  char textOutput[])
{
    int x = (j-1)*dimension;
    int y = ((i-1)*dimension + i*dimension)/2;
    int center = (dimension*2 - textwidth(textOutput))/2;
    setcolor(culoareUmbra);
    outtextxy(x, y, textOutput);
}
void printLabel2(int i, int j,  char textOutput[])
{
    int x = (j-1)*dimension;
    int y = ((i-1)*dimension + i*dimension)/2;
    int center = (dimension*2 - textwidth(textOutput))/2;
    setcolor(YELLOW);
    outtextxy(x, y, textOutput);
}
void desenareButoane(int & limba)
{
    if(limba == 2 ) //BUTOANE ENGLEZA
    {
        readimagefile("butons/singleplayer.jpg",1*dimFEREASTRA/5,2*dimFEREASTRA/5,dimFEREASTRA/2-10,dimFEREASTRA/2-10);
        readimagefile("butons/playervsplayer.jpg",dimFEREASTRA/2+10,2*dimFEREASTRA/5,4*dimFEREASTRA/5,dimFEREASTRA/2-10);
        readimagefile("butons/solutions.jpg",dimFEREASTRA/2+10,dimFEREASTRA/2,4*dimFEREASTRA/5,dimFEREASTRA/2+(dimFEREASTRA/2-10-(2*dimFEREASTRA/5))-10);
        readimagefile("butons/optionsandinformations.jpg",dimFEREASTRA/5,dimFEREASTRA/2,dimFEREASTRA/2-10,dimFEREASTRA/2+(dimFEREASTRA/2-10-(2*dimFEREASTRA/5))-10);
        readimagefile("butons/exit2.jpg",dimFEREASTRA/5,dimFEREASTRA/2+(dimFEREASTRA/2-10-(2*dimFEREASTRA/5)),4*dimFEREASTRA/5,dimFEREASTRA/2+(dimFEREASTRA/2-10-(2*dimFEREASTRA/5))+dimFEREASTRA/2-10-(2*dimFEREASTRA/5)-10);
    }
    else      //BUTOANE ROMANA
    {
        readimagefile("butons/joacasingur.jpg",1*dimFEREASTRA/5,2*dimFEREASTRA/5,dimFEREASTRA/2-10,dimFEREASTRA/2-10);
        readimagefile("butons/jucatorvsjucator.jpg",dimFEREASTRA/2+10,2*dimFEREASTRA/5,4*dimFEREASTRA/5,dimFEREASTRA/2-10);
        readimagefile("butons/solutii.jpg",dimFEREASTRA/2+10,dimFEREASTRA/2,4*dimFEREASTRA/5,dimFEREASTRA/2+(dimFEREASTRA/2-10-(2*dimFEREASTRA/5))-10);
        readimagefile("butons/informatii.jpg",dimFEREASTRA/5,dimFEREASTRA/2,dimFEREASTRA/2-10,dimFEREASTRA/2+(dimFEREASTRA/2-10-(2*dimFEREASTRA/5))-10);
        readimagefile("butons/iesire2.jpg",dimFEREASTRA/5,dimFEREASTRA/2+(dimFEREASTRA/2-10-(2*dimFEREASTRA/5)),4*dimFEREASTRA/5,dimFEREASTRA/2+(dimFEREASTRA/2-10-(2*dimFEREASTRA/5))+dimFEREASTRA/2-10-(2*dimFEREASTRA/5)-10);
    }

}
void selectOption()//Cazacu Razvan
{
    //FUNDAL
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    rectangle(0,0,dimFEREASTRA,dimFEREASTRA);
    floodfill(400,400,WHITE);
    //LOGO
    readimagefile("logo.jpg",0,0,dimFEREASTRA,dimFEREASTRA/3);
    //readimagefile("meniu.jpg",dimFEREASTRA/5,2*dimFEREASTRA/5,4*dimFEREASTRA/5,4*dimFEREASTRA/5);
    readimagefile("RO.JPG",dimFEREASTRA-75,dimFEREASTRA-145,dimFEREASTRA-25,dimFEREASTRA-95);
    readimagefile("ENG.JPG",dimFEREASTRA-75,dimFEREASTRA-75,dimFEREASTRA-25,dimFEREASTRA-25);
    desenareButoane(limba);
}
void desenareScor(int scor) //Adrian Rosu
{
    settextstyle(BOLD_FONT, HORIZ_DIR,2);
    if(scor<=18)
    {
        setcolor(10);
        setbkcolor(culoareFundalSinglePlayer);
        char scorText[]="NUMAR MUTARI:";
        outtextxy(x1-70,L/3,"NUMAR MUTARI:");
        sprintf(scorText,"%d",scor);
        outtextxy(x1,L-10,scorText);
    }
    if(scor>18&&scor<=23)
    {
        setcolor(14);
        setbkcolor(culoareFundalSinglePlayer);
        char scorText[]="NUMAR MUTARI:";
        outtextxy(x1-70,L/3,"NUMAR MUTARI:");
        sprintf(scorText,"%d",scor);
        outtextxy(x1,L-10,scorText);
    }
    if(scor>23&&scor<=28)
    {
        setcolor(12);
        setbkcolor(culoareFundalSinglePlayer);
        char scorText[]="NUMAR MUTARI:";
        outtextxy(x1-70,L/3,"NUMAR MUTARI:");
        sprintf(scorText,"%d",scor);
        outtextxy(x1,L-10,scorText);
    }
    if(scor>28)
    {
        setcolor(4);
        setbkcolor(culoareFundalSinglePlayer);
        char scorText[]="NUMAR MUTARI:";
        outtextxy(x1-70,L/3,"NUMAR MUTARI:");
        sprintf(scorText,"%d",scor);
        outtextxy(x1,L,scorText);
    }

}
// Butonul cu informatii
void informatii(int & limba) //Cazacu Razvan
{
    gata=0;
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    rectangle(0,0,dimFEREASTRA,dimFEREASTRA);
    floodfill(dimFEREASTRA/2,dimFEREASTRA/2,WHITE);

    if(limba==1)
    {
        setcolor(culoareUmbra);
        setbkcolor(WHITE);
        settextstyle(BOLD_FONT,HORIZ_DIR,4);
        int midx=dimFEREASTRA/2;
        int width=textwidth("REGULI JOC SI INFORMATII");
        outtextxy(midx-width/2,15,"REGULI JOC SI INFORMATII");

        settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
        printLabel(5,2,"1.Pe tabla jocului se afla pioni identici , in fiecare casuta cate unul , lasand una");
        printLabel(6,3,"sau mai multe casute libere.");
        printLabel(7,2,"2.Fiecare pion poate sari peste un pion vecin ,orizontal sau vertical,deci nu si ");
        printLabel(8,3,"diagonal,cu conditia ca in spatele acestuia sa existe o cauta libera.");
        printLabel(9,2,"3.Pionul peste care se sare este eliminat.");
        printLabel(10,2,"4.Jocul se termina atunci cand au fost eliminati toti pionii infara de unul singur ");
        printLabel(11,3,"care trebuie sa ajunga in centrul tablei acolo unde la inceputul jocului era o");
        printLabel(12,3,"casuta libera.");
        printLabel(13,2,"5.Deoarece avem de eliminat 31 de piese , iar la fiecare saritura se elimina cate");
        printLabel(14,3,"una , jocul poate fi terminat in exact 31 de mutari elementare");

        readimagefile("butons/iesire.jpg",dimFEREASTRA-3*L,dimFEREASTRA-2*L,dimFEREASTRA-L/2,dimFEREASTRA-L-20);
        readimagefile("butons/inapoi.jpg",L/2,dimFEREASTRA-2*L,dimFEREASTRA-7*L,dimFEREASTRA-L-20);

   }
   else
   {
        setcolor(culoareUmbra);
        setbkcolor(WHITE);
        settextstyle(BOLD_FONT,HORIZ_DIR,4);
        int midx=dimFEREASTRA/2;
        int width=textwidth("RULES");
        outtextxy(midx-width/2,15,"RULES");

        settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
        printLabel(5,2,"1.On the board of the game there are identical piece, in each box one, leaving one");
        printLabel(6,3,"or more free boxes.");

        printLabel(7,2,"2.Each piece can jump over a neighbor, horizontal or vertical , so not diagonally,");
        printLabel(8,3," provided there is a free box behind it.");

        printLabel(9,2,"3.The piece over which jump is removed .");

        printLabel(10,2,"4.The game ends when all the pieces have been eliminated from one by one who must");
        printLabel(11,3,"reach the center of the board where there was a free box at the beginning of");
        printLabel(12,3,"the game.");

        printLabel(13,2,"5.Because we have to eliminate 31 pieces, and for each jump is eliminated one,");
        printLabel(14,3,"the game can be finished in exactly 31 elementary moves.");

        readimagefile("butons/exit.jpg",dimFEREASTRA-3*L,dimFEREASTRA-2*L,dimFEREASTRA-L/2,dimFEREASTRA-L-20);
        readimagefile("butons/back.jpg",L/2,dimFEREASTRA-2*L,dimFEREASTRA-7*L,dimFEREASTRA-L-20);
   }
    int pot=1;
    while(pot){
    while (!ismouseclick(WM_LBUTTONDOWN));
    if (ismouseclick(WM_LBUTTONDOWN))
    {
        x = mousex();  //x si y coordonate click
        y = mousey();
        //exit
        if((x>=dimFEREASTRA-3*L && x<=dimFEREASTRA-L/2) && (y>=dimFEREASTRA-3*L && y<=dimFEREASTRA-L-20))
        {
            pot=0;
            clearmouseclick(WM_LBUTTONDOWN);
            exit(0);
        }
        //back
        else if((x>=L/2 && x<=dimFEREASTRA-7*L) && (y>=dimFEREASTRA-2*L && y<=dimFEREASTRA-L-20))
        {
            pot=0;
            clearmouseclick(WM_LBUTTONDOWN);
            cleardevice();
            gata=1;
            selectOption();
        }
        else
            clearmouseclick(WM_LBUTTONDOWN);
    }
    }
}

void desenareBile()//Adrian Rosu
{
    short i;

            for(i=1;i<=33;i++)
            {
                if(bile[i].ocupat==1)
                {
                    setcolor(bile[i].culoare);
                    setfillstyle(SOLID_FILL, bile[i].culoare);
                    circle(bile[i].x,bile[i].y,L/3);
                    floodfill(bile[i].x,bile[i].y, bile[i].culoare);
                }
                else
                {
                    if(i%2!=0)
                    {
                        setcolor(10);
                        setfillstyle(SOLID_FILL, 10);
                        circle(bile[i].x,bile[i].y,L/3);
                        floodfill(bile[i].x,bile[i].y,10);
                    }
                    else
                    {
                        setcolor(15);
                        setfillstyle(SOLID_FILL, 15);
                        circle(bile[i].x,bile[i].y,L/3);
                        floodfill(bile[i].x,bile[i].y, 15);
                    }
                }
            }

}
void desenareUmbreTabla()//Adrian Rosu
{
    //U1
    setcolor(culoareUmbra);
    unsigned int i,j;
    for(i=x1-3*L-L/2-umbra;i<=x1+3*L+L/2+umbra;i++)
    {
        line(i,y1-L-L/2-umbra,i,y1+L+L/2+umbra);
    }
    //U2
    for(i=x1-L-L/2-umbra;i<=x1+L+L/2+umbra;i++)
    {
        line(i,y1-3*L-L/2-umbra,i,y1+3*L+L/2+umbra);
    }

    setcolor(2);
    //LINII MARI
    line(x1-3*L-L/2-umbra,y1-L-L/2-umbra,x1-3*L-L/2-umbra,y1+L+L/2+umbra);
    line(x1-3*L-L/2-umbra,y1+L+L/2+umbra,x1-L-L/2-umbra,y1+L+L/2+umbra);
    line(x1-L-L/2-umbra,y1+L+L/2+umbra,x1-L-L/2-umbra,y1+3*L+L/2+umbra);
    line(x1-L-L/2-umbra,y1+3*L+L/2+umbra,x1+L+L/2+umbra,y1+3*L+L/2+umbra);
    line(x1+L+L/2+umbra,y1+3*L+L/2+umbra,x1+L+L/2+umbra,y1+L+L/2+umbra);
    line(x1+L+L/2+umbra,y1+L+L/2+umbra,x1+3*L+L/2+umbra,y1+L+L/2+umbra);
    line(x1+3*L+L/2+umbra,y1+L+L/2+umbra,x1+3*L+L/2+umbra,y1-L-L/2-umbra);
    line(x1+3*L+L/2+umbra,y1-L-L/2-umbra,x1+L+L/2+umbra,y1-L-L/2-umbra);
    line(x1+L+L/2+umbra,y1-L-L/2-umbra,x1+L+L/2+umbra,y1-3*L-L/2-umbra);
    line(x1+L+L/2+umbra,y1-3*L-L/2-umbra,x1-L-L/2-umbra,y1-3*L-L/2-umbra);
    line(x1-L-L/2-umbra,y1-3*L-L/2-umbra,x1-L-L/2-umbra,y1-L-L/2-umbra);
    line(x1-L-L/2-umbra,y1-L-L/2-umbra,x1-3*L-L/2-umbra,y1-L-L/2-umbra);
    //STANGA
    line(x1-L-L/2,y1-3*L-L/2,x1-L-L/2-umbra,y1-3*L-L/2-umbra);
    line(x1-L-L/2,y1-L-L/2,x1-L-L/2-umbra,y1-L-L/2-umbra);
    line(x1-3*L-L/2,y1-L-L/2,x1-3*L-L/2-umbra,y1-L-L/2-umbra);
    line(x1-3*L-L/2,y1+L+L/2,x1-3*L-L/2-umbra,y1+L+L/2+umbra);
    line(x1-L-L/2,y1+L+L/2,x1-L-L/2-umbra,y1+L+L/2+umbra);
    line(x1-L-L/2,y1+3*L+L/2,x1-L-L/2-umbra,y1+3*L+L/2+umbra);
    //DREAPTA
    line(x1+L+L/2,y1-3*L-L/2,x1+L+L/2+umbra,y1-3*L-L/2-umbra);
    line(x1+L+L/2,y1-L-L/2,x1+L+L/2+umbra,y1-L-L/2-umbra);
    line(x1+3*L+L/2,y1-L-L/2,x1+3*L+L/2+umbra,y1-L-L/2-umbra);
    line(x1+3*L+L/2,y1+L+L/2,x1+3*L+L/2+umbra,y1+L+L/2+umbra);
    line(x1+L+L/2,y1+L+L/2,x1+L+L/2+umbra,y1+L+L/2+umbra);
    line(x1+L+L/2,y1+3*L+L/2,x1+L+L/2+umbra,y1+3*L+L/2+umbra);

}
void desenareCareu()//Adrian Rosu&Razvan Cazacu
{
    int i;
    for(i=1;i<=33;i++)
    {
        if(i%2!=0)
        {
                bile[i].culoareFundal=10;
                setcolor(bile[i].culoareFundal);
                setfillstyle(SOLID_FILL, bile[i].culoareFundal);
                rectangle(bile[i].x-L/2,bile[i].y-L/2,bile[i].x+L/2,bile[i].y+L/2);
                floodfill((bile[i].x-L/2+bile[i].x+L/2)/2 , (bile[i].y-L/2+bile[i].y+L/2)/2,bile[i].culoareFundal);
        }
        else
        {
                bile[i].culoareFundal=15;
                setcolor(bile[i].culoareFundal);
                setfillstyle(SOLID_FILL, bile[i].culoareFundal);
                rectangle(bile[i].x-L/2,bile[i].y-L/2,bile[i].x+L/2,bile[i].y+L/2);
                floodfill((bile[i].x-L/2+bile[i].x+L/2)/2 , (bile[i].y-L/2+bile[i].y+L/2)/2,bile[i].culoareFundal);
        }
    }
}
void desenareFundal()//Adrian Rosu
{
    setcolor(culoareFundalSinglePlayer);
    setfillstyle(SOLID_FILL,culoareFundalSinglePlayer);
    rectangle(0,0,dimFEREASTRA,dimFEREASTRA);
    floodfill(dimFEREASTRA/2,dimFEREASTRA/2,culoareFundalSinglePlayer);
}
void solutia1() // NU E GATA
{
    int a,b,nrm;
    int bilacurenta,bilainlocuita;
    ff>>nrm;
    for(int i=1;i<=nrm;i++)
    {
        ff>>a>>b;
        bilacurenta=a;
        bilainlocuita=b;
        if(bilacurenta!= -1)
        {

            if(validBilaUrmatoare(bilacurenta,bilainlocuita)==1)
                {
                    bile[bilacurenta].ocupat=0;
                    bile[bilainlocuita].ocupat=1;
                }
        }
    }
}
void win (int scor)  // Cazacu Razvan&Adrian Rosu
{
    int i,nr=0;
    int pot=1,pot1=1;
    for(i=1;i<=33;i++)
        if(bile[i].ocupat==1)
            nr++;
    if(nr==1 && bile[17].ocupat==1)
        terminat=1;
    if(terminat==1)
    {
        gata=0;
        cleardevice();
        desenareFundal();
        terminat=0;
        if(limba==1)
        {
            cleardevice();
            setcolor(WHITE);
            setfillstyle(SOLID_FILL,WHITE);
            rectangle(0,0,dimFEREASTRA,dimFEREASTRA);
            floodfill(400,400,WHITE);
            setcolor(2);

            settextstyle(BOLD_FONT,HORIZ_DIR,4);
            setbkcolor(WHITE);
            short midx=dimFEREASTRA/2;
            int width=textwidth("!!!FELICITARI, AI TERMINAT JOCUL!!!");
            outtextxy(midx-width/2,midx-width/2,"!!!FELICITARI, AI TERMINAT JOCUL!!!");
            width=textwidth("SCORUL TAU ESTE:");
            outtextxy(midx-width/2,midx-width/2+25,"SCORUL TAU ESTE:");
            char scorText[]="NUMAR MUTARI:";
            sprintf(scorText,"%d",scor);
            width=textwidth("XZ");
            outtextxy(midx-width/2,midx-width/2+50,scorText);
            readimagefile("back.jpg",dimFEREASTRA/2-100,dimFEREASTRA/2+200,dimFEREASTRA/2+100,dimFEREASTRA/2+300);
            while(pot)
            {
            while (!ismouseclick(WM_LBUTTONDOWN));
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                x = mousex();  //x si y coordonate click
                y = mousey();
                if((x>=dimFEREASTRA/2-100 && x<=dimFEREASTRA/2+100) && (y>=dimFEREASTRA/2+200 && y<=dimFEREASTRA/2+300))
                {
                    pot1=0;pot=0;
                    clearmouseclick(WM_LBUTTONDOWN);
                    cleardevice();
                    gata=0; scor=0;
                    terminat=0;
                    selectOption();
                    selectie();
                }
                else
                    clearmouseclick(WM_LBUTTONDOWN);
            }
            }
        }
        else
        {
            cleardevice();
            setcolor(WHITE);
            setfillstyle(SOLID_FILL,WHITE);
            rectangle(0,0,dimFEREASTRA,dimFEREASTRA);
            floodfill(400,400,WHITE);
            setcolor(2);
            settextstyle(BOLD_FONT,HORIZ_DIR,4);
            setbkcolor(WHITE);
            short midx=dimFEREASTRA/2;
            int width=textwidth("!!!FELICITARI, AI TERMINAT JOCUL!!!");
            outtextxy(midx-width/2,midx-width/2,"!!!FELICITARI, AI TERMINAT JOCUL!!!");
            width=textwidth("SCORUL TAU ESTE:");
            outtextxy(midx-width/2,midx-width/2+25,"SCORUL TAU ESTE:");
            char scorText[]="NUMAR MUTARI:";
            sprintf(scorText,"%d",scor);
            width=textwidth("XZ");
            outtextxy(midx-width/2,midx-width/2+50,scorText);
            readimagefile("back.jpg",dimFEREASTRA/2-100,dimFEREASTRA/2+200,dimFEREASTRA/2+100,dimFEREASTRA/2+300);
            while(pot1)
            {
            while (!ismouseclick(WM_LBUTTONDOWN));
            if (ismouseclick(WM_LBUTTONDOWN))
                {
                x = mousex();  //x si y coordonate click
                y = mousey();
                if((x>=dimFEREASTRA/2-100 && x<=dimFEREASTRA/2+100) && (y>=dimFEREASTRA/2+200 && y<=dimFEREASTRA/2+300))
                {
                    pot1=0;pot=0;
                    clearmouseclick(WM_LBUTTONDOWN);
                    cleardevice();
                    gata=0;scor=0;
                    terminat=0;
                    selectOption();
                    selectie();
                }
                else
                    clearmouseclick(WM_LBUTTONDOWN);

                }

            }
        }
    }
}

void lose()//Adrian Rosu
{
    lost=1;
    short i;
    for(i=1;i<=33;i++)
    {
        if(bile[i].ocupat==1&&bile[bile[i].vecMicDreapta].ocupat==1&&bile[bile[i].vecDreapta].ocupat==0)
            lost=0;
        if(bile[i].ocupat==1&&bile[bile[i].vecMicStanga].ocupat==1&&bile[bile[i].vecStanga].ocupat==0)
            lost=0;
        if(bile[i].ocupat==1&&bile[bile[i].vecMicSus].ocupat==1&&bile[bile[i].vecSus].ocupat==0)
            lost=0;
        if(bile[i].ocupat==1&&bile[bile[i].vecMicJos].ocupat==1&&bile[bile[i].vecJos].ocupat==0)
            lost=0;

    }

    if(lost==1)
    {
        int pot=1,pot1=1;
        gata=0;
        cleardevice();
        desenareFundal();
        terminat=0;
        if(limba==1)
        {
            cleardevice();
            setcolor(WHITE);
            setfillstyle(SOLID_FILL,WHITE);
            rectangle(0,0,dimFEREASTRA,dimFEREASTRA);
            floodfill(400,400,WHITE);
            setcolor(2);
            settextstyle(BOLD_FONT,HORIZ_DIR,4);
            setbkcolor(WHITE);
            short midx=dimFEREASTRA/2;
            int width=textwidth("!!!NU MAI POTI MUTA BILE!!!");
            outtextxy(midx-width/2,midx-width/2,"!!!NU MAI POTI MUTA BILE!!!");
            width=textwidth("!!!OH,NUU, AI PIERDUT!!!");
            outtextxy(midx-width/2,midx-width/2+50,"!!!OH,NUU, AI PIERDUT!!!");
            readimagefile("back.jpg",dimFEREASTRA/2-100,dimFEREASTRA/2+200,dimFEREASTRA/2+100,dimFEREASTRA/2+300);
            while(pot)
            {
            while (!ismouseclick(WM_LBUTTONDOWN));
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                x = mousex();  //x si y coordonate click
                y = mousey();
                if((x>=dimFEREASTRA/2-100 && x<=dimFEREASTRA/2+100) && (y>=dimFEREASTRA/2+200 && y<=dimFEREASTRA/2+300))
                {
                    pot1=0;pot=0;
                    clearmouseclick(WM_LBUTTONDOWN);
                    cleardevice();
                    gata=0; scor=0;
                    lost=0;
                    selectOption();
                    selectie();
                }
                else
                    clearmouseclick(WM_LBUTTONDOWN);
            }
            }
        }
        else
        {
            cleardevice();
            setcolor(WHITE);
            setfillstyle(SOLID_FILL,WHITE);
            rectangle(0,0,dimFEREASTRA,dimFEREASTRA);
            floodfill(400,400,WHITE);
            setcolor(2);
            settextstyle(BOLD_FONT,HORIZ_DIR,4);
            setbkcolor(WHITE);
            short midx=dimFEREASTRA/2;
            int width=textwidth("!!!YOU CAN NOT MOVE BALLS!!!");
            outtextxy(midx-width/2,midx-width/2,"!!!YOU CAN NOT MOVE BALLS!!!!");
            width=textwidth("!!!OH,NOOO, YOU LOSE!!!");
            outtextxy(midx-width/2,midx-width/2+50,"!!!OH,NOOO, YOU LOSE!!!");
            readimagefile("back.jpg",dimFEREASTRA/2-100,dimFEREASTRA/2+200,dimFEREASTRA/2+100,dimFEREASTRA/2+300);
            while(pot1)
            {
            while (!ismouseclick(WM_LBUTTONDOWN));
            if (ismouseclick(WM_LBUTTONDOWN))
                {
                x = mousex();  //x si y coordonate click
                y = mousey();
                if((x>=dimFEREASTRA/2-100 && x<=dimFEREASTRA/2+100) && (y>=dimFEREASTRA/2+200 && y<=dimFEREASTRA/2+300))
                {
                    pot1=0;pot=0;
                    clearmouseclick(WM_LBUTTONDOWN);
                    cleardevice();
                    gata=0;scor=0;
                    lost=0;
                    selectOption();
                    selectie();
                }
                else
                    clearmouseclick(WM_LBUTTONDOWN);

                }

            }
        }
    }
}



// Selectarea unui buton
void selectie () //Cazacu Razvan & Adrian Rosu
{
    int x,y,nr=0,i;
    while (!ismouseclick(WM_LBUTTONDOWN));
    if (ismouseclick(WM_LBUTTONDOWN))
    {
        x = mousex();  //x si y coordonate click
        y = mousey();
        // Single player
        if ((x>=1*dimFEREASTRA/5 && x<=dimFEREASTRA/2-10) && (y>=2*dimFEREASTRA/5 && y<=dimFEREASTRA/2-10))
        {
            lost=0;
            tipJoc=1;
            clearmouseclick(WM_LBUTTONDOWN);
            cleardevice();
            bileInitializare(x1,y1,L);
            desenareFundal();
            desenareUmbreTabla();
            desenareCareu();
            tabla(x1,y1,L);
            do
            {
                desenareBile();
                selectareBila();
                desenareScor(scor);
                win(scor);
                lose();
            }while(gata==1);
        }
        //Player vs player
        else if ((x>=dimFEREASTRA/2+10 && x<=4*dimFEREASTRA/5) && (y>=2*dimFEREASTRA/5 && y<=dimFEREASTRA/2-10))
        {
            tipJoc==2;
            clearmouseclick(WM_LBUTTONDOWN);
            cleardevice();
            bileInitializare(x1,y1,L);
            desenareFundal();
            desenareUmbreTabla();
            desenareCareu();
            tabla(x1,y1,L);
            do
            {
                desenareBile();
                selectareBila();
                desenareScor(scor);
                win(scor);
            }while(gata==1);

        }

        //SOLUTII
        else if ((x>=dimFEREASTRA/2+10 && x<=4*dimFEREASTRA/5) && (y>=dimFEREASTRA/2 && y<=dimFEREASTRA/2+(dimFEREASTRA/2-10-(2*dimFEREASTRA/5))-10))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            cleardevice();
            setcolor(culoareUmbra);
            bileInitializare(x1,y1,L);
            desenareFundal();
            desenareUmbreTabla();
            desenareCareu();
            tabla(x1,y1,L);
            desenareBile();
            setcolor(12);
            setbkcolor(culoareFundalSinglePlayer);
            if(limba==1)
            {
                printLabel2(1,4," In anul 1962, J.D. Beary  a dat o solutie in numai 18 mutari.Iat-o :");
                printLabel2(2,4,"(5,17). (12,10), (3,11), (18,6), (30, 18), (27, 15),");
                printLabel2(3,4,"(24,26) ; (13,27,25) ; (9,11) ; (7,9) ; (22,24,26,12,10,8) ; (31,23) ; (16,28) ;");
                printLabel2(4,4,"(33,31,23) ; (21,7,9) ; (1,3,11,25) ; (4,16,28,30,18,16) ; (15,17).");
            }
            else
            {
                printLabel2(1,4," In 1962, J.D. Beary gave a solution in only 18 moves. Here it is :");
                printLabel2(2,4,"(5,17). (12,10), (3,11), (18,6), (30, 18), (27, 15),");
                printLabel2(3,4,"(24,26) ; (13,27,25) ; (9,11) ; (7,9) ; (22,24,26,12,10,8) ; (31,23) ; (16,28) ;");
                printLabel2(4,4,"(33,31,23) ; (21,7,9) ; (1,3,11,25) ; (4,16,28,30,18,16) ; (15,17).");
            }
              do{
                desenareBile();
                selectareBila();
                win(scor);
              }while(gata==1);
        }
        //OPTIUNI SI INFORMATII
        else if ((x>=dimFEREASTRA/5 && x<=dimFEREASTRA/2-10 )&& (y>=dimFEREASTRA/2 && y<=dimFEREASTRA/2+(dimFEREASTRA/2-10-(2*dimFEREASTRA/5))-10 ))
         {
            clearmouseclick(WM_LBUTTONDOWN);
            cleardevice();
            informatii(limba);
         }
         //EXIT
        else if((x>=dimFEREASTRA/5 && x<=4*dimFEREASTRA/5)&& (y>=dimFEREASTRA/2+(dimFEREASTRA/2-10-(2*dimFEREASTRA/5)) && y<=dimFEREASTRA/2+(dimFEREASTRA/2-10-(2*dimFEREASTRA/5))+dimFEREASTRA/2-10-(2*dimFEREASTRA/5)-10))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            cleardevice();
            exit(0);

        }
        //LIMBA ENGLEZA
        else if ((x>=dimFEREASTRA-75 && x<=dimFEREASTRA-25) && (y>=dimFEREASTRA-75 && y<=dimFEREASTRA-25))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            limba=2;
            desenareButoane(limba);
        }
        //LIMBA ROMANA
        else if ((x>=dimFEREASTRA-75 && x<=dimFEREASTRA-25) && (y>=dimFEREASTRA-145 && y<=dimFEREASTRA-95))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            limba=1;
            desenareButoane(limba);
        }
        else
            clearmouseclick(WM_LBUTTONDOWN);
       }

}

