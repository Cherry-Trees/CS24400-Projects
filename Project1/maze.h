#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Maze {

    public: 

        // Constructor and Destructor
        Maze(ifstream &fin);
        ~Maze();

        // Getters
        int getNumRows() {return shape[0];}
        int getNumCols() {return shape[1];} 
        char* operator[](int index) {return v[index];}  

        bool solve(); 
    
    private:

        // Double pointer for user-defined 2-D array
        char** v;
        int start[2];
        int end[2];
        int shape[2]; 

        bool is_valid(int row, int col);
        bool recursive_search(int row, int col);
};

// Overload insertion operator to easily output the maze
ostream& operator<<(ostream &out, Maze &m) {
    for (int i=0; i<m.getNumRows(); i++) {
        for (int j=0; j<m.getNumCols(); j++) {
            out << m[i][j];
        }
        out << endl;
    }
    return out;
}

// Constructor
Maze::Maze(ifstream &fin) {

    // Read in rows, cols, shape, start, and end
    string fileStr = "";

    for (int i=0; i<6; i++) {

        fin >> fileStr;
        int fileInt = stoi(fileStr);
        
        switch (i)
        {
            // Rows
            case 0:
            {
                shape[0] = fileInt;
                break;
            }

            // Cols
            case 1:
            {
                shape[1] = fileInt;
                break;
            }

            // Start row
            case 2:
            {
                start[0] = fileInt;
                break;
            }

            // Start col
            case 3:
            {
                start[1] = fileInt;
                break;
            }

            // End row
            case 4:
            {
                end[0] = fileInt;
                break;
            }

            // End col
            case 5:
            {
                end[1] = fileInt;
            }
        }
    }

    // We don't know the maze shape at compile-time -> Dynamically allocate memory using pointer
    v = new char*[shape[0]];
    for (int i=0; i<shape[0]; i++)
        v[i] = new char[shape[1]];

    // Read input file char by char, skipping over ws
    int i = 0;
    char inCh;
    while(fin >> skipws >> inCh)
        v[i/shape[1]][i++%shape[1]] = inCh;

    // Output initial maze
    cout << endl << *this << endl << endl;
}

// Destructor
Maze::~Maze() {

    // Delete 2-D array
    for (int i=0; i<shape[1]; i++) delete[] v[i];
    delete[] v;
}

// Check if the current space is a valid move
bool Maze::is_valid(int row, int col) {return (row >= 0 && row < shape[0] && col >= 0 && col < shape[1] && v[row][col] == '+');}

// Recursively search through the maze for solutions
bool Maze::recursive_search(int row, int col) {

    // Return false immediately if starting position is invalid
    if (v[start[0]][start[1]] == '#') {return false;}

    // Star start and end
    if (row == start[0] && col == start[1]) {v[row][col] = '*';}
    
    // UP
    if (is_valid(row-1, col)) {
        v[row-1][col] = '*';
        if (recursive_search(row-1, col)) {return true;}
    }
    
    // DOWN
    if (is_valid(row+1, col)) {
        v[row+1][col] = '*';
        if (recursive_search(row+1, col)) {return true;}
    }

    // LEFT
    if (is_valid(row, col-1)) {
        v[row][col-1] = '*';
        if (recursive_search(row, col-1)) {return true;}
    }

    // RIGHT
    if (is_valid(row, col+1)) {
        v[row][col+1] = '*';
        if (recursive_search(row, col+1)) {return true;}
    }

    // END
    if (row == end[0] && col == end[1]) {return true;}

    // Base case
    v[row][col] = 'B';
    return false;
}

// Solve maze, then output maze
bool Maze::solve() {
    auto b = recursive_search(start[0], start[1]);
    b ? cout << *this : cout << "NO SOLUTION FOUND";

    return b;
}