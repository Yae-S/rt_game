// This file is generated by omniidl (C++ backend)- omniORB_4_1. Do not edit.
#ifndef __RecognitionService_hh__
#define __RecognitionService_hh__

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_RecognitionService
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_RecognitionService
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_RecognitionService
#endif






#ifdef USE_stub_in_nt_dll
# ifndef USE_core_stub_in_nt_dll
#  define USE_core_stub_in_nt_dll
# endif
# ifndef USE_dyn_stub_in_nt_dll
#  define USE_dyn_stub_in_nt_dll
# endif
#endif

#ifdef _core_attr
# error "A local CPP macro _core_attr has already been defined."
#else
# ifdef  USE_core_stub_in_nt_dll
#  define _core_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _core_attr
# endif
#endif

#ifdef _dyn_attr
# error "A local CPP macro _dyn_attr has already been defined."
#else
# ifdef  USE_dyn_stub_in_nt_dll
#  define _dyn_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _dyn_attr
# endif
#endif





#ifndef __RecognitionService__
#define __RecognitionService__

class RecognitionService;
class _objref_RecognitionService;
class _impl_RecognitionService;

typedef _objref_RecognitionService* RecognitionService_ptr;
typedef RecognitionService_ptr RecognitionServiceRef;

class RecognitionService_Helper {
public:
  typedef RecognitionService_ptr _ptr_type;

  static _ptr_type _nil();
  static _CORBA_Boolean is_nil(_ptr_type);
  static void release(_ptr_type);
  static void duplicate(_ptr_type);
  static void marshalObjRef(_ptr_type, cdrStream&);
  static _ptr_type unmarshalObjRef(cdrStream&);
};

typedef _CORBA_ObjRef_Var<_objref_RecognitionService, RecognitionService_Helper> RecognitionService_var;
typedef _CORBA_ObjRef_OUT_arg<_objref_RecognitionService,RecognitionService_Helper > RecognitionService_out;

#endif

// interface RecognitionService
class RecognitionService {
public:
  // Declarations for this interface type.
  typedef RecognitionService_ptr _ptr_type;
  typedef RecognitionService_var _var_type;

  static _ptr_type _duplicate(_ptr_type);
  static _ptr_type _narrow(::CORBA::Object_ptr);
  static _ptr_type _unchecked_narrow(::CORBA::Object_ptr);
  
  static _ptr_type _nil();

  static inline void _marshalObjRef(_ptr_type, cdrStream&);

  static inline _ptr_type _unmarshalObjRef(cdrStream& s) {
    omniObjRef* o = omniObjRef::_unMarshal(_PD_repoId,s);
    if (o)
      return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
    else
      return _nil();
  }

  static _core_attr const char* _PD_repoId;

  // Other IDL defined within this scope.
  
};

class _objref_RecognitionService :
  public virtual ::CORBA::Object,
  public virtual omniObjRef
{
public:
  ::CORBA::Long getModelID();
  void setModelID(::CORBA::Long ModelID);

  inline _objref_RecognitionService()  { _PR_setobj(0); }  // nil
  _objref_RecognitionService(omniIOR*, omniIdentity*);

protected:
  virtual ~_objref_RecognitionService();

  
private:
  virtual void* _ptrToObjRef(const char*);

  _objref_RecognitionService(const _objref_RecognitionService&);
  _objref_RecognitionService& operator = (const _objref_RecognitionService&);
  // not implemented

  friend class RecognitionService;
};

class _pof_RecognitionService : public _OMNI_NS(proxyObjectFactory) {
public:
  inline _pof_RecognitionService() : _OMNI_NS(proxyObjectFactory)(RecognitionService::_PD_repoId) {}
  virtual ~_pof_RecognitionService();

  virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
  virtual _CORBA_Boolean is_a(const char*) const;
};

class _impl_RecognitionService :
  public virtual omniServant
{
public:
  virtual ~_impl_RecognitionService();

  virtual ::CORBA::Long getModelID() = 0;
  virtual void setModelID(::CORBA::Long ModelID) = 0;
  
public:  // Really protected, workaround for xlC
  virtual _CORBA_Boolean _dispatch(omniCallHandle&);

private:
  virtual void* _ptrToInterface(const char*);
  virtual const char* _mostDerivedRepoId();
  
};


_CORBA_GLOBAL_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_RecognitionService;



class POA_RecognitionService :
  public virtual _impl_RecognitionService,
  public virtual ::PortableServer::ServantBase
{
public:
  virtual ~POA_RecognitionService();

  inline ::RecognitionService_ptr _this() {
    return (::RecognitionService_ptr) _do_this(::RecognitionService::_PD_repoId);
  }
};







#undef _core_attr
#undef _dyn_attr

void operator<<=(::CORBA::Any& _a, RecognitionService_ptr _s);
void operator<<=(::CORBA::Any& _a, RecognitionService_ptr* _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, RecognitionService_ptr& _s);



inline void
RecognitionService::_marshalObjRef(::RecognitionService_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}




#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_RecognitionService
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_RecognitionService
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_RecognitionService
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_RecognitionService
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_RecognitionService
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_RecognitionService
#endif

#endif  // __RecognitionService_hh__

