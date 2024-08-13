#ifndef AFFICHEUR_GLOBAL_H
#define AFFICHEUR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(AFFICHEUR_LIBRARY)
#  define AFFICHEUR_EXPORT Q_DECL_EXPORT
#else
#  define AFFICHEUR_EXPORT Q_DECL_IMPORT
#endif

#endif // AFFICHEUR_GLOBAL_H
