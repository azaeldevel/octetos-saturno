

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


template <Data S,typename Key,Index I = unsigned int> class Engine
{
public:
	Engine(I length) : db(new Array<S,I>(length)),binary(new Binary<S,Key,I>(*db)),sorter(new MergeTopDown<S,I>(*db)),free_db(true)
	{
	}
	Engine(Array<S,I>& d) : db(&d),binary(new Binary<S,Key,I>(*db)),sorter(new MergeTopDown<S,I>(*db)),free_db(false)
	{
	}
	virtual ~Engine()
	{
		delete sorter;
		delete binary;
		if(free_db) delete db;
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


	Array<S,I>& get_array()
	{
		return *db;
	}
	const Array<S,I>& get_array() const
	{
		return db;
	}
protected:	
	Array<S,I>* db;
private:
	Search<S,Key,I>* binary;
	Sort<S,I>* sorter;
	bool free_db;
};


}

#endif