#include <iostream>
#include <vector>
#include <string>
using namespace std;
//ERRORS: el identificar la casella horitzontalment!"
    
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
int total_elems;
int mrestes[29][29]={{0}};
int msol[8][8]={{0}};
//vector< vector<int> > mrestes;
//vector< vector<int> > msol;
bool tesolucio;

void escriu2()		//mostra el triangle màgic per pantalla
{
   int i, aux;
   int espais=0;
   for(i=n; i>0; i--)
    {
        for(aux=espais; aux>0; aux--) cout << "  "; 
        espais++;
        for(int j=i; j>0; j--)
        {
            
                if(msol[i][j]<10)
                {
                    cout << "0" << msol[i][j];
                }
                else
                {
                    cout << msol[i][j];
                }
                if(j!=1) cout << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

void escriu()		//mostra el triangle màgic per pantalla
{
	for(int i = 0; i < n+1; i++) 
    {    
       	for(int j = 0; j < n+1; j++)
       	{
            cout << msol[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for(int j = 0; j < total_elems+1; j++)
    {
        cout << mrestes[0][j] << " ";
    }
    cout << endl;
    /*for(int i = 0; i < 29; i++) 
    {    
       	for(int j = 0; j < 29; j++)
       	{
            cout << mrestes[i][j] << " ";
        }
        cout << endl;
    }*/
    cout << endl;
    cout << endl;
}

void recursiu(int elem, int nivell, int pos)
{
    int j, y, dif, x;
	if (elem-1==total_elems)
    {
       cout << "solucio trobada!" << endl;
        tesolucio=true;
        escriu2();
    }
	else 						
	{
        if(elem==1||elem==2||elem==4||elem==7||elem==11||elem==16||elem==22) //cas en que es el primer element del nivell
		{
            cout << "Soc un 1,2,4,7,..." << endl;
            pos=1;
            nivell++;
            for(j=1; j <= total_elems; j++)
            {
                if(mrestes[0][j]>0)  //mirem si el nombre que volem agafar ja esta fet servir
                {
                    
                    
                    msol[nivell][pos]=mrestes[0][j];  //posem el numero a la solucio
                    cout << "Numero trobat: " << mrestes[0][j] << endl;
                    //marcar_valor(mrestes[0][j]); //marquem com a usat el numero escollit i totes les restes que usen aquest valor
                    mrestes[0][j]*=(-1);
                    escriu();
                    recursiu(elem+1,nivell, pos+1);
                    mrestes[0][j]*=(-1); //desmarquem
                    msol[nivell][pos]=0; //torna a 0
                   // marcar_valor(mrestes[0][j]); //desmarquem!
                }
            }
        }
        else
        {
            cout << "Soc un numero intermig" << endl;
            dif = msol[nivell-1][pos-1];
            x = msol[nivell][pos-1];
            
            //Busquem els 2 possibles valors tals que (x-Y = dif)
            j=1;
            while(j<=total_elems)
            {
               if(mrestes[x][j]==dif) //si trobem algun numero que compleix la resta..
               {
                    if(mrestes[0][j]>0) //..mirem si ja lhem fet servir
                    {
                        y=j;
                        msol[nivell][pos]=y; //posem el numero a la solucio
                        cout << "Numero trobat: " << y << endl;
                        mrestes[0][y]*=(-1);//marquem el numero
                        //for(j=0; j <= n; j++) mrestes[y][j]*=(-1);//marquem les restes que usen aquest numero
                        escriu();
                        recursiu(elem+1,nivell,pos+1);
                        //for(j=0; j <= n; j++) mrestes[y][j]*=(-1);//desmarquem les restes
                        mrestes[0][y]*=(-1);//desmarquem el numero
                        
                    }
                }
                j++;
            }
            msol[nivell][pos]=0; //torna a 0
        }
    }
}  
                                          
int main()
{
	cin >> n;	//nombre d'elements
	total_elems=((n*(n+1))/2);
    tesolucio=false;
    //vector< vector<int> > mrestesAux(total_elems+1,0);
    //mrestes= mrestesAux;
    //vector< vector<int> > msolAux(n+1,0);
    //msol=msolAux;
    
    for(int i=0; i < total_elems+1; i++)
	{
            for(int j=0; j < total_elems+1; j++)
            {
                    mrestes[i][j]= abs(i-j);
            }  
    }
    escriu();
    recursiu(1,0,1);
    if(tesolucio==false) cout << "sense solucio per a n = " << n << endl;
	free(mrestes);
	free(msol);
    return 0;
}
