# Taller-3.2
ethan alexis Astorga Contreras , 20718176-5 , ethan.astorga@alumnos.ucn.cl ignacio Hector Cruz Reyes , 21127029-2 , ignacio.cruz01@alumnos.ucn.cl
Taller 3 - Sistema Bancario
Descripción
Este es un sistema bancario simple escrito en C++. Permite a los usuarios crear cuentas, iniciar sesión, depositar fondos y ver su historial de transacciones. También incluye funciones para buscar transacciones por ID y generar informes financieros.

Características
Registro de Usuario: Crear nuevas cuentas de usuario.
Inicio de Sesión de Usuario: Iniciar sesión usando una cuenta de usuario registrada.
Depositar Fondos: Depositar fondos en la cuenta de otro usuario.
Ver Transacciones: Ver el historial de transacciones, incluyendo depósitos y transferencias.
Buscar Transacciones: Buscar transacciones por ID.
Generar Informes: Generar informes financieros anuales y mensuales.
Detección de Fraude: Evaluar posibles actividades fraudulentas.
Estructura de Archivos
main.cpp: Archivo principal donde comienza y termina la ejecución del programa.
Usuario.h: Archivo de encabezado que contiene la definición de la clase Usuario.
Dependencias
Biblioteca estándar de C++: <iostream>, <vector>, <fstream>, <sstream>, <chrono>, <ctime>, <iomanip>, <random>
______________________________________________________________________________________________________________________________________-
Clase Usuario
La clase Usuario representa a un usuario de un banco, incluyendo sus detalles personales, su balance, y sus transferencias. La clase maneja la lógica de las transferencias utilizando un árbol balanceado (AVL tree).

Miembros Privados
nombre: std::string
El nombre del usuario.
contrasena: std::string
La contraseña del usuario.
monto: int
El balance de la cuenta del usuario.
transfe: Transferencia*
Puntero a la raíz del árbol de transferencias.
fechas: std::vector<std::string>
Vector que almacena las fechas de las transferencias.
ruts: std::vector<std::string>
Vector que almacena los ruts asociados a las transferencias.
FechasHoras: std::vector<std::string>
Vector que almacena las fechas y horas de las transferencias.

Métodos Privados
ingresarfechas(std::string fecha)
Método para ingresar una fecha al vector fechas.
ingresarFechaHora(std::string FechaHora)
Método para ingresar una fecha y hora al vector FechasHoras.
ingresarRuts(std::string ruts)
Método para ingresar un rut al vector ruts.
Métodos de Balanceo del Árbol
int obtenerAltura(Transferencia nodo)*
Devuelve la altura de un nodo en el árbol.
int obtenerFactorBalanceo(Transferencia nodo)*
Devuelve el factor de balanceo de un nodo en el árbol.
Transferencia rotarDerecha(Transferencia y)**
Realiza una rotación a la derecha en el árbol.
Transferencia rotarIzquierda(Transferencia x)**
Realiza una rotación a la izquierda en el árbol.
Transferencia balancearNodo(Transferencia nodo)**
Balancea un nodo en el árbol.
Métodos de Transferencias
void ingresarTransferencia(Transferencia nuevaTrans)*
Ingresa una nueva transferencia al árbol.
void MostrarFechas()
Muestra las fechas de las transferencias.
void VerDepositosOrdenados(Transferencia act, int Lugar)*
Muestra los depósitos ordenados.
void MostrarVerDepositosFavor(Transferencia act, std::string FechaHora)*
Muestra los depósitos a favor del usuario.
void MostrarVerDepositosContra(Transferencia act, std::string FechaHora)*
Muestra los depósitos en contra del usuario.
void MostrarTodosLosDepositos(Transferencia act, std::string FechaHora)*
Muestra todos los depósitos.
void VerID(Transferencia root)*
Muestra las transferencias por ID.
void ObtenerBoltaID(Transferencia act, std::string ID)*
Obtiene una boleta por ID.
Métodos de Informes
std::vectorstd::string mostrarAnos()
Muestra los años disponibles para ver las transferencias.
bool existeEnVector(std::vectorstd::string ver, std::string linea)
Verifica si una línea existe en un vector.
void informeAnual(Transferencia arbol, std::string ingresar, int total)*
Genera un informe anual.
int Mostrar(Transferencia act, std::string FechaHora, int monto)*
Muestra una transferencia específica.
std::vectorstd::string mostrarMeses(std::string ingresarA)
Muestra los meses disponibles dentro de un año.
void informeMensual(Transferencia arbol, std::string ano1, std::string mes)*
Genera un informe mensual.
Clase Transferencia
La clase Transferencia representa una transacción entre cuentas, almacenando detalles como ID, cuentas involucradas, monto, fecha y hora de la transacción. Además, incluye punteros para mantener la estructura de un árbol y una variable para la altura del nodo en estructuras balanceadas como AVL.

Miembros Privados
ID: std::string
Identificador único de la transferencia.
CuentaOrigen: std::string
Cuenta desde donde se realiza la transferencia.
CuentaDestino: std::string
Cuenta hacia donde se realiza la transferencia.
monto: int
Monto transferido.
Fecha: std::string
Fecha de la transferencia.
hora: std::string
Hora de la transferencia.
derecha: Transferencia*
Puntero al nodo derecho en la estructura del árbol.
izquierda: Transferencia*
Puntero al nodo izquierdo en la estructura del árbol.
altura: int
Altura del nodo en la estructura del árbol, utilizado para el balanceo en AVL.
Métodos Adicionales
void generarBoleta()
Genera una boleta de la transferencia.
int getAltura()
Devuelve la altura del nodo en el árbol.
void setAltura(int altura)
Establece la altura del nodo en el árbol.
void DataInforme()
Método para obtener los datos de la transferencia para un informe.
