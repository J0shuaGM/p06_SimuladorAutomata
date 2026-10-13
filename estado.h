// Universidad de La Laguna
// Escuela Superior de Ingenierıa y Tecnologıa
// Grado en Ingenierıa Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 6: Diseño e implementación de un simulador de DFAs
// Autor: Joshua Gomez Marrero
// Correo: alu0101477398@ull.edu.es
// Fecha: 17/10/2025

#ifndef ESTADO_H
#define ESTADO_H

#include <iostream>
#include <map>

class Estado {
  public: 
    //Constructor
    Estado() {};
    Estado(const std::string& datos);

    //Destructor
    ~Estado() {};

    //Getters
    int getNombre(void) { return id_; }
    std::multimap<char, int> getTransiciones(void) { return transiciones_; }
    bool getFinal(void) { return final_; }
    int getNumeroTransiciones(void) { return numero_transiciones_; }

    //Setters
    void setNombre(int nombre) { id_ = nombre; }
    void setTransiciones(char clave, int valor) { transiciones_.insert({clave, valor}); }
    void setNumeroTransiciones(int numero) { numero_transiciones_ = numero; }
    void setAceptacion(bool aceptacion) { final_ = aceptacion; }

    //Sobrecarga de operadores
    friend std::istream& operator>>(std::istream& entrada, Estado& estados);
    friend std::ostream& operator<<(std::ostream& salida, const Estado& estados);
    
  private:
    int id_; // Numero identificador del estado
    bool final_; // Indica si el estado es de aceptacion
    int numero_transiciones_; // Numero de transiciones leidas para el estado
    std::multimap<char, int> transiciones_; // clave->valor (simbolo->numero estado siguiente)
};

#endif