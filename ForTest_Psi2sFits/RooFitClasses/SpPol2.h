/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            *
 *****************************************************************************/

#ifndef SPPOL2
#define SPPOL2

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

class SpPol2 : public RooAbsPdf {
public:
  SpPol2() {} ;
  SpPol2(const char *name, const char *title,
	      RooAbsReal& _x,
        RooAbsReal& _c1,
	      RooAbsReal& _c2);
  SpPol2(const SpPol2& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new SpPol2(*this,newname); }
  inline virtual ~SpPol2() { }

protected:

  RooRealProxy x ;
  RooRealProxy c1 ;
  RooRealProxy c2 ;

  Double_t evaluate() const ;

private:

  ClassDef(SpPol2,2) // Your description goes here...
};

#endif
