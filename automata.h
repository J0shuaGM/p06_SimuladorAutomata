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
    Automata(const std::string& fichero);

    //Getters
    Alfabeto getAlfabeto(void) { return alfabeto_; }
    std::map<int, Estado> getEstados(void) { return estados_; }
    int getEstadoInicial(void) { return estado_inicial_; }
    std::set<int> getEstadosFinales(void) { return estados_finales_; }
    int getNuemeroEstados(void) { return numero_estados_; }

    //Setters
    void setAlfabeto(Alfabeto alfabeto) { alfabeto_ = alfabeto; }
    void setEstados(int id, Estado estado) { estados_.insert({id, estado}); }
    void setEstadoInicial(int estado_inicial) { estado_inicial_ = estado_inicial; }
    void setEstadoFinal(int id) { estados_finales_.insert(id); }
    void setNumeroEstados(int numero) { numero_estados_ = numero;}

    //Metodos
    const bool Simulacion(Cadena cadena);

    //Sobrecarga de operadores
    friend std::istream& operator>>(std::istream& entrada, Automata& automata);
    friend std::ostream& operator<<(std::ostream& salida, const Automata& automata);

  private:
    int numero_estados_;
    Alfabeto alfabeto_;
    std::map<int, Estado> estados_; //id -> Estado
    int estado_inicial_; //id del estado inicial
    std::set<int> estados_finales_; //Se almacenan los id de los estados finales
}; 

#endif