#include "dna.h"

#include "random.h"

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

float DNA::kvalitet(void)
{
}

DNA DNA::reprodukcija(const DNA &dna)
{
}

void DNA::mutacija(float koeficientMutacije)
{
}
