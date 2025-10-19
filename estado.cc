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
#include <cctype>
#include <sstream>

#include "estado.h"

Estado::Estado(const std::string& datos) {
  std::istringstream flujo(datos);
  flujo >> id_;
  int aceptacion;
  flujo >> aceptacion; 
  if (aceptacion == 1) {
    final_ = true;
  } else if (aceptacion == 0) {
    final_ = false;
  } else {
    std::cerr << "El valor de acepacion es incorrecto, solo puede ser 0 o 1" << std::endl;
    exit(EXIT_FAILURE);
  }
  flujo >> numero_transiciones_;
  if (numero_transiciones_ != 0) {
    for(int i = 0; i < numero_transiciones_; ++i) {
      char simbolo; 
      int destino;
      flujo >> simbolo >> destino;
      transiciones_.insert({simbolo, destino});
    }
  }
}