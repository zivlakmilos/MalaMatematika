#include "aithread.h"

#include "ai.h"

AIThread::AIThread(QObject* parent)
    : QThread(parent),
      m_rezultat(0)
{
    qRegisterMetaType<std::vector<ElementOperacije>>("std::vector<ElementOperacije>");
}

AIThread::~AIThread(void)
{
}

void AIThread::pokreni(uint32_t rezultat, const std::vector<uint32_t> &ponudjeniBrojevi)
{
    m_rezultat = rezultat;
    m_ponudjeniBrojevi = ponudjeniBrojevi;
    start();
}

void AIThread::run(void)
{
    if(m_ponudjeniBrojevi.empty())
        return;

    AI ai(m_rezultat, m_ponudjeniBrojevi);
    std::vector<ElementOperacije> formula = ai.nadjiResenje();
    emit resenjeNadjeno(formula);
}
