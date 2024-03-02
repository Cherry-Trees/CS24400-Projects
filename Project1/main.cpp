#include "maze.h"

using namespace std;

int main() {

    // Get user defined input file name
    string file_name = "";
    cout << "Enter name of input file: ";
    cin >> file_name;

    // Construct ifstream object with param file name
    // Throw exception if file not found in cd
    ifstream fin(file_name);
    if (!fin) {throw runtime_error("File not found.");}
    
    // Construct a Maze object, then call the solve method
    Maze m = Maze(fin);
    m.solve();

    // Close input file
    fin.close();
    return 0;
}
