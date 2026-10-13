// Universidad de La Laguna
// Escuela Superior de Ingenierıa y Tecnologıa
// Grado en Ingenierıa Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 6: Diseño e implementación de un simulador de DFAs
// Autor: Joshua Gomez Marrero
// Correo: alu0101477398@ull.edu.es
// Fecha: 17/10/2025

#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <iomanip>
#include <cctype>

#include "automata.h"



/**
 * @brief Lee la siguiente linea util del fichero, ignorando lineas vacias y comentarios (prefijo //)
 * @param input Flujo de entrada del fichero
 * @param linea Variable donde se almacena la linea leida
 * @return true si se ha leido una linea, false si se llego al final del fichero
*/
static bool LeerLinea(std::ifstream& input, std::string& linea) {
  while (std::getline(input, linea)) {
    size_t inicio = linea.find_first_not_of(" \t\r");
    if (inicio == std::string::npos) continue;
    if (linea.compare(inicio, 2, "//") == 0) continue;
    linea = linea.substr(inicio, linea.find_last_not_of(" \t\r") - inicio + 1);
    return true;
  }
  return false;
}



/**
 * @brief Muestra un mensaje de error en la definicion del DFA y termina el programa
 * @param mensaje Descripcion del error
*/
static void ErrorDefinicion(const std::string& mensaje) {
  std::cerr << "Error en la definicion del DFA: " << mensaje << std::endl;
  exit(EXIT_FAILURE);
}



/**
 * @brief Convierte una linea en un numero entero, abortando si no es valido
 * @param linea Linea a convertir
 * @param campo Nombre del campo, para el mensaje de error
 * @return El numero leido
*/
static int LeerEntero(const std::string& linea, const std::string& campo) {
  size_t procesados = 0;
  int numero = 0;
  try {
    numero = std::stoi(linea, &procesados);
  } catch (const std::exception&) {
    ErrorDefinicion(campo + " no es un numero valido: \"" + linea + "\"");
  }
  if (procesados != linea.size()) ErrorDefinicion(campo + " no es un numero valido: \"" + linea + "\"");
  return numero;
}



/**
 * @brief Constructor parametrizado de la clase Automata
 * @param fichero Cadena que contiene el nombre del fichero con los datos 
*/
Automata::Automata(const std::string& fichero) {
  std::ifstream input(fichero); 
  if(!input.is_open()) {
    std::cerr << "El fichero " << fichero << " no se pudo abrir" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string linea_alfabeto, linea_estados, linea_inicio;
  if (!LeerLinea(input, linea_alfabeto)) ErrorDefinicion("falta la linea del alfabeto");
  if (!LeerLinea(input, linea_estados)) ErrorDefinicion("falta la linea con el numero de estados");
  if (!LeerLinea(input, linea_inicio)) ErrorDefinicion("falta la linea con el estado de arranque");
  for (char simbolo : linea_alfabeto) {
    if (!std::isalnum(static_cast<unsigned char>(simbolo))) {
      ErrorDefinicion(std::string("el simbolo '") + simbolo + "' del alfabeto no es alfanumerico");
    }
  }
  alfabeto_ = Alfabeto(linea_alfabeto);
  numero_estados_ = LeerEntero(linea_estados, "El numero de estados");
  if (numero_estados_ <= 0) ErrorDefinicion("el DFA debe tener al menos un estado");
  estado_inicial_ = LeerEntero(linea_inicio, "El estado de arranque");
  for(int i = 0; i < numero_estados_; i++) {
    std::string linea; 
    if (!LeerLinea(input, linea)) {
      ErrorDefinicion("se esperaban " + std::to_string(numero_estados_) + " lineas de estados y solo hay " + std::to_string(i));
    }
    Estado estado = Estado(linea);
    if (estados_.count(estado.getNombre())) {
      ErrorDefinicion("el estado " + std::to_string(estado.getNombre()) + " esta definido mas de una vez");
    }
    estados_.insert({estado.getNombre(), estado});
    if(estado.getFinal()) {
      estados_finales_.insert(estado.getNombre());
    }
  }
  std::string sobrante;
  if (LeerLinea(input, sobrante)) {
    ErrorDefinicion("hay mas lineas de estados que el numero de estados indicado (" + std::to_string(numero_estados_) + ")");
  }
  input.close();
  Validar();
}



/**
 * @brief Comprueba que la definicion leida corresponde a un DFA correcto
*/
void Automata::Validar(void) {
  if (!estados_.count(estado_inicial_)) {
    ErrorDefinicion("el estado de arranque " + std::to_string(estado_inicial_) + " no es un estado del automata");
  }
  for (auto& par : estados_) {
    int id = par.first;
    if (id < 0 || id >= numero_estados_) {
      ErrorDefinicion("el estado " + std::to_string(id) + " no esta en el rango [0, " + std::to_string(numero_estados_ - 1) + "]");
    }
    const std::multimap<char, int> transiciones = par.second.getTransiciones();
    for (const auto& transicion : transiciones) {
      if (!alfabeto_.search(transicion.first)) {
        ErrorDefinicion(std::string("la transicion del estado ") + std::to_string(id) + " con el simbolo '" + transicion.first + "' usa un simbolo que no pertenece al alfabeto");
      }
      if (!estados_.count(transicion.second)) {
        ErrorDefinicion("la transicion del estado " + std::to_string(id) + " lleva al estado " + std::to_string(transicion.second) + ", que no existe");
      }
    }
    // En un DFA hay exactamente una transicion por cada simbolo del alfabeto
    for (char simbolo : alfabeto_.getSimbolos()) {
      size_t numero = transiciones.count(simbolo);
      if (numero != 1) {
        ErrorDefinicion(std::string("el estado ") + std::to_string(id) + " tiene " + std::to_string(numero) + " transiciones con el simbolo '" + simbolo + "' (debe tener exactamente una)");
      }
    }
  }
}



/**
 * @brief Metodo que Simula el funcionamiento del automata para comprobar cadenas, mostrando la traza
 * @param cadena Objeto Cadena a comprobar por el automata
 * @return bool que determina si una cadena es o no aceptada por el automata
*/
const bool Automata::Simulacion(Cadena cadena) {
  std::vector<char> simbolos = cadena.getCadena();
  if (cadena.longitud() == 0) simbolos.clear(); // La cadena vacia (&) no consume simbolos
  int estado_actual = estado_inicial_;

  std::cout << "Est. Actual  Entrada  Nuevo Est." << std::endl;
  //Recorremos cada simbolo de la cadena
  for(char c : simbolos) {
    //En un DFA hay una unica transicion para el estado actual y el simbolo
    int estado_siguiente = estados_.at(estado_actual).getTransiciones().find(c)->second;
    std::cout << std::setw(7) << estado_actual << std::setw(10) << c << std::setw(11) << estado_siguiente << std::endl;
    estado_actual = estado_siguiente;
  }
  
  //Finalmente comprobamos si el estado alcanzado es final para aceptar
  return estados_finales_.count(estado_actual) > 0;
}



/**
 * @brief Sobrecarga del insercion de extraccion para el objeto Automata
 * @param entrada Variable para recibir la entrada de datos
 * @param Automata Objeto automata que va a ser sobreescrito
 * @return entrada Retornamos el nuevo valor 
*/
std::istream& operator>>(std::istream& entrada, Automata& automata) {
  std::string nombre_fichero;
  entrada >> nombre_fichero;
  automata = Automata(nombre_fichero);
  return entrada;
}



/**
 * @brief Sobrecarga del operador de extraccion para el objeto Automata
 * @param entrada Variable para escribir la salida de datos
 * @param automata Objeto automata que va a ser sobreescrito
 * @return salida Retornamos el nuevo valor 
*/
std::ostream& operator<<(std::ostream& salida, const Automata& automata) {
  salida << "Alfabeto: " << automata.alfabeto_ << std::endl;
  salida << "Numero de estados: " << automata.numero_estados_ << std::endl;
  salida << "Estado inicial: " << automata.estado_inicial_ << std::endl;
  salida << "Estados finales: ";
  for (const int estado_final : automata.estados_finales_) {
    salida << estado_final << " ";
  }
  salida << std::endl;
  salida << "Estados y transiciones:" << std::endl;
  for (const auto& par : automata.estados_) {
    salida << par.second << std::endl;
  }
  return salida;
}