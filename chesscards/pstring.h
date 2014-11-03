/********************************************************************************************
*	Class: pstring ( header file )
*
*	Overview:
*		This class is a custom string class that I wrote during inlab4 earlier this week.
*		It is a wrapper for a dynamiccally sized character array.
*		It has support for the following operators:
*			=, +, +=, ==, !=, [], <<
*
*	Manager Functions:
*		pstring()
*			The default constructor initializes a pstring with of no value.
*			The m_string data member points to nullptr, and m_len is equal to 0
*
*		pstring( const char c )
*			This constructor takes a single character and creates a copy in memory.
*			It then assigns this value to the pstring.
*
*		pstring( const char * c )
*			This constructor takes a character pointer and treats it as a character array.
*			It creates a copy in memory and assigns it to the pstring.
*
*		pstring( const pstring & p )
*			This copy consturctor takes another pstring and creates a copy of it's
*				m_string value, assigning it to the pstring.
*
*		~pstring()
*			The destructor for the class. Calls the 'dealloc' function which deletes the
*				m_string
*			data member and then assignes it to nullptr.
*
*	Mutators:
*
*		void append( const char c )
*			This function will effectively append a character onto an existing pstring
*				object
*			It will allocate memory for a new character pointer, and copy the old values
*				over, then it will append the new value.
*
*			states: none
*			returns: void
*
*		void append( const char * c )
*			This function will effectively append a character pointer onto an existing
*				pstring object
*			It will allocate memory for a new character pointer, and copy the old values
*				over, then it will append the new value.
*
*			states: none
*			returns: void
*
*		void append( const pstring & s )
*			This function will effectively append a pstring object onto an existing
*				pstring object
*			It will allocate memory for a new character pointer, and copy the old values
*				over, then it will append the new value.
*
*			states: none
*			returns: void
*
*		void alloc( const char * c )
*			This function will allocate new memory for a character string pointed to by
*				the constant 'c'.
*			The data member m_len will be equal to the number of non-null characters in
*				the character string.
*			The data member m_string will point to the start of the newly allocated copy.
*
*			states: none
*			returns: void
*
*	Methods:
*
*		unsigned length() const
*			This function will return the 'm_len' data member.
*			It will return the same value as the 'len' function.
*
*			states: const
*			returns: unsigned int
*
*		unsigned len() const
*			This function will return the 'm_len' data member.
*			It will return the same value as the 'length' function.
*
*			states: const
*			returns: unsigned int
*
*		char * begin() const
*			This function will return the 'm_string' data member.
*
*			states: const
*			returns:character pointer
*
*		char * end() const
*			This function will return a pointer to the end of the string pointed to
*			by the 'm_string' data member.
*
*			states: const
*			returns: character pointer
*
*		char pstring::operator [] ( unsigned i ) const
*			Returns the character at a certain index.
*
*			states: const, operator overload
*			returns: character
*
*		char pstring::operator [] ( int i ) const
*			Returns the character at a certain index.
*
*			states: const, operator overload
*			returns: character
*
*		char & pstring::operator [] ( unsigned i )
*			Used for assigning a character at a specific index to a character value
*
*			states: operator overload
*			returns: character reference
*
*		char & pstring::operator [] ( int i )
*			Used for assigning a character at a specific undex to a character value
*
*			states: operator overload
*			return: character reference
*
*		friend ostream & operator << ( ostream & str, const pstring & s )
*			Used when writing a pstring object to an ostream object
*
*			states: friend, operator overload
*			return: ostream reference
*
*		pstring & pstring::operator = ( const pstring & rhs )
*			Used for assigning an already initialized pstring object to be equal to
*			another pstring object
*
*			states: operator overload
*			returns: pstring reference
*
*		pstring & pstring::operator = ( const char * rhs )
*			Used for assinging an already initialized pstring object to be equal to
*			another character pointer
*
*			states: operator overload
*			returns: pstring reference
*
*		bool pstring::operator == ( const pstring & rhs )
*			Used for determining equality between two pstring objects
*
*			states: operator overload
*			returns: bool
*
*		bool pstring::operator == ( const char * rhs )
*			Used for determing equality between a pstring object and a character pointer.
*			The character pointer is assumed to be pointing to the begining a cstring
*
*			states: operator overload
*			returns: bool
*
*		bool pstring::operator != ( const pstring & rhs )
*			Used for determining non-equality between two pstring objects
*
*			states: operator overload
*			returns: bool
*
*		bool pstring::operator != ( const char * rhs )
*			Used for determining non-equality between a pstring object and
*				a character pointer.
*			The character pointer is assumed to be pointing to the begining of a cstring.
*
*			states: operator overload
*			returns: bool
*
*		const pstring & pstring::operator + ( const pstring & rhs )
*			Used for combining two pstring objects together.
*
*			states: operator overload
*			returns: const pstring reference
*
*		const pstring & pstring::operator + ( const char * rhs )
*			Used for combining a pstring object with a character pointer.
*			The character pointer is assumed to be pointing the the begining of a cstring.
*
*			states: operator overload
*			returns: const pstring reference
*
*		pstring & pstring::operator += ( const pstring & rhs )
*			Used for appending the right side pstring object onto the left pstring object.
*
*			states: operator overload
*			returns: pstring reference
*
*		pstring & pstring::operator += ( const char * rhs )
*			Used for a appending the passed character pointer string to the
*				left pstring object.
*
*			states: operator overload
*			returns: pstring reference
*
*	Data Members:
*
*		unsigned m_len
*			This unsigned integer represents the length of the m_string variable.
*			It can be retrieved through the 'len' or 'length' member functions
*			It can be assigned indirectly though the following operations:
*				'append', +, +=, =
*			This is done by modifying the m_string variable to be a different string,
*			conditional that the applied string is of a different length than the original.
*
*		char * m_string
*			This character pointer contains the location in memory of the start of the
*			string represented by the pstring object.
*			The address of this pointer is modified through the following operations:
*				'append', +, +=, =
*			This is conditional that the characters pointed to by the original are
*			different that those contained in the assigned value.
*
*
*************************************************************************************************************************************/

#pragma once
#include <ostream>
	using std::ostream; //used for overloading the insertion operator
#include <istream>
	using std::istream; //user for overloading the extraction operator
#include <iostream>
	using std::cout;
class pstring
{
	public:
	pstring();
	pstring( const char c );
	pstring( const char * c );
	pstring( const pstring & s );

	~pstring();

	void append( const char c );
	void append( const char * c );
	void append( const pstring & s );

	pstring & remove_char( const char c );
	pstring & toupper();
	pstring & tolower();

	unsigned length() const { return m_len; };
	unsigned len() const { return m_len; };
	char * begin() const { return m_string; };
	char * end() const { return m_string + len(); };

	char pstring::operator [] ( unsigned i ) const; //retrieval
	char pstring::operator [] ( int i ) const;

	char & pstring::operator [] ( unsigned i ); //assignment
	char & pstring::operator [] ( int i );

	friend ostream & operator << ( ostream & str, const pstring & s );
	friend istream & operator >> ( istream & str, pstring & s );

	pstring & pstring::operator = ( const pstring & rhs );
	pstring & pstring::operator = ( const char * rhs );

	pstring & pstring::operator += ( const pstring & rhs );
	pstring & pstring::operator += ( const char * rhs );

	const pstring pstring::operator + ( const pstring & rhs );
	const pstring pstring::operator + ( const char * rhs );

	bool pstring::operator == ( const pstring & rhs );
	bool pstring::operator == ( const char * rhs );

	bool pstring::operator != ( const pstring & rhs );
	bool pstring::operator != ( const char * rhs );

	private:
	void dealloc();
	void alloc( const char * );

	unsigned m_len;
	char * m_string;

};