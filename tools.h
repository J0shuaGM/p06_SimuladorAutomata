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

#include "alfabeto.h"
#include "cadena.h"
#include "automata.h"
#include "estado.h"

void Usage(int argc, char* argv[]);
const std::string helptext = R"(El autómata finito vendrá definido en un fichero de texto con extensión .fa. Los ficheros
.fa deberán tener el siguiente formato:
Línea 1: Símbolos del alfabeto separados por espacios.
Línea 2: Número total de estados del autómata.
Línea 3: Estado de arranque del autómata.
A continuación figurará una línea para cada uno de los estados. Cada línea contendrá
los siguientes números, separados entre sí por espacios en blanco:
• Número identificador del estado. Los estados del autómata se representarán
    mediante números naturales. La numeración de los estados corresponderá a los
    primeros números comenzando en 0.
• Un 1 si se trata de un estado de aceptación y un 0 en caso contrario.
• Número de transiciones que posee el estado.
• A continuación, para cada una de las transiciones, y utilizando espacios en
    blanco como separadores, se detallará la información siguiente:
    ◦ Símbolo de entrada necesario para que se produzca la transición. Para representar la cadena vacía (el no consumir símbolo de la entrada) se utilizará
        el carácter &
    ◦ Estado destino de la transición)";