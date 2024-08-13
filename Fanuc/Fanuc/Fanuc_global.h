#ifndef FANUC_GLOBAL_H
#define FANUC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FANUC_LIBRARY)
#define FANUC_EXPORT Q_DECL_EXPORT
#else
#define FANUC_EXPORT Q_DECL_IMPORT
#endif

#endif // FANUC_GLOBAL_H
