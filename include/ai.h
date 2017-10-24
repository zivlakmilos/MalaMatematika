#ifndef _AI_H_
#define _AI_H_

#include "dna.h"
#include "matematika.h"
#include "random.h"

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

    inline std::vector<uint32_t> getPonudjeniBrojevi(void) { return m_ponudjeniBrojevi; }

    std::vector<ElementOperacije> nadjiResenje(void);

private:
    void kreirajPrvuGeneraciju(void);
    void reprodukcija(void);
    void mutacija(void);

    uint32_t m_rezultat;
    float m_konstantaMutacije;
    uint32_t m_velicinaPopulacije;
    std::vector<uint32_t> m_ponudjeniBrojevi;

    std::vector<DNA> m_populaicja;
    std::vector<ElementOperacije> m_najboljaFormula;
    float m_najboljiKvalitet;

    Random m_random;
};

#endif // _AI_H_
