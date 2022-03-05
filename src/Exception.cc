
#include "Exception.hh"

namespace oct::sat
{
	
Exception::Exception()
{

}
Exception::Exception(unsigned int c) : oct::Exception(c)
{

}
Exception::Exception(unsigned int c,const char* f, unsigned int l) : oct::Exception(c,f,l)
{

}

const char* Exception::what () const throw ()
{
	switch(code)
	{
	case Erros::NO_ERROR:
		return "No error.";
	case Erros::NO_EQUAL_SIZE_ARRAY:
		return "Las longitudes de los arrglos no coinciden";
	case Erros::NO_MULTI_SIZE_STRING:
		return "El tamano de la cadena deve ser multipos enteros de la base";
	default:
		return "Error desconocido.";
	}
	return "Error desconocido.";
}
	
}