/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            *
 *****************************************************************************/

#ifndef POL2
#define POL2

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

class Pol2 : public RooAbsPdf {
public:
  Pol2() {} ;
  Pol2(const char *name, const char *title,
	      RooAbsReal& _x,
        RooAbsReal& _c1,
	      RooAbsReal& _c2);
  Pol2(const Pol2& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new Pol2(*this,newname); }
  inline virtual ~Pol2() { }

protected:

  RooRealProxy x ;
  RooRealProxy c1 ;
  RooRealProxy c2 ;

  Double_t evaluate() const ;

private:

  ClassDef(Pol2,2) // Your description goes here...
};

#endif
