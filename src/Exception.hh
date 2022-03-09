
#ifndef OCTETOS_SATURNO_EXCEPTION_HH
#define OCTETOS_SATURNO_EXCEPTION_HH

#include <octetos/core/Exception.hh>

namespace oct::sat
{

class Exception : public oct::Exception
{
public:
	enum Errors
	{
		NO_ERROR,
		NO_EQUAL_SIZE_ARRAY,
		NO_MULTI_SIZE_STRING,
		NO_DATA_NAME_LOADED,
		NO_DIRECTORY_NAME_FOUND,
		NO_FILE_NAMES_FOUND,
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