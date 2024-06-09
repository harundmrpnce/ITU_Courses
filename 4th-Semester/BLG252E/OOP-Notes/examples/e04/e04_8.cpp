// e04_8.cpp
// Programmer-defined copy constructor for the user-defined String class

#include <iostream>
#include <cstring>			// for old string functions inherited from C
// The new header for strings is <string>
using std::cout;
using std::endl;

/*
The standard library of C++ contains a std::string class.
Programmers do not need to write their own String classes.
We write this class using old string functions inherited from C, only to show some concepts.
*/

// A class to define strings
// contents of strings terminate with a null character '\0'
class String{
public:
	String(const char*);			// Constructor
	String(const String&);			// Copy Constructor
	void print() const;				// A member function to print the string
	void setContents(const char*);  // Setter
	~String();						// Destructor
private:
	 size_t m_size;					// length of a string
	 char *m_contents;				// pointer to the character array
};

// Constructor
// Allocates memory 
// copies the input character array that terminates with null character
// to the contents of the string
String::String(const char *inData)
{
	 cout<< "Constructor has been invoked" << endl;
	 m_size = std::strlen(inData);
	 m_contents = new char[m_size +1];   // +1 for null character
	 if (m_contents)					 // If memory is allocated copy the contents
		 for (std::size_t index = 0; index < m_size + 1; index++)     // input_data is copied to the contents
			 m_contents[index] = inData[index];
}

// Copy Constructor
// Allocates memory 
// copies the contents of the existing object to the newly constructed object
String::String(const String& originalString)
{
	cout << "Copy Constructor has been invoked" << endl;
	m_size = originalString.m_size;
	m_contents = new char[m_size + 1];   // Memory allocation. +1 for null character
	if (m_contents)					 // If memory is allocated copy the contents
		for (std::size_t index = 0; index < m_size + 1; index++)     // input_data is copied to the contents
			m_contents[index] = originalString.m_contents[index];
}
void String::print() const
{
	 cout<< m_contents << " " << m_size << endl;
}

// Setter
void String::setContents(const char* inContents) {
	delete[] m_contents;    // Delete previous contents
	m_size = std::strlen(inContents);
	m_contents = new char[m_size + 1];   // +1 for null character
	if (m_contents)					 // If memory is allocated copy the contents
		for (std::size_t index = 0; index < m_size + 1; index++)     // input_data is copied to the contents
			m_contents[index] = inContents[index];					
}
// Destructor
// Memory pointed to by the pointer contents is given back to the heap
String::~String()
{
	 cout << "Destructor has been invoked" << endl;
	 delete[] m_contents;
}

//------- Main Function -------
int main()
{
  String originalString{"string 1"};
  cout << "Printing the original string:" << endl;
  originalString.print();

  cout << "----------------------" << endl; // Seperator
  String copyString{ originalString };     // Programmer-defined copy constructor runs
  cout << "Printing the copy string:" << endl;
  copyString.print();

  cout << "----------------------" << endl;		 // Seperator
  originalString.setContents("Another Text");    // We change the contents of the original string
  cout << "Printing the original string:" << endl;
  originalString.print();
  cout << "Printing the copy string:" << endl;
  copyString.print();                              // The copy does not change

  cout << "----------------------" << endl;			// Seperator
  return 0;
 }