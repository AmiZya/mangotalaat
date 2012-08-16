#ifndef MANGOREPORTS_GLOBAL_H
#define MANGOREPORTS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MANGOREPORTS_LIBRARY)
#  define MANGOREPORTSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MANGOREPORTSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MANGOREPORTS_GLOBAL_H