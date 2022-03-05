
#ifndef OCTETOS_SATURNO_SORT_HH
#define OCTETOS_SATURNO_SORT_HH

#include <string.h>
#include "Array.hh"
#include "Exception.hh"

namespace oct::sat
{


template <typename T,typename S> class Sort
{

};

struct Data
{
	const char* index;
	unsigned int length;
};
template <typename S,typename I = unsigned int> class Merge
{
public:
	Merge(const Array<S>& in) : input(in), buffer(in.size(),false)
	{
		
	}

	void sort()
	{
		copy(0,input.size());
		split((S**)buffer,0,input.size(),(S**)input);
	}

	void split(S** out,I begin, I end,S** in)
	{
		if (end - begin <= 1) return;

		I middle = (begin + end) / 2;
		
		split(in,begin,middle,out);
		split(in,middle,end,out);

		merge(out,begin,middle,end,in);
	}

	bool compare(I i, I j)
	{
		I min_length = std::min(strlen(input[i].index),strlen(input[j].index));
		for(I c = 0; c < min_length; c++)
		{
			if(input[i].index[c] > input[j].index[c])
			{
				return false;
			}
		}

		return true;
	}
	void merge(S** in,I begin, I middle, I end,S** out)
	{
		I i = begin;
		I j = middle;

		for(I k = begin; k < end; k++)
		{
			if (i < middle && (j >= end || compare(i,j)))
			{
				out[k] = in[i];
				i++;
			}
			else
			{
				out[k] = in[j];
				j++;
			}
		}
	}
	void copy(I begin, I end)
	{
		S** in = (S**) input;
		S** bf = (S**) buffer;
		for(I i = begin; i < end; i++)
		{
			bf[i] = in[i];
		}
	}
private:
	const Array<S>& input;
	Array<S> buffer;
};

}


#endif