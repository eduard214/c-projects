#include "polinom.h"
#include <iostream>

using namespace std;

void meniu()
{
    cout << "================================MENIU================================\n\n";
    cout << "1. Dati un polinom.\n";
    cout << "2. Afisati polinomul.\n";
    cout << "3. Simplificare polinom.\n";
    cout << "4. Monotonia polinomului.\n";
    cout << "5. Radacinile polinomului.\n";
    cout << "6. Radacinile derivatei polinomului.\n";
    cout << "7. Rezolvarea unei ecuatii de tipul P(x) = c.\n";
    cout << "8. Rezolvarea unei ecuatii de tipul P'(x) = c.\n";
    cout << "9. Calculati P(x), unde x se da la tastatura.\n";
    cout << "10. Calculati P'(x), unde x se da la tastatura.\n";
    cout << "11. Afisarea graficului P(x).\n";
    cout << "12. Afisarea graficului P'(x).\n";
    cout << "13. Iesire din aplicatie.\n\n";
    cout << "================================MENIU================================\n\n";
}

void ai_bagat_ce_nu_trebuie(int n)
{
    cout << "Introduceti un numar de ordine nenul si natural mai mic sau egal decat " << n << " pentru a executa comanda aleasa.\n";
}

int main()
{
    polinom p[1001];
    int n = 0, alegere = 0;

    bool CONTINUA = true;

    while(CONTINUA)
    {
        meniu();

        cout << "Alegeti optiunea dorita.\n";
        cin >> alegere;
        bool ok = false;
        switch(alegere)
        {
        case 1:
        {
            ok = true;
            if (n < 1000)
            {
                ++n;
                cin >> p[n];
            }
            else cout << "Ati atins limita maxima de polinoame!\n";
        }

        break;

        case 2:
        {
            ok = true;

            if (n != 0)
            {
                for (int i = 1; i <= n; ++i)
                    cout << i << ". "<< p[i];
            }
            else cout << "Nu ati dat un polinom pana acum! Deci... nu avem ce afisa.\n";
        }

        break;

        case 3:
        {
            ok = true;
            int i = 0;

            if (n != 0)
            {
                while(!(i <= n && i >= 1))
                    cout << "Dati polinomul pe care vreti sa il simplificati.\n", ai_bagat_ce_nu_trebuie(n), cin >> i;
                for (int i = 1; i <= n; ++i)
                    p[i].simplificare_polinom();
            }
            else cout << "Nu ati dat un polinom pana acum! Deci... nu avem ce simplifica.\n";
        }
        break;

        case 4:
        {
            ok = true;

            int i = 0;

            if (n != 0)
            {
                while(!(i <= n && i >= 1))
                    cout << "Dati polinomul a carei monotonii vreti sa o aflati.\n", ai_bagat_ce_nu_trebuie(n), cin >> i;
                p[i].monotonie();
            }
            else cout << "Nu ati dat un polinom pana acum! Deci... nu avem cum sa aflam monotonia.\n";
        }

        break;

        case 5:
        {
            ok = true;

            int i = 0;

            if (n != 0)
            {
                while(!(i <= n && i >= 1))
                    cout << "Dati polinomul pentru a afla radacinile acestuia.\n", ai_bagat_ce_nu_trebuie(n), cin >> i;

                double sol[101] = {0};
                int nrSol = 0;

                p[i].rezolv(0, sol, nrSol);

                if (nrSol == 0)
                    cout << "Polinomul nostru nu are solutii reale sau... nu stie sa rezolve...\n";
                else
                {
                    cout << "Solutiile acestuia sunt: ";
                    for (int j = 1; j <= nrSol; ++j)
                        cout << sol[j] << ' ';
                    cout << '\n';
                }
            }
            else cout << "Nu ati dat un polinom pana acum! Deci... nu avem cum sa aflam radacinile.\n";
        }

        break;

        case 6:
        {
            ok = true;

            int i = 0;

            if (n != 0)
            {
                while(!(i <= n && i >= 1))
                    cout << "Dati polinomul pentru a afla radacinile derivatei acestuia.\n", ai_bagat_ce_nu_trebuie(n), cin >> i;

                double sol[101] = {0};
                int nrSol = 0;
                p[i].rezolv_derivata(0, sol, nrSol);

                if (nrSol == 0)
                    cout << "Polinomul nostru nu are solutii reale sau... nu stie sa rezolve...\n";
                else
                {
                    cout << "Solutiile acestuia sunt: ";
                    for (int j = 1; j <= nrSol; ++j)
                        cout << sol[j] << ' ';
                    cout << '\n';
                }
            }
            else cout << "Nu ati dat un polinom pana acum! Deci... nu avem cum sa aflam radacinile derivatei.\n";
        }

        break;

        case 7:
        {
            int i = 0;
            ok = true;

            if (n != 0)
            {
                while(!(i >= 1 && i <= n))
                    cout << "Dati polinomul pentru a afla ecuatia dorita.\n", ai_bagat_ce_nu_trebuie(n), cin >> i;
                double valoare = 0;
                cout << "Dati o valoare pentru a calcula P(x) = val\n";
                cin >> valoare;

                double sol[101] = {0};
                int nrSol = 0;

                p[i].rezolv_derivata(valoare, sol, nrSol);

                if (nrSol == 0)
                    cout << "Polinomul nostru nu are solutii reale sau... nu stie sa rezolve...\n";
                else
                {
                    cout << "Solutiile acestuia sunt: ";
                    for (int j = 1; j <= nrSol; ++j)
                        cout << sol[j] << ' ';
                    cout << '\n';
                }
            }
            else cout << "Nu ati dat un polinom pana acum! Deci... nu avem cum sa aflam ecuatia.\n";
        }

        break;

        case 8:
        {
            int i = 0;
            ok = true;

            if (n != 0)
            {
                while(!(i >= 1 && i <= n))
                    cout << "Dati polinomul pentru a afla ecuatia dorita.\n", ai_bagat_ce_nu_trebuie(n), cin >> i;
                double valoare = 0;
                cout << "Dati o valoare pentru a calcula P'(x) = val\n";
                cin >> valoare;

                double sol[101] = {0};
                int nrSol = 0;

                p[i].rezolv_derivata(valoare, sol, nrSol);

                if (nrSol == 0)
                    cout << "Polinomul nostru nu are solutii reale sau... nu stie sa rezolve...\n";
                else
                {
                    cout << "Solutiile acestuia sunt: ";
                    for (int j = 1; j <= nrSol; ++j)
                        cout << sol[j] << ' ';
                    cout << '\n';
                }
            }
            else cout << "Nu ati dat un polinom pana acum! Deci... nu avem cum sa aflam ecuatia.\n";
        }

        break;

        case 9:
        {
            int i = 0;
            ok = true;

            if (n != 0)
            {
                while(!(i >= 1 && i <= n))
                    cout << "Dati polinomul pentru a afla P(x).\n", ai_bagat_ce_nu_trebuie(n), cin >> i;

                double valoare = 0;

                cout << "Dati un x pentru a calcula P(x)... ";

                cin >> valoare;
                cout << '\n';
                cout << "P(x) este: " << p[i].f_de_x(valoare) << '\n';
            }
            else cout << "Nu ati dat un polinom pana acum! Deci... nu avem cum sa aflam P(x).\n";
        }

        break;

        case 10:
        {
            int i = 0;
            ok = true;

            if (n != 0)
            {
                while(!(i >= 1 && i <= n))
                    cout << "Dati polinomul pentru a afla P'(x).\n", ai_bagat_ce_nu_trebuie(n), cin >> i;

                double valoare = 0;

                cout << "Dati un x pentru a calcula P'(x)... ";

                cin >> valoare;
                cout << '\n';
                cout << "P'(x) este: " << p[i].f_de_x_derivat(valoare) << '\n';
            }
            else cout << "Nu ati dat un polinom pana acum! Deci... nu avem cum sa aflam P'(x).\n";
        }

        break;

        case 11:
        {
            int i = 0;
            ok = true;

            if (n != 0)
            {
                while(!(i >= 1 && i <= n))
                    cout << "Dati polinomul pentru a afla graficul polinomului.\n", ai_bagat_ce_nu_trebuie(n), cin >> i;

                p[i].grafic(1);
            }
            else cout << "Nu ati dat un polinom pana acum! Deci... nu avem cum sa aratam graficul polinomului.\n";
        }

        break;

        case 12:
        {
            int i = 0;
            ok = true;

            if (n != 0)
            {
                while(!(i >= 1 && i <= n))
                    cout << "Dati polinomul pentru a afla graficul derivatei polinomului.\n", ai_bagat_ce_nu_trebuie(n), cin >> i;
                p[i].derivare();
                p[i].grafic(2);
            }
            else cout << "Nu ati dat un polinom pana acum! Deci... nu avem cum sa aratam graficul derivatei polinomului.\n";
        }

        break;

        case 13:
        {
            ok = true;
            CONTINUA = false;
            cout << "Multumim pentru utilizare!\n";
        }

        break;
        }
        cout << '\n';

        if (ok == false) cout << "Nu ati introdus o optiune corecta!\n";
    }
    return 0;
}
