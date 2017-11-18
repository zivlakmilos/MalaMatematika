#include "matematika.h"

#include <stack>

#include "core/exceptionzagrada.h"

Matematika::Matematika(void)
{
}

Matematika::~Matematika(void)
{
}

uint32_t Matematika::racunajInfiksnu(const std::vector<ElementOperacije> &formula)
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
            if(it->vrednost.operacija == OperatorZagradaOtvorena)
            {
                std::vector<ElementOperacije> formula2;
                int zagradaIndex = it - formula.begin();
                while(true)
                {
                    it++;
                    if(it == formula.end())
                        throw ExceptionZagrada(zagradaIndex);
                    if(it->tip == TipElementaOperacijeOperator &&
                       it->vrednost.operacija == OperatorZagradaZatvorena)
                        break;

                    formula2.push_back(*it);
                }

                uint32_t tmp = racunajInfiksnu(formula2);
                if(operacija2Postoji)
                {
                    broj2 = izvrsiOperaciju(broj2, tmp, operacija2);
                    operacija2Postoji = false;
                } else
                {
                    broj2 = tmp;
                }
            } else if((it->vrednost.operacija == OperatorPuta ||
                       it->vrednost.operacija == OperatorPodeljeno) &&
                      (operacija == OperatorPlus ||
                       operacija == OperatorMinus) &&
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

uint32_t Matematika::racunajPostfoksnu(const std::vector<ElementOperacije> &formula)
{
    std::stack<uint32_t> stek;

    for(auto it = formula.begin(); it != formula.end(); it++)
    {
        if(it->tip == TipElementaOperacijeOperator)
        {
            if(stek.size() < 2)
                throw Exception("Greska prilikom racunanja infiksne notacije");

            uint32_t broj2 = stek.top();
            stek.pop();
            uint32_t broj1 = stek.top();
            stek.pop();

            stek.push(izvrsiOperaciju(broj1, broj2, it->vrednost.operacija));
        } else
        {
            stek.push(it->vrednost.operand);
        }
    }

    if(stek.empty())
        throw Exception("Greska prilikom racuanja infiksne notacije");

    return stek.top();
}

std::vector<ElementOperacije> Matematika::pretvoriInfiksnuUPostfiksnu(const std::vector<ElementOperacije> &formula)
{
    std::stack<ElementOperacije> stekOperatora;
    std::vector<ElementOperacije> izlaz;

    for(auto it = formula.begin(); it != formula.end(); it++)
    {
        if(it->tip == TipElementaOperacijeOperand)
        {
            izlaz.push_back(*it);
        } else
        {
            if(it->vrednost.operacija == OperatorZagradaOtvorena)
            {
                stekOperatora.push(*it);
            } else if(it->vrednost.operacija == OperatorZagradaZatvorena)
            {
                while(stekOperatora.top().vrednost.operacija != OperatorZagradaOtvorena)
                {
                    izlaz.push_back(stekOperatora.top());
                    stekOperatora.pop();
                }
                stekOperatora.pop();
            } else
            {
                if(!stekOperatora.empty() &&
                   it->vrednost.operacija <= stekOperatora.top().vrednost.operacija &&
                   stekOperatora.top().vrednost.operacija < OperatorZagradaOtvorena)
                {
                    izlaz.push_back(stekOperatora.top());
                    stekOperatora.pop();
                }
                stekOperatora.push(*it);
            }
        }
    }

    while(!stekOperatora.empty())
    {
        izlaz.push_back(stekOperatora.top());
        stekOperatora.pop();
    }

    return izlaz;
}

std::vector<ElementOperacije> Matematika::pretvoriPostfiksnuUInfiksnu(const std::vector<ElementOperacije> &formula)
{
    std::stack<ElementOperacije> stek;
    std::stack<std::deque<ElementOperacije>> stekIzlaza;

    ElementOperacije zagradaOtvorena;
    zagradaOtvorena.tip = TipElementaOperacijeOperator;
    zagradaOtvorena.vrednost.operacija = OperatorZagradaOtvorena;
    ElementOperacije zagradaZatvorena;
    zagradaZatvorena.tip = TipElementaOperacijeOperator;
    zagradaZatvorena.vrednost.operacija = OperatorZagradaZatvorena;

    for(auto it = formula.begin(); it != formula.end(); it++)
    {
        if(it->tip == TipElementaOperacijeOperator)
        {
            if(stek.size() >= 2)
            {
                ElementOperacije operand2 = stek.top();
                stek.pop();
                ElementOperacije operand1 = stek.top();
                stek.pop();

                std::deque<ElementOperacije> izlaz;
                izlaz.push_back(operand1);
                izlaz.push_back(*it);
                izlaz.push_back(operand2);
                stekIzlaza.push(izlaz);
            } else if(!stek.empty())
            {
                std::deque<ElementOperacije> izlaz = stekIzlaza.top();
                stekIzlaza.pop();
                ElementOperacije operand2 = stek.top();
                stek.pop();

                izlaz.push_front(zagradaOtvorena);
                izlaz.push_back(zagradaZatvorena);
                izlaz.push_back(*it);
                izlaz.push_back(operand2);
                stekIzlaza.push(izlaz);
            } else if(stekIzlaza.size() >= 2)
            {
                std::deque<ElementOperacije> operand2 = stekIzlaza.top();
                stekIzlaza.pop();
                std::deque<ElementOperacije> operand1 = stekIzlaza.top();
                stekIzlaza.pop();

                operand1.push_front(zagradaOtvorena);
                operand1.push_back(zagradaZatvorena);
                operand1.push_back(*it);
                operand1.push_back(zagradaOtvorena);
                for(auto it2 = operand2.begin(); it2 != operand2.end(); it2++)
                {
                    operand1.push_back(*it2);
                }
                operand1.push_back(zagradaZatvorena);
            }
        } else
        {
            stek.push(*it);
        }
    }

    std::deque<ElementOperacije> izlaz = stekIzlaza.top();
    return std::vector<ElementOperacije>(izlaz.begin(), izlaz.end());
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
            if(operand2 == 0)
                throw Exception("Deljenje sa nulom nije dozvoljeno");
            rezultat = operand1 / operand2;
            break;
        default:
            throw Exception("Operacija nije dozvoljena");
            break;
    }

    return rezultat;
}
