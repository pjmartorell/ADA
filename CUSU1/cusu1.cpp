#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;


void escriuSortides(queue<string> Sortides)
{
	cout << "SORTIDES" << endl;	
	cout << "--------" << endl;	
	while(not Sortides.empty())
	{
		cout << Sortides.front() << endl;
		Sortides.pop();
	}
} 

void escriuCues(int numCues, vector< queue<string> > Cues)
{
	int i;
	string aux;

	cout << "CONTINGUTS FINALS" << endl;	
	cout << "-----------------" << endl;	
	

	for(i=0; i < numCues; i++) 
	{
		cout << "cua " << i+1 << ":";
		while(Cues[i].size() != 0) 
		{
			aux = Cues[i].front();
			Cues[i].pop();
			cout << " " << aux;
		}
		cout << endl;
	}
}


int main()
{
	int numCues, i, k, ini, nC;
	string lec, aux, aux2;
	queue<string> Sortides;

	// Primer llegim el num de Cues que tindrem
	cin >> numCues;
	vector< queue<string> > Cues(numCues);

	getline(cin, lec);
	for(i=0; i < numCues; ++i)
	{
		getline(cin, lec);
		k = 0;
		while (k < lec.size())
		{
			ini = k;
			while ((k < lec.size()) && (lec.at(k) != ' ')) k++;
			aux = lec.substr(ini, k - ini);
			Cues[i].push(aux);
			k++;
		}

	}

	// Esperem linia en blanc
	getline(cin, lec);
	// Comencem a llegir tractament dinàmic de la cua
	getline(cin, lec);
	while(lec.size() != 0)
	{
                k = 0;
                ini = k;

		//Avancem la primera paraula
                while (lec.at(k) != ' ') k++;
		k++;
		if (lec.at(0)=='S') // Surt de la Cua
		{
			aux2 = lec.substr(k, lec.size() - k);
			nC = atoi(aux2.c_str());
			if ((nC > 0) && (nC <= numCues) && (not Cues[nC - 1].empty()))
			{
				Sortides.push(Cues[nC - 1].front());
				Cues[nC - 1].pop();
			}
		}
		else // Entra a la cua
		{
                        ini = k;
                       	while ((k < lec.size()) && (lec.at(k) != ' ')) k++;
			// Obtenim el nom
                        aux = lec.substr(ini, k - ini);
			// Obtenim el num de cua
			k++;
			aux2 = lec.substr(k, lec.size() - k);
			nC = atoi(aux2.c_str());
			if ((nC > 0) && (nC <= numCues)) Cues[nC - 1].push(aux);
		}
		//escriuCues(numCues, Cues);
		getline(cin, lec);
	}
	escriuSortides(Sortides);
	cout << endl;
	escriuCues(numCues, Cues);
}

