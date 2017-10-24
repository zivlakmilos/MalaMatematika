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

    static DNA generisiSlucajnuFormulu(uint8_t brojOperanada);

    float kvalitet(uint32_t rezultat, const std::vector<uint32_t> &ponudjeniBrojevi);
    DNA reprodukcija(const DNA &dna);
    void mutacija(float koeficientMutacije);

private:
    std::vector<ElementOperacije> m_dna;
};

#endif // _DNA_H_
