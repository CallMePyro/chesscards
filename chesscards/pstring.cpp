#include "pstring.h"
/*****************************************************
* Name: Pstring( default constructor )
*
* Purpose: To initialize all values to defaults
*
* Entry: a pstring object needs to be initialized
*
* Exit: values initialized to defaults
******************************************************/
pstring::pstring():m_string( nullptr ), m_len( 0 )
{}

/*****************************************************
* Name: pstring( const char c )
*
* Purpose: to initliaze a pstring as a character
*
* Entry: a character
*
* Exit: a pstring has been initialized as a character
******************************************************/
pstring::pstring( const char c ):m_string( nullptr ), m_len( 0 )
{
	if( c ) //not null character
	{
		m_string = new char[2];
		m_string[0] = c;
		m_string[1] = 0;
		m_len = 1;
	}
}

/*****************************************************
* Name: pstring( const char * str )
*
* Purpose: to initialize a pstring as a character array
*
* Entry: a character array
*
* Exit: a pstring has been initialized as a chracter array
******************************************************/
pstring::pstring( const char * str ):m_string( nullptr ), m_len( 0 )
{
	if( str ) //not nullptr
		alloc( str );
}

/*****************************************************
* Name: pstring( const pstring & o )
*
* Purpose: a pstring needs to be copied
*
* Entry: a pstring to be copied
*
* Exit: a pstring has been copied
******************************************************/
pstring::pstring( const pstring & o )
{
	this->alloc( o.begin() );
	this->m_len = o.length();
}

/*****************************************************
* Name: alloc( const char * c )
*
* Purpose: allocate space in memory for a copy of the passed cstring
*
* Entry: a cstring needs to be copied
*
* Exit: a cstring has been copied
******************************************************/
void pstring::alloc( const char * s )
{
	if( s != nullptr )
	{
		unsigned L = strlen( s );
		m_string = new char[L + 1];

		strcpy( m_string, s );
		m_len = L;
	}
}

/*****************************************************
* Name: append( const char c )
*
* Purpose: to append a character onto the end of a pstring
*
* Entry: a character needs to be appended onto a pstring
*
* Exit: a character has been appended to a cstring
******************************************************/
void pstring::append( const char c )
{
	if( c ) //is not nullptr
	{
		if( m_string == nullptr )
		{
			m_string = new char[2];
			m_string[0] = c;
			m_string[1] = '\0';
			m_len = 1;
		}
		else
		{
			char * n = new char[len() + 2];

			strcpy( n, m_string );
			n[m_len] = c;
			n[m_len + 1] = 0;

			dealloc();

			m_string = n;
			m_len++;
		}
	}
}

/*****************************************************
* Name: append( const char * s )
*
* Purpose:  to append a cstring onto the end of a pstring
*
* Entry: a cstring needs to be appended onto a pstring
*
* Exit: a cstring has been appended to a pstring
******************************************************/
void pstring::append( const char * s )
{
	if( m_string == nullptr )
		alloc( s );
	else
	{
		unsigned L = len() + strlen( s );
		char * n_str = new char[L + 1];

		strcpy( n_str, m_string );
		strcat( n_str, s );

		dealloc();
		m_string = n_str;
		m_len = L;
	}
}

/*****************************************************
* Name: append( const pstring & s )
*
* Purpose: to append a pstring to another pstring
*
* Entry: a pstring needs to be appended to another pstring
*
* Exit: a pstring has been appended to a another pstring
******************************************************/
void pstring::append( const pstring & s )
{
	if( m_string == nullptr )
		alloc( s.begin() );
	else
	{
		unsigned L = this->len() + s.len();
		char * n_str = new char[L + 1];

		strcpy( n_str, this->m_string );
		strcat( n_str, s.begin() );

		this->dealloc();
		this->m_string = n_str;
		this->m_len = L;
	}
}

pstring & pstring::remove_char( const char c )
{
	if( c == '\0' ) //we'll never find a null character
		return *this;

	pstring t;
	for( unsigned i = 0; i < len(); ++i )
	{
		if( m_string[i] != c )
			t += m_string[i];
	}
	*this = t; //copy new string
	return *this;
}

pstring & pstring::toupper()
{
	for( unsigned i = 0; i < len(); ++i )
		m_string[i] = ::toupper( m_string[i] );
	return *this;
}

pstring & pstring::tolower()
{
	for( unsigned i = 0; i < len(); ++i )
		m_string[i] = ::tolower( m_string[i] );
	return *this;
}

/*****************************************************
* Name: dealloc()
*
* Purpose: to de-allocate allocated memory
*
* Entry: allocated memory needs to be de-allocated
*
* Exit: allocated memory has been de-allocated
******************************************************/
void pstring::dealloc()
{
	delete [] m_string;
	m_string = nullptr;
}

/*****************************************************
* Name: ~pstring( default destructor )
*
* Purpose: to destruct a pstring object
*
* Entry: a pstring object needs to be destructed
*
* Exit: a pstring object has been destructed
******************************************************/
pstring::~pstring()
{
	dealloc();
}

/*****************************************************
* Name: operator [] ( unsigned i ) const
*
* Purpose: to retrieve a character at an index from 'm_string'
*
* Entry: a chracter needs to be retrieved at an index from 'm_string'
*
* Exit: a characted has been retrieved at an index from 'm_string'
******************************************************/
char pstring::operator [] ( unsigned i ) const
{
	return m_string[i];
}

/*****************************************************
* Name: operator [] ( int i ) const
*
* Purpose: to retrieve a character at an index from 'm_string'
*
* Entry: a chracter needs to be retrieved at an index from 'm_string'
*
* Exit: a characted has been retrieved at an index from 'm_string'
******************************************************/
char pstring::operator [] ( int i ) const
{
	return m_string[i];
}

/*****************************************************
* Name: operator [] ( unsigned i )
*
* Purpose: to retrieve a character at an index from 'm_string'
*
* Entry: a chracter needs to be retrieved at an index from 'm_string'
*
* Exit: a characted has been retrieved at an index from 'm_string'
******************************************************/
char & pstring::operator [] ( unsigned i )
{
	return m_string[i];
}

/*****************************************************
* Name: operator [] ( int i )
*
* Purpose: to retrieve a character at an index from 'm_string'
*
* Entry: a chracter needs to be retrieved at an index from 'm_string'
*
* Exit: a characted has been retrieved at an index from 'm_string'
******************************************************/
char & pstring::operator [] ( int i )
{
	return m_string[i];
}

/*****************************************************
* Name: operator = ( const pstring & rhs )
*
* Purpose: to assign a pstring object to another pstring object
*
* Entry: a pstring object needs to be assigned to another pstring object
*
* Exit: a pstring object has been assigned to another pstring object
******************************************************/
pstring & pstring::operator = ( const pstring & rhs )
{
	if( this != &rhs )
	{
		this->dealloc();
		this->alloc( rhs.begin() );
	}
	return *this;
}

/*****************************************************
* Name: operator = ( const pstring & rhs )
*
* Purpose: to assign a pstring object to a cstring
*
* Entry: a pstring object needs to be assigned to a cstring
*
* Exit: a pstring object has been assigned to a cstring
******************************************************/
pstring & pstring::operator = ( const char * rhs )
{
	if( rhs )
	{
		this->dealloc();
		this->alloc( rhs );
	}
	return *this;
}

/*****************************************************
* Name: operator += ( const pstring & rhs )
*
* Purpose: to append a pstring object to a pstring object
*
* Entry: a pstring object needs to be appended to a pstring object
*
* Exit: a pstring object has been appended to a pstring object
******************************************************/
pstring & pstring::operator += ( const pstring & rhs )
{
	append( rhs );
	return *this;
}

/*****************************************************
* Name: operator += ( const pstring & rhs )
*
* Purpose: to append a pstring object to a cstring
*
* Entry: a pstring object needs to be appended to a cstring
*
* Exit: a pstring object has been appended to a cstring
******************************************************/
pstring & pstring::operator += ( const char * rhs )
{
	append( rhs );
	return *this;
}

/*****************************************************
* Name: operator + ( const pstring & rhs )
*
* Purpose: to add two pstring objects together
*
* Entry: two pstring objects need to be added together
*
* Exit: two pstring objects have been added together
******************************************************/
const pstring pstring::operator + ( const pstring & rhs )
{
	return pstring( *this ) += rhs;
}

/*****************************************************
* Name: operator + ( const pstring & rhs )
*
* Purpose: to a pstring and cstring together
*
* Entry: a pstring and cstring need to be added together
*
* Exit: a pstring and cstring have been added together
******************************************************/
const pstring pstring::operator + ( const char * rhs )
{
	return pstring( *this ) += rhs;
}

/*****************************************************
* Name: operator == ( const pstring & rhs )
*
* Purpose: determine if two pstring objects are equal
*
* Entry: need to determine if two pstring objects are equal
*
* Exit: determined if two pstring objects are equal
******************************************************/
bool pstring::operator == ( const pstring & rhs )
{
	if( this->len() != rhs.len() )
		return false;
	for( unsigned i = 0; i < this->len(); ++i )
		if( ( *this )[i] != rhs[i] )
			return false;
	return true;
}

/*****************************************************
* Name: operator == ( const char * rhs )
*
* Purpose: determine if a pstring and cstring are equal
*
* Entry: need to determine if a pstring and cstring are equal
*
* Exit: determined if two pstring and cstring objects are equal
******************************************************/
bool pstring::operator == ( const char * rhs )
{
	int i = 0;
	while( rhs[i] )
		if( ( *this )[i] != rhs[i++] )
			return false;
	return i == m_len;
}

/*****************************************************
* Name: operator != ( const pstring & rhs )
*
* Purpose: determine if two pstring objects aren't equal
*
* Entry: need to determine if two pstring objects aren't equal
*
* Exit: determined if two pstring objects aren't equal
******************************************************/
bool pstring::operator != ( const pstring & rhs )
{
	return !( *this == rhs );
}

/*****************************************************
* Name: operator == ( const char * rhs )
*
* Purpose: determine if a pstring and cstring aren't equal
*
* Entry: need to determine if a pstring and cstring aren't equal
*
* Exit: determined if two pstring and cstring objects aren't equal
******************************************************/
bool pstring::operator != ( const char * rhs )
{
	return !( *this == rhs );
}

/*****************************************************
* Name: operator << ( const char * rhs )
*
* Purpose: insert a pstring into any ostream
*
* Entry: need to insert a pstring into any ostream
*
* Exit: pstring inserted into ostream
******************************************************/
ostream & operator << ( ostream & str, const pstring & s )
{
	if( s.m_string )
		str << s.m_string;
	return str;
}

istream & operator >> ( istream & str, pstring & s )
{
	char input[100] = { 0 };
	str >> input;
	s = input;
	return str;
}