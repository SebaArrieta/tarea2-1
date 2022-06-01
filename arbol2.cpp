#include <iostream>

using namespace std;
typedef int tElem;

struct tNodo{
    tElem info;
    int contador;
    int contadorMenor;
    tNodo* izq;
    tNodo* der;
};

class RankedABB{
    public:
        RankedABB();
        ~RankedABB();
        void insert(tElem x);
        void insert(tElem x, tNodo *&nodo);
        bool find(tElem x,tNodo *&tNodo);
        bool find(tElem x);
        int rank(tElem x);
        int rank(tElem x,tNodo *tNodo);
        int setContador(tNodo *nodo);
        void setContadorMenor(tNodo *nodo);
        tNodo* nuevoNodo(tElem x);
        void clear(tNodo *&nodo);
    private:
        tNodo *raiz; // se crea la raiz como un puntero a nodos
        int numEle;
};

RankedABB::RankedABB(){
    raiz = NULL;
    numEle = 0;
}

RankedABB::~RankedABB(){ //elimina mediante el clear y luego elimina la raiz
    clear(raiz);
    delete raiz;
}

void RankedABB::clear(tNodo *&nodo){ //va eliminando mediante busqueda in order
    if(nodo != NULL){
        clear(nodo->izq); 
        delete nodo->izq;
        clear(nodo->der);
        delete nodo->der;
    }
}

tNodo* RankedABB::nuevoNodo(tElem x){
    tNodo* nodo = new tNodo;
    nodo->der = NULL;
    nodo->izq = NULL;
    nodo->info = x;
    nodo->contador = 0;
    nodo->contadorMenor = 0;
    numEle++;
    return nodo;
}

void RankedABB::insert(tElem x){
    insert(x,raiz);
    setContador(raiz);
    setContadorMenor(raiz);

}

void RankedABB::insert(tElem x, tNodo *&nodo){ //se crea una sobrecarga de la funcion, para que al acceder a este funcion desde el main no sea necesario dar un nodo
    if(nodo == NULL){
        nodo = nuevoNodo(x); //le asignamos este nuevo nodo para quitarle el valor de NULL
        numEle++;
    }
    else{
        if(nodo->info > x) insert(x,nodo->izq);
        else if(nodo->info < x) insert(x,nodo->der);
        else return;
    }
}

int RankedABB::setContador(tNodo *nodo){
    if(nodo == NULL){
        return -1;
    }

    int izq = setContador(nodo->izq);
    nodo->contadorMenor =0;
    nodo->contador = 0;
    int der = setContador(nodo->der);
    nodo->contadorMenor=0;
    nodo->contador = 0;
    
    if(izq != -1){
        nodo->contadorMenor += izq + 1;
    }

    nodo->contador += izq+der+2;

    return nodo->contador;
}

void RankedABB::setContadorMenor(tNodo *nodo){
    if(nodo == NULL){
        return;
    }
    if(nodo->der != NULL){
        nodo->der->contadorMenor += nodo->contadorMenor+1;

        if(nodo->der->izq != NULL){
            tNodo *aux = nodo->der->izq;
            while (aux != NULL){
                aux->contadorMenor += nodo->contadorMenor+1;
                aux = aux->izq;
            }
        }
    }
    
    setContadorMenor(nodo->izq);
    setContadorMenor(nodo->der);
}


bool RankedABB::find(tElem x){ 
    return find(x,raiz);
}
bool RankedABB::find(tElem x,tNodo *&nodo){
    if(nodo != NULL){   
        if(nodo->info > x) return find(x, nodo->izq); 
        else if(nodo->info < x) return find(x, nodo->der); 
        else if(nodo->info == x) return true; 
    }
    return false;
}

int RankedABB::rank(tElem x){

    return rank(x,raiz);
}

int RankedABB::rank(tElem x,tNodo *nodo){
    if(nodo != NULL){   
        if(x > nodo->info){
            if(nodo->der != NULL){
                return rank(x, nodo->der);
            }else{
                return nodo->contadorMenor+1;
            }
        }else if(x < nodo->info){
            if(nodo->izq != NULL){
                return rank(x, nodo->izq);
            }else{
                return nodo->contadorMenor;
            }
        }else{
            return nodo->contadorMenor + 1;
        }
    }else{
        return -1;
    }
    
}


int main(){
    
    RankedABB a;

    a.insert(101);
    a.insert(567);
    a.insert(102);
    a.insert(1);
    a.insert(2);
    a.insert(6);
    a.insert(5);
    a.insert(8);
    a.insert(7);
    a.insert(5);

    /*a.insert(25);
    a.insert(50);
    a.insert(30);
    a.insert(28);
    a.insert(40);
    a.insert(70);
    a.insert(27);
    a.insert(45);
    a.insert(55);
    a.insert(75);*/
    //a.mostrar();


    //cout<< a.find(43)<<endl;
    cout<< a.rank(65)<<endl;
    cout<< a.rank(101)<<endl;
    cout<< a.rank(0)<<endl;
    cout<< a.rank(600)<<endl;
    cout<< a.rank(567)<<endl;

    return 0;
}