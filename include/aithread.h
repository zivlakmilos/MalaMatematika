#ifndef _AI_THREAD_H_
#define _AI_THREAD_H_

#include <QThread>

#include <QMetaType>

#include "matematika.h"

//qRegisterMetaType<std::vector<ElementOperacije>>("std::vector<ElementOperacije>");

class AIThread : public QThread
{
    Q_OBJECT

public:
    explicit AIThread(QObject *parent = 0);
    virtual ~AIThread(void);

    void pokreni(uint32_t rezultat, const std::vector<uint32_t> &ponudjeniBrojevi);

    virtual void run(void);

private:
    uint32_t m_rezultat;
    std::vector<uint32_t> m_ponudjeniBrojevi;

signals:
    void resenjeNadjeno(std::vector<ElementOperacije> formula);
};

#endif // _AI_THREAD_H_
