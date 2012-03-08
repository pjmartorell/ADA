#include <iostream>
#include <vector>
#include <string>
using namespace std;

// El cost de "recursiu" es exponencial en funció de l'entrada n.
/*
     Aquesta matriu està "dividida" en 2 parts: la 1a contindra les solucions del problema 
     i la 2a contindra tots els valors possibles de restar x - y, sent  1 =< x,y =< n.
     Daquesta manera a la hora de buscar valors que compleixin les condicions dels triangles 
     màgics només haurem de recorrer aquesta part de la matriu i trobar tots els parells de 
     valors x i y que restats donen el valor que estem buscant.
     Els valors de la fila 0 no ens serveixen pel problema pero la farem servir per identificar
     quins numeros hem fet servir marcant-los com a negatius (multiplicant-los per -1)
    
     Estat inicial de la matriu:
             y=0 1 2 3 4 5 6 7 
             ------------------
         x=0 | 0 1 2 3 4 5 6 7
           1 | 0 0 1 2 3 4 5 6
           2 | 0 0 0 1 2 3 4 5
           3 | 0 0 0 0 1 2 3 4
           4 | 0 0 0 0 0 1 2 3
           5 | 0 0 0 0 0 0 1 2
           6 | 0 0 0 0 0 0 0 1
           7 | 0 0 0 0 0 0 0 0
           
         A partir de la diagonal --> matriu[x][y] = x - y
         L'altra part de la matriu emmagatzema les solucions que anem obtenint.   
	*/

int n;								//nombre de nivells del triangle
int mrestes[8][8]={{0}};
int msol[8][8]={{0}};

void escriu()		//mostra el triangle màgic per pantalla
{
	for(int i = 0; i < 8; i++) 
    {    
       	for(int j = 0; j < 8; j++)
       	{
            		cout << msol[i][j] << " ";
        }
        cout << endl;
    }
}

void marcar_valor(int valor)
{
    int i;
    int j;
    for(i=1; i <= n; i++) mrestes[i][valor]*=(-1);
    for(j=1; j <= n; j++) mrestes[valor][j]*=(-1);
}

void recursiu(int nivell)
{
    int i, j, y, dif, x, elem;
	for (elem=1; elem<=nivell; elem++)
	{
        if ((nivell == n)&&(elem==nivell)) escriu();
        else
        {
            if(elem==1) //cas en que no es el primer element del nivell
			{
                for(j=1; j <= n; j++)
                {
                    if(mrestes[0][j]>0)  //mirem si el nombre que ovlem agafar ja esta fet servir
                    {
                        msol[nivell][elem]=mrestes[0][j];  //posem el numero a la solucio
                        marcar_valor(mrestes[0][j]); //marquem com a usades totes les restes que usen aquest valor
                        mrestes[0][j]*=(-1);   //marquem el numero escollit com a usat
                        
                    }
                }
            }
            else
            {
                dif = msol[nivell-1][elem-1];
                x = msol[nivell][elem-1];
                //Busquem els 2 possibles valors tals que (x-Y = dif)
                //1r valor
                i=1;
                bool trobat=false;
                while((i<=n)&&(trobat==false))
                {
                   if(msol[i][x]==dif)
                   {
                        y=i;
                        trobat=true;
                    }
                }
                if(trobat)
                {
                    msol[nivell][elem]=y;
                    for(i=1; i <= n; i++) mrestes[i][y]*=(-1);
                }
                
                //2n valor
                j=1;
                trobat=false;
                while((j<=n)&&(trobat==false))
                {
                   if(msol[x][j]==dif)
                   {
                        y=j;
                        trobat=true;
                    }
                }
                if(trobat)
                {
                    msol[nivell][elem]=y;
                    for(i=1; i <= n; i++) mrestes[y][i]*=(-1);
                }
              
                //Errorrr!
            }
        }
    }
    recursiu(nivell++);
}  
                                          

int main()
{
	cin >> n;	//nombre d'elements	
    int val = 1;
    int col = 1;
    
    for(int i=0; i < 8; i++)
	{
            for(int j=col; j < 8; j++)
            {
                    mrestes[i][j]= val;
                    val++;
            }
            col++;
            val=1;
    }
    recursiu(1);
	return 0;
}
