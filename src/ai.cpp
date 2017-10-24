#include "ai.h"

#include "random.h"

/*
 * Samo za debug
 */

#include <iostream>

std::ostream &operator<<(std::ostream &lhs, const DNA &rhs)
{
    std::vector<ElementOperacije> dna = rhs.getDna();

    for(auto it = dna.begin(); it != dna.end(); it++)
    {
        if(it->tip == TipElementaOperacijeOperator)
        {
            switch(it->vrednost.operacija)
            {
                case OperatorPlus:
                    lhs << "+";
                    break;
                case OperatorMinus:
                    lhs << "-";
                    break;
                case OperatorPuta:
                    lhs << "*";
                    break;
                case OperatorPodeljeno:
                    lhs << "/";
                    break;
            }
        } else
        {
            lhs << it->vrednost.operand;
        }
    }

    return lhs;
}

/*
 * Samo za debug
 */

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
    reprodukcija();
    mutacija();

    /*
    for(auto it = m_populaicja.begin(); it != m_populaicja.end(); it++)
    {
        std::cout << *it << std::endl;
    }
    */

    return m_populaicja[0].getDna();
}

void AI::kreirajPrvuGeneraciju(void)
{
    Random random;
    m_populaicja.clear();
    for(int i = 0; i < m_velicinaPopulacije; i++)
    {
        m_populaicja.push_back(DNA::generisiSlucajnuFormulu(random.nextInt(5) + 2));
    }
}

void AI::reprodukcija(void)
{
    /*
     * Proces selekcije
     */

    std::vector<DNA> selekcija;
    for(auto it = m_populaicja.begin(); it != m_populaicja.end(); it++)
    {
        float kvalitet = it->kvalitet(m_rezultat, m_ponudjeniBrojevi);
        int broj = kvalitet * 1000;
        for(int i = 0; i < broj; i++)
        {
            selekcija.push_back(*it);
        }
    }

    /*
     * Reprodukcija
     */

    m_populaicja.clear();
    for(int i = 0; i < m_velicinaPopulacije; i++)
    {
        DNA roditelj1 = selekcija[m_random.nextInt(selekcija.size())];
        DNA roditelj2 = selekcija[m_random.nextInt(selekcija.size())];
        m_populaicja.push_back(roditelj1.reprodukcija(roditelj2));
    }
}

void AI::mutacija(void)
{
    for(auto it = m_populaicja.begin(); it != m_populaicja.end(); it++)
        it->mutacija(m_konstantaMutacije);
}
