#include <iostream>
#include <string>
#include <vector>

using namespace std;



vector<vector<bool> > taulell;
int mida; 
int num_pedres = 0;
bool teSol;
bool primer;
bool solMaca;

void backtrack(int iteracio)
{
    if (num_pedres == iteracio){ 
        teSol = 1;
        solMaca = (maca ? true : ((mida && 1) && taulell[mida/2][mida/2]));
    }
    
    if (iteracio < num_pedres) {
    for(int i = 0; (i < mida) && !solMaca; i++) //Cas Horitzontals
    {
        for(int j=1; (j < mida-1) && !solMaca; j++)
        {
            bool actual = taulell[i][j];
            if(actual) 
            {
                //Es una pedra
                bool anterior = taulell[i][j-1];
                bool posterior = taulell[i][j+1];
                
                if(!anterior && posterior) // cas .PP
                {
                    taulell[i][j-1] = true;
                    taulell[i][j] = false;
                    taulell[i][j+1] = false;   

                    backtrack(iteracio + 1);
 
                    taulell[i][j-1] = false; //restaurar estat anterior
                    taulell[i][j] = true;
                    taulell[i][j+1] = true;

                }
                else if((anterior && !posterior)) // cas PP.
                {
                    taulell[i][j-1] = false;
                    taulell[i][j] = false;
                    taulell[i][j+1] = true;

                    backtrack(iteracio + 1);

                    taulell[i][j-1] = true; //restaurar estat anterior
                    taulell[i][j] = true;
                    taulell[i][j+1] = false;
                    
                }
            }
        }
    }
    
    for(int i = 1; (i < mida -1) && !solMaca; i++)//Cas Verticals
    {
        for(int j = 0; (j < mida) && !solMaca; j++)
        {
            bool actual = taulell[i][j];
            if(actual)
            {
                //Es una pedra
                bool anterior = taulell[i-1][j];
                bool posterior = taulell[i+1][j];
                
                if(!anterior && posterior) //cas .PP
                {
                    taulell[i-1][j] = true;
                    taulell[i][j] = false;
                    taulell[i+1][j] = false;

                    backtrack(iteracio + 1);

                    taulell[i-1][j] = false;
                    taulell[i][j] = true;
                    taulell[i+1][j] = true;
                    
                }
              
                else if((anterior && !posterior)) //cas PP.
                {
                    taulell[i-1][j] = false;
                    taulell[i][j] = false;
                    taulell[i+1][j] = true;

                    backtrack(iteracio + 1);
                    
                    taulell[i-1][j] = true;
                    taulell[i][j] = true;
                    taulell[i+1][j] = false;
                    
                }
            }
        }
    }
    }
}




int main()
{
	cin >> mida;

	vector<vector<bool> > taulellAux(mida);
	taulell = taulellAux;

  	char p;
    	bool value;

	teSol = false;
	primer = false;
	solMaca = false;

    	for(int i = 0; i < mida; i++) 
    	{    
        	for(int j = 0; j < mida; j++)
        	{
            		cin >> p;
           		if(p == '.') value = false; 
           		else
           		{
                		value = true;
               			num_pedres++;
        		}
	            	taulell[i][j] = value;
        	}
   	}
   	backtrack(1);
    
	if (solMaca) cout << "te solucio maca" << endl;
	else if (teSol) cout << "te solucio" << endl; 
    	else cout << "no te solucio" << endl;
}



