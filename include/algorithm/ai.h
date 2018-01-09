#ifndef _AI_H_
#define _AI_H_

#include <memory>
#include <vector>
#include <stdint.h>

#include "algorithm/tree.h"
#include "core/random.h"

#define DEFAULT_POPULATION_SIZE         50
#define DEFAULT_MUTATION_RATE           0.01

class AI
{
public:
    AI(int32_t targetNumber, const std::vector<int32_t> &numbers);
    ~AI(void);

    std::shared_ptr<Tree> findExpression(void);

private:
    void generateInitialPopulation(void);
    void selection(void);
    void reproduction(void);
    void mutation(void);

    int32_t m_targetNumber;
    std::vector<int32_t> m_numbers;

    std::shared_ptr<Tree> m_bestExpression;
    float m_bestFitness;

    int32_t m_populationSize;
    float m_mutationRante;

    std::vector<std::shared_ptr<Tree>> m_population;

    Random m_random;
};

#endif // _AI_H_
