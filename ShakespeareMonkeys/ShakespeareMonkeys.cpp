// ShakespeareMonkeys.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#include "Utils.h"
#include <iostream>
#include <vector>
#include <string>
#include "Utils.h"

using std::vector;



namespace SIMPLE_GA {


	class Chromosome
	{
	public:



		char *genes;// = new char[18];
		char *target;
		int num_genes = 18;

		float fitness;

		Chromosome()
		{

		}

		void SetTarget(char* buff)
		{
			bool check = false; // don#t bother 
			if (check)
			{
				int sz = sizeof(buff);
				if (sz != num_genes) return;
			}

			for (int i = 0; i < num_genes; i++)
				target[i] = buff[i];

		}

		void Initialize()
		{
			genes = new char[num_genes+1];
			target = new char[num_genes+1];

			for (int i = 0; i < num_genes; i++) {
				//Picking randomly from a range of characters with ASCII values between 32 and 128. For more about ASCII : http ://en.wikipedia.org/wiki/ASCII
				genes[i] = (char)RandomInt(32, 128);
			}
			genes[num_genes] = '\0';
			target[num_genes] = '\0';
		}


		void Fitness() {
			int score = 0;
			for (int i = 0; i < num_genes; i++) {
				//Is the character correct ?
				if (genes[i] == target[i]) {
					//If so, increment the score.
					score++;
				}
			}
			//Fitness is the percentage correct.
			fitness = float(score) / (float)num_genes;
			//fitness = fitness * fitness;
		}

		Chromosome* crossover(Chromosome *partner) {
			Chromosome *child = new Chromosome();
			child->num_genes = this->num_genes;
			child->Initialize();
			child->SetTarget(this->target);
			int midpoint = int(RandomInt(0, num_genes));
			for (int i = 0; i < num_genes; i++) {
				if (i > midpoint) child->genes[i] = genes[i];
				else   {
					if (partner != 0)
						child->genes[i] = partner->genes[i];
				}
			}
			return child;
		}


		void crossover2(Chromosome *partnerA, Chromosome* partnerB) {

			//child->num_genes = this->num_genes;
			//child->Initialize();
			//child->SetTarget(this->target);
			this->fitness = 0.0f;

			int midpoint = int(RandomInt(0, num_genes));
			for (int i = 0; i < num_genes; i++) {
				if (i > midpoint) genes[i] = partnerA->genes[i];
				else   {
					if (partnerB != 0)
						genes[i] = partnerB->genes[i];
				}
			}
		}

		//Mutation
		void mutate(float mutationRate) {
			for (int i = 0; i < num_genes; i++) {
				if (RandomFloat(0.0, 1.0) < mutationRate) {
					genes[i] = (char)RandomInt(32, 128);
				}
			}
		}
	};

	class Population
	{
	public:

		vector<Chromosome*> population;
		unsigned int population_size = 200;

		float mutationRate = 0.03;

		float sumFitness;

		float best_fitness = 0.0f;
		int best_index = 0;

		bool match = false;

		char* target = "to be or not to be";

		Population()
		{

		}

		Population(int sz){
			population_size = sz;
		}

		std::string  GetBest()
		{
			std::string the_best(population[best_index]->genes);

			the_best += "\0";
			return the_best;
		}
		void Initialize()
		{
			for (int i = 0; i < population_size; i++) {
				//Initializing each member of the population

				Chromosome* dna = new Chromosome();
				dna->num_genes = 18;
				dna->Initialize();
				dna->SetTarget(target);
				population.push_back(dna);


			}
		}


		void Old_Breeding()
		{
			std::vector<Chromosome*> mating_pool;

			int best = 0;
			int best_index = 0;
			for (int i = 0; i < population.size(); i++) {

				//n is equal to fitness times 100, which leaves us with an integer between 0 and 100.

				int n = int(population[i]->fitness * 100);
				if (n > best) {
					best = n;
					best_index = i;
				}
				for (int j = 0; j < n; j++) {
					//	Add each member of the population to the mating pool N times.
					mating_pool.push_back(population[i]);
				}
			}

			char best_string[19];
			//strcpy_s(best_string, population[best_index]->genes);
			for (int i = 0; i < 18; i++)
				best_string[i] = population[best_index]->genes[i];


			for (int i = 0; i < population.size(); i++) {
				int a = int(RandomInt(0, mating_pool.size() - 1));
				int b = int(RandomInt(0, mating_pool.size() - 1));
				if (a == b){ if (a < mating_pool.size() - 2)b = a + 1; else b = 0; }

				// crossover
				// mutation
				// etc
			}
			mating_pool.clear();
		}

		// Improved Roulette Wheel 
		// Mathematically computes the index into a large array and 
		// selects the correct element from the small array
		int ChooseParent()
		{
			int randSelector = (int)RandomFloat(0, sumFitness) * 100;

			// Translate this number to the corresponding member**
			int memberID = 0;
			int partialSum = 0;

			for (int i = 0; i < population.size(); i++) {
				int n = (int)(population[i]->fitness * 100);
				if (partialSum < randSelector && partialSum + n >= randSelector)
				{
					return i;
				}
				partialSum += n;
				/*			for (int j = 0; j < n; j++)
				{
				partialSum += 1;
				if (partialSum == randSelector)
				{
				return i;
				}
				}*/
			}

			int alternate = RandomInt(0, 99);

			return this->best_index;

			/*while (randSelector  > partialSum)
			{
			partialSum += population[memberID]->fitness;// / sumFitness;// fitness(memberID);
			memberID++;
			}*/

			//return memberID;
		}

		void Update()
		{
			best_fitness = 0.0f;
			sumFitness = 0.0f;
			//evaluate fitness
			for (int i = 0; i < population.size(); i++) {
				//population[i]->Fitness();
				population[i]->Fitness();

				sumFitness += population[i]->fitness;

				if (population[i]->fitness > best_fitness)
				{
					best_fitness = population[i]->fitness;
					best_index = i;
				}
			}

			// Find the sum of fitnesses. The function fitness(i) should 
			//return the fitness value   for member i**


			//for (int i = 0; i < nmembers; i++)
			//	sumFitness += fitness(i);


			// Get a floating point number in the interval 0.0 ... sumFitness**
			//float randomNumber = (float(rand() % 10000) / 9999.0f) * sumFitness;




			for (int i = 0; i < population.size(); i++) {
				//int a = int(RandomInt(0, mating_pool.size() - 1));
				//int b = int(RandomInt(0, mating_pool.size() - 1));
				//if (a == b){ if (a < mating_pool.size() - 2)b = a + 1; else b = 0; }
				//if (population[i]->fitness  > 0.8) continue;

				if (i == this->best_index) continue;  // the best scoring Chromosome makes it to the next generation

				int a = this->ChooseParent();
				int b = this->ChooseParent();

				if (a == b) if (a <= population.size() - 2)b = a + 1; else b = 0;

				Chromosome *partnerA = population[a];
				Chromosome *partnerB = population[b];

				//Step 3a: Crossover
				population[i]->crossover2(partnerA, partnerB);
				
				//Step 3b: Mutation 
				population[i]->mutate(mutationRate);


			}
		}


		void Delete()
		{
			for (int i = 0; i < population.size(); i++)
			{
				delete population[i];
				population[i] = 0;
			}

			population.clear();
		}
	};
};

using namespace SIMPLE_GA;

class SimpleExample
{
protected:
	bool m_bDeleted = false;
public:

	SimpleExample(){}
	~SimpleExample(){
		if (m_bDeleted == false)
			this->Delete();
	}

	virtual void Initialize(){}
	virtual void Run(){}
	virtual void Draw(){};
	virtual void Delete(){};
	virtual void keyboard(unsigned char key, int x, int y){};
	virtual void keyboardup(unsigned char key, int x, int y){};
	virtual void Special(int key, int x, int y){};

	virtual void mouse(int button, int state, int x, int y){}
};

class SimpleGA : public SimpleExample
{
public:

	int population_size = 100;

	char* target = "to be or not to be";
	float mutationRate = 0.01;


	Population population3;

	void SetPopulationSize(int n){ this->population_size = n; }

	void Initialize()
	{
		//population = new DNA*[population_size];
		population3.Initialize();


	}
	bool solved = false;

	void Run() {

		if (solved == false)
		{
			population3.Update();

			static int generation_count = 0;
			std::cout << "generation" << generation_count++ << ", best answer: " << population3.GetBest() << std::endl;

			if (population3.best_fitness > 0.98f)solved = true;
		}
	}

	void keyboard(unsigned char key, int x, int y){}
	void keyboardup(unsigned char key, int x, int y){}
	void Special(int key, int x, int y){};

	void mouse(int button, int state, int x, int y){}

	void Delete(){
		/*		for (int i = 0; i < population_size; i++)
		{
		delete population2[i];
		population2[i] = 0;
		}

		population2.clear();
		*/
		population3.Delete();
		//mating_pool.clear();
		this->m_bDeleted = true;

	}
};

int _tmain(int argc, _TCHAR* argv[])
{

	SimpleGA *example = new  SimpleGA();
	example->Initialize();
	while (example->solved == false)
		example->Run();

	
	example->Delete();

	return 0;
}


