

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
	Engine(I length) : db(new Array<S,I>(length)),binary(*db),count(0),sorter(new MergeTopDown<S,I>(*db))
	{
	}
	Engine(Array<S,I>& d) : db(&d),binary(*db),count(0),sorter(new MergeTopDown<S,I>(*db))
	{
	}
	virtual ~Engine()
	{
		delete sorter;
	}

	virtual bool load(std::ifstream& file) = 0;
	
	S* search(Key key)
	{
		return binary.search(key);
	}
	const S* search(Key key) const
	{
		return binary.search(key);
	}

	virtual void sort(bool asc, bool unique)
	{
		sorter->sort(asc,unique);
	}

	I get_count()const
	{
		return count;
	}
	Array<S,I>& get_db()
	{
		return *db;
	}
	const Array<S,I>& get_db() const
	{
		return db;
	}
protected:
	Array<S,I>* db;
	Binary<S,Key,I> binary;
	Sort<S,I>* sorter;
	I count;
	//static const I book_size_default = 1000000;
private:
	
};


}

#endif