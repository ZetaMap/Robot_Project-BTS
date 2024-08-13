#ifndef CONVOYEUR_GLOBAL_H
#define CONVOYEUR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CONVOYEUR_LIBRARY)
#  define CONVOYEUR_EXPORT Q_DECL_EXPORT
#else
#  define CONVOYEUR_EXPORT Q_DECL_IMPORT
#endif

#endif // CONVOYEUR_GLOBAL_H
