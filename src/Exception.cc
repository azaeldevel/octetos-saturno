
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
	case Errors::NO_ERROR:
		return "No error.";
	case Errors::NO_EQUAL_SIZE_ARRAY:
		return "Las longitudes de los arrglos no coinciden";
	case Errors::NO_MULTI_SIZE_STRING:
		return "El tamano de la cadena deve ser multipos enteros de la base";
	case Errors::NO_DATA_NAME_LOADED:
		return "No se cargaron los datos nombre y apellido necesrio para contruir la base de datos.";
	case Errors::NO_DIRECTORY_NAME_FOUND:
		return "No se encontro el directorio para cargar los nombres.";
	case Errors::NO_FILE_NAMES_FOUND:
		return "No se encontro el archivo de nombre neseario para generar la base de datos";
	default:
		return "Error desconocido.";
	}
	return "Error desconocido.";
}
	
}