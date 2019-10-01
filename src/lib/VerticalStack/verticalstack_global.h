#ifndef VERTICALSTACK_GLOBAL_H
#define VERTICALSTACK_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(VERTICALSTACK_LIBRARY)
#  define VERTICALSTACKSHARED_EXPORT Q_DECL_EXPORT
#else
#  define VERTICALSTACKSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // VERTICALSTACK_GLOBAL_H