


#ifndef OCTETOS_SATURNO_SEARCH_HH
#define OCTETOS_SATURNO_SEARCH_HH

#include "Array.hh"
#include "Exception.hh"

namespace oct::sat
{


template <Data S,typename V,Index I = unsigned int> class Search
{
public:
	virtual S* search(V value) = 0;
};

}

#endif