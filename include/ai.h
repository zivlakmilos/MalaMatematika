#ifndef _AI_H_
#define _AI_H_

#include "dna.h"
#include "matematika.h"

#define AI_PODRAZUMEVANA_KONSTANTA_MUTACIJE         0.01f
#define AI_PODRAZUMEVANA_VELICINA_POPULACIJE        1000

class AI
{
public:
    AI(uint32_t rezultat, std::vector<uint32_t> &ponudjeniBrojevi);
    ~AI(void);

    inline float getKonstantaMutacije(void) { return m_konstantaMutacije; }
    inline void setKonstantaMutacije(float konstantaMutacije) { m_konstantaMutacije = konstantaMutacije; }

    inline uint32_t getVelicinaPopulacije(void) { return m_velicinaPopulacije; }
    inline void setVelicinaPopulacije(uint32_t velicinaPopulacije) { m_velicinaPopulacije = velicinaPopulacije; }

    std::vector<ElementOperacije> nadjiResenje(void);

private:
    void kreirajPrvuGeneraciju(void);

    uint32_t m_rezultat;
    float m_konstantaMutacije;
    uint32_t m_velicinaPopulacije;
    std::vector<uint32_t> m_ponudjeniBrojevi;

    std::vector<DNA> m_populaicja;
    std::vector<ElementOperacije> m_najboljaFormula;
    uint32_t m_najboljeResenje;
};

#endif // _AI_H_
