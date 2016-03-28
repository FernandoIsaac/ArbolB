#ifndef Nodo_H
#define Nodo_H
#include <iostream>
using namespace std;
template <class Type, int orden> class ArbolB;

template <class Type, int orden> class Nodo {
	friend class ArbolB< Type, orden>;
private:
	int count;
	int izquierdos;
	Type data[orden-1];
	Nodo<Type, orden> *childs[orden];
// constructor:
public:
	Nodo();
	bool NodoVacio() const;
	bool NodoLLeno() const;
	void mostrarNodo();
	void dibujarNodoIzquierdo();
	void dibujarNodoDerecho();
	void dibujarNodoMedio();
	void dibujarNodoRaiz();
};

template <class Type, int orden> Nodo< Type,orden >::Nodo(){
	this->izquierdos=0;
	this->count = 0;
	for(int i=0;i < orden;i++) 
		this->childs[i] = NULL;
}

template< class Type, int orden > bool Nodo< Type,orden>::NodoLLeno() const{
	return (count== orden-1);
} 
template<  class Type, int orden > bool Nodo< Type, orden>::NodoVacio() const {
	return (count < (orden-1)/2);
}

template< class Type, int orden > void Nodo< Type,orden>::mostrarNodo() { 
	
	for(int i=0; i< this->count ;i++) 
		cout <<"\t["<< data[i]<<"]"; 
	
	cout <<"\n"; 

}

template< class Type, int orden > void Nodo< Type,orden>::dibujarNodoIzquierdo() { 
	izquierdos = izquierdos+1;
	for(int j=0; j<izquierdos;j++)
		cout<<"\t";
	cout<<"/";
	for(int i=0; i< this->count ;i++) 
		cout <<"["<< data[i]<<"]"; 
	
	cout <<"\n"; 

}

template< class Type, int orden > void Nodo< Type,orden>::dibujarNodoDerecho() { 
	cout<<"       \\";
	for(int i=0; i< this->count ;i++) 
		cout <<"["<< data[i]<<"]"; 
	
	//cout <<"\n"; 

}

template< class Type, int orden > void Nodo< Type,orden>::dibujarNodoMedio() { 
	cout<<"      |";
	for(int i=0; i< this->count ;i++) 
		cout <<"["<< data[i]<<"]"; 
	
	//cout <<"/\n"; 

}

template< class Type, int orden > void Nodo< Type,orden>::dibujarNodoRaiz() { 
	//cout<<"      ";
	for(int i=0; i< this->count ;i++) 
		cout <<"["<< data[i]<<"]"; 
	
	cout <<"\n"; 

}

#endif
