#ifndef CONSTANT_GLOBAL_H
#define CONSTANT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CONSTANT_LIBRARY)
#  define CONSTANTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CONSTANTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CONSTANT_GLOBAL_H
