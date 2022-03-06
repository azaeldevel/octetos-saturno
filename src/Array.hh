
#ifndef OCTETOS_SATURNO_ARRAY_HH
#define OCTETOS_SATURNO_ARRAY_HH

#include <iostream>
#include <string.h>


namespace oct::sat
{

template <typename I = unsigned int> struct Data	
{
	const char* index;
	unsigned int length;

	bool operator < (const Data& d) const
	{
		//std::cout << "\t" << index << " < " << d.index << "\n";
		I min_length = std::min(strlen(index),strlen(d.index));
		for(I c = 0; c < min_length; c++)
		{
			//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
			if(index[c] < d.index[c]) 
			{
				//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
				return true;
			}
			else if(index[c] > d.index[c]) 
			{
				//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
				return false;
			}
		}
		
		return false;
	}
};

template <template<typename> typename S,typename L = unsigned int> class Array
{
public:
	Array(L l, bool a = true) : length(l), auto_delete(a)
	{
		array = new S<L>*[length];
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
			for(unsigned int i = 0; i < length; i++)
			{
				delete array[i];
			}
		}
		delete[] array;
	}
	S<L>& operator [](L index)
	{
		return *(array[index]);
	}
	const S<L>& operator [](L index)const
	{
		return *(array[index]);
	}
	explicit operator S<L>**()
	{
		return array;
	}

	L size() const
	{
		return length;
	}
private:
	L length;
	S<L>** array;
	bool auto_delete;
};

}

#endif