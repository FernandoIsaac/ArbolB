#ifndef BTREE_H
#define BTREE_H
#include "arbolB.h"
#include <iostream>

using namespace std;

template <class Type, int orden> class ArbolB {

protected: // dato members
	Nodo<Type, orden> *root;
private:
	void recInorden(Nodo<Type, orden> * current );
	bool  Encontrar( Nodo<Type, orden> *current, Type &target);

public: // publics.
	ArbolB();
	// busqueda
	void inOrder();
	bool buscar( Type &searchitem );
	void mostrarArbol();
	void DibujarArbol();
	// insercion
	bool buscarEnNodo( Nodo<Type, orden> *current, const Type &target, int &position );
	void insertar(const Type &new_entry);
	void insertarEnRecursion( Nodo<Type, orden> *current, const Type &new_entry,Type &median,Nodo<Type, orden> * &rightchilds , bool &result );
	void insertarEnNodo(Nodo<Type, orden> *current, const Type &entry, Nodo<Type, orden> *rightchilds, int position);
	void dividirNodo( Nodo<Type, orden> *current,  const Type &extra_entry,   Nodo<Type, orden> *extra_childs,  int position, 
		Nodo<Type, orden> * &right_half,   Type &median);
	// eliminacion

	void remover( const Type &target );
	void removerEnRecursion( Nodo<Type, orden> *current, const Type &target );
	void removerDato(  Nodo<Type, orden> *current, int position  );
	void copiarDePredecesor(  Nodo<Type, orden> *current, int position );
	// funciones para restaurar despues de la eliminacion
	void restaurar( Nodo<Type, orden> *current ,int position  );
	void moverAlaIzquierda( Nodo<Type, orden> *current , int position );
	void moverAlaDerecha( Nodo<Type, orden> *current , int position );
	void combinar( Nodo<Type, orden> *current, int position );
	
	void imprimirArbol( Nodo<Type, orden> *current );
	void imprimirArbol2( Nodo<Type, orden> *current, int num );
};

template <class Type, int orden> ArbolB<Type,orden>::ArbolB(){
	root = NULL;
}

template <class Type, int orden> void ArbolB<Type,orden>::inOrder(){  
	return recInorden( root );   
}

template <class Type, int orden> void ArbolB<Type,orden>::recInorden(Nodo<Type, orden> * current ){
	if ( current != NULL )
	{
		recInorden( current->childs[0]);
		for (int i = 0; i < current->count; i++)
		{
			cout << current->data[i] << " ";
			recInorden(current->childs[i + 1]);
		}
	}
}
template <class Type, int orden> bool ArbolB<Type,orden>::buscar( Type &searchitem ){
	
	return Encontrar( root , searchitem );
}
template <class Type, int orden> bool ArbolB<Type,orden>::Encontrar( Nodo<Type, orden> *current, Type &target ){
	
	bool result = false;
	int position;
	if (current != NULL) {
		result = buscarEnNodo(current, target, position);
		if (result == false)
			result = Encontrar(current->childs[position], target);
		else
			target = current->data[position]->getData();
	}
	return result;
}


template <class Type, int orden> bool ArbolB<Type,orden>::buscarEnNodo( Nodo<Type, orden> *current, const Type &target, int &position ){
	position=0;
	while (position < current->count && target > current->data[position])
		position++; 
	if (position < current->count && target == current->data[position])
		return true;
	else
		return false;
}
template <class Type, int orden> void ArbolB<Type,orden>::insertar(const Type &new_entry){
	Type median;
	Nodo<Type, orden> *rightchilds, *new_root;
	bool  result ; 
	insertarEnRecursion(root, new_entry, median, rightchilds , result);
	if(result) { 
		new_root = new Nodo<Type, orden>;
		new_root->count = 1;
		new_root->data[0] = median;
		new_root->childs[0] = root;
		new_root->childs[1] = rightchilds;
		root = new_root;
	}
}
template <class Type, int orden> void ArbolB<Type,orden>::insertarEnRecursion( Nodo<Type, orden> *current,
	const Type &new_entry,Type &median,Nodo<Type, orden> * &rightchilds , bool &result ){

		int position;
		if (current == NULL) {

			median = new_entry;
			rightchilds = NULL;
			result = true;
		}
		else { 
			bool fl = buscarEnNodo(current, new_entry, position);
			if ( fl ){
				cout<<"El objeto ya se encuentra en el arbol\n"; 
			    result = false; 
				return; 
			}
			else {
				Type extra_entry;
				Nodo<Type, orden> *extra_childs;

				insertarEnRecursion(current->childs[position], new_entry,extra_entry, extra_childs , result);
				if ( result ) {
					if ( !current->NodoLLeno() ) {
						result = false;
						insertarEnNodo(current, extra_entry, extra_childs, position);
					}
					else 
						dividirNodo( current, extra_entry, extra_childs, position,rightchilds, median);
				}

			}
		}
}
template <class Type, int orden> void ArbolB<Type,orden>::insertarEnNodo(Nodo<Type, orden> *current,
	const Type &entry, Nodo<Type, orden> *rightchilds, int position){
		int i; 
		for(i=current->count-1;i>= position;i--){ 
			current->data[i+1]=current->data[i];
			current->childs[i+2]=current->childs[i+1]; 
		} 
		current->data[position]= entry; 
		current->childs[i+2]=rightchilds ;
		current->count++;
}
template <class Type, int orden> void ArbolB<Type,orden>::dividirNodo( Nodo<Type, orden> *current,  const Type &extra_entry,   Nodo<Type, orden> *extra_childs,  int position, 
	Nodo<Type, orden> * &right_half,   Type &median){

		right_half = new Nodo<Type,orden>;
		int mid = orden/2;
		if( position <= mid ){
			for(int i = mid;i < orden-1;i++ ){
				right_half->data[i-mid] = current->data[i];
				right_half->childs[i+1-mid] = current->childs[i+1];
			}
			current->count = mid;
			right_half->count = orden-1-mid;
			insertarEnNodo( current , extra_entry , extra_childs , position );
		} else {
			mid++;
			for(int i = mid;i < orden-1;i++ ){
				right_half->data[i-mid] = current->data[i];
				right_half->childs[i+1-mid] = current->childs[i+1];
			}
			current->count = mid;
			right_half->count = orden-1-mid;
			insertarEnNodo( right_half , extra_entry , extra_childs , position - mid);
		}
		median = current->data[current->count - 1];
		right_half->childs[0] = current->childs[current->count];
		current->count--;
}

template <class Type, int orden> void ArbolB<Type,orden>::remover( const Type &target ){

	removerEnRecursion( root , target );
	if( root != NULL && root->count == 0 ){
		Nodo<Type, orden> *delete_root = root;
		root = root->childs[0];
		delete delete_root;
	}
}
template <class Type, int orden> void ArbolB<Type,orden>::removerEnRecursion( Nodo<Type, orden> *current, const Type &target ){

	int position;
	if( current == NULL ){
		cout << "item no encontrado.\n";
		return;
	}
	else{
		bool fl = buscarEnNodo( current , target ,position );
		if( fl ){

			if( current->childs[position] != NULL ){
				copiarDePredecesor( current , position );
				removerEnRecursion( current->childs[position], current->data[position]);
			}else
				removerDato( current , position );

		}else
			removerEnRecursion( current->childs[position], target );

		if( current->childs[position] != NULL )
			if( current->childs[position]->NodoVacio() )
				restaurar( current , position );
	}
}

template <class Type, int orden> void ArbolB<Type,orden>::removerDato(  Nodo<Type, orden> *current, int position  ){

	for(int i = position; i < current->count-1 ;i++)
		current->data[i] = current->data[i+1];
	current->count--;
}
template <class Type, int orden> void ArbolB<Type,orden>::copiarDePredecesor(  Nodo<Type, orden> *current, int position ){

	Nodo<Type, orden> * leaf = current->childs[position];

	while( leaf->childs[leaf->count] != NULL )
		leaf = leaf->childs[leaf->count]; //mover hacia al hijo mas derecho
	current->data[position] = leaf->data[leaf->count-1];
}

template <class Type, int orden> void ArbolB<Type,orden>::restaurar( Nodo<Type, orden> *current ,int position  ){

	if( position == current->count )
		if( current->childs[position-1]->count > (orden-1)/2 )
			moverAlaDerecha( current , position-1);
		else
			combinar( current , position );
	else if( position == 0 )
		if( current->childs[1]->count > (orden-1)/2)
			moverAlaIzquierda( current , 1 );
		else
			combinar( current , 1 );
	else
		if( current->childs[position-1]->count > (orden-1)/2 )
			moverAlaDerecha( current , position-1 );
		else if( current->childs[position+1]->count > (orden-1)/2 )
			moverAlaIzquierda( current , position+1 );
		else
			combinar( current, position );
}

template <class Type, int orden> void ArbolB<Type,orden>::moverAlaIzquierda( Nodo<Type, orden> *current , int position ){

	Nodo<Type, orden> *leftchilds = current->childs[position-1],
		*rightchilds = current->childs[position];
	leftchilds->data[leftchilds->count] = current->data[position-1];

	leftchilds->childs[++leftchilds->count] = rightchilds->childs[0];
	current->data[position-1] = rightchilds->data[0];

	rightchilds->count--;
	for(  int i =0;i < rightchilds->count;i++ ){
		rightchilds->data[i] = rightchilds->data[i+1];
		rightchilds->childs[i] = rightchilds->childs[i+1];
	}
	rightchilds->childs[rightchilds->count] = rightchilds->childs[rightchilds->count +1];

}

template <class Type, int orden> void ArbolB<Type,orden>::moverAlaDerecha( Nodo<Type, orden> *current , int position ){

	Nodo<Type, orden>*rightchilds = current->childs[position+1],
		*leftchilds = current->childs[position];

	rightchilds->childs[rightchilds->count+1] = rightchilds->childs[rightchilds->count];

	for( int i=rightchilds->count; i > 0;i-- ){
		rightchilds->data[i] = rightchilds->data[i-1];
		rightchilds->childs[i] = rightchilds->childs[i-1];
	}

	rightchilds->count++;
	rightchilds->data[0] = current->data[position];

	rightchilds->childs[0] = leftchilds->childs[leftchilds->count--];
	current->data[position] = leftchilds->data[leftchilds->count];
}

template <class Type, int orden> void ArbolB<Type,orden>::combinar( Nodo<Type, orden> *current, int position ){

	int i;
	Nodo<Type, orden> *leftchilds = current->childs[position-1],
		*rightchilds = current->childs[position];

	leftchilds->data[leftchilds->count] = current->data[position-1];
	leftchilds->childs[++leftchilds->count] = rightchilds->childs[0];

	for( i =0;i < rightchilds->count;i++){
		leftchilds->data[leftchilds->count] = rightchilds->data[i];
		leftchilds->childs[++leftchilds->count] = rightchilds->childs[i+1];
	}
	current->count--;

	for( i=position-1; i < current->count; i++ ){
		current->data[i] = current->data[i+1];
		current->childs[i+1] = current->childs[i+2];
	}

	delete rightchilds;
}

template <class Type, int orden> void ArbolB<Type,orden>::imprimirArbol( Nodo<Type, orden> *current ){
	
	int i;
	if(!current) 
		return; 
	static int k = 1;
	cout << k <<" ";
	current->mostrarNodo(); 
	k++;
	for( i=0; i<= current->count ;i++) 
		imprimirArbol( current->childs[i] );
}

template <class Type, int orden> void ArbolB<Type,orden>::imprimirArbol2( Nodo<Type, orden> *current, int num ){
	
	int i;
	if(!current) 
		return; 
	//static int k = 1;
	//cout << k <<" ";
	//current->dibujarNodo(); 
	//k++;
	if(num==0){
		current->dibujarNodoIzquierdo();
	}
	else if(num==1){
		current->dibujarNodoMedio();
	}
	else if(num==2){
		current->dibujarNodoDerecho();
	}
	else if(num==-1){
		current->dibujarNodoRaiz();
	}
	for( i=0; i<= current->count ;i++) 
		imprimirArbol2( current->childs[i] , i);
}

template <class Type, int orden> void ArbolB<Type,orden>::mostrarArbol(){
	
	if ( root == NULL ) 
		cout<<"El Arbol esta vacio..."; 
	else{ 
		cout <<"\tLlaves Nodo\n";
		imprimirArbol( root );
	} 
}

template <class Type, int orden> void ArbolB<Type,orden>::DibujarArbol(){
	
	if ( root == NULL ) 
		cout<<"El Arbol esta vacio..."; 
	else{ 
		cout <<"\tLlaves Nodo\n";
		imprimirArbol2( root , -1);
	} 
}

#endif
