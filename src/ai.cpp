#include "ai.h"

#include <iostream>     // za debug

AI::AI(uint32_t rezultat, std::vector<uint32_t> &ponudjeniBrojevi)
    : m_rezultat(rezultat),
      m_ponudjeniBrojevi(ponudjeniBrojevi),
      m_konstantaMutacije(AI_PODRAZUMEVANA_KONSTANTA_MUTACIJE),
      m_velicinaPopulacije(AI_PODRAZUMEVANA_VELICINA_POPULACIJE)
{
}

AI::~AI(void)
{
}

std::vector<ElementOperacije> AI::nadjiResenje(void)
{
    kreirajPrvuGeneraciju();
    return m_populaicja[0].getDna();
}

void AI::kreirajPrvuGeneraciju(void)
{
    m_populaicja.clear();
    for(int i = 0; i < m_velicinaPopulacije; i++)
    {
        m_populaicja.push_back(DNA::generisiSlucajnuFormulu(6));
    }
}
