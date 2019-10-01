#ifndef LINEARDATETIME_GLOBAL_H
#define LINEARDATETIME_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LINEARDATETIME_LIBRARY)
#  define LINEARDATETIMESHARED_EXPORT Q_DECL_EXPORT
#else
#  define LINEARDATETIMESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LINEARDATETIME_GLOBAL_H
