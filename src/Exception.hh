
#ifndef OCTETOS_SATURNO_EXCEPTION_HH
#define OCTETOS_SATURNO_EXCEPTION_HH

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


#if defined(__linux__)
    #include <octetos/core/Exception-v3.hh>
#elif defined(_WIN32) || defined(_WIN64)
    #include <Exception-v3.hh>
#else
	#error "Plataforma desconocida"
#endif

namespace oct::sat
{

class Exception : public core::v3::Exception
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
		DUPLICATED_KEY,
	};

public:
	Exception();
	Exception(unsigned int code);
	Exception(unsigned int code,const char* subject);
	Exception(unsigned int code,const char* filename, unsigned int line);
	Exception(unsigned int code,const char* subject,const char* filename, unsigned int line);

	virtual const char* what () const throw ();

private:
};

}

#endif
