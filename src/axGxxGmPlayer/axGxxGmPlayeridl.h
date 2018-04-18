

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Wed Apr 18 14:50:45 2018
 */
/* Compiler settings for .\axGxxGmPlayer.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __axGxxGmPlayeridl_h__
#define __axGxxGmPlayeridl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DaxGxxGmPlayer_FWD_DEFINED__
#define ___DaxGxxGmPlayer_FWD_DEFINED__
typedef interface _DaxGxxGmPlayer _DaxGxxGmPlayer;
#endif 	/* ___DaxGxxGmPlayer_FWD_DEFINED__ */


#ifndef ___DaxGxxGmPlayerEvents_FWD_DEFINED__
#define ___DaxGxxGmPlayerEvents_FWD_DEFINED__
typedef interface _DaxGxxGmPlayerEvents _DaxGxxGmPlayerEvents;
#endif 	/* ___DaxGxxGmPlayerEvents_FWD_DEFINED__ */


#ifndef __axGxxGmPlayer_FWD_DEFINED__
#define __axGxxGmPlayer_FWD_DEFINED__

#ifdef __cplusplus
typedef class axGxxGmPlayer axGxxGmPlayer;
#else
typedef struct axGxxGmPlayer axGxxGmPlayer;
#endif /* __cplusplus */

#endif 	/* __axGxxGmPlayer_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __axGxxGmPlayerLib_LIBRARY_DEFINED__
#define __axGxxGmPlayerLib_LIBRARY_DEFINED__

/* library axGxxGmPlayerLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_axGxxGmPlayerLib;

#ifndef ___DaxGxxGmPlayer_DISPINTERFACE_DEFINED__
#define ___DaxGxxGmPlayer_DISPINTERFACE_DEFINED__

/* dispinterface _DaxGxxGmPlayer */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DaxGxxGmPlayer;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("4D340EB7-7199-42CF-86C2-BEE30C3D0F2A")
    _DaxGxxGmPlayer : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DaxGxxGmPlayerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DaxGxxGmPlayer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DaxGxxGmPlayer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DaxGxxGmPlayer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DaxGxxGmPlayer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DaxGxxGmPlayer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DaxGxxGmPlayer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DaxGxxGmPlayer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DaxGxxGmPlayerVtbl;

    interface _DaxGxxGmPlayer
    {
        CONST_VTBL struct _DaxGxxGmPlayerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DaxGxxGmPlayer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DaxGxxGmPlayer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DaxGxxGmPlayer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DaxGxxGmPlayer_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DaxGxxGmPlayer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DaxGxxGmPlayer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DaxGxxGmPlayer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DaxGxxGmPlayer_DISPINTERFACE_DEFINED__ */


#ifndef ___DaxGxxGmPlayerEvents_DISPINTERFACE_DEFINED__
#define ___DaxGxxGmPlayerEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DaxGxxGmPlayerEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DaxGxxGmPlayerEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("9563F9B4-8690-45EB-B237-BB66D7AD6FF7")
    _DaxGxxGmPlayerEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DaxGxxGmPlayerEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DaxGxxGmPlayerEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DaxGxxGmPlayerEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DaxGxxGmPlayerEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DaxGxxGmPlayerEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DaxGxxGmPlayerEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DaxGxxGmPlayerEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DaxGxxGmPlayerEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DaxGxxGmPlayerEventsVtbl;

    interface _DaxGxxGmPlayerEvents
    {
        CONST_VTBL struct _DaxGxxGmPlayerEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DaxGxxGmPlayerEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DaxGxxGmPlayerEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DaxGxxGmPlayerEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DaxGxxGmPlayerEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DaxGxxGmPlayerEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DaxGxxGmPlayerEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DaxGxxGmPlayerEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DaxGxxGmPlayerEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_axGxxGmPlayer;

#ifdef __cplusplus

class DECLSPEC_UUID("6D262904-18A7-4F97-B999-6628BF442417")
axGxxGmPlayer;
#endif
#endif /* __axGxxGmPlayerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


