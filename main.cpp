
#include "cellular_automata.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


int main(int argc, char** argv) {
    srand(time(NULL));
    int lattice_size, n_sands, iterations;
    if (argc != 4) {
        cout << "ERRO! Formato Incorreto: deve ser ./automata <lattice_size> <numero de areias> <numero de iterações>" << endl;
        cout << "OBS: os três argumentos devem ser inteiros maior que 0" << endl;
        return -1;
    }

    try {
        lattice_size = stoi(argv[1]) + 2;
        if (lattice_size <= 0) 
            throw std::invalid_argument("ERRO! Tipo Incorreto do <lattice_size>: deve ser um inteiro maior que 0");
        n_sands = stoi(argv[2]);
        if (n_sands <= 0) 
            throw std::invalid_argument("ERRO! Tipo Incorreto do <número de areias>: deve ser um inteiro maior que 0");
        iterations = stoi(argv[3]);
        if (iterations <= 0) 
            throw std::invalid_argument("ERRO! Tipo Incorreto do <número de iterações>: deve ser um inteiro maior que 0");

    } catch(const std::invalid_argument& e) {
        cout << e.what() << endl;
        return -1;
    }

    CellularAutomata automata = CellularAutomata(lattice_size, iterations);
    
    int line, column;

    for (int cell = 0; cell < n_sands; cell++) {
        line = 2 + rand() % (lattice_size-4);
        column = 2 + rand() % (lattice_size-4);

        automata.set_cell(line, column, SAND);
    }

    automata.simulate();

    return 0;

}

