
#ifndef OCTETOS_SATURNO_ARRAY_HH
#define OCTETOS_SATURNO_ARRAY_HH

namespace oct::sat
{

template <typename S,typename L = unsigned int> class Array
{
public:
	Array(L l, bool a = true) : length(l), auto_delete(a)
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
			for(unsigned int i = 0; i < length; i++)
			{
				delete array[i];
			}
		}
		delete[] array;
	}
	S& operator [](L index)
	{
		return *(array[index]);
	}
	const S& operator [](L index)const
	{
		return *(array[index]);
	}
	explicit operator S**()
	{
		return array;
	}

	L size() const
	{
		return length;
	}
private:
	L length;
	S** array;
	bool auto_delete;
};

}

#endif