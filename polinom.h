#include <iostream>
#include <cstring>
#include <cmath>
#include <cctype>
#include <graphics.h>
#include <fstream>

using namespace std;

int char_to_int(char* chars);

int putere10(int x, int y)   /// inmulteste numarul x de y ori
{
    for (int i = 0; i < y; i++)
    {
        x *= 10;
    }
    return x;
}

double putere(double x, int Putere)    /// calculam puterea unui numar
{
    if (Putere != 0)
        return x * putere(x, Putere - 1);
    else return 1.0;
}

double cmmdc(double m, double n)   /// facem cmmdc a doua numere
{
    while(n != m)
        if(n > m)
            n -= m;
        else
            m -= n;

    return n;
}

int char_to_int(char* chars)    /// converteste un sir de caractere in numar (si de ordine mai mari)
{
    int sum = 0;
    for (int x = 0; x < strlen(chars); x++)
    {
        int n = chars[strlen(chars) - (x + 1)] - '0';
        sum += putere10(n, x);
    }
    return sum;
}

class polinom
{
private:
    char *exp= new char[201];  /// sirul de caractere ce reprezinta polinomul
    double coeficient[101], coeficient_derivare[101];   /// coeficientii polinomului
public:
    polinom(); /// constructor in care facem coeficientii 0

    void set_exp( char *s ) { strcpy(exp, s); exp_to_v();} /// setam polinomul cu o anumita expresie

    void exp_to_v(); /// convertire sir caractere in functie

    friend ostream & operator<<( ostream&, polinom); /// afisarea polinomului

    friend istream & operator>>(istream&, polinom&); /// citirea polinomului

    friend bool operator&&( polinom, polinom); /// daca 2 functii au aceeasi derivata

    int get_gradPolinom();  /// calculam gradul polinomului

    bool grad2() {return get_gradPolinom() == 2; } ///verificam daca avem ec de grad2

    bool bipatrata(); /// verificam daca avem ecuatie de tipul a * x^4 + b * x ^ 2 + c

    void monotonie(); ///crescatoare / descrescatoare

    void rezolv(double, double v[], int&); /// rezolvam ecuatie de tipul f(x) = c unde c este o valoare aleatorie

    void rezolv_derivata(double, double v[], int&); /// rezolvam ecuatie de tipul f'(x) = c, unde c este o valoare aleatorie

    void grafic(int); /// Face graficul polinomului

    void derivare(); /// facem derivata polinomului

    void simplificare_polinom(); /// aici facem cmmdc al coeficientilor diferit de 0 si impartim prin cmmdc

    double f_de_x(double ); /// calculam f(x), unde x valoare aleatorie

    double f_de_x_derivat(double ); /// calculam f'(x), unde x valoare aleatorie
};

polinom :: polinom()
{
    for(int i = 0 ; i <= 100 ; i++)
        coeficient[i] = coeficient_derivare[i] = 0;
}

void polinom :: exp_to_v()
{
    for( int i = 0 ; i < strlen( exp ) ; i++ )
    {
        int coef, put;
        if( exp[i] == 'x' )     ///daca gasim x initiem conversia
        {
            if( i == 0 ) ///daca e primul caracter nu are coeficient
                coef = 1;
            else
            {
                char *numar = new char[10];
                int nrCif = 0;
                for( int j = i - 1 ; j >= 0 && exp[j] != ' ' ; j-- ) ///Aflam numarul de cifre al coeficientului
                    nrCif++;
                if( nrCif != 0 )  ///Daca are macar o cifra aplicam conversia
                {
                    for( int j = 0 ; j < nrCif ; j++ )
                        numar[j] = exp[i + j - nrCif];
                    numar[nrCif] = '\0';
                    coef = char_to_int( numar );
                }
                else  ///Daca nu are cifre verificam semnul, daca se poate
                {
                    if( i - 2 >= 0 )
                    {
                        if( exp[i - 2] == '-' )
                            coef = -1;
                        else
                            coef = 1;
                    }
                    else
                        coef = 1;
                }
            }

            if( i + 2 < strlen( exp ) )  ///Aflam puterea coeficientului, daca are
            {
                if( exp[i + 1] == '^' )  ///Daca are ridicare la putere, se poate
                {
                    char *putere = new char[10];
                    int nrCif2 = 0;
                    for( int j = i + 2 ; j < strlen( exp ) && exp[j] != ' ' ; j++ ) ///Aflam numarul de cifre al puterii
                        nrCif2++;
                    for( int j = 0 ; j < nrCif2 ; j++ ) ///Aplicam conversia
                        putere[j] = exp[ i + 2 + j ];
                    putere[nrCif2] = '\0';
                    put = char_to_int( putere );
                }
                else
                    put = 1;
            }
            else ///Daca nu, atunci e la puterea 1
                put = 1;

            coeficient[put] = coef;
        }
    }

    if( exp[strlen(exp) - 1] != '^' && exp[strlen(exp) - 1] != 'x' && exp[strlen(exp) - 2] == ' ')  ///atunci avem si x la puterea 0
    {
        char *factor_liber = new char[2];
        factor_liber[0] = exp[strlen(exp) - 1];
        factor_liber[1] = '\0';
        coeficient[0] = char_to_int( factor_liber );
    }
    if( strlen(exp) == 1 && exp[0] != 'x' )
        coeficient[0] = char_to_int( exp );
}

ostream& operator << (ostream& f, polinom a)
{
    char *p = new char[201];
    bool primul_termen = true;
    for( int i = a.get_gradPolinom(); i >= 2 ; i-- )
    {
        if( i && abs(a.coeficient[i]) )
            if( a.coeficient[i] > 0)
            {
                if (a.coeficient[i] == 1)
                {
                    if( primul_termen )
                        f << "x^" << i << " ", primul_termen = false;
                    else
                        f << "+ " << "x^" << i << " ";
                }
                else
                {
                    if( primul_termen )
                        f << a.coeficient[i] << "*x^" << i << " ", primul_termen = false;
                    else
                        f << "+ " << a.coeficient[i] << "*x^" << i << " ";
                }
            }
            else
            {
                if (a.coeficient[i] == -1)
                {
                    if( primul_termen )
                        f << "- " << "x^" << i << " ", primul_termen = false;
                    else f << "x^" << i << " ";
                }
                else
                {
                    if( primul_termen )
                        f << abs( a.coeficient[i] ) << "*x^" << i << " ", primul_termen = false;
                    else f << "- " << abs( a.coeficient[i] ) << "*x^" << i << " ";
                }
            }
    }

    if (abs(a.coeficient[1]) > 0)
    {
        if( a.coeficient[1] > 0)
        {
            if (a.coeficient[1] == 1)
            {
                if( primul_termen )
                    f << "x" << " ", primul_termen = false;
                else f << "+ " << "x" << " ";
            }
            else
            {
                if( primul_termen )
                    f << a.coeficient[1] << "*x" << " ", primul_termen = false;
                else f << "+ " << a.coeficient[1] << "*x" << " ";
            }
        }
        else
        {
            if (a.coeficient[1] == -1)
            {
                if( primul_termen )
                    f << "x" << " ", primul_termen = false;
                else f << "- " << "x" << " ";
            }
            else
            {
                if( primul_termen )
                    f << abs( a.coeficient[1] ) << "*x" << " ", primul_termen = false;
                else f << "- " << abs( a.coeficient[1] ) << "*x" << " ";
            }
        }
    }

    if (abs(a.coeficient[0]) > 0)
    {
        if (a.coeficient[0] > 0)
        {
            if( primul_termen )
                f << a.coeficient[0];
            else f << "+ " << a.coeficient[0];
        }
        else f << "- " << abs( a.coeficient[0] );
    }

    f << '\n';

    return f;
}

istream& operator >> (istream& f, polinom& a)
{
    int x, i, alegere;
    cout << "Metoda  de citire... 1 pentru sir... 2 pentru coeficienti" << '\n';
    f >> alegere;
    if( alegere == 1)    /// pentru sir de caractere
    {
        cout << "Dati sirul in functie de regulile din manual.\n";
        cin.get();
        cin.get( a.exp, 50 ); ///Folosim asta ca asa merge
        cin.get();
        a.exp_to_v();
        cout << '\n';
    }
    else
    {
        if ( alegere == 2 )    /// pentru coeficienti
        {
            cout << "Introdu cel mai mare exponent nenul: ";
            f >> i;
            cout << "Introdu pe rand fiecare coeficient de la x^" << i << " la 0: ";
            for( i ; i >= 0 ; i-- )
                f >> a.coeficient[i];
            cout << '\n';
        }
        else
        {
            cout << "Nu ai introdus 1 sau 2.\n";
        }
    }
    return f;
}

bool operator &&(polinom a, polinom b)
{
    for(int i = 100 ; i ; --i )
        if(a.coeficient_derivare[i] != b.coeficient_derivare[i])
            return false;
    return true;
}

int polinom :: get_gradPolinom()
{
    for (int i = 100; i >= 1; --i)
        if (abs(coeficient[i]) > 0)
            return i;
}

bool polinom :: bipatrata()
{
    if( get_gradPolinom() == 4 )
    {
        for(int i = 1; i <= 4; ++i)
            if( (i != 4 || i != 2 ) && abs(coeficient[i]) )
                return false;
        return true;
    }
    return false;
}

void polinom :: monotonie()
{
    derivare();
    if(get_gradPolinom() != 1)
    {
        double sol[101];
        int nrSol = 0;

        rezolv(0, sol, nrSol);

        if (nrSol != 0)
        {
            cout << "Pentru intervalul [-infinit, " << sol[1] << "] polinomul este " <<
                 (f_de_x_derivat(sol[1] - 0.1) - f_de_x_derivat(sol[1] - 0.2) < 0 ? "crescatoare" : "descrescatoare") << '\n';

            for (int i = 1; i < nrSol; ++i)
                cout << "Pentru intervalul [" << sol[i] << ", " << sol[i + 1] << "] polinomul este " <<
                     ((f_de_x_derivat(sol[i] + 0.1) - f_de_x_derivat(sol[i] + 0.2) < 0) ? "crescatoare" : "descrescatoare") << '\n';

            cout << "Pentru intervalul [" << sol[nrSol] << ", +infinit] polinomul este " <<
                 ((f_de_x_derivat(sol[nrSol] + 0.1) - f_de_x_derivat(sol[nrSol] + 0.2) < 0) ? "crescatoare" : "descrescatoare") << '\n';
        }
        else cout << "Pentru multimea numerelor reale, polinomul are monotonie "
                      << (((f_de_x_derivat(1.0) - f_de_x_derivat(2.0)) < 0) ? "crescatoare" : "descrescatoare") << '\n';
    }
    else cout << "Pentru multimea numerelor reale, polinomul are monotonie "
                  << ((coeficient_derivare[0] > 0) ? "crescatoare" : "descrescatoare") << '\n';
}

void polinom :: rezolv(double valoare, double solutie[], int &nrSolutii)
{
    coeficient[get_gradPolinom()] -= valoare; /// scadem valoarea

    nrSolutii = 0;

    if (get_gradPolinom() - 1 == 0)
    {
        coeficient[get_gradPolinom()] += valoare;
        return;
    }

    for (double i = -100000; i <= 100000; i += 1)
    {
        if (abs(f_de_x(i / 100)) <= 0.001)
            solutie[++nrSolutii] = i / 100;
    }

    coeficient[get_gradPolinom()] += valoare; /// adunam valoarea
}

void polinom :: rezolv_derivata(double valoare, double solutie[], int &nrSolutii)
{
    derivare();
    coeficient_derivare[get_gradPolinom()] -= valoare; /// scadem valoarea

    nrSolutii = 0;

    if (get_gradPolinom() - 1 == 0)
    {
        coeficient_derivare[get_gradPolinom()] += valoare;
        return;
    }

    for (double i = -100000; i <= 100000; i += 1)
    {
        if (abs(f_de_x_derivat(i / 100)) <= 0.001)
            solutie[++nrSolutii] = i / 100;
    }

    coeficient_derivare[get_gradPolinom()] += valoare; /// adunam valoarea
}

void polinom :: grafic(int optiune)
{
    initwindow(getmaxwidth(), getmaxheight(), "Fara nume ca nu avem bani de el");

    line(0, getmaxheight() / 2, getmaxwidth(), getmaxheight() / 2); /// axa Ox
    line(getmaxwidth() / 2, 0, getmaxwidth() / 2, getmaxheight()); /// axa Oy
    outtextxy(getmaxwidth() - 25, getmaxheight() / 2 + 15, "Ox");
    outtextxy(getmaxwidth() / 2 - 25, 15, "Oy");

    /// sagetile pentru axa Oy

    line(getmaxwidth() / 2 - 10, 10, getmaxwidth() / 2, 0);
    line(getmaxwidth() / 2 + 10, 10, getmaxwidth() / 2, 0);

    /// sagetile pentru axa Ox

    line(getmaxwidth(), getmaxheight() / 2, getmaxwidth() - 10, getmaxheight() / 2 - 10);
    line(getmaxwidth(), getmaxheight() / 2, getmaxwidth() - 10, getmaxheight() / 2 + 10);

    double cnt = 0.1;
    int factor_de_impartire = get_gradPolinom() * 50; /// ca sa obtinem un grafic mai clar

    if (get_gradPolinom() == 1)
        factor_de_impartire = 1;

    setcolor(RED);  /// graficul va avea culoarea albastra
    setlinestyle(1, 0, 4);
    double redimensionare_segment = 100;  /// redimensionez axa Ox

    if (optiune == 1) /// daca vrem graficul polinomului
    {
        for (double i = -(getmaxwidth() / redimensionare_segment) * 1.0 + cnt; i <= getmaxwidth() / redimensionare_segment; i += cnt)
        {
            /// desenam graficul din puncte apropiate (cnt)
            line(i * redimensionare_segment + getmaxwidth() / 2,
                 -f_de_x(i) * redimensionare_segment  + getmaxheight() / 2,
                 (i - cnt) * redimensionare_segment + getmaxwidth() / 2,
                 -f_de_x(i - cnt) * redimensionare_segment + getmaxheight() / 2);
        }
    }
    else if (optiune == 2)   /// daca vrem graficul derivatei polinomului
        {
            for (double i = -(getmaxwidth() / redimensionare_segment) * 1.0 + cnt; i <= getmaxwidth() / redimensionare_segment; i += cnt)
            {
                /// desenam graficul din puncte apropiate (cnt)
                line(i * redimensionare_segment + getmaxwidth() / 2,
                     -f_de_x_derivat(i) * redimensionare_segment  + getmaxheight() / 2,
                     (i - cnt) * redimensionare_segment + getmaxwidth() / 2,
                     -f_de_x_derivat(i - cnt) * redimensionare_segment + getmaxheight() / 2);
            }
        }
    else cout << "Nu ati introdus o optiune corecta!\n";

    setcolor(WHITE);
    setlinestyle(1, 0, 1);

    int x, y; ///Se asteapta click stanga pentru a inchide graficul
    do
    {
        getmouseclick(WM_LBUTTONDOWN, x, y);
    }
    while( x == -1 && y == -1 );
///getch(); /// curata graficul anterior
    closegraph();  /// inchide fereastra
}

void polinom :: derivare()
{
    coeficient_derivare[get_gradPolinom()] = 0;  /// dispare x^get_gradPolinom() si de aceea e 0

    for (int i = get_gradPolinom() - 1; i >= 0; --i)
    {
        if (abs(coeficient[i + 1]) > 0)
            coeficient_derivare[i] = coeficient[i + 1] * (i + 1);  /// aici se face derivarea practic
    }
}

void polinom :: simplificare_polinom()
{
    double x = coeficient[get_gradPolinom()];

    for (int i = get_gradPolinom() - 1; i >= 0; --i)
    {
        if (abs(coeficient[i]) > 0)
            x = cmmdc(abs(x), abs(coeficient[i]));
    }

    for (int i = 0; i <= get_gradPolinom(); ++i)
        coeficient[i] /= abs(x);
}

double polinom :: f_de_x(double x)
{
    double sol = 0;
    sol += coeficient[0];
    for( int i = 1 ; i <= get_gradPolinom() ; i++ )
        sol += coeficient[i] * putere(x, i);
    return sol;
}

double polinom :: f_de_x_derivat(double x)
{
    double valoare = 0;

    for (int i = 0; i < get_gradPolinom(); ++i)
        valoare += coeficient_derivare[i] * putere(x, i);

    return valoare;
}


