#include "algorithm/ai.h"

#include <iostream>

AI::AI(int32_t targetNumber, const std::vector<int32_t> &numbers)
    : m_populationSize(DEFAULT_POPULATION_SIZE),
      m_mutationRante(DEFAULT_MUTATION_RATE),
      m_targetNumber(targetNumber),
      m_numbers(numbers)
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
        //std::cout << *(*it) << std::endl;
    }
    selection();

    return m_bestExpression;
}

void AI::generateInitialPopulation(void)
{
    m_population.clear();
    for(int i = 0; i < m_populationSize; i++)
    {
        int32_t rand = m_random.nextInt(6) + 1;
        std::shared_ptr<Tree> tree = Tree::generateRandomTree(rand);
        //tree->reduce(m_numbers);
        m_population.push_back(tree);
    }
    m_bestExpression = m_population[0];
    m_bestFitness = 1 / (m_targetNumber - m_bestExpression->calculate(m_numbers) + 1);

    selection();
    std::cout << "Fitness: " << m_bestFitness << std::endl
              << *m_bestExpression << std::endl;
}

void AI::selection(void)
{
    for(auto it = m_population.begin(); it != m_population.end(); it++)
    {
        std::cout << **it << std::endl;
        (*it)->reduce(m_numbers);
        std::cout << **it << std::endl;
        float fitness = 1 / (m_targetNumber - (*it)->calculate(m_numbers) + 1);
        if(fitness > m_bestFitness)
        {
            m_bestFitness = fitness;
            m_bestExpression = *it;
        }
    }

    std::cout << "Fitness: " << m_bestFitness << std::endl
              << *m_bestExpression << std::endl;
}

void AI::reproduction(void)
{
}

void AI::mutation(void)
{
}
