#include <vector>
#include <iostream>
using namespace std;

int n;
vector< int > digits;
char sol_trobada;

void backtrack(int solucio, int nivell, vector<char> usats) 
{
	if (nivell == n) 
	{
            	if((solucio % 7) == 0)
		{
			cout << solucio << endl;
			sol_trobada = 1;
		}
        } 
	else 
	{
        	for (int j=0; j<n; ++j) 
		{
                	if(usats[digits[j] - 1] == '0') 
			{
				usats[digits[j] - 1] = '1';
				backtrack(solucio * 10 + digits[j], nivell + 1, usats);
				usats[digits[j] - 1] = '0';
			}

		} 
	}
}


int main()
{
	cin >> n;
	vector<int> digitsAux(n);
	digits = digitsAux;
	vector<char> usats(9, '0');
	//Llegim els numeros d'entrada
	for(int i = 0; i < n; i++) cin >> digits[i]; 
	
	sol_trobada = 0;

	backtrack(0, 0, usats);

	if(sol_trobada == 0) cout << "sense solucio" << endl;
}

