#ifndef MODLIB_GLOBAL_H
#define MODLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MODLIB_LIBRARY)
#define MODLIB_EXPORT Q_DECL_EXPORT
#else
#define MODLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // MODLIB_GLOBAL_H
