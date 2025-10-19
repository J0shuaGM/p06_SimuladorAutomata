// Universidad de La Laguna
// Escuela Superior de Ingenierıa y Tecnologıa
// Grado en Ingenierıa Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 6: Diseño e implementación deun simulador de autómatas finitos
// Autor: Joshua Gomez Marrero
// Correo: alu0101477398@ull.edu.es
// Fecha: 17/10/2025

#include <iostream>
#include <map>
#include <set>
#include <fstream>

#include "automata.h"



/**
 * @brief Constructor parametrizado de la clase Automata
 * @param fichero Cadena que contiene el nombre del fichero con los datos 
*/
Automata::Automata(const std::string& fichero) {
  std::ifstream input(fichero); 
  if(!input.is_open()) {
    std::cerr << "El fichero no se pudo abrir" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string linea_alfabeto, linea_estados, linea_inicio;
  std::getline(input, linea_alfabeto);
  std::getline(input, linea_estados);
  std::getline(input, linea_inicio);
  alfabeto_ = Alfabeto(linea_alfabeto);
  numero_estados_ = std::stoi(linea_estados); 
  estado_inicial_ = std::stoi(linea_inicio);
  for(int i = 0; i < numero_estados_; i++) {
    std::string linea; 
    std::getline(input, linea); 
    Estado estado = Estado(linea);
    estados_.insert({estado.getNombre(), estado});
    if(estado.getFinal()) {
      estados_finales_.insert(estado.getNombre());
    }
  }
  input.close();
}



/**
 * @brief Metodo que Simula el funcionamiento del automata para comporbar cadenass
 * @param cadena Objeto Cadena a comprobar por el automata
 * @return bool que determina si una cadena es o no acpetada por el automata
*/
const bool Automata::Simulacion(Cadena cadena) {
  std::vector<char> simbolos = cadena.getCadena();
  std::set<int> estados_actuales = {estado_inicial_};

  //Recorremos cada simbolo de la cadena
  for(char c : simbolos) {
    std::set<int> siguientes;

    //Para cada estado actual buscamos transiciones con ese simbolo
    for(int e : estados_actuales) {
      const auto& transiciones = estados_.at(e).getTransiciones();
      auto rango = transiciones.equal_range(c);
      for (auto it = rango.first; it != rango.second; ++it) {
        int destino = it->second;
        siguientes.insert(destino);
      }
    }
    estados_actuales = std::move(siguientes);

    //Si en algun momento no hay estados posibles, podemos cortar
    if (estados_actuales.empty()) return false;
  }
  
  //Finalmente buscamos si el estado actual es final para aceptar
  for(int e : estados_actuales) {
    if (estados_finales_.count(e)) return true;
  }
  return false;
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