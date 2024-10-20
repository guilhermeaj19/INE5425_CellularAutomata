#include "cellular_automata.h"



using namespace std;

CellularAutomata::CellularAutomata(const int lattice_size, const int iterations) : _lattice_size(lattice_size),
                                                                       _iterations(iterations),
                                                                       _lattice(lattice_size, vector <State>(lattice_size, EMPTY)),
                                                                       _color_print(3, Color::EMPTY)
{
    for (int i = 0; i < _lattice_size; i++) {
      _lattice[0][i] = WALL;
      _lattice[i][0] = WALL;
      _lattice[i][_lattice_size-1] = WALL;
      _lattice[_lattice_size-1][i] = WALL;
      _lattice[1][i] = WALL;
      _lattice[i][1] = WALL;
      _lattice[i][_lattice_size-2] = WALL;
      _lattice[_lattice_size-2][i] = WALL;
    }

    _next_lattice = _lattice;
    _color_print[EMPTY] = Color::Modifier(Color::EMPTY); 
    _color_print[SAND] = Color::Modifier(Color::SAND);
    _color_print[WALL] = Color::Modifier(Color::WALL);

}

void CellularAutomata::print_lattice() {
    for (int i = 1; i < _lattice_size; i++) {
        for (int j = 1; j < _lattice_size; j++) {
            cout << " " << _color_print[_lattice[j][i]] << "  ";
        }
        cout << _color_print[EMPTY] << endl;
    }
}

void CellularAutomata::set_cell(const int i, const int j, const State s) {
    if (i > _lattice_size || j > _lattice_size) {
        cout << "ERRO: posição (" << i << ", " << j << ") é indevida!" << endl;
        cout << "      dimensões do lattice é " << _lattice_size << "x" << _lattice_size << endl;
        return;
    }
    _lattice[i][j] = s;
}

void CellularAutomata::simulate() {
    print_lattice();

    for (int i = 0; i < _iterations; i++) {
        update_lattice();
        system("clear");
        print_lattice();

        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void CellularAutomata::update_lattice() {
    _next_lattice = _lattice;
    #pragma omp parallel 
    {
        int s6,s7,s8,s9,s11,s12,s14,s15,s17,s18,s19,s20;
        #pragma omp for
        for (int j = 2; j < _lattice_size-2; j++) {
            for (int k = 2; k < _lattice_size-2; k++) {
                if (_lattice[j][k] == EMPTY) {
                    s6 = _lattice[j-2][k-1];
                    s7 = _lattice[j-1][k-1];
                    s8 = _lattice[j][k-1];
                    s9 = _lattice[j+1][k-1];
                    s11 = _lattice[j-2][k];
                    s12 = _lattice[j-1][k];
                    s14 = _lattice[j+1][k];
                

                    if (s8 == SAND)
                    _next_lattice[j][k] = SAND;
                    else if (s8 == EMPTY && s9 == SAND && s14 >= SAND)
                    _next_lattice[j][k] = SAND;
                    else if (s6 == EMPTY && s7 == SAND && s8 == EMPTY && (s9 == EMPTY || s9 == WALL) && s11 >= SAND && s12 >= SAND && (s14 == EMPTY || s14 == WALL))
                    _next_lattice[j][k] = SAND;
                    else if (s6 >= SAND && s7 == SAND && s8 == EMPTY && (s9 == EMPTY || s9 == WALL) && s11 >= SAND && s12 >= SAND && (s14 == EMPTY || s14 == WALL))
                    _next_lattice[j][k] = SAND;
                }

                if (_lattice[j][k] == SAND) {
                    s12 = _lattice[j-1][k];
                    s14 = _lattice[j+1][k];
                    s15 = _lattice[j+2][k];
                    s17 = _lattice[j-1][k+1];
                    s18 = _lattice[j][k+1];
                    s19 = _lattice[j+1][k+1];
                    s20 = _lattice[j+2][k+1];


                    if (s18 == EMPTY)
                    _next_lattice[j][k] = EMPTY;
                    else if (s12 == EMPTY && s17 == EMPTY && s18 >= SAND)
                    _next_lattice[j][k] = EMPTY;
                    else if (s12 == EMPTY && s14 == EMPTY && (s15 == EMPTY || s15 == WALL) && s17 >= SAND && s18 >= SAND && s19 == EMPTY && (s20 == EMPTY || s20 == WALL))
                    _next_lattice[j][k] = EMPTY;
                    else if (s12 >= SAND && s14 == EMPTY && (s15 == EMPTY || s15 == WALL) && s17 >= SAND && s18 >= SAND  && s19 == EMPTY && (s20 == EMPTY || s20 == WALL))
                    _next_lattice[j][k] = EMPTY;
                }
            }
        }
    }
    int old_cells = 0;
    int new_cells = 0;
    for (int j = 2; j < _lattice_size-2; j++) {
        for (int k = 2; k < _lattice_size-2; k++) {
            if (_lattice[j][k] == SAND) {
                old_cells++;
            }
            if (_next_lattice[j][k] == SAND) {
                new_cells++;
            }
        }
    }

    if (old_cells != new_cells) {
        cout << "PERDA DE MATÉRIA" << endl;
        exit(0);
    }
    _lattice = _next_lattice;
}