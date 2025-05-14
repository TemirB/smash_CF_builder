// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME StPicoDst_Dict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "StPicoETofHit.h"
#include "StPicoMtdHit.h"
#include "StPicoBEmcSmdEHit.h"
#include "StPicoArrays.h"
#include "StPicoTrack.h"
#include "StPicoPhysicalHelix.h"
#include "StPicoBTofPidTraits.h"
#include "StPicoMcVertex.h"
#include "StPicoBEmcSmdPHit.h"
#include "StPicoBEmcPidTraits.h"
#include "StPicoHelix.h"
#include "StPicoEmcTrigger.h"
#include "StPicoMtdTrigger.h"
#include "StPicoBTowHit.h"
#include "StPicoCommon.h"
#include "StPicoTrackCovMatrix.h"
#include "StPicoDstReader.h"
#include "PhysicalConstants.h"
#include "StPicoEvent.h"
#include "StPicoMtdPidTraits.h"
#include "StPicoMcTrack.h"
#include "StPicoFmsHit.h"
#include "StPicoETofPidTraits.h"
#include "StPicoEpdHit.h"
#include "SystemOfUnits.h"
#include "StPicoBTofHit.h"
#include "StPicoBbcHit.h"
#include "StPicoDst.h"
#include "StPicoMessMgr.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_StPicoETofHit(void *p = nullptr);
   static void *newArray_StPicoETofHit(Long_t size, void *p);
   static void delete_StPicoETofHit(void *p);
   static void deleteArray_StPicoETofHit(void *p);
   static void destruct_StPicoETofHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoETofHit*)
   {
      ::StPicoETofHit *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoETofHit >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoETofHit", ::StPicoETofHit::Class_Version(), "StPicoETofHit.h", 19,
                  typeid(::StPicoETofHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoETofHit::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoETofHit) );
      instance.SetNew(&new_StPicoETofHit);
      instance.SetNewArray(&newArray_StPicoETofHit);
      instance.SetDelete(&delete_StPicoETofHit);
      instance.SetDeleteArray(&deleteArray_StPicoETofHit);
      instance.SetDestructor(&destruct_StPicoETofHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoETofHit*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoETofHit*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoETofHit*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoMtdHit(void *p = nullptr);
   static void *newArray_StPicoMtdHit(Long_t size, void *p);
   static void delete_StPicoMtdHit(void *p);
   static void deleteArray_StPicoMtdHit(void *p);
   static void destruct_StPicoMtdHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoMtdHit*)
   {
      ::StPicoMtdHit *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoMtdHit >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoMtdHit", ::StPicoMtdHit::Class_Version(), "StPicoMtdHit.h", 18,
                  typeid(::StPicoMtdHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoMtdHit::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoMtdHit) );
      instance.SetNew(&new_StPicoMtdHit);
      instance.SetNewArray(&newArray_StPicoMtdHit);
      instance.SetDelete(&delete_StPicoMtdHit);
      instance.SetDeleteArray(&deleteArray_StPicoMtdHit);
      instance.SetDestructor(&destruct_StPicoMtdHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoMtdHit*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoMtdHit*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoMtdHit*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoBEmcSmdEHit(void *p = nullptr);
   static void *newArray_StPicoBEmcSmdEHit(Long_t size, void *p);
   static void delete_StPicoBEmcSmdEHit(void *p);
   static void deleteArray_StPicoBEmcSmdEHit(void *p);
   static void destruct_StPicoBEmcSmdEHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoBEmcSmdEHit*)
   {
      ::StPicoBEmcSmdEHit *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoBEmcSmdEHit >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoBEmcSmdEHit", ::StPicoBEmcSmdEHit::Class_Version(), "StPicoBEmcSmdEHit.h", 17,
                  typeid(::StPicoBEmcSmdEHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoBEmcSmdEHit::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoBEmcSmdEHit) );
      instance.SetNew(&new_StPicoBEmcSmdEHit);
      instance.SetNewArray(&newArray_StPicoBEmcSmdEHit);
      instance.SetDelete(&delete_StPicoBEmcSmdEHit);
      instance.SetDeleteArray(&deleteArray_StPicoBEmcSmdEHit);
      instance.SetDestructor(&destruct_StPicoBEmcSmdEHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoBEmcSmdEHit*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoBEmcSmdEHit*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoBEmcSmdEHit*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoHelix(void *p = nullptr);
   static void *newArray_StPicoHelix(Long_t size, void *p);
   static void delete_StPicoHelix(void *p);
   static void deleteArray_StPicoHelix(void *p);
   static void destruct_StPicoHelix(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoHelix*)
   {
      ::StPicoHelix *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoHelix >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoHelix", ::StPicoHelix::Class_Version(), "StPicoHelix.h", 38,
                  typeid(::StPicoHelix), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoHelix::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoHelix) );
      instance.SetNew(&new_StPicoHelix);
      instance.SetNewArray(&newArray_StPicoHelix);
      instance.SetDelete(&delete_StPicoHelix);
      instance.SetDeleteArray(&deleteArray_StPicoHelix);
      instance.SetDestructor(&destruct_StPicoHelix);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoHelix*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoHelix*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoHelix*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoPhysicalHelix(void *p = nullptr);
   static void *newArray_StPicoPhysicalHelix(Long_t size, void *p);
   static void delete_StPicoPhysicalHelix(void *p);
   static void deleteArray_StPicoPhysicalHelix(void *p);
   static void destruct_StPicoPhysicalHelix(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoPhysicalHelix*)
   {
      ::StPicoPhysicalHelix *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoPhysicalHelix >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoPhysicalHelix", ::StPicoPhysicalHelix::Class_Version(), "StPicoPhysicalHelix.h", 22,
                  typeid(::StPicoPhysicalHelix), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoPhysicalHelix::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoPhysicalHelix) );
      instance.SetNew(&new_StPicoPhysicalHelix);
      instance.SetNewArray(&newArray_StPicoPhysicalHelix);
      instance.SetDelete(&delete_StPicoPhysicalHelix);
      instance.SetDeleteArray(&deleteArray_StPicoPhysicalHelix);
      instance.SetDestructor(&destruct_StPicoPhysicalHelix);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoPhysicalHelix*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoPhysicalHelix*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoPhysicalHelix*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoTrack(void *p = nullptr);
   static void *newArray_StPicoTrack(Long_t size, void *p);
   static void delete_StPicoTrack(void *p);
   static void deleteArray_StPicoTrack(void *p);
   static void destruct_StPicoTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoTrack*)
   {
      ::StPicoTrack *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoTrack >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoTrack", ::StPicoTrack::Class_Version(), "StPicoTrack.h", 35,
                  typeid(::StPicoTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoTrack::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoTrack) );
      instance.SetNew(&new_StPicoTrack);
      instance.SetNewArray(&newArray_StPicoTrack);
      instance.SetDelete(&delete_StPicoTrack);
      instance.SetDeleteArray(&deleteArray_StPicoTrack);
      instance.SetDestructor(&destruct_StPicoTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoTrack*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoTrack*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoTrack*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoBTofPidTraits(void *p = nullptr);
   static void *newArray_StPicoBTofPidTraits(Long_t size, void *p);
   static void delete_StPicoBTofPidTraits(void *p);
   static void deleteArray_StPicoBTofPidTraits(void *p);
   static void destruct_StPicoBTofPidTraits(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoBTofPidTraits*)
   {
      ::StPicoBTofPidTraits *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoBTofPidTraits >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoBTofPidTraits", ::StPicoBTofPidTraits::Class_Version(), "StPicoBTofPidTraits.h", 20,
                  typeid(::StPicoBTofPidTraits), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoBTofPidTraits::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoBTofPidTraits) );
      instance.SetNew(&new_StPicoBTofPidTraits);
      instance.SetNewArray(&newArray_StPicoBTofPidTraits);
      instance.SetDelete(&delete_StPicoBTofPidTraits);
      instance.SetDeleteArray(&deleteArray_StPicoBTofPidTraits);
      instance.SetDestructor(&destruct_StPicoBTofPidTraits);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoBTofPidTraits*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoBTofPidTraits*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoBTofPidTraits*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoMcVertex(void *p = nullptr);
   static void *newArray_StPicoMcVertex(Long_t size, void *p);
   static void delete_StPicoMcVertex(void *p);
   static void deleteArray_StPicoMcVertex(void *p);
   static void destruct_StPicoMcVertex(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoMcVertex*)
   {
      ::StPicoMcVertex *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoMcVertex >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoMcVertex", ::StPicoMcVertex::Class_Version(), "StPicoMcVertex.h", 16,
                  typeid(::StPicoMcVertex), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoMcVertex::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoMcVertex) );
      instance.SetNew(&new_StPicoMcVertex);
      instance.SetNewArray(&newArray_StPicoMcVertex);
      instance.SetDelete(&delete_StPicoMcVertex);
      instance.SetDeleteArray(&deleteArray_StPicoMcVertex);
      instance.SetDestructor(&destruct_StPicoMcVertex);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoMcVertex*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoMcVertex*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoMcVertex*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoBEmcSmdPHit(void *p = nullptr);
   static void *newArray_StPicoBEmcSmdPHit(Long_t size, void *p);
   static void delete_StPicoBEmcSmdPHit(void *p);
   static void deleteArray_StPicoBEmcSmdPHit(void *p);
   static void destruct_StPicoBEmcSmdPHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoBEmcSmdPHit*)
   {
      ::StPicoBEmcSmdPHit *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoBEmcSmdPHit >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoBEmcSmdPHit", ::StPicoBEmcSmdPHit::Class_Version(), "StPicoBEmcSmdPHit.h", 17,
                  typeid(::StPicoBEmcSmdPHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoBEmcSmdPHit::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoBEmcSmdPHit) );
      instance.SetNew(&new_StPicoBEmcSmdPHit);
      instance.SetNewArray(&newArray_StPicoBEmcSmdPHit);
      instance.SetDelete(&delete_StPicoBEmcSmdPHit);
      instance.SetDeleteArray(&deleteArray_StPicoBEmcSmdPHit);
      instance.SetDestructor(&destruct_StPicoBEmcSmdPHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoBEmcSmdPHit*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoBEmcSmdPHit*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoBEmcSmdPHit*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoBEmcPidTraits(void *p = nullptr);
   static void *newArray_StPicoBEmcPidTraits(Long_t size, void *p);
   static void delete_StPicoBEmcPidTraits(void *p);
   static void deleteArray_StPicoBEmcPidTraits(void *p);
   static void destruct_StPicoBEmcPidTraits(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoBEmcPidTraits*)
   {
      ::StPicoBEmcPidTraits *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoBEmcPidTraits >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoBEmcPidTraits", ::StPicoBEmcPidTraits::Class_Version(), "StPicoBEmcPidTraits.h", 18,
                  typeid(::StPicoBEmcPidTraits), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoBEmcPidTraits::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoBEmcPidTraits) );
      instance.SetNew(&new_StPicoBEmcPidTraits);
      instance.SetNewArray(&newArray_StPicoBEmcPidTraits);
      instance.SetDelete(&delete_StPicoBEmcPidTraits);
      instance.SetDeleteArray(&deleteArray_StPicoBEmcPidTraits);
      instance.SetDestructor(&destruct_StPicoBEmcPidTraits);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoBEmcPidTraits*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoBEmcPidTraits*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoBEmcPidTraits*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoEmcTrigger(void *p = nullptr);
   static void *newArray_StPicoEmcTrigger(Long_t size, void *p);
   static void delete_StPicoEmcTrigger(void *p);
   static void deleteArray_StPicoEmcTrigger(void *p);
   static void destruct_StPicoEmcTrigger(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoEmcTrigger*)
   {
      ::StPicoEmcTrigger *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoEmcTrigger >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoEmcTrigger", ::StPicoEmcTrigger::Class_Version(), "StPicoEmcTrigger.h", 18,
                  typeid(::StPicoEmcTrigger), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoEmcTrigger::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoEmcTrigger) );
      instance.SetNew(&new_StPicoEmcTrigger);
      instance.SetNewArray(&newArray_StPicoEmcTrigger);
      instance.SetDelete(&delete_StPicoEmcTrigger);
      instance.SetDeleteArray(&deleteArray_StPicoEmcTrigger);
      instance.SetDestructor(&destruct_StPicoEmcTrigger);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoEmcTrigger*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoEmcTrigger*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoEmcTrigger*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoMtdTrigger(void *p = nullptr);
   static void *newArray_StPicoMtdTrigger(Long_t size, void *p);
   static void delete_StPicoMtdTrigger(void *p);
   static void deleteArray_StPicoMtdTrigger(void *p);
   static void destruct_StPicoMtdTrigger(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoMtdTrigger*)
   {
      ::StPicoMtdTrigger *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoMtdTrigger >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoMtdTrigger", ::StPicoMtdTrigger::Class_Version(), "StPicoMtdTrigger.h", 15,
                  typeid(::StPicoMtdTrigger), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoMtdTrigger::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoMtdTrigger) );
      instance.SetNew(&new_StPicoMtdTrigger);
      instance.SetNewArray(&newArray_StPicoMtdTrigger);
      instance.SetDelete(&delete_StPicoMtdTrigger);
      instance.SetDeleteArray(&deleteArray_StPicoMtdTrigger);
      instance.SetDestructor(&destruct_StPicoMtdTrigger);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoMtdTrigger*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoMtdTrigger*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoMtdTrigger*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoBTowHit(void *p = nullptr);
   static void *newArray_StPicoBTowHit(Long_t size, void *p);
   static void delete_StPicoBTowHit(void *p);
   static void deleteArray_StPicoBTowHit(void *p);
   static void destruct_StPicoBTowHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoBTowHit*)
   {
      ::StPicoBTowHit *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoBTowHit >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoBTowHit", ::StPicoBTowHit::Class_Version(), "StPicoBTowHit.h", 19,
                  typeid(::StPicoBTowHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoBTowHit::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoBTowHit) );
      instance.SetNew(&new_StPicoBTowHit);
      instance.SetNewArray(&newArray_StPicoBTowHit);
      instance.SetDelete(&delete_StPicoBTowHit);
      instance.SetDeleteArray(&deleteArray_StPicoBTowHit);
      instance.SetDestructor(&destruct_StPicoBTowHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoBTowHit*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoBTowHit*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoBTowHit*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoTrackCovMatrix(void *p = nullptr);
   static void *newArray_StPicoTrackCovMatrix(Long_t size, void *p);
   static void delete_StPicoTrackCovMatrix(void *p);
   static void deleteArray_StPicoTrackCovMatrix(void *p);
   static void destruct_StPicoTrackCovMatrix(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoTrackCovMatrix*)
   {
      ::StPicoTrackCovMatrix *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoTrackCovMatrix >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoTrackCovMatrix", ::StPicoTrackCovMatrix::Class_Version(), "StPicoTrackCovMatrix.h", 12,
                  typeid(::StPicoTrackCovMatrix), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoTrackCovMatrix::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoTrackCovMatrix) );
      instance.SetNew(&new_StPicoTrackCovMatrix);
      instance.SetNewArray(&newArray_StPicoTrackCovMatrix);
      instance.SetDelete(&delete_StPicoTrackCovMatrix);
      instance.SetDeleteArray(&deleteArray_StPicoTrackCovMatrix);
      instance.SetDestructor(&destruct_StPicoTrackCovMatrix);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoTrackCovMatrix*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoTrackCovMatrix*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoTrackCovMatrix*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *StPicoDst_Dictionary();
   static void StPicoDst_TClassManip(TClass*);
   static void *new_StPicoDst(void *p = nullptr);
   static void *newArray_StPicoDst(Long_t size, void *p);
   static void delete_StPicoDst(void *p);
   static void deleteArray_StPicoDst(void *p);
   static void destruct_StPicoDst(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoDst*)
   {
      ::StPicoDst *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::StPicoDst));
      static ::ROOT::TGenericClassInfo 
         instance("StPicoDst", "StPicoDst.h", 40,
                  typeid(::StPicoDst), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &StPicoDst_Dictionary, isa_proxy, 4,
                  sizeof(::StPicoDst) );
      instance.SetNew(&new_StPicoDst);
      instance.SetNewArray(&newArray_StPicoDst);
      instance.SetDelete(&delete_StPicoDst);
      instance.SetDeleteArray(&deleteArray_StPicoDst);
      instance.SetDestructor(&destruct_StPicoDst);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoDst*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoDst*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoDst*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *StPicoDst_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::StPicoDst*>(nullptr))->GetClass();
      StPicoDst_TClassManip(theClass);
   return theClass;
   }

   static void StPicoDst_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoEvent(void *p = nullptr);
   static void *newArray_StPicoEvent(Long_t size, void *p);
   static void delete_StPicoEvent(void *p);
   static void deleteArray_StPicoEvent(void *p);
   static void destruct_StPicoEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoEvent*)
   {
      ::StPicoEvent *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoEvent >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoEvent", ::StPicoEvent::Class_Version(), "StPicoEvent.h", 24,
                  typeid(::StPicoEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoEvent::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoEvent) );
      instance.SetNew(&new_StPicoEvent);
      instance.SetNewArray(&newArray_StPicoEvent);
      instance.SetDelete(&delete_StPicoEvent);
      instance.SetDeleteArray(&deleteArray_StPicoEvent);
      instance.SetDestructor(&destruct_StPicoEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoEvent*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoEvent*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoEvent*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_StPicoDstReader(void *p);
   static void deleteArray_StPicoDstReader(void *p);
   static void destruct_StPicoDstReader(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoDstReader*)
   {
      ::StPicoDstReader *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoDstReader >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoDstReader", ::StPicoDstReader::Class_Version(), "StPicoDstReader.h", 31,
                  typeid(::StPicoDstReader), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoDstReader::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoDstReader) );
      instance.SetDelete(&delete_StPicoDstReader);
      instance.SetDeleteArray(&deleteArray_StPicoDstReader);
      instance.SetDestructor(&destruct_StPicoDstReader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoDstReader*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoDstReader*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoDstReader*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoMtdPidTraits(void *p = nullptr);
   static void *newArray_StPicoMtdPidTraits(Long_t size, void *p);
   static void delete_StPicoMtdPidTraits(void *p);
   static void deleteArray_StPicoMtdPidTraits(void *p);
   static void destruct_StPicoMtdPidTraits(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoMtdPidTraits*)
   {
      ::StPicoMtdPidTraits *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoMtdPidTraits >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoMtdPidTraits", ::StPicoMtdPidTraits::Class_Version(), "StPicoMtdPidTraits.h", 16,
                  typeid(::StPicoMtdPidTraits), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoMtdPidTraits::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoMtdPidTraits) );
      instance.SetNew(&new_StPicoMtdPidTraits);
      instance.SetNewArray(&newArray_StPicoMtdPidTraits);
      instance.SetDelete(&delete_StPicoMtdPidTraits);
      instance.SetDeleteArray(&deleteArray_StPicoMtdPidTraits);
      instance.SetDestructor(&destruct_StPicoMtdPidTraits);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoMtdPidTraits*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoMtdPidTraits*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoMtdPidTraits*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoMcTrack(void *p = nullptr);
   static void *newArray_StPicoMcTrack(Long_t size, void *p);
   static void delete_StPicoMcTrack(void *p);
   static void deleteArray_StPicoMcTrack(void *p);
   static void destruct_StPicoMcTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoMcTrack*)
   {
      ::StPicoMcTrack *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoMcTrack >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoMcTrack", ::StPicoMcTrack::Class_Version(), "StPicoMcTrack.h", 32,
                  typeid(::StPicoMcTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoMcTrack::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoMcTrack) );
      instance.SetNew(&new_StPicoMcTrack);
      instance.SetNewArray(&newArray_StPicoMcTrack);
      instance.SetDelete(&delete_StPicoMcTrack);
      instance.SetDeleteArray(&deleteArray_StPicoMcTrack);
      instance.SetDestructor(&destruct_StPicoMcTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoMcTrack*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoMcTrack*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoMcTrack*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoFmsHit(void *p = nullptr);
   static void *newArray_StPicoFmsHit(Long_t size, void *p);
   static void delete_StPicoFmsHit(void *p);
   static void deleteArray_StPicoFmsHit(void *p);
   static void destruct_StPicoFmsHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoFmsHit*)
   {
      ::StPicoFmsHit *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoFmsHit >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoFmsHit", ::StPicoFmsHit::Class_Version(), "StPicoFmsHit.h", 17,
                  typeid(::StPicoFmsHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoFmsHit::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoFmsHit) );
      instance.SetNew(&new_StPicoFmsHit);
      instance.SetNewArray(&newArray_StPicoFmsHit);
      instance.SetDelete(&delete_StPicoFmsHit);
      instance.SetDeleteArray(&deleteArray_StPicoFmsHit);
      instance.SetDestructor(&destruct_StPicoFmsHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoFmsHit*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoFmsHit*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoFmsHit*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoETofPidTraits(void *p = nullptr);
   static void *newArray_StPicoETofPidTraits(Long_t size, void *p);
   static void delete_StPicoETofPidTraits(void *p);
   static void deleteArray_StPicoETofPidTraits(void *p);
   static void destruct_StPicoETofPidTraits(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoETofPidTraits*)
   {
      ::StPicoETofPidTraits *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoETofPidTraits >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoETofPidTraits", ::StPicoETofPidTraits::Class_Version(), "StPicoETofPidTraits.h", 20,
                  typeid(::StPicoETofPidTraits), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoETofPidTraits::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoETofPidTraits) );
      instance.SetNew(&new_StPicoETofPidTraits);
      instance.SetNewArray(&newArray_StPicoETofPidTraits);
      instance.SetDelete(&delete_StPicoETofPidTraits);
      instance.SetDeleteArray(&deleteArray_StPicoETofPidTraits);
      instance.SetDestructor(&destruct_StPicoETofPidTraits);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoETofPidTraits*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoETofPidTraits*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoETofPidTraits*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoEpdHit(void *p = nullptr);
   static void *newArray_StPicoEpdHit(Long_t size, void *p);
   static void delete_StPicoEpdHit(void *p);
   static void deleteArray_StPicoEpdHit(void *p);
   static void destruct_StPicoEpdHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoEpdHit*)
   {
      ::StPicoEpdHit *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoEpdHit >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoEpdHit", ::StPicoEpdHit::Class_Version(), "StPicoEpdHit.h", 46,
                  typeid(::StPicoEpdHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoEpdHit::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoEpdHit) );
      instance.SetNew(&new_StPicoEpdHit);
      instance.SetNewArray(&newArray_StPicoEpdHit);
      instance.SetDelete(&delete_StPicoEpdHit);
      instance.SetDeleteArray(&deleteArray_StPicoEpdHit);
      instance.SetDestructor(&destruct_StPicoEpdHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoEpdHit*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoEpdHit*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoEpdHit*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoBTofHit(void *p = nullptr);
   static void *newArray_StPicoBTofHit(Long_t size, void *p);
   static void delete_StPicoBTofHit(void *p);
   static void deleteArray_StPicoBTofHit(void *p);
   static void destruct_StPicoBTofHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoBTofHit*)
   {
      ::StPicoBTofHit *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoBTofHit >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoBTofHit", ::StPicoBTofHit::Class_Version(), "StPicoBTofHit.h", 18,
                  typeid(::StPicoBTofHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoBTofHit::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoBTofHit) );
      instance.SetNew(&new_StPicoBTofHit);
      instance.SetNewArray(&newArray_StPicoBTofHit);
      instance.SetDelete(&delete_StPicoBTofHit);
      instance.SetDeleteArray(&deleteArray_StPicoBTofHit);
      instance.SetDestructor(&destruct_StPicoBTofHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoBTofHit*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoBTofHit*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoBTofHit*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoBbcHit(void *p = nullptr);
   static void *newArray_StPicoBbcHit(Long_t size, void *p);
   static void delete_StPicoBbcHit(void *p);
   static void deleteArray_StPicoBbcHit(void *p);
   static void destruct_StPicoBbcHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoBbcHit*)
   {
      ::StPicoBbcHit *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoBbcHit >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoBbcHit", ::StPicoBbcHit::Class_Version(), "StPicoBbcHit.h", 38,
                  typeid(::StPicoBbcHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoBbcHit::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoBbcHit) );
      instance.SetNew(&new_StPicoBbcHit);
      instance.SetNewArray(&newArray_StPicoBbcHit);
      instance.SetDelete(&delete_StPicoBbcHit);
      instance.SetDeleteArray(&deleteArray_StPicoBbcHit);
      instance.SetDestructor(&destruct_StPicoBbcHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoBbcHit*)
   {
      return GenerateInitInstanceLocal(static_cast<::StPicoBbcHit*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::StPicoBbcHit*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr StPicoETofHit::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoETofHit::Class_Name()
{
   return "StPicoETofHit";
}

//______________________________________________________________________________
const char *StPicoETofHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoETofHit*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoETofHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoETofHit*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoETofHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoETofHit*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoETofHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoETofHit*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoMtdHit::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoMtdHit::Class_Name()
{
   return "StPicoMtdHit";
}

//______________________________________________________________________________
const char *StPicoMtdHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdHit*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoMtdHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdHit*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoMtdHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdHit*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoMtdHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdHit*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoBEmcSmdEHit::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoBEmcSmdEHit::Class_Name()
{
   return "StPicoBEmcSmdEHit";
}

//______________________________________________________________________________
const char *StPicoBEmcSmdEHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBEmcSmdEHit*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoBEmcSmdEHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBEmcSmdEHit*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoBEmcSmdEHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBEmcSmdEHit*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoBEmcSmdEHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBEmcSmdEHit*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoHelix::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoHelix::Class_Name()
{
   return "StPicoHelix";
}

//______________________________________________________________________________
const char *StPicoHelix::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoHelix*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoHelix::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoHelix*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoHelix::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoHelix*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoHelix::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoHelix*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoPhysicalHelix::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoPhysicalHelix::Class_Name()
{
   return "StPicoPhysicalHelix";
}

//______________________________________________________________________________
const char *StPicoPhysicalHelix::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoPhysicalHelix*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoPhysicalHelix::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoPhysicalHelix*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoPhysicalHelix::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoPhysicalHelix*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoPhysicalHelix::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoPhysicalHelix*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoTrack::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoTrack::Class_Name()
{
   return "StPicoTrack";
}

//______________________________________________________________________________
const char *StPicoTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoTrack*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoTrack*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoTrack*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoTrack*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoBTofPidTraits::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoBTofPidTraits::Class_Name()
{
   return "StPicoBTofPidTraits";
}

//______________________________________________________________________________
const char *StPicoBTofPidTraits::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTofPidTraits*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoBTofPidTraits::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTofPidTraits*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoBTofPidTraits::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTofPidTraits*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoBTofPidTraits::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTofPidTraits*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoMcVertex::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoMcVertex::Class_Name()
{
   return "StPicoMcVertex";
}

//______________________________________________________________________________
const char *StPicoMcVertex::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoMcVertex*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoMcVertex::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoMcVertex*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoMcVertex::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoMcVertex*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoMcVertex::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoMcVertex*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoBEmcSmdPHit::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoBEmcSmdPHit::Class_Name()
{
   return "StPicoBEmcSmdPHit";
}

//______________________________________________________________________________
const char *StPicoBEmcSmdPHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBEmcSmdPHit*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoBEmcSmdPHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBEmcSmdPHit*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoBEmcSmdPHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBEmcSmdPHit*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoBEmcSmdPHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBEmcSmdPHit*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoBEmcPidTraits::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoBEmcPidTraits::Class_Name()
{
   return "StPicoBEmcPidTraits";
}

//______________________________________________________________________________
const char *StPicoBEmcPidTraits::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBEmcPidTraits*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoBEmcPidTraits::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBEmcPidTraits*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoBEmcPidTraits::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBEmcPidTraits*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoBEmcPidTraits::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBEmcPidTraits*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoEmcTrigger::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoEmcTrigger::Class_Name()
{
   return "StPicoEmcTrigger";
}

//______________________________________________________________________________
const char *StPicoEmcTrigger::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoEmcTrigger*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoEmcTrigger::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoEmcTrigger*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoEmcTrigger::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoEmcTrigger*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoEmcTrigger::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoEmcTrigger*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoMtdTrigger::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoMtdTrigger::Class_Name()
{
   return "StPicoMtdTrigger";
}

//______________________________________________________________________________
const char *StPicoMtdTrigger::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdTrigger*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoMtdTrigger::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdTrigger*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoMtdTrigger::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdTrigger*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoMtdTrigger::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdTrigger*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoBTowHit::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoBTowHit::Class_Name()
{
   return "StPicoBTowHit";
}

//______________________________________________________________________________
const char *StPicoBTowHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTowHit*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoBTowHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTowHit*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoBTowHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTowHit*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoBTowHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTowHit*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoTrackCovMatrix::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoTrackCovMatrix::Class_Name()
{
   return "StPicoTrackCovMatrix";
}

//______________________________________________________________________________
const char *StPicoTrackCovMatrix::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoTrackCovMatrix*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoTrackCovMatrix::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoTrackCovMatrix*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoTrackCovMatrix::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoTrackCovMatrix*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoTrackCovMatrix::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoTrackCovMatrix*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoEvent::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoEvent::Class_Name()
{
   return "StPicoEvent";
}

//______________________________________________________________________________
const char *StPicoEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoEvent*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoEvent*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoEvent*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoEvent*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoDstReader::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoDstReader::Class_Name()
{
   return "StPicoDstReader";
}

//______________________________________________________________________________
const char *StPicoDstReader::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoDstReader*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoDstReader::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoDstReader*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoDstReader::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoDstReader*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoDstReader::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoDstReader*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoMtdPidTraits::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoMtdPidTraits::Class_Name()
{
   return "StPicoMtdPidTraits";
}

//______________________________________________________________________________
const char *StPicoMtdPidTraits::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdPidTraits*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoMtdPidTraits::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdPidTraits*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoMtdPidTraits::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdPidTraits*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoMtdPidTraits::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdPidTraits*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoMcTrack::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoMcTrack::Class_Name()
{
   return "StPicoMcTrack";
}

//______________________________________________________________________________
const char *StPicoMcTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoMcTrack*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoMcTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoMcTrack*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoMcTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoMcTrack*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoMcTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoMcTrack*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoFmsHit::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoFmsHit::Class_Name()
{
   return "StPicoFmsHit";
}

//______________________________________________________________________________
const char *StPicoFmsHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoFmsHit*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoFmsHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoFmsHit*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoFmsHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoFmsHit*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoFmsHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoFmsHit*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoETofPidTraits::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoETofPidTraits::Class_Name()
{
   return "StPicoETofPidTraits";
}

//______________________________________________________________________________
const char *StPicoETofPidTraits::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoETofPidTraits*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoETofPidTraits::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoETofPidTraits*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoETofPidTraits::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoETofPidTraits*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoETofPidTraits::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoETofPidTraits*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoEpdHit::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoEpdHit::Class_Name()
{
   return "StPicoEpdHit";
}

//______________________________________________________________________________
const char *StPicoEpdHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoEpdHit*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoEpdHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoEpdHit*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoEpdHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoEpdHit*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoEpdHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoEpdHit*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoBTofHit::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoBTofHit::Class_Name()
{
   return "StPicoBTofHit";
}

//______________________________________________________________________________
const char *StPicoBTofHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTofHit*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoBTofHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTofHit*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoBTofHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTofHit*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoBTofHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTofHit*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoBbcHit::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoBbcHit::Class_Name()
{
   return "StPicoBbcHit";
}

//______________________________________________________________________________
const char *StPicoBbcHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBbcHit*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoBbcHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBbcHit*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoBbcHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBbcHit*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoBbcHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBbcHit*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void StPicoETofHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoETofHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoETofHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoETofHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoETofHit(void *p) {
      return  p ? new(p) ::StPicoETofHit : new ::StPicoETofHit;
   }
   static void *newArray_StPicoETofHit(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoETofHit[nElements] : new ::StPicoETofHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoETofHit(void *p) {
      delete (static_cast<::StPicoETofHit*>(p));
   }
   static void deleteArray_StPicoETofHit(void *p) {
      delete [] (static_cast<::StPicoETofHit*>(p));
   }
   static void destruct_StPicoETofHit(void *p) {
      typedef ::StPicoETofHit current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoETofHit

//______________________________________________________________________________
void StPicoMtdHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoMtdHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoMtdHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoMtdHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoMtdHit(void *p) {
      return  p ? new(p) ::StPicoMtdHit : new ::StPicoMtdHit;
   }
   static void *newArray_StPicoMtdHit(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoMtdHit[nElements] : new ::StPicoMtdHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoMtdHit(void *p) {
      delete (static_cast<::StPicoMtdHit*>(p));
   }
   static void deleteArray_StPicoMtdHit(void *p) {
      delete [] (static_cast<::StPicoMtdHit*>(p));
   }
   static void destruct_StPicoMtdHit(void *p) {
      typedef ::StPicoMtdHit current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoMtdHit

//______________________________________________________________________________
void StPicoBEmcSmdEHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoBEmcSmdEHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoBEmcSmdEHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoBEmcSmdEHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoBEmcSmdEHit(void *p) {
      return  p ? new(p) ::StPicoBEmcSmdEHit : new ::StPicoBEmcSmdEHit;
   }
   static void *newArray_StPicoBEmcSmdEHit(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoBEmcSmdEHit[nElements] : new ::StPicoBEmcSmdEHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoBEmcSmdEHit(void *p) {
      delete (static_cast<::StPicoBEmcSmdEHit*>(p));
   }
   static void deleteArray_StPicoBEmcSmdEHit(void *p) {
      delete [] (static_cast<::StPicoBEmcSmdEHit*>(p));
   }
   static void destruct_StPicoBEmcSmdEHit(void *p) {
      typedef ::StPicoBEmcSmdEHit current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoBEmcSmdEHit

//______________________________________________________________________________
void StPicoHelix::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoHelix.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoHelix::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoHelix::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoHelix(void *p) {
      return  p ? new(p) ::StPicoHelix : new ::StPicoHelix;
   }
   static void *newArray_StPicoHelix(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoHelix[nElements] : new ::StPicoHelix[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoHelix(void *p) {
      delete (static_cast<::StPicoHelix*>(p));
   }
   static void deleteArray_StPicoHelix(void *p) {
      delete [] (static_cast<::StPicoHelix*>(p));
   }
   static void destruct_StPicoHelix(void *p) {
      typedef ::StPicoHelix current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoHelix

//______________________________________________________________________________
void StPicoPhysicalHelix::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoPhysicalHelix.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoPhysicalHelix::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoPhysicalHelix::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoPhysicalHelix(void *p) {
      return  p ? new(p) ::StPicoPhysicalHelix : new ::StPicoPhysicalHelix;
   }
   static void *newArray_StPicoPhysicalHelix(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoPhysicalHelix[nElements] : new ::StPicoPhysicalHelix[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoPhysicalHelix(void *p) {
      delete (static_cast<::StPicoPhysicalHelix*>(p));
   }
   static void deleteArray_StPicoPhysicalHelix(void *p) {
      delete [] (static_cast<::StPicoPhysicalHelix*>(p));
   }
   static void destruct_StPicoPhysicalHelix(void *p) {
      typedef ::StPicoPhysicalHelix current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoPhysicalHelix

//______________________________________________________________________________
void StPicoTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoTrack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoTrack::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoTrack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoTrack(void *p) {
      return  p ? new(p) ::StPicoTrack : new ::StPicoTrack;
   }
   static void *newArray_StPicoTrack(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoTrack[nElements] : new ::StPicoTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoTrack(void *p) {
      delete (static_cast<::StPicoTrack*>(p));
   }
   static void deleteArray_StPicoTrack(void *p) {
      delete [] (static_cast<::StPicoTrack*>(p));
   }
   static void destruct_StPicoTrack(void *p) {
      typedef ::StPicoTrack current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoTrack

//______________________________________________________________________________
void StPicoBTofPidTraits::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoBTofPidTraits.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoBTofPidTraits::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoBTofPidTraits::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoBTofPidTraits(void *p) {
      return  p ? new(p) ::StPicoBTofPidTraits : new ::StPicoBTofPidTraits;
   }
   static void *newArray_StPicoBTofPidTraits(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoBTofPidTraits[nElements] : new ::StPicoBTofPidTraits[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoBTofPidTraits(void *p) {
      delete (static_cast<::StPicoBTofPidTraits*>(p));
   }
   static void deleteArray_StPicoBTofPidTraits(void *p) {
      delete [] (static_cast<::StPicoBTofPidTraits*>(p));
   }
   static void destruct_StPicoBTofPidTraits(void *p) {
      typedef ::StPicoBTofPidTraits current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoBTofPidTraits

//______________________________________________________________________________
void StPicoMcVertex::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoMcVertex.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoMcVertex::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoMcVertex::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoMcVertex(void *p) {
      return  p ? new(p) ::StPicoMcVertex : new ::StPicoMcVertex;
   }
   static void *newArray_StPicoMcVertex(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoMcVertex[nElements] : new ::StPicoMcVertex[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoMcVertex(void *p) {
      delete (static_cast<::StPicoMcVertex*>(p));
   }
   static void deleteArray_StPicoMcVertex(void *p) {
      delete [] (static_cast<::StPicoMcVertex*>(p));
   }
   static void destruct_StPicoMcVertex(void *p) {
      typedef ::StPicoMcVertex current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoMcVertex

//______________________________________________________________________________
void StPicoBEmcSmdPHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoBEmcSmdPHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoBEmcSmdPHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoBEmcSmdPHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoBEmcSmdPHit(void *p) {
      return  p ? new(p) ::StPicoBEmcSmdPHit : new ::StPicoBEmcSmdPHit;
   }
   static void *newArray_StPicoBEmcSmdPHit(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoBEmcSmdPHit[nElements] : new ::StPicoBEmcSmdPHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoBEmcSmdPHit(void *p) {
      delete (static_cast<::StPicoBEmcSmdPHit*>(p));
   }
   static void deleteArray_StPicoBEmcSmdPHit(void *p) {
      delete [] (static_cast<::StPicoBEmcSmdPHit*>(p));
   }
   static void destruct_StPicoBEmcSmdPHit(void *p) {
      typedef ::StPicoBEmcSmdPHit current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoBEmcSmdPHit

//______________________________________________________________________________
void StPicoBEmcPidTraits::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoBEmcPidTraits.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoBEmcPidTraits::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoBEmcPidTraits::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoBEmcPidTraits(void *p) {
      return  p ? new(p) ::StPicoBEmcPidTraits : new ::StPicoBEmcPidTraits;
   }
   static void *newArray_StPicoBEmcPidTraits(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoBEmcPidTraits[nElements] : new ::StPicoBEmcPidTraits[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoBEmcPidTraits(void *p) {
      delete (static_cast<::StPicoBEmcPidTraits*>(p));
   }
   static void deleteArray_StPicoBEmcPidTraits(void *p) {
      delete [] (static_cast<::StPicoBEmcPidTraits*>(p));
   }
   static void destruct_StPicoBEmcPidTraits(void *p) {
      typedef ::StPicoBEmcPidTraits current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoBEmcPidTraits

//______________________________________________________________________________
void StPicoEmcTrigger::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoEmcTrigger.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoEmcTrigger::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoEmcTrigger::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoEmcTrigger(void *p) {
      return  p ? new(p) ::StPicoEmcTrigger : new ::StPicoEmcTrigger;
   }
   static void *newArray_StPicoEmcTrigger(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoEmcTrigger[nElements] : new ::StPicoEmcTrigger[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoEmcTrigger(void *p) {
      delete (static_cast<::StPicoEmcTrigger*>(p));
   }
   static void deleteArray_StPicoEmcTrigger(void *p) {
      delete [] (static_cast<::StPicoEmcTrigger*>(p));
   }
   static void destruct_StPicoEmcTrigger(void *p) {
      typedef ::StPicoEmcTrigger current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoEmcTrigger

//______________________________________________________________________________
void StPicoMtdTrigger::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoMtdTrigger.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoMtdTrigger::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoMtdTrigger::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoMtdTrigger(void *p) {
      return  p ? new(p) ::StPicoMtdTrigger : new ::StPicoMtdTrigger;
   }
   static void *newArray_StPicoMtdTrigger(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoMtdTrigger[nElements] : new ::StPicoMtdTrigger[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoMtdTrigger(void *p) {
      delete (static_cast<::StPicoMtdTrigger*>(p));
   }
   static void deleteArray_StPicoMtdTrigger(void *p) {
      delete [] (static_cast<::StPicoMtdTrigger*>(p));
   }
   static void destruct_StPicoMtdTrigger(void *p) {
      typedef ::StPicoMtdTrigger current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoMtdTrigger

//______________________________________________________________________________
void StPicoBTowHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoBTowHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoBTowHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoBTowHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoBTowHit(void *p) {
      return  p ? new(p) ::StPicoBTowHit : new ::StPicoBTowHit;
   }
   static void *newArray_StPicoBTowHit(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoBTowHit[nElements] : new ::StPicoBTowHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoBTowHit(void *p) {
      delete (static_cast<::StPicoBTowHit*>(p));
   }
   static void deleteArray_StPicoBTowHit(void *p) {
      delete [] (static_cast<::StPicoBTowHit*>(p));
   }
   static void destruct_StPicoBTowHit(void *p) {
      typedef ::StPicoBTowHit current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoBTowHit

//______________________________________________________________________________
void StPicoTrackCovMatrix::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoTrackCovMatrix.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoTrackCovMatrix::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoTrackCovMatrix::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoTrackCovMatrix(void *p) {
      return  p ? new(p) ::StPicoTrackCovMatrix : new ::StPicoTrackCovMatrix;
   }
   static void *newArray_StPicoTrackCovMatrix(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoTrackCovMatrix[nElements] : new ::StPicoTrackCovMatrix[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoTrackCovMatrix(void *p) {
      delete (static_cast<::StPicoTrackCovMatrix*>(p));
   }
   static void deleteArray_StPicoTrackCovMatrix(void *p) {
      delete [] (static_cast<::StPicoTrackCovMatrix*>(p));
   }
   static void destruct_StPicoTrackCovMatrix(void *p) {
      typedef ::StPicoTrackCovMatrix current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoTrackCovMatrix

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoDst(void *p) {
      return  p ? new(p) ::StPicoDst : new ::StPicoDst;
   }
   static void *newArray_StPicoDst(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoDst[nElements] : new ::StPicoDst[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoDst(void *p) {
      delete (static_cast<::StPicoDst*>(p));
   }
   static void deleteArray_StPicoDst(void *p) {
      delete [] (static_cast<::StPicoDst*>(p));
   }
   static void destruct_StPicoDst(void *p) {
      typedef ::StPicoDst current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoDst

//______________________________________________________________________________
void StPicoEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoEvent(void *p) {
      return  p ? new(p) ::StPicoEvent : new ::StPicoEvent;
   }
   static void *newArray_StPicoEvent(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoEvent[nElements] : new ::StPicoEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoEvent(void *p) {
      delete (static_cast<::StPicoEvent*>(p));
   }
   static void deleteArray_StPicoEvent(void *p) {
      delete [] (static_cast<::StPicoEvent*>(p));
   }
   static void destruct_StPicoEvent(void *p) {
      typedef ::StPicoEvent current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoEvent

//______________________________________________________________________________
void StPicoDstReader::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoDstReader.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoDstReader::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoDstReader::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_StPicoDstReader(void *p) {
      delete (static_cast<::StPicoDstReader*>(p));
   }
   static void deleteArray_StPicoDstReader(void *p) {
      delete [] (static_cast<::StPicoDstReader*>(p));
   }
   static void destruct_StPicoDstReader(void *p) {
      typedef ::StPicoDstReader current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoDstReader

//______________________________________________________________________________
void StPicoMtdPidTraits::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoMtdPidTraits.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoMtdPidTraits::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoMtdPidTraits::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoMtdPidTraits(void *p) {
      return  p ? new(p) ::StPicoMtdPidTraits : new ::StPicoMtdPidTraits;
   }
   static void *newArray_StPicoMtdPidTraits(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoMtdPidTraits[nElements] : new ::StPicoMtdPidTraits[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoMtdPidTraits(void *p) {
      delete (static_cast<::StPicoMtdPidTraits*>(p));
   }
   static void deleteArray_StPicoMtdPidTraits(void *p) {
      delete [] (static_cast<::StPicoMtdPidTraits*>(p));
   }
   static void destruct_StPicoMtdPidTraits(void *p) {
      typedef ::StPicoMtdPidTraits current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoMtdPidTraits

//______________________________________________________________________________
void StPicoMcTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoMcTrack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoMcTrack::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoMcTrack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoMcTrack(void *p) {
      return  p ? new(p) ::StPicoMcTrack : new ::StPicoMcTrack;
   }
   static void *newArray_StPicoMcTrack(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoMcTrack[nElements] : new ::StPicoMcTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoMcTrack(void *p) {
      delete (static_cast<::StPicoMcTrack*>(p));
   }
   static void deleteArray_StPicoMcTrack(void *p) {
      delete [] (static_cast<::StPicoMcTrack*>(p));
   }
   static void destruct_StPicoMcTrack(void *p) {
      typedef ::StPicoMcTrack current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoMcTrack

//______________________________________________________________________________
void StPicoFmsHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoFmsHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoFmsHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoFmsHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoFmsHit(void *p) {
      return  p ? new(p) ::StPicoFmsHit : new ::StPicoFmsHit;
   }
   static void *newArray_StPicoFmsHit(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoFmsHit[nElements] : new ::StPicoFmsHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoFmsHit(void *p) {
      delete (static_cast<::StPicoFmsHit*>(p));
   }
   static void deleteArray_StPicoFmsHit(void *p) {
      delete [] (static_cast<::StPicoFmsHit*>(p));
   }
   static void destruct_StPicoFmsHit(void *p) {
      typedef ::StPicoFmsHit current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoFmsHit

//______________________________________________________________________________
void StPicoETofPidTraits::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoETofPidTraits.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoETofPidTraits::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoETofPidTraits::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoETofPidTraits(void *p) {
      return  p ? new(p) ::StPicoETofPidTraits : new ::StPicoETofPidTraits;
   }
   static void *newArray_StPicoETofPidTraits(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoETofPidTraits[nElements] : new ::StPicoETofPidTraits[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoETofPidTraits(void *p) {
      delete (static_cast<::StPicoETofPidTraits*>(p));
   }
   static void deleteArray_StPicoETofPidTraits(void *p) {
      delete [] (static_cast<::StPicoETofPidTraits*>(p));
   }
   static void destruct_StPicoETofPidTraits(void *p) {
      typedef ::StPicoETofPidTraits current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoETofPidTraits

//______________________________________________________________________________
void StPicoEpdHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoEpdHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoEpdHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoEpdHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoEpdHit(void *p) {
      return  p ? new(p) ::StPicoEpdHit : new ::StPicoEpdHit;
   }
   static void *newArray_StPicoEpdHit(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoEpdHit[nElements] : new ::StPicoEpdHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoEpdHit(void *p) {
      delete (static_cast<::StPicoEpdHit*>(p));
   }
   static void deleteArray_StPicoEpdHit(void *p) {
      delete [] (static_cast<::StPicoEpdHit*>(p));
   }
   static void destruct_StPicoEpdHit(void *p) {
      typedef ::StPicoEpdHit current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoEpdHit

//______________________________________________________________________________
void StPicoBTofHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoBTofHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoBTofHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoBTofHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoBTofHit(void *p) {
      return  p ? new(p) ::StPicoBTofHit : new ::StPicoBTofHit;
   }
   static void *newArray_StPicoBTofHit(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoBTofHit[nElements] : new ::StPicoBTofHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoBTofHit(void *p) {
      delete (static_cast<::StPicoBTofHit*>(p));
   }
   static void deleteArray_StPicoBTofHit(void *p) {
      delete [] (static_cast<::StPicoBTofHit*>(p));
   }
   static void destruct_StPicoBTofHit(void *p) {
      typedef ::StPicoBTofHit current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoBTofHit

//______________________________________________________________________________
void StPicoBbcHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoBbcHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoBbcHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoBbcHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoBbcHit(void *p) {
      return  p ? new(p) ::StPicoBbcHit : new ::StPicoBbcHit;
   }
   static void *newArray_StPicoBbcHit(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoBbcHit[nElements] : new ::StPicoBbcHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoBbcHit(void *p) {
      delete (static_cast<::StPicoBbcHit*>(p));
   }
   static void deleteArray_StPicoBbcHit(void *p) {
      delete [] (static_cast<::StPicoBbcHit*>(p));
   }
   static void destruct_StPicoBbcHit(void *p) {
      typedef ::StPicoBbcHit current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::StPicoBbcHit

namespace ROOT {
   static TClass *vectorlEunsignedsPshortgR_Dictionary();
   static void vectorlEunsignedsPshortgR_TClassManip(TClass*);
   static void *new_vectorlEunsignedsPshortgR(void *p = nullptr);
   static void *newArray_vectorlEunsignedsPshortgR(Long_t size, void *p);
   static void delete_vectorlEunsignedsPshortgR(void *p);
   static void deleteArray_vectorlEunsignedsPshortgR(void *p);
   static void destruct_vectorlEunsignedsPshortgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<unsigned short>*)
   {
      vector<unsigned short> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<unsigned short>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<unsigned short>", -2, "vector", 389,
                  typeid(vector<unsigned short>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEunsignedsPshortgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<unsigned short>) );
      instance.SetNew(&new_vectorlEunsignedsPshortgR);
      instance.SetNewArray(&newArray_vectorlEunsignedsPshortgR);
      instance.SetDelete(&delete_vectorlEunsignedsPshortgR);
      instance.SetDeleteArray(&deleteArray_vectorlEunsignedsPshortgR);
      instance.SetDestructor(&destruct_vectorlEunsignedsPshortgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<unsigned short> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<unsigned short>","std::vector<unsigned short, std::allocator<unsigned short> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<unsigned short>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEunsignedsPshortgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<unsigned short>*>(nullptr))->GetClass();
      vectorlEunsignedsPshortgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEunsignedsPshortgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEunsignedsPshortgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<unsigned short> : new vector<unsigned short>;
   }
   static void *newArray_vectorlEunsignedsPshortgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<unsigned short>[nElements] : new vector<unsigned short>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEunsignedsPshortgR(void *p) {
      delete (static_cast<vector<unsigned short>*>(p));
   }
   static void deleteArray_vectorlEunsignedsPshortgR(void *p) {
      delete [] (static_cast<vector<unsigned short>*>(p));
   }
   static void destruct_vectorlEunsignedsPshortgR(void *p) {
      typedef vector<unsigned short> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<unsigned short>

namespace ROOT {
   static TClass *vectorlEunsignedsPintgR_Dictionary();
   static void vectorlEunsignedsPintgR_TClassManip(TClass*);
   static void *new_vectorlEunsignedsPintgR(void *p = nullptr);
   static void *newArray_vectorlEunsignedsPintgR(Long_t size, void *p);
   static void delete_vectorlEunsignedsPintgR(void *p);
   static void deleteArray_vectorlEunsignedsPintgR(void *p);
   static void destruct_vectorlEunsignedsPintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<unsigned int>*)
   {
      vector<unsigned int> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<unsigned int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<unsigned int>", -2, "vector", 389,
                  typeid(vector<unsigned int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEunsignedsPintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<unsigned int>) );
      instance.SetNew(&new_vectorlEunsignedsPintgR);
      instance.SetNewArray(&newArray_vectorlEunsignedsPintgR);
      instance.SetDelete(&delete_vectorlEunsignedsPintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEunsignedsPintgR);
      instance.SetDestructor(&destruct_vectorlEunsignedsPintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<unsigned int> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<unsigned int>","std::vector<unsigned int, std::allocator<unsigned int> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<unsigned int>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEunsignedsPintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<unsigned int>*>(nullptr))->GetClass();
      vectorlEunsignedsPintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEunsignedsPintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEunsignedsPintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<unsigned int> : new vector<unsigned int>;
   }
   static void *newArray_vectorlEunsignedsPintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<unsigned int>[nElements] : new vector<unsigned int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEunsignedsPintgR(void *p) {
      delete (static_cast<vector<unsigned int>*>(p));
   }
   static void deleteArray_vectorlEunsignedsPintgR(void *p) {
      delete [] (static_cast<vector<unsigned int>*>(p));
   }
   static void destruct_vectorlEunsignedsPintgR(void *p) {
      typedef vector<unsigned int> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<unsigned int>

namespace {
  void TriggerDictionaryInitialization_StPicoDst_Dict_Impl() {
    static const char* headers[] = {
"StPicoETofHit.h",
"StPicoMtdHit.h",
"StPicoBEmcSmdEHit.h",
"StPicoArrays.h",
"StPicoTrack.h",
"StPicoPhysicalHelix.h",
"StPicoBTofPidTraits.h",
"StPicoMcVertex.h",
"StPicoBEmcSmdPHit.h",
"StPicoBEmcPidTraits.h",
"StPicoHelix.h",
"StPicoEmcTrigger.h",
"StPicoMtdTrigger.h",
"StPicoBTowHit.h",
"StPicoCommon.h",
"StPicoTrackCovMatrix.h",
"StPicoDstReader.h",
"PhysicalConstants.h",
"StPicoEvent.h",
"StPicoMtdPidTraits.h",
"StPicoMcTrack.h",
"StPicoFmsHit.h",
"StPicoETofPidTraits.h",
"StPicoEpdHit.h",
"SystemOfUnits.h",
"StPicoBTofHit.h",
"StPicoBbcHit.h",
"StPicoDst.h",
"StPicoMessMgr.h",
nullptr
    };
    static const char* includePaths[] = {
"/home/tahea/root_install/include",
"/home/tahea/root_install/include/",
"/home/tahea/smash_CF_builder/smash_CF_builder/sthbtmaker/StRoot/StPicoEvent/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "StPicoDst_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$StPicoETofHit.h")))  StPicoETofHit;
class __attribute__((annotate("$clingAutoload$StPicoMtdHit.h")))  StPicoMtdHit;
class __attribute__((annotate("$clingAutoload$StPicoBEmcSmdEHit.h")))  StPicoBEmcSmdEHit;
class __attribute__((annotate("$clingAutoload$StPicoHelix.h")))  __attribute__((annotate("$clingAutoload$StPicoTrack.h")))  StPicoHelix;
class __attribute__((annotate("$clingAutoload$StPicoPhysicalHelix.h")))  __attribute__((annotate("$clingAutoload$StPicoTrack.h")))  StPicoPhysicalHelix;
class __attribute__((annotate("$clingAutoload$StPicoTrack.h")))  StPicoTrack;
class __attribute__((annotate("$clingAutoload$StPicoBTofPidTraits.h")))  StPicoBTofPidTraits;
class __attribute__((annotate("$clingAutoload$StPicoMcVertex.h")))  StPicoMcVertex;
class __attribute__((annotate("$clingAutoload$StPicoBEmcSmdPHit.h")))  StPicoBEmcSmdPHit;
class __attribute__((annotate("$clingAutoload$StPicoBEmcPidTraits.h")))  StPicoBEmcPidTraits;
class __attribute__((annotate("$clingAutoload$StPicoEmcTrigger.h")))  StPicoEmcTrigger;
class __attribute__((annotate("$clingAutoload$StPicoMtdTrigger.h")))  StPicoMtdTrigger;
class __attribute__((annotate("$clingAutoload$StPicoBTowHit.h")))  StPicoBTowHit;
class __attribute__((annotate("$clingAutoload$StPicoTrackCovMatrix.h")))  StPicoTrackCovMatrix;
class __attribute__((annotate("$clingAutoload$StPicoDst.h")))  __attribute__((annotate("$clingAutoload$StPicoDstReader.h")))  StPicoDst;
class __attribute__((annotate("$clingAutoload$StPicoEvent.h")))  __attribute__((annotate("$clingAutoload$StPicoDstReader.h")))  StPicoEvent;
class __attribute__((annotate("$clingAutoload$StPicoDstReader.h")))  StPicoDstReader;
class __attribute__((annotate("$clingAutoload$StPicoMtdPidTraits.h")))  StPicoMtdPidTraits;
class __attribute__((annotate("$clingAutoload$StPicoMcTrack.h")))  StPicoMcTrack;
class __attribute__((annotate("$clingAutoload$StPicoFmsHit.h")))  StPicoFmsHit;
class __attribute__((annotate("$clingAutoload$StPicoETofPidTraits.h")))  StPicoETofPidTraits;
class __attribute__((annotate("$clingAutoload$StPicoEpdHit.h")))  StPicoEpdHit;
class __attribute__((annotate("$clingAutoload$StPicoBTofHit.h")))  StPicoBTofHit;
class __attribute__((annotate("$clingAutoload$StPicoBbcHit.h")))  StPicoBbcHit;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "StPicoDst_Dict dictionary payload"

#ifndef _VANILLA_ROOT_
  #define _VANILLA_ROOT_ 1
#endif
#ifndef ROOT_CINT
  #define ROOT_CINT 1
#endif
#ifndef __ROOT__
  #define __ROOT__ 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "StPicoETofHit.h"
#include "StPicoMtdHit.h"
#include "StPicoBEmcSmdEHit.h"
#include "StPicoArrays.h"
#include "StPicoTrack.h"
#include "StPicoPhysicalHelix.h"
#include "StPicoBTofPidTraits.h"
#include "StPicoMcVertex.h"
#include "StPicoBEmcSmdPHit.h"
#include "StPicoBEmcPidTraits.h"
#include "StPicoHelix.h"
#include "StPicoEmcTrigger.h"
#include "StPicoMtdTrigger.h"
#include "StPicoBTowHit.h"
#include "StPicoCommon.h"
#include "StPicoTrackCovMatrix.h"
#include "StPicoDstReader.h"
#include "PhysicalConstants.h"
#include "StPicoEvent.h"
#include "StPicoMtdPidTraits.h"
#include "StPicoMcTrack.h"
#include "StPicoFmsHit.h"
#include "StPicoETofPidTraits.h"
#include "StPicoEpdHit.h"
#include "SystemOfUnits.h"
#include "StPicoBTofHit.h"
#include "StPicoBbcHit.h"
#include "StPicoDst.h"
#include "StPicoMessMgr.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"StPicoBEmcPidTraits", payloadCode, "@",
"StPicoBEmcSmdEHit", payloadCode, "@",
"StPicoBEmcSmdPHit", payloadCode, "@",
"StPicoBTofHit", payloadCode, "@",
"StPicoBTofPidTraits", payloadCode, "@",
"StPicoBTowHit", payloadCode, "@",
"StPicoBbcHit", payloadCode, "@",
"StPicoDst", payloadCode, "@",
"StPicoDstReader", payloadCode, "@",
"StPicoETofHit", payloadCode, "@",
"StPicoETofPidTraits", payloadCode, "@",
"StPicoEmcTrigger", payloadCode, "@",
"StPicoEpdHit", payloadCode, "@",
"StPicoEvent", payloadCode, "@",
"StPicoFmsHit", payloadCode, "@",
"StPicoHelix", payloadCode, "@",
"StPicoMcTrack", payloadCode, "@",
"StPicoMcVertex", payloadCode, "@",
"StPicoMtdHit", payloadCode, "@",
"StPicoMtdPidTraits", payloadCode, "@",
"StPicoMtdTrigger", payloadCode, "@",
"StPicoPhysicalHelix", payloadCode, "@",
"StPicoTrack", payloadCode, "@",
"StPicoTrackCovMatrix", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("StPicoDst_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_StPicoDst_Dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_StPicoDst_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_StPicoDst_Dict() {
  TriggerDictionaryInitialization_StPicoDst_Dict_Impl();
}
