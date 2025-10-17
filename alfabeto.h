// Universidad de La Laguna
// Escuela Superior de Ingenierıa y Tecnologıa
// Grado en Ingenierıa Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 2: Cadenas y lenguajes
// Autor: Joshua Gomez Marrero
// Correo: alu0101477398@ull.edu.es
// Fecha: 17/09/2024
// Archivo alfabeto.h: programa cliente.
// Contiene la declaración de la clase alfebeto
// para ... (indicar brevemente el objetivo)
// Referencias:
// Enlaces de interes
// Historial de revisiones
// 17/09/2024 - Creacion (primera version) del codigo 

// Directrices usadas para evitar el solapamiento de los headers en el programa
#ifndef ALFABETO_H
#define ALFABETO_H

#include <iostream>
#include <set>


class Alfabeto {
  public: 
    // Constructores
    Alfabeto(void) {}  // Predeterminado
    Alfabeto(std::string simbolos); // Parametrizado

    // Destructor
    ~Alfabeto() {}

    //Getters y setters
    std::set<char> getSimbolos(void) { return simbolos_; }
    void setSimbolos(std::set<char> simbolos) { simbolos_ = simbolos; }

    //insert y search
    void insertar(char c);
    bool search(char c);

    // Sobrecarga de operadores de inserción y extracción
    friend std::istream& operator>>(std::istream& entrada, Alfabeto& simbolos);
    friend std::ostream& operator<<(std::ostream& salida, const Alfabeto& simbolos);

  private:
    std::set<char> simbolos_; // Atributo set de caracteres que actuara de Alfabeto
};

#endif