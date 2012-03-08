/*

#######################################
## Funcionament de l'algoritme voraç ##
#######################################
S'emmagatzemen les freqüències en ordre creixent dins una cua de prioritat.
A cada etapa es fusionen els 2 nodes de freqüència més baixa fins que finalment
la cua de prioritat es queda amb un sol element, que és el arbre de huffman resultant.
L'algoritme voraç funciona de manera que un cop s'han fusionat les 2 freqüències més
baixes, es treuen aquests 2 elements de la cua i se n'inserta 1 de nou que té com a 
freqüència la suma dels dos anteriors. Llavors es repeteix el procés però aquest cop 
amb un element menys a la cua.
Un cop tenim l'arbre de huffman només cal calcular l'alçada de cadascun dels nodes fins
a l'arrel per extreure'n finalment el nombre esperat de bits per lletra.
El cost de fusionar tots els elements per construir l'arbre resultant en cas pitjor
és de (n log n) amb n = nombre de freqüencies.

*/
#include <iostream>
#include <vector>
#include <queue>
#define null 0
using namespace std;

double bplla;   //nombre esperat de bits per lletra

struct node {
    node *fe, *fd, *pare;
    double f;

    node (node* fee, node* fdd, double ff)
    {
         fe=fee;
         fd=fdd;
         pare=null;
         f=ff;
        if (fe) fe->pare = this;
        if (fd) fd->pare = this;
    }
        
    ~node () { delete fe; delete fd; }
};
    
node* arrel;
vector<node*> fulles;   //vector de punters als nodes fulla de l'arbre de Huffman
    
struct comparador {
    bool operator() (node* p, node* q) {
        return p->f > q->f;
    }
};

int alcada (node* p) {
    if(p->pare!=null)
    {
        return alcada(p->pare)+1;
    }
    else return 0;
}

//Retorna la suma de multiplicar la frequencia de cada fulla amb seva l'alçada fins a l'arrel
double bpll () 
{
    double r=0;
    for (unsigned i=0; i<fulles.size(); ++i) 
        r += (fulles[i]->f)*alcada(fulles[i]);
    return r;
}

//Crea un arbre de Huffman a partir d'una cua de prioritat que emmagatzemma els nodes.
void Huffman (vector<double>& F) {
    priority_queue<node*,vector<node*>,comparador> CP;
    for(int i=0; i < F.size(); i++)
    {
        node* p = new node(null,null,F[i]);
        CP.push(p);
        fulles.push_back(p);
    }
    while (CP.size()!=1) {
        node* p = CP.top();  CP.pop();
        node* q = CP.top();  CP.pop();
        CP.push(new node(p,q,p->f+q->f));
    }
    arrel = CP.top();
    bplla = bpll();
    bplla = bplla/100;
    cout << "nombre esperat de bits per lletra: " << bplla << endl;
}

int main () {
    
    cout.setf(ios::fixed);
    cout.precision(4);
    int simbols;    //nombre de simbols
    double aux = 0;
    vector<double> F;   //vector de frequencies
    cin >> simbols;
    
    for(int i=0; i<simbols; i++)
    {
        cin >> aux;
        F.push_back(aux);
    }
    
    Huffman (F);
}


