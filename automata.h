// Universidad de La Laguna
// Escuela Superior de Ingenierıa y Tecnologıa
// Grado en Ingenierıa Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 6: Diseño e implementación deun simulador de autómatas finitos
// Autor: Joshua Gomez Marrero
// Correo: alu0101477398@ull.edu.es
// Fecha: 17/10/2025

#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <iostream>
#include <set>
#include <map>

#include "cadena.h"
#include "alfabeto.h"
#include "estado.h"

class Automata {
  public:
    //Constructor
    Automata(std::string fichero);

    //Getters
    Alfabeto getAlfabeto(void) { return alfabeto_; }
    std::map<int, Estado> getEstados(void) { return estados_; }
    Estado getEstadoInicial(void) { return estado_inicial_; }
    std::set<int> getEstadosFinales(void) { return estados_finales_; }

    //Setters
    void setAlfabeto(Alfabeto alfabeto) { alfabeto_ = alfabeto; }
    void setEstados(int id, Estado estado) { estados_.insert({id, estado}); }
    void setEstadoInicial(Estado estado_inicial) { estado_inicial_ = estado_inicial; }
    void setEstadoFinal(int id) { estados_finales_.insert(id); }

    //Metodos
    const bool Simulacion(Cadena cadena);

    //Sobrecarga de operadores
    friend std::ostream& operator<<(std::ostream& salida, const Automata& automata);
    friend std::istream operator>>(std::istream entrada, Automata automata);

  private:
    Alfabeto alfabeto_;
    std::map<int, Estado> estados_; //id -> Estado
    Estado estado_inicial_;
    std::set<int> estados_finales_; //Se almacenan los id de los estados finales
}; 

#endif