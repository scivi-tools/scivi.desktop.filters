#ifndef GLOVE_GLOBAL_H
#define GLOVE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GLOVE_LIBRARY)
#  define GLOVESHARED_EXPORT Q_DECL_EXPORT
#else
#  define GLOVESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GLOVE_GLOBAL_H
