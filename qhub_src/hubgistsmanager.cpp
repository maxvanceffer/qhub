#include "hubgistsmanager.h"
#include <QDebug>
#include <QMutex>

static HubGistsManager * m_instance = 0;

class HubGistsManager::Private {
public:
};

HubGistsManager *HubGistsManager::instance()
{
    if(!m_instance) {
        QMutex mutex;
        mutex.lock();
        m_instance = new HubGistsManager();
        mutex.unlock();
    }
    return m_instance;
}

HubGistsManager::HubGistsManager(QObject *parent) : QObject(parent),d(new Private)
{
}

HubGistsManager::~HubGistsManager()
{

}



