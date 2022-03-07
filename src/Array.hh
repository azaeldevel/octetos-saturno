
#ifndef OCTETOS_SATURNO_ARRAY_HH
#define OCTETOS_SATURNO_ARRAY_HH

#include <iostream>
#include <string.h>


namespace oct::sat
{

template <typename I> concept Index = std::unsigned_integral<I>;

template <typename S> concept Sortable = requires (S data,S comp)
{
	data.keys;
	data.operator<(comp);
	data.operator>(comp);
};





template <typename S,Index I = unsigned int> class Array
{
public:
	Array(I l, bool a = true) : length(l), auto_delete(a)
	{
		array = new S*[length];
		if(auto_delete)
		{
			for(unsigned int i = 0; i < length; i++)
			{
				array[i] = new S;
			}
		}
	}

	~Array()
	{
		if(auto_delete)
		{
			for(I i = 0; i < length; i++)
			{
				delete array[i];
			}
		}
		delete[] array;
	}
	S& operator [](I index)
	{
		return *(array[index]);
	}
	const S& operator [](I index)const
	{
		return *(array[index]);
	}
	explicit operator S**()
	{
		return array;
	}

	I size() const
	{
		return length;
	}
private:
	I length;
	S** array;
	bool auto_delete;
};

}

#endif