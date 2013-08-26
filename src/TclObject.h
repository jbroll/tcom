// $Id$
#ifndef TCLOBJECT_H
#define TCLOBJECT_H

#ifdef WIN32
#include "TypeInfo.h"
#include "NativeValue.h"
#endif
#include <tcl.h>
#include <string>
#include "tcomApi.h"

// This class provides access to Tcl's built-in internal representation types.

class TclTypes
{
    static Tcl_ObjType *ms_pBooleanType;
    static Tcl_ObjType *ms_pDoubleType;
    static Tcl_ObjType *ms_pIntType;
    static Tcl_ObjType *ms_pListType;

public:
    static void initialize();

    static Tcl_ObjType *booleanType ()
    { return ms_pBooleanType; }

    static Tcl_ObjType *doubleType ()
    { return ms_pDoubleType; }

    static Tcl_ObjType *intType ()
    { return ms_pIntType; }

    static Tcl_ObjType *listType ()
    { return ms_pListType; }

#if TCL_MINOR_VERSION >= 1
private:
    static Tcl_ObjType *ms_pByteArrayType;

public:
    static Tcl_ObjType *byteArrayType ()
    { return ms_pByteArrayType; }
#endif
};

// This class wraps a Tcl_Obj pointer to provide copy and value semantics by
// automatically incrementing and decrementing its reference count.

class TCOM_API TclObject
{
    Tcl_Obj *m_pObj;

public:
    TclObject();
    TclObject(const TclObject &rhs);
    TclObject(Tcl_Obj *pObj);
    TclObject(const char *src, int len = -1);
    TclObject(const std::string &s);
    TclObject(bool value);
    TclObject(int value);
    TclObject(long value);
    TclObject(double value);
    TclObject(int objc, Tcl_Obj *CONST objv[]);
    ~TclObject();

    TclObject &operator=(const TclObject &rhs);
    TclObject &operator=(Tcl_Obj *pObj);

    // Get raw object pointer.
    operator Tcl_Obj * () const
    { return const_cast<Tcl_Obj *>(m_pObj); }

    // Get UTF-8 string representation of the object.
    const char *c_str () const
    { return Tcl_GetStringFromObj(const_cast<Tcl_Obj *>(m_pObj), 0); }

#if TCL_MINOR_VERSION >= 2
    // Construct Unicode string value.
    TclObject(const wchar_t *src, int len = -1);

    // Get Unicode string representation of the object.
    const wchar_t *getUnicode() const
    { return reinterpret_cast<const wchar_t *>(
	Tcl_GetUnicode(const_cast<Tcl_Obj *>(m_pObj))); }
#endif

    // Convert object to bool and return value.
    bool getBool() const;

    // Convert object to int and return value.
    int getInt() const;

    // Convert object to long and return value.
    long getLong() const;

    // Convert object to double and return value.
    double getDouble() const;

    // Convert the object to a list if it's not already a list,
    // and then append the element to the end of the list.
    TclObject &lappend(Tcl_Obj *pElement);

#ifdef WIN32
    // Construct Tcl object from native machine value.
    TclObject(
        VARIANT *pSrc,          // value to convert from
        const Type &type,       // expected type for interface pointers
        Tcl_Interp *interp,
	Tcl_Obj const *obj);

    // Construct Tcl object from _bstr_t.
    TclObject(const _bstr_t &src);

    // Construct Tcl object from SAFEARRAY.
    TclObject(
        SAFEARRAY *psa,         // value to convert from
        const Type &type,       // array type
        Tcl_Interp *interp,
	Tcl_Obj const *obj);

    // Convert Tcl object to VARIANT value.
    void toVariant(
        VARIANT *pDest,         // converted value put here
        const Type &type,       // desired data type
        Tcl_Interp *interp,
        bool addRef=false);     // call AddRef on interface pointer

    // Convert Tcl object to native machine value.
    void toNativeValue(
        NativeValue *pDest,     // converted value put here
        const Type &type,       // desired data type
        Tcl_Interp *interp,
        bool addRef=false);     // call AddRef on interface pointer

    // Get BSTR representation.  Caller is responsible for freeing the
    // returned BSTR.
    BSTR getBSTR() const;

    // Get SAFEARRAY representation.  Caller is responsible for freeing the
    // returned array.
    SAFEARRAY *getSafeArray(const Type &elementType, Tcl_Interp *interp) const;
#endif
};

#endif
