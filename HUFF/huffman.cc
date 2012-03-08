
/***

Creació d'un arbre de Huffman.

A partir d'una taula de freqüències que assigna a cada caràcter la seva freqüència
es construeix un arbre de Huffman. S'ofereixen mètodes per codificar
i decodificar utilitzant aquest arbre.

***/
#include <iostream>
#include <vector>
#include <queue>

#define null 0
using namespace std;
//#include "ada.hh"


class Huffman {

private:

    struct node {
        node *fe, *fd, *pare;
        double f;

        node (node* fe, node* fd, double f) :
            fe(fe), fd(fd), pare(null), f(f) {
                if (fe) fe->pare = this;
                if (fd) fd->pare = this;
                }
            
        ~node () { delete fe; delete fd; }
    };
    
    node* arrel;
    //map<char,node*> fulles;
    vector<node*> fulles;

    struct comparador {
        bool operator() (node* p, node* q) {
            return p->f > q->f;
        }
    };
    
    double bpll () 
    {
        double r=0;
        for (unsigned i=0; i<fulles.size(); ++i) 
            r += (fulles[i]->f)*alcada(fulles[i]);
        return r;
    }
    
    int alcada (node* p) {
        if(p->pare!=null)
        {
            return alcada(p->pare)+1;
        }
        else return 0;
    }

public:
    
    double bplla;
    
    ~Huffman () {
        delete arrel;
    }

    Huffman (vector<double>& F) {
        priority_queue<node*,vector<node*>,comparador> CP;
        //foreach(it,F) {
        for(int i=0; i < F.size(); i++)
        {
            node* p = new node(null,null,F[i]);
            CP.push(p);
            //fulles[it->first] = p;
            //fulles[i] = p;
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
    
    /*double bitsxlletra()
    {
        return bitsxlletrarec(arrel, 0, 0);
    }
    
    double bitsxlletrarec(node* p, int alcada, double bpl)
    {
        int bpl1, bpl2;
        if(p) 
        {
            bpl1 = bitsxlletrarec(p->fesq, alcada+1);
            bpl2 = bitsxlletrarec(p->fdre, alcada+1);
            return p->f;
        }
    }*/
    

};


// Exemple d'ús

int main () {
    
    cout.setf(ios::fixed);
    cout.precision(4);
    int simbols;
    double aux; 
  //  double bpll;
    cin >> simbols;
    
    //map<char,double> F;
    vector<double> F;
    
    for(int i=0; i<simbols; i++)
    {
        cin >> aux;
        F.push_back(aux);
    }

    Huffman h(F);
   // bpll = Huffman.bpll();
    //bpll = bpll/100;
   // cout << bpll;
    
}
