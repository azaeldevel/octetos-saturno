
#ifndef OCTETOS_SATURNO_SORT_HH
#define OCTETOS_SATURNO_SORT_HH



#include "Array.hh"
#include "Exception.hh"

namespace oct::sat
{

template <Data S,Index I = unsigned int> class Sort
{
public:
	virtual void sort(bool asc, bool unique) = 0;
};


}


#endif