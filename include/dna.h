#ifndef _DNA_H_
#define _DNA_H_

#include "matematika.h"

class AI;

class DNA
{
public:
    DNA(const std::vector<ElementOperacije> &dna);
    DNA(void);
    ~DNA(void);

    inline std::vector<ElementOperacije> getDna(void) const { return m_dna; }
    inline std::vector<ElementOperacije> getFormula(void) const { return m_formula; }

    static DNA generisiSlucajnuFormulu(uint8_t brojOperanada);

    uint32_t izracunajVrednost(const std::vector<uint32_t> &ponudjeniBrojevi);
    float kvalitet(uint32_t rezultat);
    DNA reprodukcija(const DNA &dna);
    void mutacija(float koeficientMutacije);

private:
    std::vector<ElementOperacije> m_dna;
    std::vector<ElementOperacije> m_formula;
    uint32_t m_rezultat;
};

#endif // _DNA_H_
