#ifndef FLOATADAPTER_GLOBAL_H
#define FLOATADAPTER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FLOATADAPTER_LIBRARY)
#  define FLOATADAPTERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FLOATADAPTERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FLOATADAPTER_GLOBAL_H
