

#ifndef OCTETOS_SATURNO_HH
#define OCTETOS_SATURNO_HH

#include <random>

namespace oct::sat
{

class RandomString
{
public:
	virtual void generate(char*,unsigned int) = 0;
};

class RandomHash : public RandomString
{
public:
	RandomHash();
	~RandomHash();
	virtual void generate(char*,unsigned int);

private:
	std::default_random_engine generator;
	std::uniform_int_distribution<int>* alpha;
	std::uniform_int_distribution<int>* number;
	std::bernoulli_distribution* selection;
};

}

#endif