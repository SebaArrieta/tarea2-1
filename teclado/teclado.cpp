#include <iostream>
#include <fstream>
#include <string>
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
        ~Lista(){};
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
    return 'a';
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

    Lista list,aux;
    char c;// caracter
    unsigned int size;
    entrada.get(c);
    while(!entrada.eof()){ //para cuando llegue al final del archivo
        while(c != '\r' && c != '\n'){ //se detiene cuando encuentra un salto de linea
            switch(c){
                case '<':
                    list.prev();
                    break;
                case '>':
                    list.next();
                    break;
                case '[':
                    list.moveToStart();
                    break;
                case ']':
                    list.moveToEnd();
                    break;
                default:
                    list.insertar(c);
                    list.next();
                    break;
            }
            entrada.get(c);
        }
        size = list.getSize();
        list.moveToStart();

        for(unsigned int i = 0; i<size;i++){
            salida<<list.getInfo();
            list.next();
        }
        salida<<'\n';
        list = aux;
        entrada.get(c);//se salta el \r
        entrada.get(c); // se salta el \n
    }
    entrada.close();
    salida.close();

} 

// void salidaTexto(Lista list){
//     ofstream salida;
//     char c; //caracter
//     unsigned int size = list.getSize();
//     salida.open("teclado-salida.txt");
//     if(!salida.is_open()){
//         cout<<"error al abrir el archivo de salida"<<endl; 
//         exit(1);
//     }
//     list.moveToStart();

//     for(unsigned int i = 0; i<size;i++){
//         salida<<list.getInfo();
//         list.next();
//     }
//     salida<<'\n';
//     salida.close();
// }

// void modificarArchivo(){
    
//     Lista list = entradaTexto();
//     salidaTexto(list);
// }

int main(){
    modificarTexto();
}