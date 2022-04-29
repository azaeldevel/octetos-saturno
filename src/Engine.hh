

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
	Engine(I length) : db(new Array<S,I>(length)),binary(new Binary<S,Key,I>(*db)),sorter(new MergeTopDown<S,I>(*db))
	{
	}
	Engine(Array<S,I>& d) : db(&d),binary(new Binary<S,Key,I>(*db)),sorter(new MergeTopDown<S,I>(*db))
	{
	}
	Engine(const std::filesystem::path& in) : db(NULL), sorter(NULL), binary(NULL)
	{
		load(in);
	}
	virtual ~Engine()
	{
		if(sorter) delete sorter;
		if(binary) delete binary;
		if(db) delete db;
	}

	const v1::Header<I>& get_header()const
	{
		return header;
	}

	//virtual bool load(std::ifstream& file) = 0;
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


	Array<S,I>& get_array()
	{
		return *db;
	}
	const Array<S,I>& get_array() const
	{
		return *db;
	}
	bool load(const std::filesystem::path& in)
	{
		//std::cout << "Step 1.\n";
		std::ifstream file(in, std::ios::binary);
		//std::cout << "Step 2.\n";		
		file.read(reinterpret_cast<char*>(&header.ver),sizeof(header.ver));
		//std::cout << "ver : " << header.ver << "\n";
		switch(header.ver)
		{
		case 1:
			file.read(reinterpret_cast<char*>(&header.counter),sizeof(v1::Header<I>::counter));
			//std::cout << "header.counter  : " << header.counter << "\n";
			break;
		default:
			throw Exception(Exception::UNKNOW_VERSION_HEADER,__FILE__,__LINE__);
		}
		//std::cout << "Step 3.\n";
		db = new Array<S,I>(header.counter);
		//std::cout << "Step 4.\n";
		file.read((char*)(S*)*db,sizeof(S) * header.counter);
		//std::cout << "Step 5.\n";
		binary = new Binary<S,Key,I>(*db);
		//std::cout << "Step 6.\n";
		sorter = new MergeTopDown<S,I>(*db);
		//std::cout << "Step 7.\n";
		return true;
	}
	bool save(const std::filesystem::path& out)
	{
		std::ofstream fileout(out, std::ios::out | std::ios::binary);
		header.counter = db->size();
		//header.ver = 1;
		switch(header.ver)
		{
		case 1:
			fileout.write(reinterpret_cast<const char*>(&header.ver),sizeof(v1::Header<I>::ver));
			fileout.write(reinterpret_cast<const char*>(&header.counter),sizeof(v1::Header<I>::counter));
			//fileout << header.ver;
			//fileout << header.counter;
			break;
		default:
			throw Exception(Exception::UNKNOW_VERSION_HEADER,__FILE__,__LINE__);
		}
		/*
		for(I i = 0; i < db->size(); i++)
		{
			std::cout << db->operator[](i).key << " -> " << (db->operator[](i).voto? "Si" : "No") << "\n";
		}
		*/
		fileout.write((char*)(S*)*db, sizeof(S) * header.counter);
		fileout.flush();
		fileout.close();
		
		return true;
	}
protected:	
	Array<S,I>* db;
	
private:
	Search<S,Key,I>* binary;
	Sort<S,I>* sorter;
	v1::Header<I> header;
};
}

#endif