

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_axGxxGmPlayerLib,0x2E3A279F,0x5861,0x424D,0xA8,0x6F,0x35,0x45,0x61,0x6E,0xD1,0xC7);


MIDL_DEFINE_GUID(IID, DIID__DaxGxxGmPlayer,0x4D340EB7,0x7199,0x42CF,0x86,0xC2,0xBE,0xE3,0x0C,0x3D,0x0F,0x2A);


MIDL_DEFINE_GUID(IID, DIID__DaxGxxGmPlayerEvents,0x9563F9B4,0x8690,0x45EB,0xB2,0x37,0xBB,0x66,0xD7,0xAD,0x6F,0xF7);


MIDL_DEFINE_GUID(CLSID, CLSID_axGxxGmPlayer,0x6D262904,0x18A7,0x4F97,0xB9,0x99,0x66,0x28,0xBF,0x44,0x24,0x17);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



