#ifndef SURFACE3D_GLOBAL_H
#define SURFACE3D_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SURFACE3D_LIBRARY)
#  define SURFACE3DSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SURFACE3DSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SURFACE3D_GLOBAL_H
