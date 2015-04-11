#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <list>

using namespace std;
/* Metodos de apoyo */
string digit_to_string(int valor){
	/* Transforma un digito a string */
	string respuesta;
	switch(valor){
		case 1:
		respuesta = "1";
		break;
		case 2:
		respuesta = "2";
		break;
		case 3:
		respuesta = "3";
		break;
		case 4:
		respuesta = "4";
		break;
		case 5:
		respuesta = "5";
		break;
		case 6:
		respuesta = "6";
		break;
		case 7:
		respuesta = "7";
		break;
		default:
		respuesta = "0";
		break;
	}
return respuesta;
};

string pull_left(string cadena, int cantidad, string caracter=" "){
	/* funcion que rellena con caracteres a la derecha de una cadena */
	string respuesta = cadena;
	int longitud = cadena.length();
 	if (cantidad > longitud){
	 	for (int i=0;i < cantidad - longitud;i++){
			respuesta = respuesta + caracter;
			//cout << i << respuesta << endl;
		}
 	}else{
 		respuesta = cadena.substr(0,longitud-1);
 	}
	return respuesta;
};

void pausa(){
	string null;
	cout << "Enter para continuar ...";
	cin.ignore();
	cout << endl;
		
};
/* Objetos */
class Permiso {
	public:
	string delimiter;
	string codigo, descripcion;
	void decodificar(string hash){
		/* Tranforma cadela en atributos de objeto */
		delimiter = '|';
		codigo = hash.substr(0,hash.find(delimiter));
		hash.erase(0,codigo.length()+delimiter.length());
		descripcion = hash.substr(0,hash.find(delimiter));
		hash.erase(0,descripcion.length()+delimiter.length());
	}
	void to_string(){
		/* Imprime descripcion del objeto */
		cout << codigo << " " << descripcion << endl;
	}
};

class UsuarioPermiso {
	public:
	string delimiter;
	string username, codigo;
	void decodificar(string hash){
		/* Tranforma cadena en atributos de objeto */
		delimiter = '|';
		username = hash.substr(0,hash.find(delimiter));
		hash.erase(0,username.length()+delimiter.length());
		codigo = hash.substr(0,hash.find(delimiter));
		hash.erase(0,codigo.length()+delimiter.length());
	}
	void to_string(){
		/* Imprime descripción de objeto */
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
		/* Lee los los modulos habilitados para el usuario */
		ifstream in("db/perfiles.db");
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

	void cargar_permisos(){
		/* Carga los permisos según el perfil leido */
		//cout << "Cargando modulos de usuario ..." << endl;
		ifstream in("db/modulos.db");
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
		/* inicializa el objeto*/
		leer_perfil();
		cargar_permisos();
	}

	void decodificar(string hash="|||"){
		/* convierte cadena a parametros de objeto*/
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

	int tiene_permiso(int opcion){
		/* valida si el usuario tiene el permiso que ingresa*/
		int respuesta = 0;
		list<Permiso>::iterator it;
		it = permisos.begin();
		while(it != permisos.end()){ 
			if (it->codigo.compare(digit_to_string(opcion))==0){
				respuesta = 1;
				break;
			}
			it++;
		}
		return respuesta;
	}

	void to_string(){
	    //cout << "+---------+------------------+" << endl;
	    string row = "| " + pull_left(username,9," ") + "| " + pull_left(full_name,19," ") + "|" ;
		//cout << "|" << pull_left(username,10," ") << "|" << pull_left(full_name,20," ") << "|" << endl;
		cout << row << endl;
	}
};
int imprimir_logo(){
	/* Imprime logo de empresa */
	ifstream input("db/logo.db");
	string s,line;
	while (getline(input,line)){	
		cout << line << endl;
	 }	
	 return 0;
};

void imprimir_opciones(Usuario sesion){
	ifstream in("db/perfiles.db");
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
/* Metodos para mantenimiento */
void listar_usuarios(){
	string registro;
	ifstream in("db/usuarios.db");
	cout << "+----------+--------------------+" << endl;
	cout << "| CODIGO   | NOMBRE COMPLETO    |" << endl;
	cout << "+----------+--------------------+" << endl;
	while (getline(in,registro)){	
		Usuario u;
		u.decodificar(registro);
		u.iniciar();
		u.to_string();
	}
	cout << "+----------+--------------------+" << endl;
};

int mantenimiento(Usuario sesion){
	/* Menu de modulo de mantenimiento*/
	int opcion;
	opcion = 1;
	while (opcion != 0) {
		cout << "+---------------------+"<< endl;
		cout << "|----MANTENIMIENTO----|"<< endl;
		cout << "+---------------------+"<< endl;		
		cout << "| 0. ATRAS            |" << endl;	
		cout << "| 1. LISTAR USUARIOS  |" << endl;	
		cout << "| 2. LISTAR PERMISOS  |" << endl;	
		cout << "+---------------------+" << endl;	
		cout << "Seleccionar:";
		cin >> opcion;
		switch(opcion){
			case 0:
			break;
			case 1:
				listar_usuarios();
				break;
			case 2:
				cout << "Opción en construcción." << endl;
			break;
			default:
			cout << "Opción no existe" << endl;
		}
	}
	//cout << "Fin de mantenimieto" << endl;
return 0;
};

int miscelaneos(){
cout << "Modulo en contrucción ... " << endl;
return 0;
};
int menu_principal(Usuario sesion){
	/* Menu pricipal según perfil de usuario */
  int opcion = 1;
  //opcion = 0;
  list<Permiso> mis_permisos = sesion.permisos;
  list<Permiso>::iterator it;
	while (opcion!=0){
  		it = mis_permisos.begin();
	  //Mostrando la lista de modulos segun permisos
	  cout << "+---------------------+"<< endl;
	  cout << "|---MENU PRINCIPAL----|"<< endl;
	  cout << "+---------------------+"<< endl;
	  cout << "|" + pull_left(" 0 SALIR.",21)+ "|"<< endl;
	  while(it != mis_permisos.end()){
			//cout << "| " << it->codigo << " "<< it->descripcion << "." << endl;
			cout << "| " << pull_left(it->codigo + " " + it->descripcion + ".",20) << "|"<< endl;
			it++;
		}
	  cout << "+---------------------+"<< endl;
		cout << "Seleccionar:";
		cin >> opcion;
  		if (sesion.tiene_permiso(opcion)){
  			//cout << "tiene permiso" << endl;
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
				 	cout << "Modulo de mantenimiento" << endl;
				  	mantenimiento(sesion);
	 
				  	break;
				 case 7 :
				  	miscelaneos();
				  	break;
				 default:
			  		cout << "Opcion inválida." << endl;
		 	}
  		}else{
  			if (opcion!=0){
  				cout << "Ingrese una opción válida." << endl;
  			}else{
  				salir();
  			}
  		}
	}

  return 1;
};
// Metodo que retorna el usuario de sesion
Usuario login(list<Usuario> usuarios){
	/* Metodo que genera sesion de usuario correctamente logueado */
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
	/* Metodo principal */
	list<Usuario> usuarios;
	Usuario sesion;
	string s,reg;
	int contador;
	// Cargamos los usuarios guardados
	//contador = 0;
	ifstream in("db/usuarios.db");
	while (getline(in,reg)){	
		Usuario u;
		u.decodificar(reg);
		usuarios.push_back(u);
	//	contador = contador + 1;
	}
	// Usando comandos unix
	system("clear");
	imprimir_logo();
	pausa();
	sesion = login(usuarios); 
	sesion.iniciar();
	menu_principal(sesion);
	return 0;
}
