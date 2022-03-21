

#ifndef OCTETOS_SATURNO_SORT_MERGE_HH
#define OCTETOS_SATURNO_SORT_MERGE_HH



#include "Sort.hh"

namespace oct::sat
{


template <Data S,Index I = unsigned int> class MergeTopDown : public Sort<S,I>
{
public:
	MergeTopDown(Array<S,I>& in) : input(in), buffer(in.size(),false)
	{
	}


	virtual void sort(bool asc, bool unique)
	{
		if(asc) comp = &S::operator<;
		else comp = &S::operator>;

		if(unique) ms = &MergeTopDown<S,I>::merge_unique;
		else ms = &MergeTopDown<S,I>::merge;

		copy(0,input.size());
		split((S**)buffer,0,input.size() - 1,(S**)input);
	}

private:
	void split(S** out,I begin, I end,S** in)
	{
		if (end - begin < 1) return;
		
		I middle = begin + (end - begin) / 2;

		split(in,begin,middle,out);
		split(in,middle+1,end,out);

		(this->*ms)(out,begin,middle+1,end,in);
	}
	void merge(S** in,I begin, I middle, I end,S** out)
	{
		I i = begin;
		I j = middle;
		I k = begin;

		while(i < middle && j <= end)
		{
			if ((*in[i].*comp)(*in[j]))
			{
				//std::cout << " : Cierto\n";
				out[k] = in[i];
				i++;
			}
			else
			{
				//std::cout << " : Falso\n";
				out[k] = in[j];
				j++;
			}
			k++;
		}
		while(i < middle )
		{
			//std::cout << "\tvaciando " << in[i]->index << "\n";
			out[k] = in[i];
			i++;
			k++;
		}
		while(j <= end )
		{
			//std::cout << "\tvaciando " << in[j]->index << "\n";
			out[k] = in[j];
			j++;
			k++;
		}
	}
	void merge_unique(S** in,I begin, I middle, I end,S** out)
	{
		I i = begin;
		I j = middle;
		I k = begin;

		while(i < middle && j <= end)
		{
			if ((*in[i].*comp)(*in[j]))
			{
				//std::cout << " : Cierto\n";
				out[k] = in[i];
				i++;
			}
			else
			{
				//std::cout << " : Falso\n";
				if(*in[i] == *in[j]) throw oct::sat::Exception(oct::sat::Exception::DUPLICATED_KEY,__FILE__,__LINE__);
				out[k] = in[j];
				j++;
			}
			k++;
		}
		while(i < middle )
		{
			//std::cout << "\tvaciando " << in[i]->index << "\n";
			out[k] = in[i];
			i++;
			k++;
		}
		while(j <= end )
		{
			//std::cout << "\tvaciando " << in[j]->index << "\n";
			out[k] = in[j];
			j++;
			k++;
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
	Array<S,I>& input;
	Array<S,I> buffer;
	typedef bool (S::* comparer)(const S&)const;
	comparer comp;
	typedef void (MergeTopDown<S,I>::* sorter)(S** in,I begin, I middle, I end,S** out);
	sorter ms;
};

}

#endif