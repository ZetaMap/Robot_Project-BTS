#ifndef NIRYO_GLOBAL_H
#define NIRYO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NIRYO_LIBRARY)
#define NIRYO_EXPORT Q_DECL_EXPORT
#else
#define NIRYO_EXPORT Q_DECL_IMPORT
#endif

#endif // NIRYO_GLOBAL_H
