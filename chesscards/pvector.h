#pragma once
enum PVECTOR_ERR
{
	ERROR_OUT_OF_RANGE,
	ERROR_NOPOP,
	ERROR_BADEND,
};
template < class T > class pvector
{
public:

	pvector<T>(){}
	pvector( pvector<T> & p ) { *this = p; }
	~pvector() { delete[]m_array; m_array = nullptr; m_len = 0; }
	T operator[]( int i ) const { return m_array[i]; }
	T & operator[]( int i ){ return m_array[i]; }

	pvector<T> & operator=( pvector<T> & p )
	{
		delete[]m_array;
		m_array = new T[p.length()];
		m_len = p.length();
		for( unsigned i = 0; i < m_len; ++i )
			m_array[i] = p[i];
		return *this;
	}
	bool operator==( pvector<T> & p )
	{
		for( unsigned i = 0; i < m_len; ++i )
			if( m_array[i] != p[i] )
				return false;
		return true;
	}
	bool operator!=( pvector<T> & p ){ return !( *this == p ); }

	unsigned length() const{ return m_len; }
	unsigned len() const{ return m_len; }
	unsigned size() const{ return m_len; }

	bool empty() const { return m_len == 0; }
	T * begin() const { return m_array; }
	T * end() const { return m_array + m_len; }

	void clear() { delete[]m_array; m_array = nullptr; m_len = 0; }

	void push_back( T a )
	{
		T * n = new T[m_len + 1]; //allocate old space + 1
		for( unsigned i = 0; i < m_len; ++i ) //copy all old values
			n[i] = m_array[i];
		n[m_len] = a; //assign last index to new value
		delete[]m_array; //delete old array
		m_array = n; //move pointer
		m_len++;//increment count
	}
	T pop_back()
	{
		if( empty() ) throw ERROR_NOPOP; //nothing to pop
		T ret = m_array[m_len - 1]; //cache the value we'll be removing
		T * n = new T[m_len]; //allocate old space - 1
		for( unsigned i = 0; i < m_len - 1; ++i ) //copy old values except last
			n[i] = m_array[i];
		delete[]m_array; //delete old array
		m_array = n; //assign pointer
		m_len--; // decrement count
		return ret; //return value that was popped
	}
	void insert( unsigned pos, T obj )
	{
		if( pos > m_len ) throw ERROR_OUT_OF_RANGE;
		if( pos == m_len ) //if we're adding to the end, just push
			push_back( obj );
		else
		{
			T * n = new T[m_len + 1]; //allocate old spacee + 1
			for( unsigned i = 0; i < pos; ++i ) //copy all old values before index
				n[i] = m_array[i]; 
			n[pos] = obj; //assign new value to index
			for( unsigned i = pos + 1; i < m_len + 1; ++i ) //bump all values past insertion point up one index
				n[i] = m_array[i - 1];
			delete[]m_array; //delete old array
			m_array = n; //move pointer
			m_len++; //increment counter
		}
	}
	void remove( unsigned pos )
	{
		if( pos < 0 || pos > m_len ) throw ERROR_OUT_OF_RANGE;
		T * n = new T[m_len-1]; //allocate old memory - 1
		unsigned idx = 0; //count of new array index
		for( unsigned i = 0; i < m_len; ++i ) //copy all values except the one to remove
			if( i != pos )
				n[idx++] = m_array[i];
		delete[]m_array; //delete old array
		m_array = n; //move pointer
		m_len--; //decrement counter
	}
	void remove( unsigned begin, unsigned end )
	{
		if( begin > m_len ) throw ERROR_OUT_OF_RANGE;
		else if( end < begin ) throw ERROR_BADEND; //they probably messed up here though, so we should let 'em know.
		if( end > m_len ) end = m_len; //if we want to delete more than we have just delete to the end. This is a safe assumption.

		if( begin == 0 )
			clear(); //save ourself some work
		else
		{
			T * n = new T[m_len - (end-begin+1)]; //allocate old memory - the number of items we're removing
			unsigned idx = 0; //count of new array index
			for( unsigned i = 0; i < m_len; ++i ) //copy all values except the ones between removal range
				if( i < begin || i > end  )
					n[idx++] = m_array[i];
			delete[]m_array; //delete old array
			m_array = n; //move pointer
			m_len-=(end-begin+1); //decrement counter
		}
	}
private:
	T * m_array = nullptr;
	unsigned m_len = 0;
};