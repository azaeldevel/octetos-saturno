

#ifndef OCTETOS_SATURNO_ENGINE_HH
#define OCTETOS_SATURNO_ENGINE_HH

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

#include <random>
#include <filesystem>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Array.hh"
#include "sort-merge.hh"
#include "search-binary.hh"

namespace oct::sat
{
	namespace v1
	{
		template <Index I = unsigned int> struct Header
		{
			unsigned short ver;
			I counter;
			
			Header() : ver(1)
			{
			}			
		};
	}

template <Data S,typename Key,Index I = unsigned int> class Engine
{
public:
	Engine(I length) : db(new Block<S,I>(length)),binary(new Binary<S,Key,I>(*db)),sorter(new MergeTopDown<S,I>(*db))
	{
	}
	Engine(Block<S,I>& d) : db(&d),binary(new Binary<S,Key,I>(*db)),sorter(new MergeTopDown<S,I>(*db))
	{
	}
	Engine(const std::filesystem::path& in)
	{
		load(in);
	}
	virtual ~Engine()
	{
		delete sorter;
		delete binary;
	}

	virtual bool load(std::ifstream& file) = 0;
	virtual I get_actual()const = 0;
	
	S* search(Key key)
	{
		return binary->search(key);
	}
	const S* search(Key key) const
	{
		return binary->search(key);
	}

	virtual void sort(bool asc, bool unique)
	{
		sorter->sort(asc,unique);
	}


	Block<S,I>& get_array()
	{
		return *db;
	}
	const Block<S,I>& get_array() const
	{
		return *db;
	}
	void load(const std::filesystem::path& in)
	{
		std::ifstream file(in, std::ios::binary);
		file.read(static_cast<char*>(header.ver),sizeof(header.ver));
		switch(header.ver)
		{
		case 1:
			file.read(static_cast<char*>(&header),sizeof(v1::Header<I>));
			break;
		default:
			throw Exception(Exception::UNKNOW_VERSION_HEADER,__FILE__,__LINE__);
		}
		db = new Block<S,I>(header.counter);
		file.read(static_cast<char*>((S*)db),sizeof(S) * header.counter);
		binary = new Binary<S,Key,I>(*db);
		sorter = new MergeTopDown<S,I>(*db);
	}
	void save(const std::filesystem::path& out)
	{
		std::ofstream file(out, std::ios::binary);
		header.counter = db->size();
		file.write(reinterpret_cast<const char*>(&header),sizeof(v1::Header<I>));
		file.write((const char*)(S*)db, sizeof(S) * header.counter);
		file.flush();
		file.close();
	}
protected:	
	Block<S,I>* db;
	
private:
	Search<S,Key,I>* binary;
	Sort<S,I>* sorter;
	v1::Header<I> header;
};


}

#endif