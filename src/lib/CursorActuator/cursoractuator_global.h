#ifndef CURSORACTUATOR_GLOBAL_H
#define CURSORACTUATOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CURSORACTUATOR_LIBRARY)
#  define CURSORACTUATORSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CURSORACTUATORSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CURSORACTUATOR_GLOBAL_H