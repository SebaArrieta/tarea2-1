#include <iostream>
#include <fstream>
using namespace std;
typedef char tElem;

struct tNodo{
    tElem info;
    tNodo* sig;
};

class Lista{
    private:
        tNodo* head;
        tNodo* tail;
        tNodo* curr;
        unsigned int size;
        unsigned int pos;
    public:
        Lista();
        ~Lista();
        tNodo* crearNodo(tElem x);
        int insertar(tElem x);
        void moveToStart();
        void moveToEnd();
        void prev();
        void next();
        unsigned int getSize();
        tElem getInfo();
        void clear();
};

Lista::Lista(){
    head = tail = curr = new tNodo;
    head->sig = tail ->sig = curr->sig = NULL;
    size = 0; pos = 0;
}

Lista::~Lista(){ // destructor que elimina todos los nodos para que no queden en la memoria
    tNodo* nodo;

    while(head!= NULL){ //se detiene cuando elimine todos los nodos y solo quede el ultimo que apunta a NULL;
        nodo = head->sig; //apunta al siguiente y al siguiente asi sucesivamente
        delete head; //eliminamos el head de la lista
        head = nodo; //el nuevo head va a ser el que continuaba al head actual
    }
    delete head; // elimina el ultimo head
}

int Lista::insertar(tElem x){
    tNodo* aux = curr->sig;
    curr->sig = new tNodo;
    curr->sig->info = x;
    curr->sig->sig = aux;
    if(tail == curr) {tail = curr->sig; } //si el actual es cola, la cola será el nuevo que se creó
    size++;
    return pos;
}

void Lista::moveToStart(){ curr = head; pos = 0; }
void Lista::moveToEnd(){ curr = tail; pos = size; }

void Lista::prev(){
    tNodo* nodo;
    if (curr == head){ return; } //si se encuentra en head no se puede ir más atras
    nodo = head;    
    while(nodo->sig != curr){ nodo = nodo->sig; } // va avanzando hasta llegar al anterior del actual
    curr = nodo; // el nodo actual ahora es el anterior 
    pos--;
}

void Lista::next(){
    if(curr!=tail){curr = curr->sig; pos++; }
}

unsigned int Lista::getSize(){ return size;}

tElem Lista::getInfo(){
    if(curr->sig != NULL){
        return curr->sig->info;
    }
    return '\0';
}

void modificarTexto(){
    ifstream entrada;
    ofstream salida;
    entrada.open("teclado-entrada.txt");
    if(!entrada.is_open()){
        cout<<"error al abrir el archivo de entrada"<<endl; 
        exit(1);
    }

    salida.open("teclado-salida.txt");
    if(!salida.is_open()){
    cout<<"error al abrir el archivo de salida"<<endl; 
        exit(1);
    }

    Lista* list = new Lista;
    char c;// caracter
    unsigned int size;
    entrada.get(c);
    while(!entrada.eof()){ //para cuando llegue al final del archivo
        while(c != '\r' && c != '\n' && !entrada.eof()){ //se detiene cuando encuentra un salto de linea
            switch(c){
                case '<':
                    list->prev();
                    break;
                case '>':
                    list->next();
                    break;
                case '[':
                    list->moveToStart();
                    break;
                case ']':
                    list->moveToEnd();
                    break;
                default:
                    list->insertar(c);
                    list->next();
                    break;
            }
            entrada.get(c);
        }
        size = list->getSize();
        list->moveToStart();

        for(unsigned int i = 0; i<size;i++){
            salida<<list->getInfo();
            list->next();
        }
        delete list;
        list = new Lista;
        entrada.get(c);//se salta el \r
        entrada.get(c);// se salta el \n
        if(!entrada.eof()){ salida<<'\n'; } // solo hace el salto de linea cuando no sea el final del texto
    }
    delete list; //elimina la ultima lista creada
    entrada.close();
    salida.close();

} 

int main(){
    modificarTexto();
}