// $Id$
#ifndef TCLRUNTIME_H
#define TCLRUNTIME_H

#include <tcl.h>

// Link the Tcl run-time library.
#ifdef USE_TCL_STUBS
#pragma comment(lib, \
    "tclstub" STRINGIFY(JOIN(TCL_MAJOR_VERSION, TCL_MINOR_VERSION)))
#else
#pragma comment(lib, \
    "tcl" STRINGIFY(JOIN(TCL_MAJOR_VERSION, TCL_MINOR_VERSION)))
#endif

#endif
