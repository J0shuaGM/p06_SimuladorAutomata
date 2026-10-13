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
#include <fstream>

#include "tools.h"

/**
 * @brief Funcion que explica como usar este programa 
 * @param argc Numero de argumentos pasados por linea de comandos
 * @param agrv Las cadenas que han sido pasadas por linea de comandos
*/
void Usage(int argc, char* argv[]) {
  if (argc == 3) return;
  if (argc == 2 && std::string(argv[1]) == "--help") {
    std::cout << "Este programa simula el comportamiento de un automata finito determinista (DFA)" << std::endl;
    std::cout << "Uso: ./p06_DFA_simulator input.dfa input.txt" << std::endl;
    std::cout << "Se necesitan dos ficheros, un .dfa que contenga la definicion del DFA y un .txt que contenga las cadenas a comprobar" << std::endl << std::endl;
    std::cout << helptext << std::endl;
    exit(EXIT_SUCCESS);
  }
  std::cerr << "Modo de empleo: ./p06_DFA_simulator input.dfa input.txt" << std::endl;
  std::cerr << "Pruebe 'p06_DFA_simulator --help' para más información." << std::endl;
  exit(EXIT_FAILURE);
}



/**
 * @brief Funcion encargada de gestionar la simulacion del automata
 * @param automata Objeto Automata que contiene los datos del automata
 * @param fichero_cadenas variable que indica el nombre del fichero que contiene las cadenas a ser comprobadas
*/
void SimulacionAutomata(Automata automata, const std::string& fichero_cadenas) {
  Alfabeto alfabeto_automata = automata.getAlfabeto();
  std::ifstream entrada(fichero_cadenas); 
  if(!entrada.is_open()) {
    std::cerr << "El fichero de cadenas no se ha podido abrir" << std::endl;
    return;
  }
  std::string cadenas; 
  while(std::getline(entrada, cadenas)) {
    if (!cadenas.empty() && cadenas.back() == '\r') cadenas.pop_back();
    if (cadenas.empty()) continue;
    Cadena cadena(cadenas);
    std::cout << "Cadena: " << cadena << std::endl;
    bool pertenece_alfabeto = true;
    if (cadenas != "&") {
      for(char c : cadena.getCadena()) {
        if (!alfabeto_automata.search(c)) pertenece_alfabeto = false;
      }
    }
    if (pertenece_alfabeto) {
      bool aceptada = automata.Simulacion(cadena);
      std::cout << std::endl << "Cadena de entrada " << (aceptada ? "ACEPTADA." : "RECHAZADA.") << std::endl;
    } else {
      std::cout << "La cadena contiene simbolos que no pertenecen al alfabeto " << alfabeto_automata << std::endl;
    }
    std::cout << std::endl;
  }
  entrada.close();
}
