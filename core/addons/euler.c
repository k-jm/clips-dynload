#include "../clips.h"
#include <math.h>
void EulersNumber(
Environment *env,
UDFContext *udfc,
UDFValue *out);
void InitUserFunctions(Environment *env)
{
  AddUDF(env,"e","d",0,0,NULL,EulersNumber,"EulersNumber",NULL);
}
void EulersNumber(Environment *env,
		  UDFContext *udfc,
		  UDFValue *out)
{
  out->floatValue = CreateFloat(env,exp(1.0));
}
