

#ifndef OCTETOS_SATURNO_SEARCH_BINARY_HH
#define OCTETOS_SATURNO_SEARCH_BINARY_HH

#include "Array.hh"


namespace oct::sat
{

template <Data S,typename V,Index I = unsigned int> class Binary
{
public:
	Binary(Array<S,I>& in) : input(in)
	{
	}

	S* search(V value)
	{
		return search(value,0,input.size()-1);
	}

	S* search(V value, I begin, I end)
	{
		I middle = (begin + end) / 2;

		if(input[middle] < value)
		{
			return search(value,begin,middle - 1);
		}
		else if(input[middle] > value)
		{
			return search(value,middle + 1,end);
		}
		else if(input[middle] == value)
		{
			return &input[middle];
		}

		return NULL;
	}
private:
	Array<S,I>& input;
};

}

#endif