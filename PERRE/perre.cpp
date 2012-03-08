#include <iostream>
#include <vector>
#include <string>
using namespace std;


/*El cost de "recursiu" es exponencial en funci� de l'entrada n.
*Comencem agafant una paraula i provem d'omplir el vector amb totes les paraules que tenim.
*L'index "nivell" ens indica quina posici� del subconjunt anem a omplir.
*L'index "ant" ens indica de quina posici� de paraula veniem, d'aquesta manera comencem a fer combinacions des de la seguent *paraula de la anterior d'on veniem per tal de no repetir les paraules que ja haviem col�locat.
*/

int n;								//nombre de paraules
vector< string > paraules; 			//seq�encia de paraules

void escriu(vector < string > sol)		//imprimeix el vector per pantalla
{
	cout << "(";
	int i;
	for(i = 0; i < (n - 1); ++i) cout << sol[i] << ",";
	cout << sol[n - 1] << ")" << endl;
}

void recursiu(int nivell, vector< string > sol)
{
	if (nivell == n) escriu(sol);//quan tenim una permutaci� l'imprimim per pantalla
	else 						//sino continuem omplint el vector amb totes les paraules possibles
	{
		int j;
        for (j = 0; j < n; ++j)
		{	
			sol[nivell] = paraules[j];
			recursiu(nivell + 1, sol);
    	}   
	}   
}

int main()
{
	cin >> n;	//nombre de paraules
	
	vector < string > sol(n, "");
	vector < string > paraux(n);		
	paraules = paraux;	//seq��ncia de paraules

	for(int i=0; i < n; ++i) cin >> paraules[i];
	
	if(n < 1) 
	{
		cout << "()" << endl;
		return 0;
	}
	recursiu(0, sol);
	return 0;
}
