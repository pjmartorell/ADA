#include <iostream>
#include <vector>
#include <string>
using namespace std;
    
// El cost de "recursiu" es exponencial en funció de l'entrada n.
/*
    Raonament:
        Si comencem a resoldre el triangle des del nivell de dalt (tamany n) se'ns fa un arbre 
        de busqueda molt gran, per això vaig pensar en començar a resoldre el triangle des de la
        la part de baix i fer-lo creixer cap amunt, així es restringeix més el problema.
        Si comencem des del nivell de dalt, les possibilitats serien masses. Per un triangle 
        màgic de 5 nivells:
        1r nivell    15 14 13 12 11 = 15*14*13*12*11 possibilitats
        2n   ""          _ _ _ _     
        3r   ""           _ _ _        
        4t   ""            _ _
        5e   ""             _
        
        En els següents nivells es restringeixen molt les possibilitats degut a les condicions
        del problema, tot i així m'ha semblat que era molt més eficient començar des del nivell
        de sota.
        1r nivell       _  _  _  _  _   
        2n   ""          _  _  _  _     
        3r   ""           _  _  _      
        4t   ""            _  _        
        5e   ""             15  = 15 possibilitats
        
        La solució s'emmagatzema en una matriu "msol" de l'estil:
             y=0  1  2  3  4  5 ... n 
             ----------------------->
         x=0 | 0  0  0  0  0  0  0  0
           1 | 0  1  0  0  0  0  0  0
           2 | 0  2  3  0  0  0  0  0
           3 | 0  4  5  6  0  0  0  0 
           . | 0  7  8  9  10 0  0  0
           . | 0  11 12 13 14 15 0  0
           . | 0  0  0  0  0  0  0  0
           n | 0  0  0  0  0  0  0  0
           
        La solució al triangle màgic com es veu es guarda i es resol al revés.
        
        Per altra banda tenim una matriu anomenada "mrestes", tal que cada element 
        mrestes[x][y] = x - y; sent  1 =< x,y =< (n(n+1))/2
        Aquesta matriu ens serveix per buscar valors que compleixin les condicions dels triangles 
        màgics: només haurem de recorrer la fila "x" de la matriu i trobar quin es el valor "y"
        que dona com a diferencia un valor determinat.
        Per exemple, si tenim:
            
               1
             3  2
            5 8  _ ---> volem trobar un valor y tal que abs(x - y) = dif, és a dir, que 
           . . . . .    abs(8 - y) = 2; per això recorrerem la fila 8 de mrestes i buscarem
                        tots els valors iguals a 2 en aquella fila i mirarem quina y és.
                        Si el valor y que hem trobat ja està usat s'acaba el cas recursiu.
                        
        Els valors de la fila 0 de mrestes no ens serveixen pel problema pero la farem servir per
        identificar quins numeros hem fet servir marcant-los com a negatius (multiplicant-los per -1)
*/

int n;				//nombre de nivells del triangle
int total_elems;	//nombre total delements del triangle
int mrestes[29][29]={{0}};
int msol[8][8]={{0}};
vector< int > sims;	//emmagatzema un valor per cada solucio que ens servira per identificar els triangles simetrics.
bool tesolucio;
int poss=0;

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
    poss++;
    int j, y, dif, x, i;
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
            while(j<=total_elems)
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
            }
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
    recursiu(1,0,1);
    if(tesolucio==false) cout << "sense solucio per a n = " << n << endl;
	//free(mrestes);
	//free(msol);
	cout << poss << endl;
    return 0;
}
