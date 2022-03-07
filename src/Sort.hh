
#ifndef OCTETOS_SATURNO_SORT_HH
#define OCTETOS_SATURNO_SORT_HH



#include "Array.hh"
#include "Exception.hh"

namespace oct::sat
{



template <Data S,Index I = unsigned int> class Merge
{
public:
	Merge(Array<S,I>& in) : input(in), buffer(in.size(),false)
	{
	}

	void sort()
	{
		copy(0,input.size());
		split((S**)buffer,0,input.size() - 1,(S**)input);
	}
	void split(S** out,I begin, I end,S** in)
	{
		if (end - begin < 1) return;
		//std::cout << "new split >>>\n";
		I middle = begin + (end - begin) / 2;
		/*std::cout << "begin = " << begin << "\n";
		std::cout << "middle = " << middle << "\n";
		std::cout << "end = " << end << "\n";*/
		split(in,begin,middle,out);
		split(in,middle+1,end,out);

		merge(out,begin,middle+1,end,in);
	}
	void merge(S** in,I begin, I middle, I end,S** out)
	{
		I i = begin;
		I j = middle;
		I k = begin;

		/*std::cout << "new merge >>>\n";
		std::cout << "input merge >>>\n";
		for(I i = begin; i <= end; i++)
		{
			std::cout << "\t" << in[i]->index << "\n";
		}
		std::cout << "index merge >>>\n";
		std::cout << "begin = " << begin << "\n";
		std::cout << "middle = " << middle << "\n";
		std::cout << "end = " << end << "\n";*/
		while(i < middle && j <= end)
		{
			//std::cout << "\t" << i << " < " << j << "\n";
			//std::cout << "\t" << in[i]->index << " < " << in[j]->index;
			if (*in[i] < *in[j])
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
		/*std::cout << "result merge >>>\n";
		for(I i = begin; i <= end; i++)
		{
			std::cout << "\t" << out[i]->index << "\n";
		}
		std::cout << "new merge <<<\n\n	";*/
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
};

}


#endif