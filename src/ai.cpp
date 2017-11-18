#include "ai.h"

#include "core/random.h"

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

    uint32_t i = 0;
    while(true)
    {
        reprodukcija();

        std::cout << "============================================"<< std::endl;
        for(auto it = m_populaicja.begin(); it != m_populaicja.end(); it++)
        {
            std::cout << *it << std::endl;
        }
        std::cout << DNA(m_najboljaFormula) << "\t"
                  << m_najboljiKvalitet << std::endl;

        if(m_najboljiKvalitet >= 1.0f || i++ > 100)
            break;
    }

    return m_najboljaFormula;
}

void AI::kreirajPrvuGeneraciju(void)
{
    Random random;
    m_populaicja.clear();
    for(int i = 0; i < m_velicinaPopulacije; i++)
    {
        m_populaicja.push_back(DNA::generisiSlucajnuFormulu(random.nextInt(2) + 2));
    }

    auto it = m_populaicja.begin();
    it->izracunajVrednost(m_ponudjeniBrojevi);
    m_najboljaFormula = it->getFormula();
    m_najboljiKvalitet = it->kvalitet(m_rezultat);
}

void AI::reprodukcija(void)
{
    /*
     * Proces selekcije
     */

    std::vector<DNA> selekcija;
    float sum = 0.0f;
    for(auto it = m_populaicja.begin(); it != m_populaicja.end(); it++)
    {
        it->izracunajVrednost(m_ponudjeniBrojevi);

        float kvalitet = it->kvalitet(m_rezultat);
        if(kvalitet > m_najboljiKvalitet)
        {
            m_najboljiKvalitet = kvalitet;
            m_najboljaFormula = it->getFormula();
        }

        int broj = kvalitet * 100;
        if(broj <= 0)
            broj = 1;
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
        (--m_populaicja.end())->mutacija(m_konstantaMutacije);
    }
}
