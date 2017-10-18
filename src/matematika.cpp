#include "matematika.h"

Matematika::Matematika(void)
{
}

Matematika::~Matematika(void)
{
}

uint32_t Matematika::racunajInfiksu(const std::vector<ElementOperacije> &formula)
{
    uint32_t broj1 = 0;
    uint32_t broj2 = 0;
    Operator operacija = OperatorPlus;
    Operator operacija2;
    bool operacijaPostoji = false;
    bool operacija2Postoji = false;

    for(auto it = formula.begin(); it != formula.end(); it++)
    {
        if(it->tip == TipElementaOperacijeOperand)
        {
            if(operacija2Postoji)
            {
                broj2 = izvrsiOperaciju(broj2, it->vrednost.operand, operacija2);
                operacija2Postoji = false;
            } else
            {
                broj2 = it->vrednost.operand;
            }
        } else
        {
            if((it->vrednost.operacija == OperatorPuta ||
                it->vrednost.operacija == OperatorPodeljeno) &&
                operacijaPostoji)
            {
                operacija2 = it->vrednost.operacija;
                operacija2Postoji = true;
            } else
            {
                broj1 = izvrsiOperaciju(broj1, broj2, operacija);
                operacija = it->vrednost.operacija;
                operacijaPostoji = true;
            }
        }
    }
    broj1 = izvrsiOperaciju(broj1, broj2, operacija);

    return broj1;
}

uint32_t Matematika::izvrsiOperaciju(uint32_t operand1, uint32_t operand2, Operator operacija)
{
    uint32_t rezultat = 0;
    switch(operacija)
    {
        case OperatorPlus:
            rezultat = operand1 + operand2;
            break;
        case OperatorMinus:
            rezultat = operand1 - operand2;
            break;
        case OperatorPuta:
            rezultat = operand1 * operand2;
            break;
        case OperatorPodeljeno:
            rezultat = operand1 / operand2;
            break;
        default:
            // TODO: Baci expcetion
            break;
    }

    return rezultat;
}
