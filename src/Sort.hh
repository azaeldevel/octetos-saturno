
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

template <typename I = unsigned int> struct Data
{
	const char* index;
	unsigned int length;

	bool operator <= (const Data& d) const
	{
		I min_length = std::min(strlen(index),strlen(d.index));
		for(I c = 0; c < min_length; c++)
		{
			if(index[c] > d.index[c])
			{
				return false;
			}
		}

		return true;
	}
};
template <typename S,typename I = unsigned int> class Merge
{
public:
	Merge(Array<S>& in) : input(in), buffer(in.size(),false)
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

	void merge(S** in,I begin, I middle, I end,S** out)
	{
		I i = begin;
		I j = middle;

		for(I k = begin; k < end; k++)
		{
			if (i < middle && (j >= end || in[i] <= in[j]))
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
	Array<S>& input;
	Array<S> buffer;
};

}


#endif