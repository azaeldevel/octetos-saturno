

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
		//std::cout << "value = " << value << "\n";
		return search(value,0,input.size()-1);
	}

	S* search(V value, I begin, I end)
	{
		//std::cout << "Buscando en [" << begin << "," << end << "]\n";
		I middle = (begin + end)/ 2;
		//std::cout << "middle = " << middle << "\n";

		if(input[middle] < value)
		{
			//std::cout << "\t --> " << value << "\n";
			return search(value,middle,end);
		}
		else if(input[middle] > value)
		{
			//std::cout << "\t --> " << value << "\n";
			return search(value,begin,middle);
		}
		else if(input[middle] == value)
		{
			//std::cout << "\t --> " << value << "\n";
			return &input[middle];
		}

		return NULL;
	}
private:
	Array<S,I>& input;
};

}

#endif