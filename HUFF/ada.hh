/***

    Ànalisi i Disseny d'Algorismes.
    
    Jordi Petit
    Salvador Roura
    Febrer 2005

***/


#ifndef ada_hh
#define ada_hh


/** Inclusions estàndards **/

#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <cassert>
#include <cmath>


using namespace std;



/** Definició del tipus ¡boolean¡. El tipus ¡boolean¡ és un ¡int¡, però
    s'usa com si fos un ¡bool¡. El propòsit s'aquesta definició és poder
    fer ¡vector¡s de ¡booleans¡ ràpids. Si es fés un ¡vector<bool>¡, són
    lents perquè funcionen a nivell de bits.
**/

typedef int boolean;



/** Definició del punter null ¡null¡. En \CPP un punter null és senzillament 
un zero.
**/

#define null 0



/** Definició de la classe genèrica ¡matrix¡. Serveix per fer taules
    de dues dimensions sense haver de fer vectors de vectors. El mal
    que té és que el nombre de files i columnes és fix.
**/


template <typename T>
class matrix {

    int r,c;
    vector<vector<T> > t;

public:

    matrix () :
        r(0), c(0) {  }
    
    matrix (int rows, int cols, T init=T()) :
        r(rows), c(cols), t(vector<vector<T> >(r, vector<T>(c,init))) {  }
    
    int rows () const { 
        return r; 
    }
    
    int cols () const { 
        return c; 
    }

    vector<T>& operator[] (int i) {
        return t[i];
    }
   
    const vector<T>& operator[] (int i) const {
        return t[i];
    }

    
    friend ostream& operator<< (ostream& s, matrix<T> m) {
        for (int j=0; j<m.c; ++j) {
            for (int i=0; i<m.r; ++i) {
                s << m.t[i][j] << " ";
            }
            s << endl;
        }
        return s;
    }
};



/** Operador per escriure directament els continguts d'un ¡vector¡. **/
   
template <typename T> ostream& operator<< (ostream& s, vector<T> v) {
    for (int i=0; i<int(v.size()); ++i) {
        s << v[i] << " ";
    }
    return s;
}


/** Funcions per fer lectures de tipus bàsics. **/

inline int      readint     ()  { int    n;  cin >> n;  return n; }
inline char     readchar    ()  { char   n;  cin >> n;  return n; }
inline bool     readbool    ()  { bool   n;  cin >> n;  return n; }
inline double   readdouble  ()  { double n;  cin >> n;  return n; }


/** Defineix el double infinit, que és més gran que qualsevol altre double
    (excepte infinit, és clar).  **/
    
const double infinit = numeric_limits<double>::infinity(); 

/** Defineix l'enter maxint, que és l'enter més gran que es pot representar **/
    
const int maxint = numeric_limits<int>::max(); 


/** Funcions per generar números aleatoris. **/

// Retorna un real aleatori en $[0,1)$.
inline double randdouble () {
    return rand()/double(RAND_MAX);
}

// Retorna un enter aleatori en $[a..b]$.
inline int randint (int a, int b) {
    return a + rand() % (b-a+1);  
}

// Retorna un enter aleatori en $[0..n-1]$.
inline double randint (int n) {
    return rand() % n;  
}

// Retorna cert amb probabilitat $p$.
inline boolean randbit (double p) {
    return randdouble() < p;  
}

// Retorna una matriu de $n\times n$ reals aleatoris.
matrix<double> randmatrix (int n) {
    matrix<double> m(n,n);
    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; j++) {
            m[i][j] = randdouble();
    }   }
    return m;
}


// Retorna un vector de $n$ reals aleatoris.
vector<double> randvector (int n) {
    vector<double> v(n);
    for (int i=0; i<n; ++i) {
        v[i] = randdouble();
    }   
    return v;
}


// Retorna un vector de $n$ enters aleatoris entre $a$ i $b$.
vector<int> randvector (int n, int a, int b) {
    vector<int> v(n);
    for (int i=0; i<n; ++i) {
        v[i] = randint(a,b);
    }   
    return v;
}


/**

Macro per iterar sobre tots els elements d'un contenidor.

**/

#define foreach(it,c) for (__typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)


/**
    ¡ErrorPrec¡ i ¡ErrorImpl¡ són les excepcions
    que es llencen. ¡Error¡ és una classe base comuna, adient per poder
    caçar (\textsl{catch}) qualsevol d'elles. Aquest és l'únic punt del curs
    on s'utilitza herència.
**/


class Error {
    private:    
        string err;
    public:    
        Error (string s) : err(s) {}
        string error () const {return err;}        
};


class ErrorPrec: public Error {
    public:    
        ErrorPrec (string s) : Error("Error de precondició: "+s) {}
};


class ErrorImpl: public Error {
    public:    
        ErrorImpl (string s) : Error("Error d'implementació: "+s) {}       
};


#endif
