#include "hubmanager.h"

HubManager::HubManager(QObject *parent):QObject(parent)
{
    connect(QHub::instance(),SIGNAL(authorityChanged(HubAuthority*)),SLOT(authorityChanged(HubAuthority*)));
    connect(QHub::instance(),SIGNAL(userAuthorized()),SLOT(userChanged()));
}

void HubManager::authorityChanged(HubAuthority *)
{
}

void HubManager::userChanged()
{
}
