#ifndef INPUTFILE_GLOBAL_H
#define INPUTFILE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(INPUTFILE_LIBRARY)
#  define INPUTFILESHARED_EXPORT Q_DECL_EXPORT
#else
#  define INPUTFILESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // INPUTFILE_GLOBAL_H
