#include <iostream>
#include <vector>
#include <string>
using namespace std;
    
// El cost de "recursiu" es exponencial en funció de l'entrada n.

int n;				//nombre de nivells del triangle
int total_elems;	//nombre total delements del triangle
int mrestes[29][29]={{0}};
int msol[8][8]={{0}};
int candidats[2]={0};	//emmagatzema els 2 candidats possibles que compleixen la diferencia entre 2 valors
vector< int > sims;	//emmagatzema un valor per cada solucio que ens servira per identificar els triangles simetrics.
bool tesolucio;

//mostra el triangle màgic per pantalla
void escriu()
{
   int i, aux;
   int espais=0;
   for(i=n; i>0; i--)
    {
        for(aux=espais; aux>0; aux--) cout << "  "; 
        espais++;
		for(int j=1; j<=i; j++)
        {
            
                if(msol[i][j]<10)
                {
                    cout << "0" << msol[i][j];
                }
                else
                {
                    cout << msol[i][j];
                }
                if(j!=i) cout << "  ";
        }
        cout << endl;
    }
    cout << endl;
}
/*
void escriurestes()
{
   int i;
   int espais=0;
   for(i=0; i<15; i++)
    {
		for(int j=0; j<15; j++)
        {
            
                if(mrestes[i][j]<10)
                {
                    cout << "0" << mrestes[i][j];
                }
                else
                {
                    cout << mrestes[i][j];
                }
				 cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}
*/
//Retorna un valor que ens servira per identificar si un triangle es simetric a un altre.
//Es calcula com la suma de la multiplicació de cadascun dels valors de la solucio pel nivell on es troba el valor en el triangle.
int calc_sim()
{
	int i, j;
	int aux= 0;
	for(i=n; i>0; i--)
    {
        for(j=i; j>0; j--)
        {
			aux += i*msol[i][j];
        }
    }
   return aux;
}

void recursiu(int elem, int nivell, int pos)
{
    int j, dif, x, i, y;
	if (elem-1==total_elems)	//cas en que tenim una solucio
    {
		bool simetric=false;
        tesolucio=true;
		int sim = calc_sim();	//comprova que no sigui un triangle simetric a un altre
		for(i=0; i<sims.size(); i++)
		{
			if(sim==sims[i]) simetric=true;
		}
		sims.push_back(sim);
        if (simetric==false)escriu();
    }
	else	//cas en que encara no tenim el triangle ple				
	{
        if(elem==1||elem==2||elem==4||elem==7||elem==11||elem==16||elem==22) //cas en que es el primer element del nivell
		{
            pos=1;
            nivell++;
            for(j=1; j <= total_elems; j++)
            {
                if(mrestes[0][j]>0)  //mirem si el nombre que volem agafar ja esta fet servir
                {
                    msol[nivell][pos]=mrestes[0][j];  //posem el numero a la solucio             
                    mrestes[0][j]*=(-1);
                    recursiu(elem+1,nivell, pos+1);
                    mrestes[0][j]*=(-1); //desmarquem
                    msol[nivell][pos]=0; //restaurem el valor a 0
                }
            }
        }
        else
        {
            dif = msol[nivell-1][pos-1];
            x = msol[nivell][pos-1];
            //Busquem els 2 possibles valors tals que (x-Y = dif)
            j=1;
			//Calculem els 2 possibles candidats
			candidats[0]= x-dif;
			candidats[1]= x+dif;
			int cand;
           for(i=0;i<2;i++)
		   {
			   cand=candidats[i];
			   //cout << cand << endl;
			   if(cand>0)
			   {
				   if(cand<=total_elems)
				   {
						if(mrestes[0][cand]>0) //..mirem si ja esta fet servir
						{
							msol[nivell][pos]=cand; //posem el numero a la solucio
							mrestes[0][cand]*=(-1);//marquem el numero
							cout << "posem numero" << endl;
							escriu();
							recursiu(elem+1,nivell, pos+1);
							mrestes[0][cand]*=(-1);//desmarquem el numero
							msol[nivell][pos]=0; //restaurem el valor a zero
						}
				   }
			   }
		   }
			/*while(j<=total_elems)
            {
               if(mrestes[x][j]==dif) //si trobem algun numero que compleix la resta..
               {
                    if(mrestes[0][j]>0) //..mirem si ja esta fet servir
                    {
                        y=j;
                        msol[nivell][pos]=y; //posem el numero a la solucio
                        mrestes[0][y]*=(-1);//marquem el numero
                        recursiu(elem+1,nivell, pos+1);
                        mrestes[0][y]*=(-1);//desmarquem el numero
                        msol[nivell][pos]=0; //restaurem el valor a zero
                    }
                }
                j++;
            }*/
        }
    }
}  
                                          
int main()
{
	cin >> n;	//nombre de nivells del triangle
	total_elems=((n*(n+1))/2);
    tesolucio=false;

    for(int i=0; i < total_elems+1; i++)
	{
            for(int j=0; j < total_elems+1; j++)
            {
                    mrestes[i][j]= abs(i-j);
            }  
    }
	//escriurestes();
    recursiu(1,0,1);
    if(tesolucio==false) cout << "sense solucio per a n = " << n << endl;
	//free(mrestes);
	//free(msol);
    return 0;
}
