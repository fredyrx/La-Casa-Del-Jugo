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

class UsuarioPermiso {
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
	list<UsuarioPermiso> perfil;
	Usuario(){
		//decodificar(hash);
		// A partir de la cadena separamos los parametros
	};
	void leer_perfil(){
		//cout << "Leyendo perfil de usuario ..." << endl;
		ifstream in("perfiles.txt");
	 	string s,reg;
	 	int contador;
	 	// Cargamos los permisos segun perfil
	 	contador = 0;
	 	while (getline(in,reg)){	
			UsuarioPermiso opcion;
			opcion.decodificar(reg);
			if (username.compare(opcion.username)==0){
				perfil.push_back(opcion);
			} 
			//opcion.to_string();
			contador = contador + 1;
	 	}
	 	//cout << "Total de permisos: " << perfil.size() << endl;
	}

	// Metodo no usado
	void cargar_modulos(){
		list<UsuarioPermiso>::iterator it;
		it = perfil.begin();
		// Hasta recorrer todos los emementos
		while(it != perfil.end()){
			cout << "#Mis permisos" << endl;
			cout << it->username << " " << it->codigo << endl;
			it++;
		}
	}
	void cargar_permisos(){
		cout << "Cargando modulos de usuario ..." << endl;
		ifstream in("modulos.txt");
	 	string s,reg;
		list<UsuarioPermiso>::iterator it;
	 	int contador;
	 	// Cargamos los permisos segun perfil
	 	contador = 0;
	 	while (getline(in,reg)){	
			Permiso p;
			p.decodificar(reg);
			// Cramos iterador
			it = perfil.begin();
			while(it != perfil.end()){
				if (p.codigo.compare(it->codigo)==0){
					permisos.push_back(p);
					//cout << "permiso " << p.codigo << p.descripcion << "Fue guardado." << endl;
					break;
				}
				//cout << "#Mis permisos" << endl;
				//cout << it->username << " " << it->codigo << endl;
				it++;
			}
		//p.to_string();
	 	//cout << "Total de modulos: " << contador << p.codigo << p.descripcion << endl;
		contador = contador + 1;
	 	}
	}	
	
	void iniciar(){
		leer_perfil();
		cargar_permisos();
		//cargar_modulos();	
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
		//leer_perfil();
		//cargar_permisos();
		//cargar_modulos();		
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


int salir(){
cout << "Cerrando sesion de usuario " << endl;
return 0;
};

int inicio(){
cout << "Modulo en contruccion ...  " << endl;
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

int stock(){
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

int miscelaneos(){
cout << "Modulo en contruccion ... " << endl;
return 0;
};
int menu_principal(Usuario sesion){
  int opcion;
  //opcion = 0;
  list<Permiso> mis_permisos = sesion.permisos;
  list<Permiso>::iterator it;
	while (opcion!=0){
  		it = mis_permisos.begin();
	  //Mostrando la lista de modulos segun permisos
	  cout << "+---------------------+"<< endl;
	  cout << "|---MENU PRINCIPAL----|"<< endl;
	  cout << "+---------------------+"<< endl;
	  cout << "| 0." << " SALIR."<< endl;
	  while(it != mis_permisos.end()){
			cout << "| " << it->codigo << ". "<< it->descripcion << "." << endl;
			it++;
		}
	  cout << "+---------------------+"<< endl;
		cout << "Seleccionar:";
		cin >> opcion;
		switch(opcion){	
			 case 0 :
			 	salir();
			 	break;
			 case 1 :
			 	inicio();
			  	break;
			 case 2 :
			  	pedidos();
			  	break;
			 case 3 :
			  	pagos();
			  	break;
			 case 4 :
			  	stock();
			  	break;
			 case 5 :
			  	finanzas();
			  	break;
			 case 6 :
			  	mantenimiento();
			  	break;
			 case 7 :
			  	miscelaneos();
			  	break;
			 default:
		  		cout << "Opcion invalida." << endl;	 
	 	}
	}

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
  //cout << ok << endl;
  }
  return sesion;
};

int main(){
 list<Usuario> usuarios;
 Usuario sesion;
 string s,reg;
 int contador;
 // Cargamos los usuarios guardados
 contador = 0;
 ifstream in("usuarios.txt");
 while (getline(in,reg)){	
	Usuario u;
	u.decodificar(reg);
	usuarios.push_back(u);
	contador = contador + 1;
 }
// Usando comandos unix
system("clear");
print_logo();
sesion = login(usuarios); 
sesion.iniciar();
menu_principal(sesion);
return 0;
}
