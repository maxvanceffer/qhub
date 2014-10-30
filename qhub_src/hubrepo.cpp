#include "hubrepo.h"

HubRepo::HubRepo(QObject *parent) :QObject(parent)
{
}

void HubRepo::setName(QString arg)
{
    if (m_name != arg) {
        m_name = arg;
        emit nameChanged(arg);
    }
}
