

#ifndef OCTETOS_SATURNO_HH
#define OCTETOS_SATURNO_HH

/*
 * Copyright (C) 2022 Azael R. <azael.devel@gmail.com>
 * 
 * octetos-saturno is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * octetos-saturno is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Engine.hh"

namespace oct::sat
{

class OCTETOS_SATURNO_DECLSPCE_DLL RandomString
{
public:
	virtual void generate(char*,unsigned int) = 0;
};

class OCTETOS_SATURNO_DECLSPCE_DLL RandomHash : public RandomString
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