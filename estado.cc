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



/**
 * @brief Constructor parametrizado de la clase Estado
 * @param datos cadena que contiene todos los datos del estado
*/
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
      if (!(flujo >> simbolo >> destino)) {
        std::cerr << "Erro al leer la transicion nummero " << i << " en el estado " << id_ << std::endl;
        exit(EXIT_FAILURE);
      }
      transiciones_.insert({simbolo, destino});
    }
  }
}



/**
 * @brief Sobrecarga del operador de insercion para el objeto Estado
 * @param entrada Variable para recibir la entrada de datos
 * @param estados Objeto Estado que va a ser sobreescrito
 * @return entrada Retornamos el nuevo valor 
*/
std::istream& operator>>(std::istream& entrada, Estado& estados) {
  std::string cadena_datos;
  entrada >> cadena_datos; 
  estados = Estado(cadena_datos);
  return entrada;
}



/**
 * @brief Sobrecarga del operador de extraccion para el objeto Estado
 * @param salida Variable para mostrar la salida de datos
 * @param estados Objeto Estado que va a ser mostrado por pantalla
 * @return salida Retornamos el nuevo valor 
*/
std::ostream& operator<<(std::ostream& salida, const Estado& estados) {
  salida << "Estado: " << estados.id_ << "\n";
  salida << "Aceptacion: " << estados.final_ << "\n";
  salida << "Numero de transiciones: " << estados.numero_transiciones_ << "\n";
  salida << "Transiciones: \n";
  for (const auto& transicion : estados.transiciones_) {
    salida << "  Simbolo: " << transicion.first << " -> Destino: " << transicion.second << "\n";
  } 
  return salida;
}