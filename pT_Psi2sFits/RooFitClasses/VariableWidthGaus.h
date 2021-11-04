/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            *
 *****************************************************************************/

#ifndef VARIABLEWIDTHGAUS
#define VARIABLEWIDTHGAUS

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

class VariableWidthGaus : public RooAbsPdf {
public:
  //VariableWidthGaus() {} ;
  VariableWidthGaus(const char *name, const char *title,
	      RooAbsReal& _x,
	      RooAbsReal& _x0,
	      RooAbsReal& _alpha,
	      RooAbsReal& _beta);
  VariableWidthGaus(const VariableWidthGaus& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new VariableWidthGaus(*this,newname); }

protected:

  RooRealProxy x ;
  RooRealProxy x0 ;
  RooRealProxy alpha ;
  RooRealProxy beta ;

  Double_t evaluate() const ;

private:

  ClassDef(VariableWidthGaus,2) // Your description goes here...
};

#endif
