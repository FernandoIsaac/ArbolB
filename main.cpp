#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include<ctime>
#include<cstdio>
#include"nodo.h"
#include"arbolB.h"

using namespace std;

void InsertarInts(FILE *fa, ArbolB<int,3> &arbol);
void LeerInts(FILE*fa, ArbolB<int,3> &arbol);
void InsertarStrings(FILE *fa, ArbolB<string,3> &arbol);
void LeerStrings(FILE*fa, ArbolB<string,3> &arbol);

int main(){

	int menu=0;
	int opcion=0;
	int num;//SI ES ARBOL DE NUMEROS ESTE ES EL NUMERO A AGREGAR
	string cadena;//SI ES ARBOL DE 
	string nombreArchivo;
	const char * c;
	FILE *fa;
	ArbolB<int,3> arbolEnteros;
	ArbolB<string,3> arbolCadenas;
	bool saved = false;
	bool created = false;
	bool Entero = false;
	do{
		cout<<"Ingrese opcion:"<<endl<<"1)Crear Nuevo Arbol"<<endl
		<<"2)Agregar Llave"<<endl<<"3)Eliminar Llave"<<endl
		<<"4)Cargar Arbol-B"<<endl<<"5)Guardar Arbol-B"<<endl
		<<"6)Mostar Arbol Dibujado"<<endl<<"7)Mostrar Arbol En Consola"<<endl;
		cin>>menu;
		cin.ignore(256,'\n');
		if(menu == 1){
			if(created==true&&saved==false){
				cout<<"Usted ha creado o cargado un archivo ya y no lo ha salvado, Salve y vuelva a ingresar al programa"<<endl;
			}
			else{	
				cout<<"Ingrese El nombre del archivo donde guardara su arbol"<<endl;
				//cin>>nombreArchivo;
				getline(cin, nombreArchivo);
				c = nombreArchivo.c_str();
				//fa = fopen (c, "r+b");
				//if(!fa){
				//	fa = fopen(c, "w+b");
				created = true;
					//cout<<"el archivo ya existe";
					//exit(EXIT_FAILURE);
				//}else{
					//fa = fopen(c, "w+b");
				//	cout<<"el archivo ya existe";
				//	exit(EXIT_FAILURE);
				//}
				do{
					cout<<"Sus llaves seran: 1)Numeros o 2) Cadenas?"<<endl;
					cin>>opcion;
				}while(opcion!=1&&opcion!=2);
				if(opcion==1){
					//ArbolB<int, 3> arbol;
					Entero = true;
				}
				if(opcion==2){
					Entero = false;
					//ArbolB<string,3>arbol;
				}
			}	
		}
		if(menu == 2){
			if(!created){
				cout<<"No ha creado o cargado ningun arbol"<<endl;
			}
			else{
				if(Entero){
					cout<<"Ingrese el numero que quiere agregar al arbol"<<endl;
					cin>>num;
					arbolEnteros.insertar(num);
				}
				else{
					cout<<"Ingrese la cadena que quiere agregar al arbol"<<endl;
					getline(cin, cadena);
					arbolCadenas.insertar(cadena);
				}
			}
		}
		if(menu==3){
			if(!created){
				cout<<"no ha creado o cargado ningun arbol"<<endl;
			}
			else{
				if(Entero){
					cout<<"Ingrese el numero que quiere borrar del arbol"<<endl;
					cin>>num;
					arbolEnteros.remover(num);
				}
				else{
					cout<<"Ingrese la cadena que quiere borrar del arbol"<<endl;
					getline(cin, cadena);
					arbolCadenas.remover(cadena);
				}
			}
		}
		if(menu==4){////////////OJO ACORDATE QUE NO HAS TERMINADO ESTE!!
			if(created==true&&saved==false){
				cout<<"usted ya cargo o creo un arbol y no lo ha guardado, salvelo y vuelva a correr el programa"<<endl;
			}
			else{
				cout<<"Ingrese el nombre del archivo a cargar"<<endl;
				getline(cin, nombreArchivo);
				c = nombreArchivo.c_str();
				//fa = fopen (c, "r+b");
				//if(!fa){
				//	cout<<"El archivo no existe"<<endl;
				//	exit(EXIT_FAILURE);
				//}
			//	else{
					do{
						cout<<"Su arbol es de : 1) Enteros o 2) Cadenas?"<<endl;
						cin>>opcion;
					}while(opcion!=1&&opcion!=2);
					if(opcion==1){
						Entero=true;
					}
					if(opcion==2){
						Entero=false;
					}
					if(Entero){
						//arbolEnteros.mostrarArbol();
						//LeerInts(fa, arbolEnteros);
						//arbolEnteros.mostrarArbol();
						ifstream in(c,ios::binary);
						if(in.is_open()){
            						//in.read((char *)arbol2,sizeof(Btree<string,3>));
            						in.read(reinterpret_cast<char *>(&arbolEnteros),sizeof(ArbolB<int,3>));
            						in.close();
       						}
						created=true;
						
					}
					else{
                                                //arbolEnteros.mostrarArbol();
                                                //LeerInts(fa, arbolEnteros);
                                                //arbolEnteros.mostrarArbol();
                                                ifstream in(c,ios::binary);
                                                if(in.is_open()){
                                                        //in.read((char *)arbol2,sizeof(Btree<string,3>));
                                                        in.read(reinterpret_cast<char *>(&arbolCadenas),sizeof(ArbolB<string,3>));
                                                        in.close();
                                                }
						//LeerStrings(fa, arbolCadenas);
						created=true;
					}
			//	}
				
			}
		}
		if(menu==5){
			if(!created){
				cout<<"usted no ha creado ni cargado archivo para guardar"<<endl;
			}
			else{
				if(Entero){
					//InsertarInts(fa, arbolEnteros);
					ofstream out(c,ios::binary);
        				//out.write((char *)arbol, sizeof(Btree<string,3>));
        				out.write(reinterpret_cast<char *>(&arbolEnteros), sizeof(ArbolB<int,3>));
        				out.close();
					saved = true;
				}
				else{
					//InsertarStrings(fa, arbolCadenas);
					ofstream out(c,ios::binary);
                                        //out.write((char *)arbol, sizeof(Btree<string,3>));
                                        out.write(reinterpret_cast<char *>(&arbolCadenas), sizeof(ArbolB<string,3>));
                                        out.close();
					saved = true;
				}
			}
		}
		if(menu==7){
			if(!created){
				cout<<"no hay arbol que mostrar"<<endl;
			}
			else{
				if(Entero){
					arbolEnteros.mostrarArbol();
				}
				else{
					arbolCadenas.mostrarArbol();
				}
			}
		}
	}while(menu<8);
//	if(created)
//		fclose(fa);
        ArbolB<int, 3> arbol;
	//ArbolB<int, 3> arbol2;
        //for(int i = 1; i <=200; i++){
              //arbol.insertar(rand()%100+1);
	//	arbol.insertar(i*10);
       // }
	//arbol2 = arbol;
        /*arbol.insertar("Joel");
        arbol.insertar("Luis");
        arbol.insertar("Xavier");
        arbol.insertar("Alvaro");
        arbol.insertar("Orlis");
        arbol.insertar("Krista");
        arbol.insertar("Andrea");
        arbol.insertar("Rene");
        arbol.insertar("Fernando");
        arbol.insertar("Ximena");*/
	cout<<"arbol: "<<sizeof(arbol)<<endl;	
        arbolEnteros.mostrarArbol();
	arbolCadenas.mostrarArbol();
//	cout<<"SIZE OF: "<<sizeof(int)<<endl;
	cout<<"Enteros"<<sizeof(ArbolB<int,3>)<<endl;
	cout<<"Cadenas"<<sizeof(ArbolB<string,3>)<<endl;
	cout<<"Removiendo 160"<<endl;
	arbol.remover(160);
	cout<<"arbol: "<<sizeof(arbol)<<endl;	
	//arbol.mostrarArbol();
	//cout<<"Removiendo 200"<<endl;
	//arbol.remover(200);
	//cout<<"ARBOL"<<endl;
	//arbol.mostrarArbol();
	//cout<<"ARBOL 2"<<endl;	
	//arbol2.mostrarArbol();
        return 0;
}

void InsertarInts(FILE *fa, ArbolB<int,3> &arbol){
	// Insertar al inicio:
  	//fseek(fa, 0, SEEK_SET);
  	fwrite(&arbol, sizeof(ArbolB<int,3>), 1, fa);
}
void LeerInts(FILE *fa, ArbolB<int,3> &arbol){
	fseek(fa, sizeof(ArbolB<int,3>) , SEEK_SET);
      	fread(&arbol, sizeof(ArbolB<int,3>), 1, fa);
}
void InsertarStrings(FILE *fa, ArbolB<string,3> &arbol){
	// Insertar al inicio:
  	//fseek(fa, 0, SEEK_SET);
  	fwrite(&arbol, sizeof(ArbolB<string,3>), 1, fa);
}
void LeerStrings(FILE*fa, ArbolB<string,3> &arbol){
	fseek(fa, sizeof(ArbolB<string,3>) , SEEK_SET);
      	fread(&arbol, sizeof(ArbolB<string,3>), 1, fa);
}
