
#include "cellular_automata.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


int main(int argc, char** argv) {
    srand(time(NULL));
    int lattice_size, n_sands, iterations;
    if (argc != 4) {
        cout << "ERROR! Incorrect format: must be ./automata <lattice_size> <number of sands> <number of iterations>" << endl;
        cout << "OBS: the three arguments must be integers > 0" << endl;
        return -1;
    }

    try {
        lattice_size = stoi(argv[1]) + 2;
        if (lattice_size <= 0) 
            throw std::invalid_argument("ERROR! Incorrect type of <lattice_size>: it must be a integer > 0");
        n_sands = stoi(argv[2]);
        if (n_sands <= 0) 
            throw std::invalid_argument("ERROR! Incorrect type of <number of sands>: it must be a integer > 0");
        iterations = stoi(argv[3]);
        if (iterations <= 0) 
            throw std::invalid_argument("ERROR! Incorrect type of <number of iterations>: it must be a integer > 0");

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

