/**
 * @author  Jamie Miles
 * @date    3/15/2024
 * 
 * COMPILE: g++ test.cpp Library.cpp Book.cpp
 * RUN:     a.exe   / Windows CMD       
 *          ./a.exe / Powershell
 *          ./a.out / Linux CMD
 * 
 * Implementation file for the Library class.
*/


#include <string>
#include "Library.hpp"

/**
 * Default Library object constructor.
 * Initializes this Library to have five empty Book slots.
*/
Library::Library() : used_slots(0), max_slots(5), e(new Book[5]) {}

/**
 * Library object constructor that takes an input stream as an argument.
 * Reads Book objects from the input stream and holds them in an array.
*/
Library::Library(std::istream &in) 
{
    // Initialize the number of used and max slots to the number of lines in the input stream
    std::string line; for (used_slots = 0, max_slots = 0; std::getline(in, line); max_slots++, used_slots++);

    // Dynamically allocate an array of Book objects to be of size max slots
    e = new Book[max_slots];

    // Clear EOF flag 
    in.clear();

    // Reset back to beginning of input stream
    in.seekg(0);

    // Now read in Books
    for (int i = 0; i < used_slots; i++)
    {
        Book b;
        b.read(in);

        e[i] = b;
    }
}

/**
 * Library object destructor.
 * Frees the memory allocated by the Book array.
*/
Library::~Library() {delete[] e;}

/**
 * @return  Number of used Book slots in this Library
*/
const int Library::size() const {return used_slots;}

/**
 * @return  Number of remaining slots left in this Library
*/
const int Library::emptySlots() const {return max_slots - used_slots;}

/**
 * Initialize all used Book slots in the Library to empty Book objects.
*/
void Library::clear() 
{
    // Set each book entry to an empty book
    for (int i = 0; i < used_slots; i++)
        e[i] = {};
    
    // Reset used slots to 0
    used_slots = 0;
}

/**
 * Searches for the passed Book argument in this Library.
 * If the Book is not in this Library, return a null pointer.
 * 
 * @param   Book to search
 * @return  Pointer to Book object
 * @return  Null pointer if Book is not found
*/
Book* Library::find(const Book& book) const
{
    // Linear search
    for (int i = 0; i < used_slots; i++)
        if (e[i] == book) 
            return e + i;
    
    return nullptr;
}

/**
 * Checks out a Book from the Library.
 * Increments the Book checkout count attribute by 1.
 * 
 * @param   Book to checkout
 * @return  Pointer to the Book argument
 * @return  Null pointer if Book is not found
*/
const Book* Library::checkOut(const Book& book)
{
    // If the Book is found in this Library, increment its check out count by one
    if (Book* book_ptr = find(book))
        return &++*book_ptr; // <-- Dereference, increment, then re-reference :)

    return nullptr;   
}

/**
 * Changes this Library object to be a copy of the argument Library object.
 * 
 * @param   Library to copy from
 * @return  Copy of this Library object
*/
const Library& Library::operator=(const Library& library)
{
    // Update used and max slots to the Library argument's used and max slots
    used_slots = library.used_slots;
    max_slots = library.max_slots;

    // Delete Book array and initialize new array to be of size updated max slots
    delete[] e;
    e = new Book[max_slots];

    // Iterate and copy elements from Library argument
    for (int i = 0; i < max_slots; i++)  
        e[i] = library.e[i];
    
    return *this;
}

/**
 * Adds a Book object to this Library object.
 * 
 * @param   Book to be added  
 * @return  Copy of this Library object
*/
const Library& Library::operator+=(const Book& book)
{

    // If the Book is already in the Library, do nothing
    if (find(book))
        return *this;

    // Check if there's no more empty slots left
    if (!emptySlots())
    {

        // Create temp array and copy elements from book array to temp
        Book* temp = new Book[max_slots]; 
        for (int i = 0; i < max_slots; i++) temp[i] = e[i];
        
        // Reallocate memory if the PFA is full
        delete[] e;
        e = new Book[max_slots *= 2];
        for (int i = 0; i < max_slots / 2; i++) e[i] = temp[i];
        delete[] temp;
    }

    // Add the book to the end of the PFA
    e[used_slots++] = book;
    return *this;
}

/**
 * Adds the Book objects from Library argument to this Library.
 * Skips over duplicate Book objects.
 * 
 * @param   Library to add Books from
 * @return  Copy of this Library object
*/
const Library& Library::operator+=(const Library& library)
{
    // Iterate over library Object's used slots and add the Book objects to the current Library if they aren't duplicates
    for (int i = 0; i < library.used_slots; i++)
        if (library.e[i] != e[i])
            *this += library.e[i];
    
    return *this;
}

/**
 * Removes a Book object from this Library object.
 * 
 * @param   Book to remove
 * @return  Copy of this Library object
*/
const Library& Library::operator-=(const Book& book)
{

    // If the Book isn't in the Library, do nothing
    if (!find(book))
        return *this;

    // Decrement used book slots
    used_slots--;

    // If the find method does not return a null pointer, "remove" our Book
    if (Book* book_ptr = find(book))
    {
        // Dereference the book pointer and initialize to empty Book object using an initializer list
        *book_ptr = {};

        // Shift Books in front of empty Book down the array
        for (int i = 0; i < max_slots - 1; i++) 
            if (e + i >= book_ptr)
                *(e + i) = *(e + i + 1);
        
        // Set final element to empty after everything has been shifted down
        *(e + max_slots - 1) = {};    
    }

    return *this;
}

/**
 * Adds the Books from passed Library argument and the Books from this Library object.
 * Skips over duplicate Books.
 * Does not modify either Library objects.
 * 
 * @param   Library to add from
 * @return  Union of passed Library argument and this Library
*/
Library Library::operator+(const Library& library) const
{

    // Construct empty Library object
    Library result;

    // Add this object's Books to result
    for (int i = 0; i < used_slots; i++)
        result += e[i];
    
    // Add other Library object's Books to result if they aren't duplicates
    for (int i = 0; i < library.used_slots; i++)
        if (library.e[i] != e[i])
            result += library.e[i];

    return result;
}

/**
 * Helper method for insertion operator overload method.
 * Iterates over the Book array while writing the elements to an ostream object.
 * 
 * @param   std::ostream
 * @return  std::ostream of Books in this Library
*/
std::ostream& Library::print(std::ostream& out) const
{
    // Output Book objects line by line
    for (int i = 0; i < used_slots; i++)
        out << e[i] << std::endl;
    
    return out;
}

/**
 * Helper method for extraction operator overload method.
 * Constructs Book objects from input stream and adds them to this Library.
 * 
 * @param   std::istream
 * @return  std::istream
*/
std::istream& Library::read(std::istream& in)
{
    // Read input stream until EOF and add books to this Library   
    Book b; while (in >> b) *this += b;
    return in;
}

/**
 * Overloaded insertion operator.
 * 
 * @param   std::ostream
 * @param   Library to output
 * @return  std::ostream
*/
std::ostream& operator<<(std::ostream& out, const Library& library)
{
    // Call print method
    return library.print(out);
}

/**
 * Overloaded extraction operator.
 * 
 * @param   std::istream
 * @param   Library to read in
 * @return  std::istream
*/
std::istream& operator>>(std::istream& in, Library& library)
{
    // Call read method
    return library.read(in);
}
