// Universidad de La Laguna
// Escuela Superior de Ingenierıa y Tecnologıa
// Grado en Ingenierıa Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 2: Cadenas y lenguajes
// Autor: Joshua Gomez Marrero
// Correo: alu0101477398@ull.edu.es
// Fecha: 17/09/2024


#include <iostream>
#include <vector>
#include <algorithm>

#include "cadena.h"

/**
 * @brief Constructor parametrizado de la clase Cadena que usa un std::string para construir
 * el objeto
 * @param cadena string a partir de la que se construye el objeto Cadena
*/
Cadena::Cadena(std::string cadena) {
  for(char caracter : cadena) {
    cadena_.push_back(caracter);
  }
  if (cadena_[0] == '&') longitud_ = 0;
  else longitud_ = cadena_.size();
}



/**
 * @brief Metodo que devuelve la longitud del objeto Cadena
 * @return cadena_.size() Longitud de la cadena
*/
int Cadena::longitud(void) {
  if (cadena_[0] == '&') return 0; // La cadena vacia tiene longitud 0
  return cadena_.size();
}



/**
 * @brief Metodo que devulve la inversa del la cadena
 * @return reverse Devuelve la cadena invertida
*/
void Cadena::reverse(void) {
  std::vector<char> aux;
  for(int i = cadena_.size() - 1; i >= 0; i--) aux.push_back(cadena_[i]);
  for(int j{0}; j < aux.size(); j++) cadena_[j] = aux[j];
}



/**
 * @brief Sobrecarga del operador de extraccion para el objeto Cadena
 * @param entrada Variable para recibir la entrada de datos
 * @param cadena Objeto Cadena que va a ser sobreescrito
 * @return entrada Retornamos el nuevo valor 
*/
std::istream& operator>>(std::istream& entrada, Cadena& cadena) {
  char caracter; 
  entrada >> caracter; 
  cadena.cadena_.push_back(caracter); 
  return entrada;
}



/**
 * @brief Sobrecarga del operador de insercion para la clase Cadena
 * @param salida Variable que contiene la salida de escritura
 * @param cadena Objeto alfabeto que sera escrito
*/
std::ostream& operator<<(std::ostream& salida, const Cadena& cadena) {
  for(char caracter : cadena.cadena_) {
    salida << caracter;
  }
  return salida;
}



/**
 * @brief Sobrecarga del operador estrictamente menor (<) para la comparación de dos cadenas
 * @param cadena La primera de las dos cadenas a comparar
 * @param cadena2 La segunda de las dos cadenas a comparar  
*/
bool operator<(Cadena cadena, Cadena cadena2) {
  if(cadena.longitud_ == 0 || cadena.longitud_ < cadena2.longitud_) return true;
  return false;
}