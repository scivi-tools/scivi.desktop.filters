#ifndef MOUSE_GLOBAL_H
#define MOUSE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MOUSE_LIBRARY)
#  define MOUSESHARED_EXPORT Q_DECL_EXPORT
#else
#  define MOUSESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MOUSE_GLOBAL_H
