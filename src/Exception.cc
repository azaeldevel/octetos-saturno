
/*
 * Copyright (C) 2022 Azael R. <azael.devel@gmail.com>
 * 
 * octetos-saturno is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * octetos-saturno is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "Exception.hh"

namespace oct::sat
{
	
Exception::Exception()
{

}
Exception::Exception(unsigned int c) : core::v3::Exception(c)
{
}
Exception::Exception(unsigned int c,const char* s) : core::v3::Exception(c,s)
{
}
Exception::Exception(unsigned int c,const char* f, unsigned int l) : core::v3::Exception(c,f,l)
{
}
Exception::Exception(unsigned int c,const char* s,const char* f, unsigned int l) : core::v3::Exception(c,s,f,l)
{
}

const char* Exception::what () const throw ()
{
	switch(code())
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
	case Errors::DUPLICATED_KEY:
		return "Llave duplicada.";
	default:
		return "Error desconocido.";
	}
	return "Error desconocido.";
}
	
}