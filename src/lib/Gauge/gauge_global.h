#ifndef GAUGE_GLOBAL_H
#define GAUGE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GAUGE_LIBRARY)
#  define GAUGESHARED_EXPORT Q_DECL_EXPORT
#else
#  define GAUGESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GAUGE_GLOBAL_H
