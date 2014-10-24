#ifndef QHUB_GLOBAL_H
#define QHUB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QHUB_LIBRARY)
#  define QHUBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QHUBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QHUB_GLOBAL_H
