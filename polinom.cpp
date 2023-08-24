#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <cctype>
#include <graphics.h>


using namespace std;

int char_to_int(char* chars);

class polinom{
private:
    char *exp= new char[201];  /// sirul de caractere ce reprezinta polinomul
    double coeficient[101], coeficient_derivare[101];   /// coeficientii polinomului

    int putere10(int x, int y) { /// inmulteste numarul x de y ori
        for (int i = 0; i < y; i++)
        {
            x *= 10;
        }
        return x;
    }

    double putere(double x, int Putere) {  /// calculam puterea unui numar
        if (Putere != 0)
            return x * putere(x, Putere - 1);
        else return 1.0;
    }

    double cmmdc(double m, double n) { /// facem cmmdc a doua numere
        while(n != m)
            if(n > m)
                n -= m;
            else
                m -= n;

        return n;
    }

    int char_to_int(char* chars) {  /// converteste un sir de caractere in numar (si de ordine mai mari)
        int sum = 0;
        for (int x = 0; x < strlen(chars); x++)
        {
            int n = chars[strlen(chars) - (x + 1)] - '0';
            sum += putere10(n, x);
        }
        return sum;
    }

public:
    polinom() {  /// constructor in care facem coeficientii 0
        for(int i = 0 ; i <= 100 ; i++) coeficient[i] = 0, coeficient_derivare[i] = 0;
    }

    void set_exp( char *s ){  /// setam polinomul cu o anumita expresie
        strcpy(exp, s);
        exp_to_v();
    }

    void exp_to_v() { /// convertire sir caractere in functie
        for( int i = 0 ; i < strlen( exp ) ; i++ ){
            int coef, put;
            if( exp[i] == 'x' ){    ///daca gasim x initiem conversia
                if( i == 0 ) ///daca e primul caracter nu are coeficient
                    coef = 1;
                else{
                    char *numar = new char[10];
                    int nrCif = 0;
                    for( int j = i - 1 ; j >= 0 && exp[j] != ' ' ; j-- ) ///Aflam numarul de cifre al coeficientului
                        nrCif++;
                    if( nrCif != 0 ){ ///Daca are macar o cifra aplicam conversia
                        for( int j = 0 ; j < nrCif ; j++ )
                            numar[j] = exp[i + j - nrCif];
                        numar[nrCif] = '\0';
                        coef = char_to_int( numar );
                    }
                    else{ ///Daca nu are cifre verificam semnul, daca se poate
                        if( i - 2 >= 0 ){
                            if( exp[i - 2] == '-' )
                                coef = -1;
                            else
                                coef = 1;
                        }
                        else
                            coef = 1;
                    }
                }

                if( i + 2 < strlen( exp ) ){ ///Aflam puterea coeficientului, daca are
                    if( exp[i + 1] == '^' ){ ///Daca are ridicare la putere, se poate
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

       if( exp[strlen(exp) - 1] != '^' && exp[strlen(exp) - 1] != 'x' && exp[strlen(exp) - 2] == ' '){ ///atunci avem si x la puterea 0
            char *factor_liber = new char[2];
            factor_liber[0] = exp[strlen(exp) - 1];
            factor_liber[1] = '\0';
            coeficient[0] = char_to_int( factor_liber );
       }
       if( strlen(exp) == 1 && exp[0] != 'x' )
            coeficient[0] = char_to_int( exp );
    }

    friend ostream & operator<<( ostream& f, polinom a){  /// afisarea polinomului
        char *p = new char[201];
        bool primul_termen = true;
        for( int i = a.get_gradPolinom(); i >= 2 ; i-- ){
            if( i && abs(a.coeficient[i]) )
                if( a.coeficient[i] > 0) {
                    if (a.coeficient[i] == 1){
                        if( primul_termen )
                            f << "x^" << i << " ", primul_termen = false;
                        else
                            f << "+ " << "x^" << i << " ";
                    }
                    else{
                        if( primul_termen )
                            f << a.coeficient[i] << "*x^" << i << " ", primul_termen = false;
                        else
                            f << "+ " << a.coeficient[i] << "*x^" << i << " ";
                    }
                }
                else{
                    if (a.coeficient[i] == -1){
                        if( primul_termen )
                            f << "- " << "x^" << i << " ", primul_termen = false;
                        else f << "x^" << i << " ";
                    }
                    else{
                        if( primul_termen )
                            f << abs( a.coeficient[i] ) << "*x^" << i << " ", primul_termen = false;
                        else f << "- " << abs( a.coeficient[i] ) << "*x^" << i << " ";
                    }
                }
        }

        if (abs(a.coeficient[1]) > 0) {
            if( a.coeficient[1] > 0) {
                if (a.coeficient[1] == 1){
                    if( primul_termen )
                        f << "x" << " ", primul_termen = false;
                    else f << "+ " << "x" << " ";
                }
                else{
                    if( primul_termen )
                        f << a.coeficient[1] << "*x" << " ", primul_termen = false;
                    else f << "+ " << a.coeficient[1] << "*x" << " ";
                }
            }
            else{
                if (a.coeficient[1] == -1){
                    if( primul_termen )
                        f << "x" << " ", primul_termen = false;
                    else f << "- " << "x" << " ";
                }
                else{
                    if( primul_termen )
                        f << abs( a.coeficient[1] ) << "*x" << " ", primul_termen = false;
                    else f << "- " << abs( a.coeficient[1] ) << "*x" << " ";
                }
            }
        }

        if (abs(a.coeficient[0]) > 0) {
            if (a.coeficient[0] > 0){
                if( primul_termen )
                    f << a.coeficient[0];
                else f << "+ " << a.coeficient[0];
            }
            else f << "- " << abs( a.coeficient[0] );
        }

        f << '\n';

        return f;

    }

    friend istream & operator>>( istream& f, polinom& a){  /// citirea polinomului
        int x, i;
        cout << "Metoda  de citire... 1 pentru sir... 2 pentru coeficienti" << '\n';
        gets( a.exp );
        if( a.exp[0] == '1' ){   /// pentru sir de caractere
            cout << "Dati sirul in functie de regulile din manual\n";
            gets( a.exp ); ///Folosim asta ca asa merge
            a.exp_to_v();
        }
        else{
            if ( a.exp[0] == '2' ) {  /// pentru coeficienti
                cout << "Introdu cel mai mare exponent nenul..." << '\n' ;
                f >> i;
                cout << "Introdu pe rand fiecare coeficient de la x^" << i << " la 0" << '\n';
                for( i ; i >= 0 ; i-- )
                    f >> a.coeficient[i];
            }
            else {
                cout << "Nu ai introdus 1 sau 2\n";
            }
        }
        return f;
    }

    friend bool operator&&( polinom a, polinom b ){ /// daca 2 functii au aceeasi derivata
        for(int i = 100 ; i ; --i )
            if(a.coeficient_derivare[i] != b.coeficient_derivare[i])
                return false;
        return true;
    }

    int get_gradPolinom() {  /// calculam gradul polinomului
        for (int i = 100; i >= 1; --i)
            if (abs(coeficient[i]) > 0)
                return i;
    }

    bool grad2() { ///verificam daca avem ec de grad2
        return get_gradPolinom() == 2;
    }

    bool bipatrata(){  /// verificam daca avem ecuatie de tipul a * x^4 + b * x ^ 2 + c
        if( get_gradPolinom() == 4 ){
            for(int i = 1; i <= 4; ++i)
                if( (i != 4 || i != 2 ) && abs(coeficient[i]) )
                    return false;
            return true;
        }
        return false;
    }

    void monotonie() { ///crescatoare / descrescatoare
        derivare();
        if(get_gradPolinom() != 1) {
            double sol[101];
            int nrSol = 0;

            rezolv(0, sol, nrSol);

            if (nrSol != 0) {
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

    void rezolv(double valoare, double solutie[], int &nrSolutii) {
        /// rezolvam ecuatie de tipul f(x) = c (c valoare aleatorie)
        /// "valoare" are urmatoarea semnificatie f(x) = valoare

        coeficient[get_gradPolinom()] -= valoare; /// scadem valoarea

        nrSolutii = 0;

        for (double i = -500000; i <= 500000; i += 1) {
            if (abs(f_de_x(i / 100)) == 0)
                solutie[++nrSolutii] = i / 100;
        }

        coeficient[get_gradPolinom()] += valoare; /// adunam valoarea
    }

    void rezolv_derivata(double valoare, double solutie[], int &nrSolutii) {
        /// "valoare" are urmatoarea semnificatie f(x) = valoare
        /// rezolvam ecuatie de tipul f'(x) = c, unde c este o valoare aleatorie

        coeficient_derivare[get_gradPolinom()] -= valoare; /// scadem valoarea

        nrSolutii = 0;

        for (double i = -500000; i <= 500000; i += 1) {
            if (abs(f_de_x_derivat(i / 100)) == 0)
                solutie[++nrSolutii] = i / 100;
        }

        coeficient_derivare[get_gradPolinom()] += valoare; /// adunam valoarea
    }

    void grafic() { /// Face graficul polinomului
        initwindow(getmaxwidth(), getmaxheight(), "Fara nume, asa e mai fancy");

        line(0, getmaxheight() / 2, getmaxwidth(), getmaxheight() / 2); /// axa Ox
        line(getmaxwidth() / 2, 0, getmaxwidth() / 2, getmaxheight()); /// axa Oy
        outtextxy(getmaxwidth() - 25, getmaxheight() / 2 + 15, "Ox"); /// afisam Oy pe ecran
        outtextxy(getmaxwidth() / 2 - 25, 15, "Oy"); /// afisam Ox pe ecran

        /// sagetile pentru axa Oy

        line(getmaxwidth() / 2 - 10, 10, getmaxwidth() / 2, 0);
        line(getmaxwidth() / 2 + 10, 10, getmaxwidth() / 2, 0);

        /// sagetile pentru axa Ox

        line(getmaxwidth(), getmaxheight() / 2, getmaxwidth() - 10, getmaxheight() / 2 - 10);
        line(getmaxwidth(), getmaxheight() / 2, getmaxwidth() - 10, getmaxheight() / 2 + 10);

        double cnt = 0.1;  /// variabila cu ajutorul careia putem sa trasam graficul

        setcolor(RED);  /// graficul va avea culoarea rosie
        setlinestyle(1, 0, 4);
        double redimensionare_segment = 100;  /// redimensionez axa Ox

        for (double i = -(getmaxwidth() / redimensionare_segment) * 1.0 + cnt; i <= getmaxwidth() / redimensionare_segment; i += cnt) {
            /// desenam graficul din puncte apropiate (cnt)
            line(i * redimensionare_segment + getmaxwidth() / 2,
                 -f_de_x(i) * redimensionare_segment  + getmaxheight() / 2,
                    (i - cnt) * redimensionare_segment + getmaxwidth() / 2,
                 -f_de_x(i - cnt) * redimensionare_segment + getmaxheight() / 2);
        }

        setcolor(WHITE);
        setlinestyle(1, 0, 1);

        int x, y; ///Se asteapta click stanga pentru a inchide graficul

        do{
           getmouseclick(WM_LBUTTONDOWN, x, y);
        }while( x == -1 && y == -1 );

        closegraph();  /// inchide fereastra
    }

    void derivare(){ /// facem derivata polinomului
        coeficient_derivare[get_gradPolinom()] = 0;  /// dispare x^get_gradPolinom() si de aceea e 0

        for (int i = get_gradPolinom() - 1; i >= 0; --i) {
            if (abs(coeficient[i + 1]) > 0)
                coeficient_derivare[i] = coeficient[i + 1] * (i + 1);  /// aici se face derivarea practic
        }
    }

    void simplificare_polinom() {  /// aici facem cmmdc al coeficientilor diferit de 0 si impartim prin cmmdc
        double x = coeficient[get_gradPolinom()];

        for (int i = get_gradPolinom() - 1; i >= 0; --i) {
            if (abs(coeficient[i]) > 0)
                x = cmmdc(abs(x), abs(coeficient[i]));
        }

        for (int i = 0; i <= get_gradPolinom(); ++i)
            coeficient[i] /= abs(x);
    }

    double f_de_x( double x ){  /// calculam f(x), unde x valoare aleatorie
        double sol = 0;
        sol += coeficient[0];
        for( int i = 1 ; i <= get_gradPolinom() ; i++ )
            sol += coeficient[i] * putere(x, i);
        return sol;
    }

    double f_de_x_derivat(double x) { /// calculam f'(x), unde x valoare aleatorie
        double valoare = 0;

        for (int i = 0; i < get_gradPolinom(); ++i)
            valoare += coeficient_derivare[i] * putere(x, i);

        return valoare;
    }
};

int main()
{
    polinom test, tes1;

    cin >> test;
    test.grafic();

    return 0;
}
