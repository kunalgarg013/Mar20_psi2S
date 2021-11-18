/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            *
 *****************************************************************************/

#ifndef DoubleEXPO
#define DoubleEXPO

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

class DoubleExpo : public RooAbsPdf {
public:
  DoubleExpo(const char *name, const char *title,RooAbsReal& _x,RooAbsReal& _beta1,RooAbsReal& _alpha2,RooAbsReal& _beta2) ;
  DoubleExpo(const DoubleExpo& other, const char* name) ;
  virtual TObject* clone(const char* newname) const { return new DoubleExpo(*this,newname); }
  virtual ~DoubleExpo() {};

protected:

  RooRealProxy x ;
  RooRealProxy beta1 ;
  RooRealProxy alpha2 ;
  RooRealProxy beta2 ;


  Double_t evaluate() const ;

private:

  ClassDef(DoubleExpo,2) // Your description goes here...
};

#endif