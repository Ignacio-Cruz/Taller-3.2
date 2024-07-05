#include "Usuario.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <sstream>

void Usuario::ingresarfechas(std::string fecha)
{
	bool bandera = true;
	for (int i = 0; i < fechas.size(); i++) {
		if (fechas[i] == fecha) {
			bandera = false;
			break;
		}
	}
	if (bandera) {
		fechas.push_back(fecha);
	}
}

void Usuario::ingresarFechaHora(std::string FechaHora)
{
	bool bandera = true;
	for (int i = 0; i < FechasHoras.size(); i++) {
		if (FechasHoras[i] == FechaHora) {
			bandera = false;
			break;
		}
	}
	if (bandera) {
		FechasHoras.push_back(FechaHora);
	}

}

void Usuario::ingresarRuts(std::string rut)
{
	bool bandera = true;
	for (int i = 0; i < ruts.size(); i++) {
		if (ruts[i] == rut) {
			bandera = false;
			break;
		}
	}
	if (bandera) {
		ruts.push_back(rut);
	}
}

Usuario::Usuario(std::string nombre, std::string contrasena)
{
	this->nombre = nombre;
	this->contrasena = contrasena;
	monto = 0;
	transfe = nullptr;
}

Usuario::~Usuario() {}

std::string Usuario::getNombre()
{
	return nombre;
}

std::string Usuario::getContrasena()
{
	return contrasena;
}

int Usuario::getMonto()
{
	return monto;
}

Transferencia* Usuario::getArbol()
{
	return transfe;
}

std::vector<std::string> Usuario::getRuts()
{
	return ruts;
}

void Usuario::setNombre(std::string nom)
{
	nombre = nom;
}

void Usuario::setContrasena(std::string cont)
{
	contrasena = cont;
}

void Usuario::setMonto(int monto)
{
	this->monto = monto;
}

int Usuario::obtenerAltura(Transferencia* nodo) {
	return nodo ? nodo->getAltura() : 0;
}

// Función para obtener el factor de balanceo de un nodo
int Usuario::obtenerFactorBalanceo(Transferencia* nodo) {
	return nodo ? obtenerAltura(nodo->getIzquierda()) - obtenerAltura(nodo->getDerecha()) : 0;
}

// Rotación a la derecha
Transferencia* Usuario::rotarDerecha(Transferencia* y) {
	Transferencia* x = y->getIzquierda();
	Transferencia* T2 = x->getDerecha();

	// Realizar rotación
	x->setDerecha(y);
	y->setIzquierda(T2);

	// Actualizar alturas
	y->setAltura(std::max(obtenerAltura(y->getIzquierda()), obtenerAltura(y->getDerecha())) + 1);
	x->setAltura(std::max(obtenerAltura(x->getIzquierda()), obtenerAltura(x->getDerecha())) + 1);

	// Retornar nueva raíz
	return x;
}

// Rotación a la izquierda
Transferencia* Usuario::rotarIzquierda(Transferencia* x) {
	Transferencia* y = x->getDerecha();
	Transferencia* T2 = y->getIzquierda();

	// Realizar rotación
	y->setIzquierda(x);
	x->setDerecha(T2);

	// Actualizar alturas
	x->setAltura(std::max(obtenerAltura(x->getIzquierda()), obtenerAltura(x->getDerecha())) + 1);
	y->setAltura(std::max(obtenerAltura(y->getIzquierda()), obtenerAltura(y->getDerecha())) + 1);

	// Retornar nueva raíz
	return y;
}

// Función para balancear el nodo
Transferencia* Usuario::balancearNodo(Transferencia* nodo) {
	nodo->setAltura(std::max(obtenerAltura(nodo->getIzquierda()), obtenerAltura(nodo->getDerecha())) + 1);

	int balance = obtenerFactorBalanceo(nodo);

	// Caso izquierda izquierda
	if (balance > 1 && obtenerFactorBalanceo(nodo->getIzquierda()) >= 0)
		return rotarDerecha(nodo);

	// Caso izquierda derecha
	if (balance > 1 && obtenerFactorBalanceo(nodo->getIzquierda()) < 0) {
		nodo->setIzquierda(rotarIzquierda(nodo->getIzquierda()));
		return rotarDerecha(nodo);
	}

	// Caso derecha derecha
	if (balance < -1 && obtenerFactorBalanceo(nodo->getDerecha()) <= 0)
		return rotarIzquierda(nodo);

	// Caso derecha izquierda
	if (balance < -1 && obtenerFactorBalanceo(nodo->getDerecha()) > 0) {
		nodo->setDerecha(rotarDerecha(nodo->getDerecha()));
		return rotarIzquierda(nodo);
	}

	return nodo;
}

void Usuario::ingresarTransferencia(Transferencia* nuevaTrans)
{
	if (!transfe) {
		transfe = nuevaTrans;
	}
	else {
		// Pila para realizar la inserción y balanceo sin recursión
		std::vector<Transferencia*> path;
		Transferencia* current = transfe;

		// Encuentra la posición correcta para la nueva transferencia
		while (current) {
			path.push_back(current);
			if (nuevaTrans->getMonto() < current->getMonto()) {
				if (!current->getIzquierda()) {
					current->setIzquierda(nuevaTrans);
					break;
				}
				current = current->getIzquierda();
			}
			else {
				if (!current->getDerecha()) {
					current->setDerecha(nuevaTrans);
					break;
				}
				current = current->getDerecha();
			}
		}

		// Balancea el árbol AVL
		for (auto it = path.rbegin(); it != path.rend(); ++it) {
			*it = balancearNodo(*it);
		}

		// Actualiza la raíz en caso de que haya cambiado
		transfe = path.front();
	}
	std::string FechaHora = nuevaTrans->getFecha() + "," + nuevaTrans->getHora();
	ingresarFechaHora(FechaHora);
	ingresarfechas(nuevaTrans->getFecha());
	if (nombre == nuevaTrans->getCuentaD()) {
		ingresarRuts(nuevaTrans->getCuentaO());
	}
	else {
		ingresarRuts(nuevaTrans->getCuentaD());
	}
}

void Usuario::MostrarFechas()
{
	for (int i = 0; i < fechas.size(); i++) {
		std::cout << fechas[i] << std::endl;
	}
}

void Usuario::VerDepositosOrdenados(Transferencia* act, int Lugar)
{
	for (int i = FechasHoras.size()-1;i>=0;i--) {
		if (Lugar == 0) { // Depositos a favor
			MostrarVerDepositosFavor(act, FechasHoras[i]);
		}
		else if (Lugar == 1) { // Depositos en contra
			MostrarVerDepositosContra(act, FechasHoras[i]);
		}
		else if (Lugar == 2) { // Todos los depositos
			MostrarTodosLosDepositos(act, FechasHoras[i]);
		}
	}
}

void Usuario::MostrarVerDepositosFavor(Transferencia* act,std::string FechaHora)
{

	if (act == nullptr) {
		return;
	}

	MostrarVerDepositosFavor(act->getIzquierda(), FechaHora);

	std::string FechaActualHora = act->getFecha() + "," + act->getHora();

	if (act->getMonto() > 0 && FechaActualHora == FechaHora) {
		act->generarBoleta();
	}

	MostrarVerDepositosFavor(act->getDerecha(), FechaHora);
}

void Usuario::MostrarVerDepositosContra(Transferencia* act, std::string FechaHora)
{
	if (act == nullptr) {
		return;
	}

	MostrarVerDepositosContra(act->getIzquierda(), FechaHora);
	std::string FechaActualHora = act->getFecha() + "," + act->getHora();
	
	if (act->getMonto() < 0 && FechaActualHora == FechaHora) {
		act->generarBoleta();
	}

	MostrarVerDepositosContra(act->getDerecha(), FechaHora);
}

void Usuario::MostrarTodosLosDepositos(Transferencia* act, std::string FechaHora)
{
	if (act == nullptr) {
		return;
	}

	MostrarTodosLosDepositos(act->getIzquierda(), FechaHora);
	std::string FechaActualHora = act->getFecha() + "," + act->getHora();

	if (FechaActualHora == FechaHora) {
		act->generarBoleta();
	}

	MostrarTodosLosDepositos(act->getDerecha(), FechaHora);
}

void Usuario::VerID(Transferencia* root)
{
	if (root == nullptr) {
		return;
	}
	
	std::cout << "ID: " << root->getID() << std::endl;
	
	VerID(root->getIzquierda());
	VerID(root->getDerecha());
}

void Usuario::ObtenerBoltaID(Transferencia* act, std::string ID)
{
	if (act == nullptr) {
		return;
	}
	if (act->getID() == ID) {
		act->generarBoleta();
	}
	ObtenerBoltaID(act->getIzquierda(), ID);
	ObtenerBoltaID(act->getDerecha(), ID);
}

bool Usuario::existeEnVector(std::vector<std::string> ver , std::string linea)
{
	bool bandera = false;
	for (int i = 0;i<ver.size();i++) {
		if (ver[i] == linea) {
			bandera = true;
			return bandera;
		}
	
	}
	return bandera;
}

void Usuario::informeAnual(Transferencia* arbol , std::string ingresar ,int total)
{
	
	for (int i = 0;i < FechasHoras.size();i++) {
		std::string linea = FechasHoras[i];

		std::string token; // token para poder obtener el string

		std::istringstream iss(linea); // llamamos al istingstream para poder separarlo

		std::vector<std::string> Datos; // donde vamos a guardar todos los datos del Cliente

		while (std::getline(iss, token, ',')) { // hacemos todas las separaciones y las guardamos

			Datos.push_back(token);
		}

		std::string ano = Datos[0];
		
		std::istringstream h(ano);

		std::vector<std::string> Datos2;

		while (std::getline(h, token, '-')) { // hacemos todas las separaciones y las guardamos

			Datos2.push_back(token);
		}

		if (Datos2[2] == ingresar) {
			total += Mostrar(arbol,linea,0);
		}

	}

	std::cout << std::endl;

	std::cout << "Total anual (" << ingresar << "): " << total << std::endl;
	
	std::cout << std::endl;
}

int Usuario::Mostrar(Transferencia* act, std::string FechaHora,int monto)
{

	if (act == nullptr) {
		return monto;
	}
	
	std::string FechaActualHora = act->getFecha() + "," + act->getHora();

	if (FechaActualHora == FechaHora) {
		
		act->DataInforme();
		monto = act->getMonto();
		return monto;
	}
	
	monto = Mostrar(act->getIzquierda(), FechaHora,monto);
	monto = Mostrar(act->getDerecha(), FechaHora,monto);
	
	return monto;
}

std::vector<std::string> Usuario::mostrarMeses(std::string ingresarA)
{
	std::vector<std::string> meses;
	for (int i = 0; i < fechas.size(); i++) {
		std::string linea = fechas[i];

		std::string token; // token para poder obtener el string

		std::istringstream iss(linea); // llamamos al istingstream para poder separarlo

		std::vector<std::string> Datos; // donde vamos a guardar todos los datos del Cliente

		while (std::getline(iss, token, '-')) { // hacemos todas las separaciones y las guardamos

			Datos.push_back(token);
		}

		std::string mes = Datos[1];

		if (!existeEnVector(meses, mes) && ingresarA == Datos[2]) {
			std::cout << "Mes : " << mes << std::endl;
			meses.push_back(mes);
		}

	}
	return meses;
}

void Usuario::informeMensual(Transferencia* arbol,std::string ano1, std::string mes)
{
	int total = 0;
	for (int i = 0; i < FechasHoras.size(); i++) {
		std::string linea = FechasHoras[i];

		std::string token; // token para poder obtener el string

		std::istringstream iss(linea); // llamamos al istingstream para poder separarlo

		std::vector<std::string> Datos; // donde vamos a guardar todos los datos del Cliente

		while (std::getline(iss, token, ',')) { // hacemos todas las separaciones y las guardamos

			Datos.push_back(token);
		}

		std::string ano = Datos[0];

		std::istringstream h(ano);

		std::vector<std::string> Datos2;

		while (std::getline(h, token, '-')) { // hacemos todas las separaciones y las guardamos

			Datos2.push_back(token);
		}

		if (Datos2[2] == ano1 && Datos2[1] == mes ) {
			total += Mostrar(arbol, linea, 0);
		}

	}

	std::cout << std::endl;

	std::cout << "Total Mensual (" << mes << "): " << total << std::endl;

	std::cout << std::endl;
}

std::vector<std::string> Usuario::mostrarAnos()
{
	std::vector<std::string> anos;
	for (int i = 0; i < fechas.size(); i++) {
		std::string linea = fechas[i];

		std::string token; // token para poder obtener el string

		std::istringstream iss(linea); // llamamos al istingstream para poder separarlo

		std::vector<std::string> Datos; // donde vamos a guardar todos los datos del Cliente

		while (std::getline(iss, token, '-')) { // hacemos todas las separaciones y las guardamos

			Datos.push_back(token);
		}

		std::string ano = Datos[2];

		if (!existeEnVector(anos , ano)) {
			std::cout << "Año : " << ano << std::endl;
			anos.push_back(ano);
		}

	}
	return anos;
}


void Usuario::evaluarestafas(Transferencia* act) {
	if (!act) return;

	// Vector para almacenar todas las transferencias
	std::vector<Transferencia*> todasTransferencias;
	std::vector<Transferencia*> pila;

	// Recorrido en preorden para obtener todas las transferencias
	pila.push_back(act);
	while (!pila.empty()) {
		Transferencia* nodo = pila.back();
		pila.pop_back();
		todasTransferencias.push_back(nodo);
		if (nodo->getDerecha()) pila.push_back(nodo->getDerecha());
		if (nodo->getIzquierda()) pila.push_back(nodo->getIzquierda());
	}

	// Vectores para contar las transferencias recibidas y enviadas por cada cuenta
	std::vector<std::string> cuentasRecibidas;
	std::vector<int> cantidadRecibidas;
	std::vector<std::string> cuentasEnviadas;
	std::vector<int> cantidadEnviadas;

	// Función para encontrar el índice de una cuenta en un vector
	auto encontrarIndice = [](const std::vector<std::string>& cuentas, const std::string& cuenta) -> int {
		for (int i = 0; i < cuentas.size(); i++) {
			if (cuentas[i] == cuenta) return i;
		}
		return -1;
		};

	// Contar las transferencias recibidas y enviadas por cada cuenta
	for (Transferencia* trans : todasTransferencias) {
		std::string cuentaD = trans->getCuentaD();
		std::string cuentaO = trans->getCuentaO();

		int indiceD = encontrarIndice(cuentasRecibidas, cuentaD);
		if (indiceD == -1) {
			cuentasRecibidas.push_back(cuentaD);
			cantidadRecibidas.push_back(1);
		}
		else {
			cantidadRecibidas[indiceD]++;
		}

		int indiceO = encontrarIndice(cuentasEnviadas, cuentaO);
		if (indiceO == -1) {
			cuentasEnviadas.push_back(cuentaO);
			cantidadEnviadas.push_back(1);
		}
		else {
			cantidadEnviadas[indiceO]++;
		}
	}

	// Determinar cuentas sospechosas
	std::vector<std::string> cuentasSospechosas;

	const int umbral = 2; // Ajustar el umbral según sea necesario

	for (int i = 0; i < cuentasRecibidas.size(); i++) {
		if (cantidadRecibidas[i] >= umbral && cuentasRecibidas[i] != nombre) {
			cuentasSospechosas.push_back(cuentasRecibidas[i]);
		}
	}

	for (int i = 0; i < cuentasEnviadas.size(); i++) {
		if (cantidadEnviadas[i] >= umbral && cuentasEnviadas[i] != nombre) {
			cuentasSospechosas.push_back(cuentasEnviadas[i]);
		}
	}

	// Imprimir cuentas sospechosas
	std::cout << "Cuentas sospechosas:" << std::endl;
	for (const std::string& cuentaS : cuentasSospechosas) {
		std::cout << cuentaS << std::endl;
	}
}


