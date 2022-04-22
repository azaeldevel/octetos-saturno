
#ifndef OCTETOS_SATURNO_ARRAY_HH
#define OCTETOS_SATURNO_ARRAY_HH

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

#include <iostream>
#include <string.h>
#include <concepts>

#include "Exception.hh"

namespace oct::sat
{

template <typename I> concept Index = std::unsigned_integral<I>;

template <typename S> concept Data = requires (S data,S comp)
{
	//data.key;
	data < comp;
	data > comp;
	data == comp;
	//data < comp.key;
	//data > comp.key;
	//data == comp.key;
	std::default_initializable<S>;
	//std::destructible<S>;
};



template <Data S,Index I = unsigned int> class Array
{
public:
	Array(I l, bool a) : length(l), auto_delete(a)
	{
		array = new S*[length];
		if(auto_delete)
		{
			for(unsigned int i = 0; i < length; i++)
			{
				array[i] = new S;
			}
		}
	}
	Array(const Array<S,I>& a) : length(a.size()), auto_delete(true)
	{
		array = new S*[length];
		for(unsigned int i = 0; i < length; i++)
		{
				array[i] = new S(*a.array[i]);
		}
	}
	Array(I l) : length(l), auto_delete(true)
	{
		array = new S*[length];
		//TODO: Crear bloque completo en una sola llamada
		for(unsigned int i = 0; i < length; i++)
		{
			array[i] = new S;
		}
	}
	~Array()
	{
		if(auto_delete)
		{
			for(I i = 0; i < length; i++)
			{
				delete array[i];
			}
		}
		delete[] array;
	}
	S& operator [](I index)
	{
		return *(array[index]);
	}
	const S& operator [](I index)const
	{
		return *(array[index]);
	}
	explicit operator S**()
	{
		return array;
	}
	explicit operator const S**() const
	{
		return (const S**)array;
	}

	I size() const
	{
		return length;
	}

private:
	I length;
	S** array;
	bool auto_delete;
};

template <Data S, Index I = unsigned int> class Block
{
public:
	Block(I leng) : length(leng)
	{
		block = new S[length];
	}
	Block(const Block<S,I>& a)
	{
		length = a.length;
		block = new S[length];
		for(I i = 0; i < length; i++)
		{
			block[i] = a[i];
		}
	}
	~Block()
	{
		delete[] block;
	}


	explicit operator S* ()
	{
		return block;
	}
	explicit operator const S* () const
	{
		return block;
	}
	S& operator [](I index)
	{
		if (index >= length) throw Exception(Exception::OUT_OF_RANGE,__FILE__,__LINE__);
		
		return block[index];
	}
	const S& operator [](I index) const
	{
		if (index >= length) throw Exception(Exception::OUT_OF_RANGE,__FILE__,__LINE__);
		
		return block[index];
	}

	I size() const
	{
		return length;
	}

private:
	S* block;
	I length;
};

}

#endif