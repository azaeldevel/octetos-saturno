
#ifndef OCTETOS_SATURNO_ARRAY_HH
#define OCTETOS_SATURNO_ARRAY_HH

#include <iostream>
#include <string.h>


namespace oct::sat
{

template <typename I> concept Index = std::unsigned_integral<I>;

template <typename S> concept Searchable = requires (S data)
{
	data.keys;
	data.operator <();
};



template <Index I = unsigned int> struct Data	
{
	const char* keys;
	unsigned int length;

	bool operator < (const Data& d) const
	{
		//std::cout << "\t" << index << " < " << d.index << "\n";
		I min_length = std::min(strlen(keys),strlen(d.keys));
		for(I c = 0; c < min_length; c++)
		{
			//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
			if(keys[c] < d.keys[c]) 
			{
				//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
				return true;
			}
			else if(keys[c] > d.keys[c]) 
			{
				//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
				return false;
			}
		}
		
		return false;
	}
};

template <template<typename> typename S,Index I = unsigned int> class Array
{
public:
	Array(I l, bool a = true) : length(l), auto_delete(a)
	{
		array = new S<I>*[length];
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
	S<I>& operator [](I index)
	{
		return *(array[index]);
	}
	const S<I>& operator [](I index)const
	{
		return *(array[index]);
	}
	explicit operator S<I>**()
	{
		return array;
	}

	I size() const
	{
		return length;
	}
private:
	I length;
	S<I>** array;
	bool auto_delete;
};

}

#endif