// Universidad de La Laguna
// Escuela Superior de Ingenierıa y Tecnologıa
// Grado en Ingenierıa Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 2: Cadenas y lenguajes
// Autor: Joshua Gomez Marrero
// Correo: alu0101477398@ull.edu.es
// Fecha: 17/09/2024


#ifndef CADENA_H
#define CADENA_H

#include <iostream>
#include <vector>
#include <string>


class Cadena {
	public:
    // Contructores
    Cadena(void){} // Predeterminado
    Cadena(std::string cadena); // Parametrizado

    // Destructor
    ~Cadena() {}

    // Metodos
    int longitud(void);
    void reverse(void);
    void clear(void) { cadena_.clear(); }

    //Getters y setters
    std::vector<char> getCadena(void) { return cadena_; }
    int getSize(void) { return longitud_; }
    void setCadena(std::vector<char> cadena) { cadena_ = cadena; }
    void setSize(int size) {longitud_ = size; }


    // Sobrecarga de operadores
    friend std::istream& operator>>(std::istream& entrada, Cadena& cadena);
    friend std::ostream& operator<<(std::ostream& salida, const Cadena& cadena); 
    friend bool operator<(Cadena cadena, Cadena cadena2);


	private:
    std::vector<char> cadena_; // Vector de caracteres que actua como nuestra cadena
    int longitud_;
};

#endif