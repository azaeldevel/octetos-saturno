

#ifndef OCTETOS_SATURNO_ENGINE_HH
#define OCTETOS_SATURNO_ENGINE_HH

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