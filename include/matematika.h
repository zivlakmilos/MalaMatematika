#ifndef _MATEMATIKA_H_
#define _MATEMATIKA_H_

enum Operator {
    OperatorPlus = 0,
    OperatorMinus,
    OperatorPuta,
    OperatorPodeljeno,
    OperatorZagradaOtvorena,
    OperatorZagradaZatvorena
};

enum TipElementaOperacije
{
    TipElementaOperacijeOperator = 0,
    TipElementaOperacijeOperand
};

struct ElementOperacije
{
    TipElementaOperacije tip;

    union
    {
        Operator operacija;
        int operand;
    } vrednost;
};

#endif // _MATEMATIKA_H_
