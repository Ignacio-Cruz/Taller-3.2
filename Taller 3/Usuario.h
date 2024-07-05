#pragma once
#include <string>
#include <vector>
#include <tuple>
#include "Transferencia.h"
class Usuario
{

private:
	std::string nombre;
	std::string contrasena;
	int monto;
	
	// arboles
	Transferencia* transfe;  // arbol completo 
	
	std::vector<std::string> fechas;
	// obtener ruts
	std::vector<std::string> ruts;
	std::vector<std::string> FechasHoras;

	void ingresarfechas(std::string fecha);
	void ingresarFechaHora(std::string FechaHora);
	void ingresarRuts(std::string ruts);
	 

public:
	
	//constructor
	Usuario(std::string nombre, std::string contrasena);

	// destructor
	~Usuario();

	//gets
	std::string getNombre();
	std::string getContrasena();
	int getMonto();
	Transferencia* getArbol();
	std::vector<std::string> getRuts();

	// sets
	void setNombre(std::string nom);
	void setContrasena(std::string cont);
	void setMonto(int monto);

	int obtenerAltura(Transferencia* nodo);

	int obtenerFactorBalanceo(Transferencia* nodo);

	Transferencia* rotarDerecha(Transferencia* y);

	Transferencia* rotarIzquierda(Transferencia* x);

	Transferencia* balancearNodo(Transferencia* nodo);

	// transferencias
	void ingresarTransferencia(Transferencia* nuevaTrans);
	void MostrarFechas();
	void VerDepositosOrdenados(Transferencia* act , int Lugar);
	void MostrarVerDepositosFavor(Transferencia* act, std::string FechaHora);
	void MostrarVerDepositosContra(Transferencia* act, std::string FechaHora);
	void MostrarTodosLosDepositos(Transferencia* act, std::string FechaHora);
	void VerID(Transferencia* root);
	void ObtenerBoltaID(Transferencia* act,std::string ID);

	//ver informe
	std::vector<std::string> mostrarAnos(); // mostrar años para ver la transferencia
	bool existeEnVector(std::vector<std::string> ver, std::string linea);
	void informeAnual(Transferencia* arbol ,std::string ingresar,int total);
	int Mostrar(Transferencia* act, std::string FechaHora,int monto);
	std::vector<std::string> mostrarMeses(std::string ingresarA);
	void informeMensual(Transferencia* arbol , std::string ano1 , std::string mes);

	// Evaluar estafa
	void evaluarestafas(Transferencia* act);

};

