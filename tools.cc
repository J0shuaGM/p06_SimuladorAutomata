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

#include "tools.h"

/**
 * @brief Funcion que explica como usar este programa 
 * @param argc Numero de argumentos pasados por linea de comandos
 * @param agrv Las cadenas que han sido pasadas por linea de comandos
*/
void Usage(int argc, char* argv[]) {
  switch (argc) {
    case 1: {
      std::cerr << argv[0] << " Modo de empleo: ./Automata input.fa input.txt" << std::endl;
      std::cerr << "Use: " << argv[0] << " --help para mas información" << std::endl;
      exit(EXIT_SUCCESS);
      break;
    }
    case 2: {
      std::string parametro = argv[1];
      if (parametro == "--help") {
        std::cout << "Este programa simula el comportamiento de un automata" << std::endl;
        std::cout << "Se necesita dos fichero, un .fa que contenga la definicion del automata y un .txt que contenga las cadenas a comprobar" << std::endl;
        std::cout << helptext << std::endl;
        exit(EXIT_SUCCESS);
      }
      else {
        std::cerr << argv[0] << " Modo de empleo: ./Expreciones Entrada.cc Salida.txt" << std::endl;
        std::cerr << "Use: " << argv[0] << " --help para mas información" << std::endl;
        exit(EXIT_SUCCESS);
      }
      break;   
    }
    case 3: {
      break;
    }
    default: {
      std::cerr << argv[0] << " Modo de empleo: ./Expreciones Entrada.cc Salida.txt" << std::endl;
      std::cerr << "Use: " << argv[0] << " --help para mas información" << std::endl;
      exit(EXIT_SUCCESS); 
      break;
    }
  }
}

