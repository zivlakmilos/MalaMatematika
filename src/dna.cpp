#include "dna.h"

#include <cmath>

#include "random.h"
#include "ai.h"
#include "exception.h"

DNA::DNA(const std::vector<ElementOperacije> &dna)
    : m_dna(dna)
{
}

DNA::DNA(void)
{
}

DNA::~DNA(void)
{
}

DNA DNA::generisiSlucajnuFormulu(uint8_t brojOperanada)
{
    Random random;
    std::vector<uint8_t> operandi;
    for(int i = 0; i < 6; i++)
        operandi.push_back(i);

    std::vector<ElementOperacije> dna;

    ElementOperacije element;
    uint8_t brOperanada = 0;
    while(brojOperanada > 0)
    {
        if(brOperanada >= 2)
        {
            if(random.nextInt(2))
            {
                element.tip = TipElementaOperacijeOperator;
                element.vrednost.operacija = static_cast<Operator>(random.nextInt(OperatorZagradaOtvorena));
                brOperanada--;
            } else
            {
                uint8_t index = random.nextInt(operandi.size());
                element.tip = TipElementaOperacijeOperand;
                element.vrednost.operand = operandi[index];
                operandi.erase(operandi.begin() + index);
                brOperanada++;
                brojOperanada--;
            }
        } else
        {
            uint8_t index = random.nextInt(operandi.size());
            element.tip = TipElementaOperacijeOperand;
            element.vrednost.operand = operandi[index];
            operandi.erase(operandi.begin() + index);
            brOperanada++;
            brojOperanada--;
        }

        dna.push_back(element);
    }

    while(--brOperanada > 0)
    {
        element.tip = TipElementaOperacijeOperator;
        element.vrednost.operacija = static_cast<Operator>(random.nextInt(OperatorZagradaOtvorena));
        dna.push_back(element);
    }

    return DNA(dna);
}

float DNA::kvalitet(uint32_t rezultat, const std::vector<uint32_t> &ponudjeniBrojevi)
{
    Matematika matematika;
    std::vector<ElementOperacije> formula;

    for(auto it = m_dna.begin(); it != m_dna.end(); it++)
    {
        formula.push_back(*it);
        auto it2 = --formula.end();
        if(it2->tip == TipElementaOperacijeOperand)
        {
            it2->vrednost.operand = ponudjeniBrojevi[it->vrednost.operand];
        }
    }

    uint32_t resenje;
    try {
        resenje = matematika.racunajPostfoksnu(formula);
    } catch(Exception &ex) {
        return 0.0f;
    }

    uint32_t razlika;
    uint32_t kolicnik;

    if(resenje == rezultat)
    {
        return 1.0f;
    } else if(resenje > rezultat)
    {
        razlika = resenje - rezultat;
        kolicnik = resenje / rezultat;
    } else
    {
        razlika = rezultat - resenje;
        if(resenje == 0)
            kolicnik = 0;
        else
            kolicnik = rezultat / resenje;
    }

    float kvalitet;
    kvalitet = 1 / (float)(razlika + kolicnik);

    return kvalitet;
}

DNA DNA::reprodukcija(const DNA &dna)
{
    Random random;
    uint8_t granica = random.nextInt(std::min(m_dna.size(), dna.m_dna.size()));
}

void DNA::mutacija(float koeficientMutacije)
{
    Random random;
    std::vector<uint8_t> operandi;
    for(int i = 0; i < 6; i++)
        operandi.push_back(i);
    for(auto it = m_dna.begin(); it != m_dna.end(); it++)
    {
        if(it->tip == TipElementaOperacijeOperand)
        {
            for(auto it2 = operandi.begin(); it2 != operandi.end(); it2++)
            {
                if(it->vrednost.operand == *it2)
                {
                    operandi.erase(it2);
                    break;
                }
            }
        }
    }

    for(auto it = m_dna.begin(); it != m_dna.end(); it++)
    {
        if(random.nextFloat() <= koeficientMutacije)
        {
            if(it->tip == TipElementaOperacijeOperator)
            {
                it->vrednost.operacija = static_cast<Operator>(random.nextInt(OperatorZagradaOtvorena));
            } else
            {
                if(!operandi.empty())
                {
                    uint8_t index = random.nextInt(operandi.size());
                    it->vrednost.operand = operandi[index];
                    operandi.erase(operandi.begin() + index);
                }
            }
        }
    }
}
