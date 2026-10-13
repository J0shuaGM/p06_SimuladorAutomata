// Universidad de La Laguna
// Escuela Superior de Ingenierıa y Tecnologıa
// Grado en Ingenierıa Informatica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Practica 6: Diseño e implementación de un simulador de DFAs
// Autor: Joshua Gomez Marrero
// Correo: alu0101477398@ull.edu.es
// Fecha: 17/10/2025

#include <iostream>

#include "alfabeto.h"
#include "cadena.h"
#include "automata.h"
#include "estado.h"

const std::string helptext = R"(El DFA vendrá definido en un fichero de texto con extensión .dfa. Los ficheros
.dfa deberán tener el siguiente formato:
Línea 1: Símbolos del alfabeto. Caracteres alfanuméricos (letras o dígitos) escritos
    en una única línea sin espacios de separación entre ellos.
Línea 2: Número total de estados del DFA.
Línea 3: Estado de arranque del DFA.
A continuación figurará una línea para cada uno de los estados, con los siguientes
datos separados entre sí por espacios en blanco:
• Número identificador del estado (numerados desde 0).
• Un 1 si se trata de un estado de aceptación y un 0 en caso contrario.
• A continuación, para cada una de las transiciones:
    ◦ Símbolo de entrada necesario para que se produzca la transición.
    ◦ Estado destino de la transición.
Cada estado debe tener exactamente una transición para cada símbolo del alfabeto.
Las líneas que comiencen por // se consideran comentarios y se ignoran.

Ejemplo (DFA que reconoce (a|b)*abb):
ab
5
0
0 0 a 1 b 2
1 0 a 1 b 3
2 0 a 1 b 2
3 0 a 1 b 4
4 1 a 1 b 2

El fichero .txt contiene una cadena por línea, sin separación entre sus símbolos.
La cadena vacía se representa con el símbolo &.)";
void Usage(int argc, char* argv[]);
void SimulacionAutomata(Automata automata, const std::string& fichero_cadenas);