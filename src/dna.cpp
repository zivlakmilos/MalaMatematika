#include "dna.h"

#include <cmath>

#include "core/random.h"
#include "core/exception.h"
#include "ai.h"

DNA::DNA(const std::vector<ElementOperacije> &dna)
    : m_dna(dna),
      m_rezultat(0)
{
}

DNA::DNA(void)
    : m_rezultat(0)
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

    DNA result(dna);
    return result;
}

uint32_t DNA::izracunajVrednost(const std::vector<uint32_t> &ponudjeniBrojevi)
{
    Matematika matematika;

    m_formula.clear();
    for(auto it = m_dna.begin(); it != m_dna.end(); it++)
    {
        m_formula.push_back(*it);
        auto it2 = --m_formula.end();
        if(it2->tip == TipElementaOperacijeOperand)
        {
            it2->vrednost.operand = ponudjeniBrojevi[it->vrednost.operand];
        }
    }

    try {
        m_rezultat =  matematika.racunajPostfoksnu(m_formula);
    } catch(Exception &ex) {
        m_rezultat = 0;
    }

    return m_rezultat;
}

float DNA::kvalitet(uint32_t rezultat)
{
    uint32_t razlika;
    uint32_t kolicnik;

    bool operandi[6];
    for(int i = 0; i < 6; i++)
        operandi[i] = false;
    for(auto it = m_dna.begin(); it != m_dna.end(); it++)
    {
        int i = it->vrednost.operand;
        if(it->tip == TipElementaOperacijeOperand)
        {
            if(operandi[i])
                return 0.0;
            else
                operandi[i] = true;
        }
    }

    if(m_rezultat == rezultat)
    {
        return 1.0f;
    } else if(m_rezultat > rezultat)
    {
        razlika = m_rezultat - rezultat;
        kolicnik = m_rezultat / rezultat;
    } else
    {
        razlika = rezultat - m_rezultat;
        if(m_rezultat == 0)
            kolicnik = 0;
        else
            kolicnik = rezultat / m_rezultat;
    }

    float kvalitet;
    kvalitet = 1 / (float)(razlika + kolicnik);

    return kvalitet;
}

DNA DNA::reprodukcija(const DNA &dna)
{
    std::vector<ElementOperacije> formula = m_dna;

    int brojOperanada = 1;
    for(auto it = dna.m_dna.begin(); it != dna.m_dna.end(); it++)
    {
        if(it->tip == TipElementaOperacijeOperand)
        {
            formula.push_back(*it);
            brojOperanada++;
        } else if(brojOperanada >= 2)
        {
            formula.push_back(*it);
            brojOperanada--;
        }
    }

    ElementOperacije element;
    element.tip = TipElementaOperacijeOperator;
    while(--brojOperanada > 0)
    {
        element.vrednost.operacija = static_cast<Operator>(m_random.nextInt(OperatorZagradaOtvorena));
        formula.push_back(element);
    }

    return DNA(formula);
}

void DNA::mutacija(float koeficientMutacije)
{
    for(auto it = m_dna.begin(); it != m_dna.end(); it++)
    {
        if(m_random.nextFloat() <= koeficientMutacije)
        {
            if(it->tip == TipElementaOperacijeOperator)
            {
                it->vrednost.operacija = static_cast<Operator>(m_random.nextInt(OperatorZagradaOtvorena));
            } else
            {
                it->vrednost.operand = m_random.nextInt(6);
            }
        }
    }
}
