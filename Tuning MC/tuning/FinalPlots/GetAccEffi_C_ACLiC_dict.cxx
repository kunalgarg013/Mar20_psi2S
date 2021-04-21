// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIkunaldIanalysisdIdiMuondIMar20_psi2SdITuningsPMCdItuningdIFinalPlotsdIGetAccEffi_C_ACLiC_dict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
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

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/Users/kunal/analysis/diMuon/Mar20_psi2S/Tuning MC/tuning/FinalPlots/./GetAccEffi.C"

// Header files passed via #pragma extra_include

namespace {
  void TriggerDictionaryInitialization_GetAccEffi_C_ACLiC_dict_Impl() {
    static const char* headers[] = {
"./GetAccEffi.C",
0
    };
    static const char* includePaths[] = {
"/Users/kunal/alice/sw/osx_x86-64/ROOT/v6-20-08-alice1-1/include",
"/Users/kunal/alice/sw/osx_x86-64/AliPhysics/master-1/include",
"/Users/kunal/alice/sw/osx_x86-64/KFParticle/v1.1-3-1/include",
"/Users/kunal/alice/sw/osx_x86-64/treelite/8498081-1/runtime/native/include",
"/Users/kunal/alice/sw/osx_x86-64/treelite/8498081-1/include",
"/Users/kunal/alice/sw/osx_x86-64/RooUnfold/V02-00-01-alice5-1/include",
"/Users/kunal/alice/sw/osx_x86-64/AliRoot/v5-09-56-1/include/Pythia8",
"/Users/kunal/alice/sw/osx_x86-64/AliRoot/v5-09-56-1/include",
"/Users/kunal/alice/sw/osx_x86-64/JAliEn-ROOT/0.6.4-1/include",
"/Users/kunal/alice/sw/osx_x86-64/Vc/1.4.1-1/include",
"/Users/kunal/alice/sw/osx_x86-64/fastjet/v3.3.3_1.042-alice1-1/include",
"/Users/kunal/alice/sw/osx_x86-64/boost/v1.74.0-1/include",
"/Users/kunal/alice/sw/osx_x86-64/ROOT/v6-20-08-alice1-1/etc/",
"/Users/kunal/alice/sw/osx_x86-64/ROOT/v6-20-08-alice1-1/etc//cling",
"/Users/kunal/alice/sw/osx_x86-64/ROOT/v6-20-08-alice1-1/include/",
"/Users/kunal/alice/sw/osx_x86-64/ROOT/v6-20-08-alice1-1/include",
"/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.1.sdk/usr/include",
"/opt/local/include",
"/Users/kunal/alice/sw/osx_x86-64/ROOT/v6-20-08-alice1-1/include/",
"/Users/kunal/analysis/diMuon/Mar20_psi2S/Tuning MC/tuning/FinalPlots/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "GetAccEffi_C_ACLiC_dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "GetAccEffi_C_ACLiC_dict dictionary payload"

#ifndef __ACLIC__
  #define __ACLIC__ 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "./GetAccEffi.C"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"GetAccEffi", payloadCode, "@",
"PrintEffi2", payloadCode, "@",
"inputFileName", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("GetAccEffi_C_ACLiC_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_GetAccEffi_C_ACLiC_dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_GetAccEffi_C_ACLiC_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_GetAccEffi_C_ACLiC_dict() {
  TriggerDictionaryInitialization_GetAccEffi_C_ACLiC_dict_Impl();
}
