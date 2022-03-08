

#ifndef OCTETOS_SATURNO_HH
#define OCTETOS_SATURNO_HH

#include <random>
#include <filesystem>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Array.hh"
#include "Sort.hh"
#include "search-binary.hh"

namespace oct::sat
{

class RandomString
{
public:
	virtual void generate(char*,unsigned int) = 0;
};

class RandomHash : public RandomString
{
public:
	RandomHash();
	~RandomHash();
	virtual void generate(char*,unsigned int);

private:
	std::default_random_engine generator;
	std::uniform_int_distribution<int>* alpha;
	std::uniform_int_distribution<int>* number;
	std::bernoulli_distribution* selection;
};


template <Data S,typename Key,Index I = unsigned int> class Engine
{
public:
	Engine(I length) : db(length),binary(db),merge(db),count(0)
	{
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

	void asc()
	{
		merge.asc();
	}
	void desc()
	{
		merge.desc();
	}

	I get_count()const
	{
		return count;
	}
	Array<S,I>& get_db()
	{
		return db;
	}
protected:
	Array<S,I> db;
	Binary<S,Key,I> binary;
	Merge<S,I> merge;
	I count;
	//static const I book_size_default = 1000000;
};

}

#endif