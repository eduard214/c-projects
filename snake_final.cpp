#include <graphics.h>
#include <winbgim.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iostream>

using namespace std;

struct punct
{
    int x, y;
};

time_t timpStart, timpCrt;

int readKey()
{
    char c;
    c = getch();
    if( c == 0)
        c = getch();
    return c;
}

int patrat( int x , int y , int COLOR, int marime )
{
    int old_color=getcolor();
    setcolor(COLOR);
    rectangle( x, y, x+marime, y+marime );
}

bool iesire_din_harta( int x, int y )
{
    ///525, 285, 790, 400
    if ( x <= 0 || x >= 1390 || y <= 0 || y >=690)
        return true;
    if( x >= 525 && x <= 790 && y >= 285 && y <= 400 )
        return true;
    return false;

}

bool iesire_din_harta_beat(int x, int y)
{
    if( x-75 <= 100 || x+75 >= 1390 || y-75 <= 0 || y+75 >= 690 )
        return true;
    else
        return false;
}

void stea(int x, int y, int raza, int COLOR)
{
    int old_color=getcolor(), poligon[26], l=raza*3/sqrt(3);
    setcolor( COLOR );

   poligon[0]=x, poligon[1]=y-raza;
   poligon[2]=x+ raza/5, poligon[3]=y-raza/5;
   poligon[4]=x+ sqrt(35)*raza/5, poligon[5]=y-raza/5;
   poligon[6]=x+ 4*raza/15, poligon[7]=y+raza/5;
   poligon[8]=x+3*raza/5, poligon[9]=y+raza;
   poligon[10]=x, poligon[11]=y+2*raza/5;
   poligon[12]=x-3*raza/5, poligon[13]=y+raza;
   poligon[14]=x-4*raza/15, poligon[15]=y+raza/5;
   poligon[16]=x-sqrt(35)*raza/5, poligon[17]=y-raza/5;
   poligon[18]=x-raza/5, poligon[19]=y-raza/5;
   poligon[20]=x, poligon[21]=y-raza;

    drawpoly(11, poligon);
    setcolor(old_color);
}

bool lovire_cerc( int xc, int yc, int &Lung, int xcerc, int ycerc, int raza, int marime )  ///DE FACUT
{
    int old_color=getcolor(), hitbox;
    xc+=marime/2;
    yc+=marime/2;
    hitbox=raza+raza/3;
    if( xc >= xcerc - hitbox && xc <= xcerc + hitbox && yc >= ycerc - hitbox && yc <= ycerc + hitbox )
    {
        Lung++;
        setcolor(BLACK);
        stea( xcerc, ycerc, raza, BLACK );
        setcolor( old_color );
        return true;
    }
    return false;
}

bool lovire_cerc_beat( int xc, int yc, int &Lung, int xcerc, int ycerc, int raza, int marime, punct sarpe[] )  ///DE FACUT
{
    int old_color=getcolor(), hitbox;
    xc+=marime/2;
    yc+=marime/2;
    hitbox=raza+raza/5+marime*3;
    if( xc >= xcerc - hitbox && xc <= xcerc + hitbox && yc >= ycerc - hitbox && yc <= ycerc + hitbox )
    {
        Lung++;
        sarpe[Lung].x=sarpe[Lung-1].x;
        sarpe[Lung].y=sarpe[Lung-1].y+marime;
        setcolor(BLACK);
        stea( xcerc, ycerc, raza, BLACK );
        setcolor( old_color );
        return true;
    }
    return false;
}

void generare_cerc( int &xcerc, int &ycerc, int raza )
{
    ///525, 285, 790, 400
    int old_color=getcolor(), old_xcerc=xcerc, old_ycerc=ycerc;
    srand((unsigned) time(0));
    while( 300 > sqrt((old_xcerc-xcerc)*(old_xcerc-xcerc) + (old_ycerc-ycerc)*(old_ycerc-ycerc)) )
    {
        switch( rand()%4 )
        {
        case 0:
            {
                xcerc = rand()%400+99;
                ycerc = rand()%550+75;
            } break;
        case 1:
            {
                xcerc = rand()%1200+99;
                ycerc = rand()%175+75;
            } break;
        case 2:
            {
                xcerc = rand()%400+850;
                ycerc = rand()%550+75;
            } break;
        case 3:
            {
                xcerc = rand()%1200+99;
                ycerc = rand()%200+450;
            }
        }

    }
    setcolor(GREEN);
    stea( xcerc, ycerc, raza, GREEN );
    setcolor(old_color);
}

void generare_cerc_beat( int &xcerc, int &ycerc, int raza )
{
    int old_color=getcolor(), old_xcerc=xcerc, old_ycerc=ycerc;
    srand((unsigned) time(0));
    while( 300 > sqrt((old_xcerc-xcerc)*(old_xcerc-xcerc) + (old_ycerc-ycerc)*(old_ycerc-ycerc)) )
    {
        xcerc = rand()%1150+130;
        ycerc = rand()%550+75;
    }
    setcolor(GREEN);
    stea( xcerc, ycerc, raza, GREEN );
    setcolor(old_color);
}

void game_over()
{
    int tasta, old_color=getcolor();
    cleardevice();
    setcolor(RED);
    rectangle(200, 100, 1200, 600);

    setlinestyle(SOLID_FILL, 6, 15);
    for(int i = 1, culoare=1 ; 2*i <= getmaxx() ; i+=10, culoare++  )
    {
        if(culoare >= 14)
            culoare=1;
        setcolor( culoare );
        rectangle(2*i, i, getmaxx()-2*i, getmaxy()-i);
    }
    setlinestyle(SOLID_FILL, 6, 1);


    settextstyle( BOLD_FONT, 0, 8 );
    setcolor(YELLOW);
    outtextxy( getmaxx()/2-230, getmaxy()/2-50, "Ai pierdut" );
    tasta = readKey();
    while ( tasta != 27 )
        tasta = readKey();
    setcolor(old_color);
    closegraph();
}

void game_over_beat()
{
    int tasta, old_color=getcolor();
    cleardevice();
    setcolor(RED);
    rectangle(200, 100, 1200, 600);

    setlinestyle(SOLID_FILL, 6, 15);
    for(int i = 1, culoare=1 ; 2*i <= getmaxx() ; i+=10, culoare++  )
    {
        if(culoare >= 14)
            culoare=1;
        setcolor( culoare );
        rectangle(2*i, i, getmaxx()-2*i, getmaxy()-i);
    }
    setlinestyle(SOLID_FILL, 6, 1);


    settextstyle( BOLD_FONT, 0, 8 );
    setcolor(YELLOW);
    outtextxy( getmaxx()/2+239, getmaxy()/2+30, "Ai pierdut" );
    tasta = readKey();
    while ( tasta != 27 )
        tasta = readKey();
    setcolor(old_color);
    closegraph();
}

void loading()
{
    initwindow(1400, 700, "Snake start");
    srand((unsigned) time(0));
    settextstyle(BOLD_FONT, 0, 10 );
    setcolor(GREEN);
    outtextxy(getmaxx()/2-200, getmaxy()/2-125, "Snake");
    settextstyle(BOLD_FONT, 0, 5);
    outtextxy(getmaxx()/2, getmaxy()/2, "Origini");

    setcolor(WHITE);
    settextstyle(BOLD_FONT, 0, 3);
    outtextxy(getmaxx()/2-90, getmaxy()/2+100, "Loading ...");

    setcolor(RED);

    line(200, 500, 1200, 500);
    setcolor(GREEN);


    int random;
    for( int i=200 ; i <=1200; i+=rand()%100+100 )
        {line(200, 500, i, 500);
        delay(rand()%1500+500);}

    line(200, 500, 1200, 500);

    closegraph();
}

int UI_dificultate()
{
    int x, y, old_color;




    initwindow(1300, 400, "Sarpe_UI");
    old_color=getcolor();
    setlinestyle( SOLID_FILL, 4, 5 );
    setcolor(CYAN);
    settextstyle(BOLD_FONT, 0, 4 );
    outtextxy(500, 50, "Alege dificultatea:");
    settextstyle(BOLD_FONT, 0, 4 );

    setcolor(GREEN);
    rectangle(1, 100, 300, 350);
    outtextxy( 50, 150, "Sarpe beat" );

    setcolor(YELLOW);
    rectangle(305, 100, 605, 350);
    outtextxy(350, 150, "Normal");

    setcolor(RED);
    rectangle(610, 100, 910, 350);
    outtextxy(650, 150, "Greu");

    setcolor( DARKGRAY );
    rectangle(915, 100, 1215, 350);
    outtextxy(950, 150, "Imposibil");

    while ( !ismouseclick(WM_LBUTTONDOWN) )
        delay(200);
    getmouseclick(WM_LBUTTONDOWN, x, y);

    setcolor(old_color);
    setlinestyle( SOLID_FILL, 4, 1 );

    closegraph();

    if( y >= 100 && y <= 350 )
    {
        if (  x <= 300 && x >= 1  )  ///USOR
            return 500;
        if( x >= 305 && x <= 605  ) ///Normal
            return 125;
        if( x>= 610 && x <= 910 ) ///greu
            return 100;
        if( x >= 915 && x <= 1215 ) ///imposibil
            return 60;
    }
    UI_dificultate();
}

void calc_scor(int  dificultate, int Lung, int &scor )
{

  switch( dificultate )
  {
      case 75:{   ///pt sarpe_beat
          scor= (Lung - 2)*1;
      } break;
      case 125:{
          scor = ( Lung - 2 ) * 2;
      } break;
      case 100:{
          scor = ( Lung - 2 ) * 3;
      } break;
      case 60:{
          scor = ( Lung - 2 ) * 10;
      } break;
  }
}

void cap_beat(int x, int y, int marime, int color)
{
    int old_color=getcolor();
    x+=marime/2;
    y-=marime/2;
    setcolor(color);
    circle(x, y, marime*3);
    ellipse(x-3*marime/2, y-3*marime/2, 0, 180, 2*marime/3, 5);
    ellipse(x-3*marime/2, y-3*marime/2, 180, 0, 2*marime/3, 5);

    ellipse(x+3*marime/2, y-3*marime/2, 0, 180, 2*marime/3, 5);
    ellipse(x+3*marime/2, y-3*marime/2, 180, 0, 2*marime/3, 5);

    if( color == BLACK)
        setcolor(BLACK);
    else
        setcolor(WHITE);
    circle(x-3*marime/2, y-3*marime/2, 3);
    circle(x+3*marime/2, y-3*marime/2, 3);

    setcolor(old_color);
}

void tabela_scor_beat()
{
    int old_color=getcolor();

    setcolor(CYAN);
    rectangle(1, 1, 100, 700 );
    settextstyle(BOLD_FONT, 1, 5);
    outtextxy(71, 200, "Stele mancate:" );
    settextstyle(BOLD_FONT, 0, 5);


    setcolor(old_color);
}

void afisare_scor_beat(int scor)
{
    char scor_beat[11];
    sprintf(scor_beat, "%d", scor);
    if( scor < 10 )
        outtextxy(65, 195, scor_beat);
    else
    {
        if( scor >=10 && scor <= 99 )
            outtextxy(75, 195, scor_beat);
    }
}

int incepere_joc_beat( int marime, int raza, int &scor, int &Lung, int &dificultate )
{
    Lung=2;
    punct sarpe[101];
    dificultate=75;
    marime=25;
    initwindow(1400, 700, "Sarpe_beat");
    char scor_beat[11];
    bool terminat = false, miscare_permisa=false;
    int tasta_old, tasta=72, xc=getmaxx()/2, yc=getmaxy()/2, directie, xcerc, ycerc, overflow, culoare_sarpe=YELLOW, old_color=getcolor();
    ///desenez un cerc pt prima oara
    generare_cerc(xcerc, ycerc, raza);
    ///desenez sarpili pt prima data
    sarpe[1].x=getmaxx()/2;
    sarpe[1].y=getmaxy()/2;
    sarpe[2].y=sarpe[1].y+marime;
    sarpe[2].x=sarpe[1].x;
    for( int i = 1 ; i <= Lung ; i++)
        patrat( sarpe[i].x, sarpe[i].y, culoare_sarpe, marime );
    tabela_scor_beat();
    while (! terminat)
    {
        tasta_old = tasta;
        while (  kbhit() ){
            tasta = readKey();
            if( !(tasta == 72 || tasta == 77 || tasta == 75 || tasta == 80 || tasta == 27) )
                tasta = tasta_old;
            }

        switch(tasta)
        {
            case 119: break;
            ///sageata-sus
            case 72: {
                for(int i=1 ; i <= Lung; i++){
                    if( i == 1 )
                        patrat(sarpe[i].x, sarpe[i].y, BLACK, marime), cap_beat(sarpe[i].x, sarpe[i].y, marime, BLACK );
                    else
                        patrat(sarpe[i].x, sarpe[i].y, BLACK, marime);}
                for(int i=1 ; i <= Lung; i++)
                    sarpe[i].y-=marime;
                for(int i=1 ; i <= Lung; i++){
                    if( i == 1 )
                        patrat(sarpe[i].x, sarpe[i].y, YELLOW, marime), cap_beat(sarpe[i].x, sarpe[i].y, marime, culoare_sarpe);
                    else
                        patrat(sarpe[i].x, sarpe[i].y, culoare_sarpe, marime);}
                delay(dificultate);
                if( iesire_din_harta_beat(sarpe[1].x, sarpe[1].y) )
                        {game_over_beat();
                         return 0;}
                if( lovire_cerc_beat(sarpe[1].x, sarpe[1].y, Lung, xcerc, ycerc, raza, marime, sarpe) )
                        generare_cerc_beat(xcerc, ycerc, raza);
            } break;
            ///sageata-jos
            case 80: {
                for(int i=1 ; i <= Lung ; i++){  ///sterg sarpele
                     if( i == 1 )
                        patrat(sarpe[i].x, sarpe[i].y, BLACK, marime), cap_beat(sarpe[i].x, sarpe[i].y, marime, BLACK);
                     else
                     patrat(sarpe[i].x, sarpe[i].y, BLACK, marime);}
                for(int i=1 ; i <= Lung ; i++)
                    sarpe[i].y+=marime;
                for(int i=1 ; i <= Lung ; i++){
                    if( i == 1 )
                        patrat(sarpe[i].x, sarpe[i].y, YELLOW, marime), cap_beat(sarpe[i].x, sarpe[i].y, marime, culoare_sarpe);
                    else
                        patrat( sarpe[i].x, sarpe[i].y, culoare_sarpe, marime );}
                delay(dificultate);
                if( iesire_din_harta_beat(sarpe[1].x, sarpe[1].y) )
                        {game_over_beat();
                         return 0;}
                if( lovire_cerc_beat(sarpe[1].x, sarpe[1].y, Lung, xcerc, ycerc, raza, marime, sarpe) )
                        generare_cerc_beat(xcerc, ycerc, raza);
            } break;
            ///sageata-stanga
            case 75: {
                for(int i=1 ; i <= Lung ; i++){  ///sterg sarpele
                     if( i == 1 )
                        patrat(sarpe[i].x, sarpe[i].y, BLACK, marime), cap_beat(sarpe[i].x, sarpe[i].y, marime, BLACK);
                     else
                     patrat(sarpe[i].x, sarpe[i].y, BLACK, marime);}
                for(int i=1 ; i <= Lung ; i++)
                    sarpe[i].x-=marime;
                for(int i=1 ; i <= Lung ; i++){
                    if( i == 1 )
                        patrat(sarpe[i].x, sarpe[i].y, YELLOW, marime), cap_beat(sarpe[i].x, sarpe[i].y, marime, culoare_sarpe);
                    else
                        patrat( sarpe[i].x, sarpe[i].y, YELLOW, marime );}
                delay(dificultate);
                if( iesire_din_harta_beat(sarpe[1].x, sarpe[1].y) )
                        {game_over_beat();
                         return 0;}
                if( lovire_cerc_beat(sarpe[1].x, sarpe[1].y, Lung, xcerc, ycerc, raza, marime, sarpe) )
                        generare_cerc_beat(xcerc, ycerc, raza);
            } break;
            ///sageata-dreapta
            case 77: {
                for(int i=1 ; i <= Lung ; i++){  ///sterg sarpele
                     if( i == 1 )
                        patrat(sarpe[i].x, sarpe[i].y, BLACK, marime), cap_beat(sarpe[i].x, sarpe[i].y, marime, BLACK);
                     else
                        patrat(sarpe[i].x, sarpe[i].y, BLACK, marime);}
                for(int i=1 ; i <= Lung ; i++)
                    sarpe[i].x+=marime;
                for(int i=1 ; i <= Lung ; i++){
                    if( i == 1 )
                        patrat(sarpe[i].x, sarpe[i].y, YELLOW, marime), cap_beat(sarpe[i].x, sarpe[i].y, marime, culoare_sarpe);
                    else
                        patrat( sarpe[i].x, sarpe[i].y, YELLOW, marime );}
                delay(dificultate);
                if( iesire_din_harta_beat(sarpe[1].x, sarpe[1].y) )
                        {game_over_beat();
                         return 0;}
                if( lovire_cerc_beat(sarpe[1].x, sarpe[1].y, Lung, xcerc, ycerc, raza, marime, sarpe) )
                        generare_cerc_beat(xcerc, ycerc, raza);
            } break;
            ///tasta ESC
            case 27: terminat = true;
        }

        afisare_scor_beat(Lung-2);


    }
    closegraph();
    calc_scor( dificultate, Lung, scor );
    return 1;
}

void tabela_normal(int Lung, int dificultate, int ora_incepere)
{
    int scor, sec=0, minut=0, timp, old_color=getcolor();
    char s[10], m[10], scor_char[10];
    timp = ( clock() - ora_incepere )/CLOCKS_PER_SEC;

    timpCrt = time(NULL);

    ///facem timpul secunde
    calc_scor(dificultate, Lung, scor);
    timp = timpCrt - timpStart;
    minut = timp/60 ;
    sec=timp%60;

    sprintf(s, "%d", sec);
    sprintf(m, "%d", minut);
    sprintf(scor_char, "%d", scor);

    setcolor(DARKGRAY);
    setlinestyle(0, 0, 3);
    rectangle(525, 285, 790, 400 );

    settextstyle(BOLD_FONT, 0, 5);
    setcolor(CYAN);
    outtextxy(550, 350, "Scor:");
    outtextxy(533, 300, "Timp:");
    if( scor < 10 )
        setcolor(BLUE);
    else
    {
        if(scor < 100)
            setcolor(YELLOW);
        else
            setcolor(RED);
    }
    outtextxy(700, 350, scor_char);
    setcolor(GREEN);
    if( sec < 10 )
    {
        outtextxy(731, 300, "0");
        outtextxy(755, 300, s);
    }
    else
        outtextxy(733, 300, s);
    outtextxy(708, 300, ":");
    if( !minut )
        outtextxy(660, 300, "00");
    else
    {
        if( minut > 9 )
            outtextxy(683, 300, m);
        else
        {
            outtextxy(658, 300, "0");
            outtextxy(682, 300, m);
        }

    }



    settextstyle(BOLD_FONT, 0, 5);
    setlinestyle(0, 0, 1);
    setcolor(old_color);
}

int incepere_joc( int marime, int raza, int &scor, int &Lung, int &dificultate )
{
    Lung=2;
    dificultate=UI_dificultate();
    if ( dificultate == 60 )  ///daca alegem imposibil, sarpele devine mai gras
        marime=25;
    if( dificultate == 500 ) ///sarpe_beat
    {
        if(incepere_joc_beat(marime, raza, scor, Lung, dificultate))
            return 1;
        else
            return 0;
    }
    initwindow(1400, 700, "Snake");

    bool terminat = false, miscare_permisa=false;
    int tasta_old, tasta=72, xc=getmaxx()/2+200, yc=getmaxy()/2, directie, xcerc, ycerc, overflow;
    long long ora_incepere=clock();

    timpStart = time(NULL);

    ///desenez un cerc pt prima oara
    generare_cerc(xcerc, ycerc, raza);
    ///desenez sarpili pt prima data
    for( int i = 1, ysec=yc+(Lung-1)*marime ; i <= Lung ; i++)
    {
        patrat( xc, ysec, YELLOW, marime );
        ysec-=marime;
    }

    while (! terminat)
    {


        if (  kbhit() )
        {
            miscare_permisa=false;
            tasta_old = tasta;
            while( !miscare_permisa && kbhit() ) ///cat timp miscarile date de utilizator nu au sens, se citesc toate pana nu mai sunt
            {
                ///tasta_old = tasta;
                tasta = readKey();
                if( !(tasta == 72 || tasta == 77 || tasta == 75 || tasta == 80 || tasta == 27) )
                    tasta = tasta_old;
                if( (tasta_old == 72 && tasta == 80) || ( tasta_old == 80 && tasta == 72 ) || ( tasta_old == 75 && tasta == 77 ) || ( tasta_old == 77 && tasta == 75 ) )
                {
                    miscare_permisa = FALSE;  ///verific ca sarpele sa nu dea cu spatele
                    tasta = tasta_old;
                }
                else
                {
                    miscare_permisa = TRUE;
                }
            }
            if ( miscare_permisa )  ///daca sarpele nu da cu spatele, face viraju
            {
                ///avem mai multe cazuri ...
                if ( tasta_old == 72  ) ///daca se misca in sus ... poate vira la stanga/dreapta
                {
                    if ( tasta == 75 ) ///viraj la stanga
                    {
                        yc+=marime;
                        ///patrat( xc, yc+(Lung-0)*marime, BLACK, marime );
                        ///patrat ( xc, yc+(Lung-1)*marime, YELLOW, marime );
                        for ( int i = 1, xsec=xc, ysec=yc ; i <= Lung ; i++ )
                        {
                            patrat( xsec, ysec + (Lung+1-i)*marime, BLACK, marime );
                            patrat ( xsec, ysec + (Lung-i)*marime, YELLOW, marime );
                            patrat( xsec - marime*i, ysec, YELLOW, marime );
                            while ( kbhit() )
                                overflow = readKey();
                            delay(dificultate);

                            if( iesire_din_harta(xsec-marime*i, ysec) )    ///de modificat la fiecare viraj xc cu xsec-marime*i
                                {game_over();
                                return 0;}
                            if( lovire_cerc(xsec-marime*i, yc, Lung, xcerc, ycerc, raza, marime) )
                                generare_cerc(xcerc, ycerc, raza);
                            tabela_normal(Lung, dificultate, ora_incepere);
                        }
                        patrat( xc, yc, BLACK, marime );
                        patrat( xc-marime, yc, YELLOW, marime);
                        xc-=marime*Lung;

                    }
                    if( tasta == 77 ) ///viraj la dreapta
                    {
                        yc+=marime;
                        for ( int i = 1, xsec=xc, ysec=yc ; i <= Lung ; i++ )
                        {
                            patrat( xsec, ysec + (Lung+1-i)*marime, BLACK, marime );
                            patrat ( xsec, ysec + (Lung-i)*marime, YELLOW, marime );
                            patrat( xsec + marime*i, ysec, YELLOW, marime );
                            while ( kbhit() )
                                overflow = readKey();
                            delay(dificultate);

                            if( iesire_din_harta(xsec+marime*i, ysec) )
                                {game_over();
                                 return 0;}
                            if( lovire_cerc(xsec+marime*i, yc, Lung, xcerc, ycerc, raza, marime) )
                                generare_cerc(xcerc, ycerc, raza);
                            tabela_normal(Lung, dificultate, ora_incepere);
                        }
                        patrat( xc, yc, BLACK, marime );
                        patrat( xc+marime, yc, YELLOW, marime);
                        xc+=marime*Lung;

                    }
                }
                if( tasta_old == 80 ) ///daca sarpele se misca in jos ... poate vira la stanga/dreapta
                {
                    if( tasta == 75 ) ///viraj la stanga
                    {
                        yc-=marime;
                        for ( int i = 1, xsec=xc, ysec=yc ; i <= Lung ; i++ )
                        {
                            patrat( xsec, ysec - (Lung+1-i)*marime, BLACK, marime );
                            patrat ( xsec, ysec - (Lung-i)*marime, YELLOW, marime );
                            patrat( xsec - marime*i, ysec, YELLOW, marime );
                            while ( kbhit() )
                                overflow = readKey();
                            delay(dificultate);

                            if( iesire_din_harta(xsec-marime*i, ysec) )
                                {game_over();
                                 return 0;}
                            if( lovire_cerc(xsec-marime*i, yc, Lung, xcerc, ycerc, raza, marime) )
                                generare_cerc(xcerc, ycerc, raza);
                            tabela_normal(Lung, dificultate, ora_incepere);
                        }
                        patrat( xc, yc, BLACK, marime );
                        patrat( xc-marime, yc, YELLOW, marime);
                        xc-=marime*Lung;
                    }
                    if( tasta == 77 ) ///viraj la dreapta
                    {
                        yc-=marime;
                        for ( int i = 1, xsec=xc, ysec=yc ; i <= Lung ; i++ )
                        {
                            patrat( xsec, ysec - (Lung+1-i)*marime, BLACK, marime );
                            patrat ( xsec, ysec - (Lung-i)*marime, YELLOW, marime );
                            patrat( xsec + marime*i, ysec, YELLOW, marime );
                            while ( kbhit() )
                                overflow = readKey();
                            delay(dificultate);

                            if( iesire_din_harta(xsec+marime*i, ysec) )
                                {game_over();
                                 return 0;}
                            if( lovire_cerc(xsec+marime*i, yc, Lung, xcerc, ycerc, raza, marime) )
                                generare_cerc(xcerc, ycerc, raza);
                            tabela_normal(Lung, dificultate, ora_incepere);
                        }
                        patrat( xc, yc, BLACK, marime );
                        patrat( xc+marime, yc, YELLOW, marime);
                        xc+=marime*Lung;
                    }
                }
                if( tasta_old == 75 ) ///sarpele se misca spre stanga... poate vira in sus/jos
                {
                    if( tasta == 72 )  ///viraj in sus
                    {
                        xc+=marime;
                        for( int i = 1, xsec=xc, ysec=yc ; i <= Lung ; i++ )
                        {
                            patrat( xsec+(Lung-i+1)*marime, ysec, BLACK, marime );
                            patrat( xsec+(Lung-i)*marime, ysec, YELLOW, marime );
                            patrat( xsec, ysec-i*marime, YELLOW, marime );
                            while ( kbhit() )
                                overflow = readKey();
                            delay(dificultate);

                            if( iesire_din_harta(xsec, ysec-i*marime) )
                                {game_over();
                                return 0;}
                            if( lovire_cerc(xc, ysec-i*marime, Lung, xcerc, ycerc, raza, marime) )
                                generare_cerc(xcerc, ycerc, raza);
                            tabela_normal(Lung, dificultate, ora_incepere);
                        }
                        patrat( xc, yc, BLACK, marime );
                        patrat( xc, yc-marime, YELLOW, marime);
                        yc-=marime*Lung;

                    }
                    if( tasta == 80 ) ///viraj in jos
                    {
                        xc+=marime;
                        for( int i = 1, xsec=xc, ysec=yc ; i <= Lung ; i++ )
                        {
                            patrat( xsec+(Lung-i+1)*marime, ysec, BLACK, marime );
                            patrat( xsec+(Lung-i)*marime, ysec, YELLOW, marime );
                            patrat( xsec, ysec+i*marime, YELLOW, marime );
                            while ( kbhit() )
                                overflow = readKey();
                            delay(dificultate);

                            if( iesire_din_harta(xsec, ysec+i*marime) )
                                {game_over();
                                 return 0;}
                            if( lovire_cerc(xc, ysec+i*marime, Lung, xcerc, ycerc, raza, marime) )
                                generare_cerc(xcerc, ycerc, raza);
                            tabela_normal(Lung, dificultate, ora_incepere);
                        }
                        patrat( xc, yc, BLACK, marime );
                        patrat( xc, yc+marime, YELLOW, marime);
                        yc+=marime*Lung;
                    }
                }
                if( tasta_old == 77 ) ///sarpele se misca spre dreapta ... poate vira in sus/jos
                {
                    if( tasta == 72 ) ///viraj in sus
                    {
                        xc-=marime;
                        for( int i = 1, xsec=xc, ysec=yc ; i <= Lung ; i++ )
                        {
                            patrat( xsec-(Lung-i+1)*marime, ysec, BLACK, marime );
                            patrat( xsec-(Lung-i)*marime, ysec, YELLOW, marime );
                            patrat( xsec, ysec-i*marime, YELLOW, marime );
                            while ( kbhit() )
                                overflow = readKey();
                            delay(dificultate);

                            if( iesire_din_harta(xsec, ysec-i*marime) )
                                {game_over();
                                 return 0;}
                            if( lovire_cerc(xc, ysec-i*marime, Lung, xcerc, ycerc, raza, marime) )
                                generare_cerc(xcerc, ycerc, raza);
                            tabela_normal(Lung, dificultate, ora_incepere);
                        }
                        patrat( xc, yc, BLACK, marime );
                        patrat( xc, yc-marime, YELLOW, marime);
                        yc-=marime*Lung;
                    }
                    if( tasta == 80 ) ///viraj in jos
                    {
                        xc-=marime;
                        for( int i = 1, xsec=xc, ysec=yc ; i <= Lung ; i++ )
                        {
                            patrat( xsec-(Lung-i+1)*marime, ysec, BLACK, marime );
                            patrat( xsec-(Lung-i)*marime, ysec, YELLOW, marime );
                            patrat( xsec, ysec+i*marime, YELLOW, marime );
                            while ( kbhit() )
                                overflow = readKey();
                            delay(dificultate);

                            if( iesire_din_harta(xsec, ysec+i*marime) )
                                {game_over();
                                 return 0;}
                            if( lovire_cerc(xc, ysec+i*marime, Lung, xcerc, ycerc, raza, marime) )
                                generare_cerc(xcerc, ycerc, raza);
                            tabela_normal(Lung, dificultate, ora_incepere);
                        }
                        patrat( xc, yc, BLACK, marime );
                        patrat( xc, yc+marime, YELLOW, marime);
                        yc+=marime*Lung;
                    }
                }
            }


        }


        switch(tasta)
        {
            case 119: break;

            ///sageata-sus
            case 72: {


                        patrat( xc, yc, YELLOW, marime );



                    delay(dificultate);

                    patrat( xc, yc+(Lung-1)*marime, BLACK, marime );
                    patrat( xc, yc+(Lung - 2)*marime, YELLOW, marime );
                    yc-=marime;
                    if( iesire_din_harta(xc, yc) )
                        {game_over();
                         return 0;}
                    if( lovire_cerc(xc, yc, Lung, xcerc, ycerc, raza, marime) )
                        generare_cerc(xcerc, ycerc, raza);
                    tabela_normal(Lung, dificultate, ora_incepere);


            } break;

            ///sageata-jos
            case 80: {


                        patrat( xc, yc, YELLOW, marime );



                    delay(dificultate);

                    patrat( xc, yc-(Lung-1)*marime, BLACK, marime );
                    patrat( xc, yc-(Lung-2)*marime, YELLOW, marime);
                    yc+=marime;
                    if( iesire_din_harta(xc, yc) )
                        {game_over();
                         return 0;}
                    if( lovire_cerc(xc, yc, Lung, xcerc, ycerc, raza, marime) )
                        generare_cerc(xcerc, ycerc, raza);
                    tabela_normal(Lung, dificultate, ora_incepere);




            } break;

            ///sageata-stanga
            case 75: {


                    patrat(xc, yc, YELLOW, marime);


                delay(dificultate);

                patrat( xc+(Lung-1)*marime, yc, BLACK, marime );
                patrat( xc+(Lung-2)*marime, yc, YELLOW, marime );
                xc-=marime;
                if( iesire_din_harta(xc, yc) )
                        {game_over();
                         return 0;}
                if( lovire_cerc(xc, yc, Lung, xcerc, ycerc, raza, marime) )
                    generare_cerc(xcerc, ycerc, raza);
                tabela_normal(Lung, dificultate, ora_incepere);
            } break;

            ///sageata-dreapta
            case 77: {


                    patrat(xc, yc, YELLOW, marime);


                delay(dificultate);
                patrat( xc-(Lung-1)*marime, yc, BLACK, marime );
                patrat( xc-(Lung-2)*marime, yc, YELLOW, marime );
                xc+=marime;
                if( iesire_din_harta(xc, yc) )
                        {game_over();
                         return 0;}
                if( lovire_cerc(xc, yc, Lung, xcerc, ycerc, raza, marime) )
                        generare_cerc(xcerc, ycerc, raza);
                    tabela_normal(Lung, dificultate, ora_incepere);
            } break;

            ///tasta ESC
            case 27: terminat = true;
        }

    }

    closegraph();
    calc_scor( dificultate, Lung, scor );
    return 1;
}

int main()
{
    int scor, marime=10, raza=20, optiuni=1, scor_max=0, scor_brut, dificultate;
    bool inchidere=false;
    loading();

    if (incepere_joc(marime, raza, scor, scor_brut, dificultate))
    {
        cout << "Felicitari!" << '\n' << "Te-ai oprit inainte sa pierzi, deci scorul tau primeste un bonus" << '\n';
        scor += scor/10;
        cout << "Scorul este: " << scor << '\n';
    }
    else
    {
        cout << "Trist!" << '\n' << "Deoarece ai pierdut scorul tau scade!" << '\n' ;
        calc_scor( dificultate, scor_brut, scor );
        scor -= scor/10;
        cout << "Scorul este: " << scor << '\n';
    }

    scor_max = scor;
    cout << "Meniu" << '\n';
    cout << "1. Joaca din nou" << '\n';
    cout << "2. Iesire din joc" << '\n';
    cout << "3. Afiseaza scorul de data trecuta" << '\n';
    cout << "4. Afiseaza scorul maxim" << '\n';
    cout << "5. Reafiseaza meniul" << '\n';



    while( !inchidere )
    {
        cin >> optiuni;
        switch(optiuni)
        {
            case 1:{
                 if (incepere_joc(marime, raza, scor, scor_brut, dificultate))
                {
                    cout << "Felicitari!" << '\n' << "Te-ai oprit inainte sa pierzi, deci scorul tau primeste un bonus" << '\n';
                    scor += scor/10;
                    cout << "Scorul este: " << scor << '\n';
                }
                else
                {
                    cout << "Trist!" << '\n' << "Deoarece ai pierdut scorul tau scade!" << '\n' ;
                    calc_scor( dificultate, scor_brut, scor );
                    scor -= scor/10;
                    cout << "Scorul este: " << scor << '\n';
                }
                scor_max = max( scor, scor_max );
            } break;

            case 2:{
                inchidere = true;
            } break;

            case 3:{
                cout << "Scorul de data trecuta este " << scor << '\n';
            } break;

            case 4:{
                cout << "Scorul maxim pe care l-ai obtinut este " << scor_max << '\n';
            } break;

            case 5:{
                 cout << "Meniu" << '\n';
                cout << "1. Joaca din nou" << '\n';
                cout << "2. Iesire din joc" << '\n';
                cout << "3. Afiseaza scorul de data trecuta" << '\n';
                cout << "4. Afiseaza scorul maxim" << '\n';
                cout << "5. Reafiseaza meniul" << '\n';
            } break;
        }
    }
    return 0;
}

