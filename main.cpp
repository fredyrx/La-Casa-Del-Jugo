#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <list>

using namespace std;

class Permiso {
	public:
	string delimiter;
	string codigo, descripcion;
	void decodificar(string hash){
	delimiter = '|';
	codigo = hash.substr(0,hash.find(delimiter));
	hash.erase(0,codigo.length()+delimiter.length());
	descripcion = hash.substr(0,hash.find(delimiter));
	hash.erase(0,descripcion.length()+delimiter.length());
	}
	void to_string(){
		cout << codigo << " " << descripcion << endl;
	}
};

class Opcion {
	public:
	string delimiter;
	string username, codigo;
	void decodificar(string hash){
	delimiter = '|';
	username = hash.substr(0,hash.find(delimiter));
	hash.erase(0,username.length()+delimiter.length());
	codigo = hash.substr(0,hash.find(delimiter));
	hash.erase(0,codigo.length()+delimiter.length());
	}
	void to_string(){
		cout << username << "|" << codigo << endl;
	}
};

class Usuario {
public:
	string delimiter;
	string username,password,full_name,profile,text_encoded;
	list<Permiso> permisos;
	list<Opcion> modulos;
	Usuario(){
		//decodificar(hash);
		// A partir de la cadena separamos los parametros
	};
	void leer_perfil(){
		cout << "Cargando permisos ..." << endl;
		ifstream in("perfiles.txt");
	 	string s,reg;
	 	int contador;
	 	// Cargamos los permisos segun perfil
	 	contador = 0;
	 	while (getline(in,reg)){	
			Opcion opcion;
			opcion.decodificar(reg);
			if (username.compare(opcion.username)==0){
				modulos.push_back(opcion);
			} 
			opcion.to_string();
			contador = contador + 1;
	 	}
	 	cout << "Total de permisos: " << modulos.size() << endl;
	}

	void cargar_modulos(){

	}

	void decodificar(string hash="|||"){
		delimiter = '|';
		text_encoded = hash;
		username = hash.substr(0,hash.find(delimiter));
		hash.erase(0,username.length()+delimiter.length());
		password = hash.substr(0,hash.find(delimiter));
		hash.erase(0,password.length()+delimiter.length());
		full_name = hash.substr(0,hash.find(delimiter));
		hash.erase(0,full_name.length()+delimiter.length());
		profile = hash.substr(0,hash.find(delimiter));
		leer_perfil();		
	}
};

int print_logo(){
	ifstream input("logo.txt");
	string s,line;
	while (getline(input,line)){	
		cout << line << endl;
	 }	
	 return 0;
};

void imprimir_opciones(Usuario sesion){
	ifstream in("perfiles.txt");
	 string s,reg;
	 int contador;
	 list<Usuario> usuarios;
	 // Cargamos los usuarios guardados
	 contador = 0;
	 while (getline(in,reg)){	
		Usuario u;
		u.decodificar(reg);
		usuarios.push_back(u);
		contador = contador + 1;
	 }
};


int inicio(){
cout << "Modulo en contruccion ... " << endl;
return 0;
};

int pedidos(){
cout << "Modulo en contruccion ... " << endl;
return 0;
};

int pagos(){
cout << "Modulo en contruccion ... " << endl;
return 0;
};

int finanzas(){
cout << "Modulo en contruccion ... " << endl;
return 0;
};

int mantenimiento(){
cout << "Modulo en contruccion ... " << endl;
return 0;
};

int moscelaneos(){
cout << "Modulo en contruccion ... " << endl;
return 0;
};
int menu_principal(Usuario sesion){
  int opcion;
  opcion = 0;
  cout << "Menu para " << sesion.full_name << endl;
  cout << "0. Salir" << endl;
  cout << "1. Inicio" << endl;
  cout << "2. Pedidos " << endl;
  cout << "3. pagos " << endl;
  cout << "4. finanzar " << endl;
  cout << "5. mantenimiento " << endl;
  cout << "6. miscelaneos " << endl;
  cout << "Seleccionar opcion:";
  cin >> opcion;
  switch(opcion){	
  case 1 :
  	inicio();
  	break;
  case 2 :
  	pedidos();
  	break;
  default:
  cout << "Opcion invalida." << endl;	 
  }
  cout << endl;

  return 1;
};
// Metodo que retorna el usuario de sesion
Usuario login(list<Usuario> usuarios){
  //cout << "TOTAL DE USUARIOS" << usuarios.size() << endl; 
  list<Usuario>::iterator it;
  string user;
  string pass;
  int ok = 0;
  Usuario sesion; 
  // comparar hasta encontrar igualdades y cambiar ok a 1
  while (ok == 0){
  cout << "Ingrese su usuario:";
  cin >> user;
  cout << "Ingrese su password:";
  cin >> pass;
	it = usuarios.begin();
	// Hasta recorrer todos los emementos
	while(it != usuarios.end()){ 
		if (user.compare(it->username) == 0) {
			// Reiniciamos en iterador
			it = usuarios.begin();
			// Comparamos los passwords
			while(it != usuarios.end()){
				if (pass.compare(it->password) == 0){
					// Valores correctos
					ok = 1;
  					sesion.decodificar(it->text_encoded);
  					cout << "Bienvenido " << sesion.full_name << endl;	
  					//menu_principal();
					break;
				}
				it++;
			}
			break;
		}
		it++;
	}
  cout << ok << endl;
  }
  return sesion;
};

int main(){
 int logeo;
 Usuario sesion;
 // Usando comandos unix
 system("clear");
 //system("cat logo.txt");
 print_logo();
 list<Usuario> usuarios;
 //Usuario usuarios[10]; 
 ifstream in("usuarios.txt");
 string s,reg;
 int contador;
 // Cargamos los usuarios guardados
 contador = 0;
 while (getline(in,reg)){	
	Usuario u;
	u.decodificar(reg);
	usuarios.push_back(u);
	contador = contador + 1;
 }
sesion = login(usuarios); 
menu_principal(sesion);
 //if (login(usuarios)==1){
 //	menu_principal();
 //}
 return 0;
}
