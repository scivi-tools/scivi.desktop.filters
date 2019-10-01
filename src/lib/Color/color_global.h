#ifndef COLOR_GLOBAL_H
#define COLOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COLOR_LIBRARY)
#  define COLORSHARED_EXPORT Q_DECL_EXPORT
#else
#  define COLORSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // COLOR_GLOBAL_H
