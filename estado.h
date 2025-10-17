// Universidad de La Laguna
// Escuela Superior de Ingenierıa y Tecnologıa
// Grado en Ingenierıa Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 6: Diseño e implementación deun simulador de autómatas finitos
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
    Estado(const std::string datos);

    //Destructor
    ~Estado() {};

    //Getters
    char getNombre(void) { return id_; }
    std::multimap<char, int> getTransiciones(void) { return transiciones_; }

    //Setters
    void setNombre(char nombre) { id_ = nombre; }
    void setTransiciones(char clave, int valor) { transiciones_.insert({clave, valor}); }
  private:
    int id_; 
    bool final_;
    std::multimap<char, int> transiciones_; // clave->valor (simbolo->numero estado siguiente)
};

#endif