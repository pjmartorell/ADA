#include <iostream>
#include <vector>
#include <list>
using namespace std;


int debug;

int cols;
int files;
int millorSol;
vector <vector < int > > Puzzle;
vector<int> TaulaHash;

struct estatTaulell
{
	vector <vector < int > > taulell;
	int clau;
};

typedef list < estatTaulell > Llista;
//vector<Llista> taulaHash;
typedef Llista::iterator iter;

void escriuTaulell()
{
	if(debug)
	{	
		int i, j;
		for(i = 0; i < files; i++)
		{
			for(j = 0; j < cols; j++) cout << Puzzle[i][j] << " ";
			cout << endl;
		}

	}
}

bool finalitzat() 
{
	int i, j, ant;
	bool ordenat = true;
	ant = -1;
	for(i = 0; (i < files) && ordenat; i++)
	{
		for(j = 0; (j < cols) && ordenat; j++)
		{
			//Si el seguent es inferior: o es el 0 i esta al final, o el vector no esta ordenat
			if(Puzzle[i][j] < ant) ordenat = ((i == files - 1) && (j == cols - 1));		
			ant = Puzzle[i][j];
		}	
	}
	return ordenat;
}

bool repetit(vector< vector < int > > Puzz, vector<Llista> &taulaHash) 
{
	int clau, i, j, pos;
	bool iguals = true;
	bool trobat = false;
	
	//Calcul de la clau
	clau = 0;
	for(i = 0; i < files; i++)
	{
		for(j = 0; j < cols; j++) clau += (i + 1) * (j + 1) * Puzz[i][j];
	}
	pos = clau % (taulaHash.size());

	if(debug) cout << "#Dins Repetit: pos=" << pos << " clau=" << clau << endl;
		
	estatTaulell estatActual;
	estatActual.taulell = Puzz;
	estatActual.clau = clau;
	
	if(taulaHash[pos].empty())
	{
		if(debug) cout << "-taulaHash[pos].empty()" << endl;
		taulaHash[pos].push_back(estatActual);
		return false;
	}
	else
	{
		if(debug) cout << "-taulaHash[pos].plena()" << endl;
		iter p = taulaHash[pos].begin();
		while(p != taulaHash[pos].end() && !trobat)
		{
			if(p->clau == estatActual.clau)
			{
				iguals = true;
				for(i = 0; (i < files) && iguals; i++)
				{	
					for(j = 0; (j < cols) && iguals; j++) 
					{
						if(p->taulell[i][j] != estatActual.taulell[i][j]) iguals = false;	
						if(debug) cout << estatActual.taulell[i][j] << "|" << p->taulell[i][j] << " ";
					}
					if (debug) cout << endl;
					if (debug) cout << "iguals=" << iguals << endl;
				}
				if(iguals)
				{
					trobat = true;
					return true;
				}
			}
			if(debug) cout << "p->clau=" << p->clau << " estatActual.clau=" << estatActual.clau << endl;
			++p;
		}
		if(debug) cout << "-trobat=" << trobat << endl;
		if(!trobat) taulaHash[pos].push_back(estatActual);
	}
	return false;
}

void swap(int i1, int j1, int i2, int j2)
{
	int aux = Puzzle[i1][j1];
	Puzzle[i1][j1] = Puzzle[i2][j2];
	Puzzle[i2][j2] = aux;
}

bool backtrack(int i, int j, int solCurs, vector<Llista> taulaHash)
{
	//M'aprofito del tractament dinamic de C++ sobre el tractament de les condicions dels if, que les fa ordenadament
	if((i == files - 1) && (j == cols - 1) && finalitzat())
	{
		if(solCurs < millorSol) millorSol = solCurs;
		if(debug) cout << "\n#CasBase: solCurs=" << solCurs << endl;
		return true;
	}
	else if(!repetit(Puzzle, taulaHash))
	{
		if (debug) cout << "#Cas NO REPETIT: solCurs=" << solCurs << endl;
		bool sol1 = false, sol2 = false, sol3 = false, sol4 = false;
		if(i - 1 >= 0) 
		{
			swap(i, j, i - 1, j);

			if(debug) cout << "\n#Cas Amunt: solCurs=" << solCurs << endl;
			escriuTaulell();

			sol1 = backtrack(i - 1, j, solCurs + 1, taulaHash);
			swap(i, j, i - 1, j);
		}
		if(j - 1 >= 0)
		{
			swap(i, j, i, j - 1);

			if(debug) cout << "\n#Cas Esquerra: solCurs=" << solCurs << endl;
			escriuTaulell();
			
			sol2 = backtrack(i, j - 1, solCurs + 1, taulaHash);
			swap(i, j, i, j - 1);
		}
		if(i + 1 < files)
		{
			swap(i, j, i + 1, j);

			if(debug) cout << "\n#Cas Avall: solCurs=" << solCurs << endl;
			escriuTaulell();

			sol3 = backtrack(i + 1, j, solCurs + 1, taulaHash);
			swap(i, j, i + 1, j);
		}
		if(j + 1 < cols)
		{
			swap(i, j, i, j + 1);

			if(debug) cout << "\n#Cas Dreta: solCurs=" << solCurs << endl;
			escriuTaulell();

			sol4 = backtrack(i, j + 1, solCurs +1, taulaHash);
			swap(i, j, i, j + 1);
		}
		if(sol1 || sol2 || sol3 || sol4) return true;
		else return false;
	}
	else 
	{ 
		if (debug)	cout << "#Cas REPETIT solCurs=" << solCurs << endl;
		return false;
	}	
}


int main()
{
	cin >> files;
	cin >> cols;
	cin >> debug;

	vector< vector < int > > PuzzleAux(files, cols);
	Puzzle = PuzzleAux;

//	vector< Llista > TaulaHashAux(cols * files);
	vector< Llista > taulaHash(1009);

	int i, j, iInicial, jInicial;
	for(i = 0; i < files; i++)
	{
		for(j = 0; j < cols; j++) 
		{
			cin >> Puzzle[i][j];
			if(Puzzle[i][j] == 0)
			{
				iInicial = i;
				jInicial = j;	
			}
		}
	}

	millorSol = INT_MAX;

	bool sol;

	sol = backtrack(iInicial, jInicial, 0, taulaHash);

	if(!sol) cout << "\nno te solucio" << endl;
	else cout << "\nte solucio en " << millorSol << " passos" << endl;

	return 0;
}

