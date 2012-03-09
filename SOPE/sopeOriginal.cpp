#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<vector<bool> > taulell;

void debug(const taulell &t, int mida)
{
    cerr << "debug :" << endl;
    for(int i = 0; i < mida; i++)
    {
        for(int j = 0; j < mida; j++)
        {
            cerr << (t[i][j] ? 'P' : '.');
        }
        cerr << endl;
    }
}

int mida; //es posen com a variables globals per estalviar pas de parÃ metres a avaluar
int num_pedres = 0;
bool funciona = false;
bool primer = false;
bool maca = false;

void avaluar_taulell2(taulell &t, int iteracio)
{
    if (num_pedres == iteracio){ 
        funciona = 1;
        maca = (maca ? true : ((mida && 1) && t[mida/2][mida/2]));
    }
    
    if (iteracio < num_pedres) {
    //millor no crear masses instÃ ncies, i tirar enrere els moviments... 
    //cal trobar el conjunt de moviments acceptables.
    //Una optimitzaciÃ³ seria tractar cada possible cas (cert o fals) com un bit i tractar les comparacions en enters concatenats, aixÃ­, amb un switch case molt llarg i cada comparaciÃ³ d'enters podrien tractar-se 32 caselles enlloc d'una sola
    for(int i = 0; (i < mida) && !maca; i++)//busca horitzontal
    {
        //buscar solucio
        for(int j=1; (j < mida-1) && !maca; j++)
        {
            bool actual = t[i][j];
            if(actual) 
            {
                //Ã©s una pedra
                bool anterior = t[i][j-1];
                bool posterior = t[i][j+1];
                
                if(!anterior && posterior) // cas .PP
                {
                    t[i][j-1] = true;
                    t[i][j] = false;
                    t[i][j+1] = false;   

                    avaluar_taulell2(t, iteracio + 1);
 
                    t[i][j-1] = false; //restaurar estat anterior
                    t[i][j] = true;
                    t[i][j+1] = true;

                }
                else if((anterior && !posterior)) // cas PP.
                {
                    t[i][j-1] = false;
                    t[i][j] = false;
                    t[i][j+1] = true;

                    avaluar_taulell2(t, iteracio + 1);

                    t[i][j-1] = true; //restaurar estat anterior
                    t[i][j] = true;
                    t[i][j+1] = false;
                    
                }
            }
        }
    }
    
    for(int i = 1; (i < mida -1) && !maca; i++)//Busca vertical
    {
        //buscar solucio
        for(int j = 0; (j < mida) && !maca; j++)
        {
            bool actual = t[i][j];
            if(actual)
            {
                //Ã©s una pedra
                bool anterior = t[i-1][j];
                bool posterior = t[i+1][j];
                
                if(!anterior && posterior) //cas .PP
                {
                    t[i-1][j] = true;
                    t[i][j] = false;
                    t[i+1][j] = false;

                    avaluar_taulell2(t, iteracio + 1);

                    t[i-1][j] = false;
                    t[i][j] = true;
                    t[i+1][j] = true;
                    
                }
              
                else if((anterior && !posterior)) //cas PP.
                {
                    t[i-1][j] = false;
                    t[i][j] = false;
                    t[i+1][j] = true;

                    avaluar_taulell2(t, iteracio + 1);
                    
                    t[i-1][j] = true;
                    t[i][j] = true;
                    t[i+1][j] = false;
                    
                }
            }
        }
    }
    }
}




int main()
{
    cin >> mida;
    
    taulell t (mida);
    char p;
    bool value;
    for(int i = 0; i < mida; i++) //emplenar taulell amb bools segons correspongui pedra
    {    
        for(int j = 0; j < mida; j++)
        {
            cin >> p;
            if(p == '.')
            {
                value = false; 
            }
            else
            {
                value = true;
                num_pedres++;
            }
            t[i][j] = value;
        }
    }
    avaluar_taulell2(t, 1);
    int resultat = -1;
    if (maca) resultat = 1;
    else if (funciona) resultat = 0; 
    switch(resultat)
    {
        case -1: cout << "no te solucio" << endl; break;
        case 0: cout << "te solucio" << endl; break;
        case 1: cout << "te solucio maca" << endl; break;
    }
}



