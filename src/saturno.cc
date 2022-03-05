

#include "saturno.hh"

namespace oct::sat
{

RandomHash::RandomHash()
{
	alpha = new std::uniform_int_distribution<int>(97,122);
	number = new std::uniform_int_distribution<int>(48,57);
	selection = new std::bernoulli_distribution(0.6);
}

RandomHash::~RandomHash()
{
	delete alpha;
	delete number;
	delete selection;
}

void RandomHash::generate(char* string,unsigned int length)
{
	for(unsigned int i = 0; i < length; i++)
	{
		if(selection->operator()(generator))
		{
			string[i] = (char)(alpha->operator()(generator));
		}
		else
		{
			string[i] = (char)(number->operator()(generator));
		}
	}
}

}