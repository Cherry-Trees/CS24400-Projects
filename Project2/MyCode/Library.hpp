/**
 * @author  Jamie Miles
 * @date    3/15/2024
 * 
 * COMPILE: g++ test.cpp Library.cpp Book.cpp
 * RUN:     a.exe   / Windows CMD       
 *          ./a.exe / Powershell
 *          ./a.out / Linux CMD
 * 
 * Header file for the Library class.
*/


#pragma once

#include <iostream>
#include "Book.hpp"

/**
 * Library class that stores a collection of Book objects.
*/
class Library
{

    public:

        /* -------CONSTRUCTORS / DESTRUCTORS------- */

        // Constructor - Initialize the Book array e to five empty Book slots
        Library();

        // Constructor - Reads in Books from an input stream
        Library(std::istream& in);

        // Destructor - Frees the memory allocated by Book array e
        ~Library();



        /* -------ACCESSORS------- */

        // Accessor - Get the number of used slots in this Library
        const int size() const;         

        // Accessor - Get the number of empty slots in this Library
        const int emptySlots() const;   

        // Accessor - Get the pointer of the Book argument within the array e
        Book* find(const Book& book) const;



        /* -------MODIFIERS------- */

        // Modifier - Set all of the elements in the Book array e to empty Books
        void clear();
        
        // Modifier - Increment the Book argument's check out count by one
        const Book* checkOut(const Book& book);



        /* -------OPERATORS------- */

        // Modifier - Set this Library to be a copy of the passed Library object
        const Library& operator=(const Library& library);

        // Modifier - Add the Book argument to this Library
        const Library& operator+=(const Book& book);

        // Modifier - Add the Books from Library argument to this Library
        const Library& operator+=(const Library& library);

        // Modifier - Remove the Book argument from this Library
        const Library& operator-=(const Book& book);

        // Accessor - Construct a new Library object to be the union of this Library and the Library argument
        Library operator+(const Library& library) const;


        /* -------I/O------- */

        // Accessor - Write the elements in the Book array e to an output stream
        std::ostream& print(std::ostream& out) const;

        // Modifier - Read in the contents of an input stream as Books and add them to this Library
        std::istream& read(std::istream& in);


    private:

        /* -------INSTANCE VARIABLES------- */

        // Instance Variable - Number of Books stored in the Book PFA
        unsigned int used_slots;

        // Instance Variable - Number of total elements in the Book PFA
        unsigned int max_slots;

        // Instance Variable - Dynamic Book PFA
        Book* e;

};

/* -------STANDALONE FUNCTIONS-------*/

// Write the Book array elements to an output stream
std::ostream& operator<<(std::ostream& out, const Library& library);

// Read in Book objects from an input stream
std::istream& operator>>(std::istream& in, Library& library);
