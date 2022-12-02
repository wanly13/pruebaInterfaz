  #include <iostream>
//#include <mysql.h>
//#include <openssl/md5.h>
//#include "md5.h"
#include<mysql.h>

using namespace std;
int q_estado;


void sql() {
	cout << "Conectar al SQL" << endl;
	MYSQL* conectar;
	MYSQL_ROW fila;
	MYSQL_RES* resultado;
	conectar = mysql_init(0);
	conectar = mysql_real_connect(conectar, "34.234.138.171", "root", "utec", "tienda", 8005, NULL, 0);
	cout << "Ingresa opcion: " << endl;
	cout << "1.Insert" << endl;
	cout << "2. select" << endl;
	int v;
	cin >> v;
	if (v == 1) {
		if (conectar) {
			cout << "Exito" << endl;
			cout << "Nombra el fabricante: ";
			string fabri;
			cin >> fabri;
			//INSERT INTO fabricantes(nombre) VALUES('Asus')
			string insert = "insert into fabricantes(nombre) values('" + fabri + "');";
			const char* i = insert.c_str();
			q_estado = mysql_query(conectar, i);
			if (!q_estado) {
				cout << "Ingreso exitoso" << endl;
			}
			else {
				cout << "error al insertar" << endl;
			}

		}
		else {
			cout << "Error" << endl;
		}
	}
	if (v == 2) {


		if (conectar) {
			cout << "Exito" << endl;
			string consulta = "select * from tienda.fabricantes";
			const char* c = consulta.c_str();
			q_estado = mysql_query(conectar, c);
			if (!q_estado) {
				resultado = mysql_store_result(conectar);
				int valor = 0;
				while (fila = mysql_fetch_row(resultado)) {
					cout << "iter " << valor << endl;
					cout << fila[0] << ", " << fila[1] << endl;

					valor++;
				}
			}
			else {
				cout << "error en la consulta" << endl;
			}


		}
		else {
			cout << "Error" << endl;
		}


	}

}






int main() {
	/*cout << "Conectar al SQL" << endl;
	MYSQL* conectar;
	MYSQL_ROW fila;
	MYSQL_RES* resultado;
	conectar=mysql_init(0);
	conectar = mysql_real_connect(conectar,"34.234.138.171","root","utec","tienda", 8005,NULL,0);
	cout << "Ingresa opcion: " << endl;
	cout << "1.Insert" << endl;
	cout << "2. select" << endl;
	int v;
	cin >> v;
	if (v == 1) {
		if (conectar) {
			cout << "Exito" << endl;
			cout << "Nombra el fabricante: ";
			string fabri;
			cin >> fabri;
			//INSERT INTO fabricantes(nombre) VALUES('Asus')
			string insert = "insert into fabricantes(nombre) values('"+ fabri +"');";
			const char* i = insert.c_str();
			q_estado = mysql_query(conectar, i);
			if (!q_estado) {
				cout << "Ingreso exitoso" << endl;
			}
			else {
				cout << "error al insertar" << endl;
			}

		}
		else {
			cout << "Error" << endl;
		}
	}
	if (v == 2) {

	
		if (conectar) {
			cout << "Exito" << endl;
			string consulta = "select * from tienda.fabricantes";
			const char* c = consulta.c_str();
			q_estado = mysql_query(conectar,c);
			if (!q_estado) {
				resultado = mysql_store_result(conectar);
				int valor = 0;
				while(fila=mysql_fetch_row(resultado)){
					cout << "iter " << valor << endl;
					cout << fila[0] << ", " << fila[1] << endl;
				
					valor++;
				}
			}
			else {
				cout << "error en la consulta" << endl;
			}
		

		}
		else{
			cout << "Error" << endl;
		}


	}*/

	sql();

}
