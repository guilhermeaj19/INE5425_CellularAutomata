#pragma once

#include <vector>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

#include "color_terminal.cpp"

using namespace std;

enum State : int {
    EMPTY = 0,
    SAND = 1,
    WALL = 2
} typedef State;


class CellularAutomata {
    public:


        CellularAutomata(const int lattice_size, const int iterations);
        void print_lattice();
        void set_cell(const int i, const int j, const State s);
        void simulate();
    private:
        void update_lattice();

        int _lattice_size;
        int _iterations;
        vector< vector<State> > _lattice;
        vector< vector<State> > _next_lattice;
        vector<Color::Modifier> _color_print;
};