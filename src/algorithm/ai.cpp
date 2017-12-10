#include "algorithm/ai.h"

#include <iostream>

AI::AI(int32_t result, const std::vector<int32_t> &numbers)
    : m_populationSize(DEFAULT_POPULATION_SIZE),
      m_mutationRante(DEFAULT_MUTATION_RATE)
{
}

AI::~AI(void)
{
}

std::shared_ptr<Tree> AI::findExpression(void)
{
    generateInitialPopulation();
    for(auto it = m_population.begin(); it != m_population.end(); it++)
    {
        std::cout << *(*it) << std::endl;
    }

    return nullptr;
}

void AI::generateInitialPopulation(void)
{
    for(int i = 0; i < m_populationSize; i++)
    {
        int32_t rand = m_random.nextInt(6) + 1;
        m_population.push_back(Tree::generateRandomTree(rand));
    }
}

void AI::selection(void)
{
}

void AI::reproduction(void)
{
}

void AI::mutation(void)
{
}
