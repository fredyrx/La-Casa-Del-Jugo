#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

struct Usuario {
	string delimiter;
	string username,password,full_name,profile;
	Usuario(string hash){
		delimiter = '|';
		// A partir de la cadena separamos los parametros
		username = hash.substr(0,hash.find(delimiter));
		hash.erase(0,username.length()+delimiter.length());
		password = hash.substr(0,hash.find(delimiter));
		hash.erase(0,password.length()+delimiter.length());
		full_name = hash.substr(0,hash.find(delimiter));
		hash.erase(0,full_name.length()+delimiter.length());
		profile = hash.substr(0,hash.find(delimiter));
	};
};

int print_logo(){
	ifstream input("usuarios.txt");
	string s,line;
	while (getline(input,line)){	
		cout << line << endl;
	 }	
	 return 0;
};

int main(){
 print_logo;
 char user;
 char password;
 string users[10];
 string passwords[10];
 string names[10];
 string profiles[10];
 ifstream in("usuarios.txt");
 string s,reg;
 int contador;
 // Usando comandos unix
 system("clear");
 system("cat logo.txt");
 // Cargamos los usuarios guardados
 contador = 0;
 while (getline(in,reg)){	
	Usuario u(reg);
	users[contador] = u.username;
	passwords[contador] = u.password;
	names[contador] = u.full_name;
	profiles[contador] = u.profile;

	cout << users[contador] << endl;
	contador = contador + 1;
 }
  cout << "Ingrese su usuario:";
  cin >> user;
  cout << "1. Seguridad del Sistema";
  cout << "2. Crear ";
 return 0;
}
