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

#include "alfabeto.h"
#include "cadena.h"
#include "tools.h"
#include "automata.h"
#include "estado.h"

int main(int argc, char* argv[]) {
  Usage(argc, argv);
  std::string fichero_automata = argv[1];
  std::string fichero_cadenas = argv[2];
  Automata automata(fichero_automata);
  SimulacionAutomata(automata, fichero_cadenas);
  return 0;
}