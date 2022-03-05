
#ifndef OCTETOS_SATURNO_EXCEPTION_HH
#define OCTETOS_SATURNO_EXCEPTION_HH

#include <octetos/core/Exception.hh>

namespace oct::sat
{

class Exception : public oct::Exception
{
public:
	enum Erros
	{
		NO_ERROR,
		NO_EQUAL_SIZE_ARRAY,
		NO_MULTI_SIZE_STRING,
	};
	
public:
	Exception();
	Exception(unsigned int code);
	Exception(unsigned int code,const char* filename, unsigned int line);

	virtual const char* what () const throw ();

private:
};

}

#endif