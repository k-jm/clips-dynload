#include "../clips.h"
#include <math.h>
void Cube(
	  Environment *env,
	  UDFContext *udfc,
	  UDFValue *out);
void InitUserFunctions(
		       Environment *env)
{
  AddUDF(env,"cube","ld",1,1,"ld",Cube,"Cube",NULL);
}

void Cube(
	  Environment *env,
	  UDFContext *udfc,
	  UDFValue *out)
{
  UDFValue theArg;
  // Retrieve the first argument.
  if (! UDFFirstArgument(udfc,NUMBER_BITS,&theArg))
    { return; }
  // Cube the argument.
  if (theArg.header->type == INTEGER_TYPE)
    {
      long long integerValue = theArg.integerValue->contents;
      integerValue = integerValue * integerValue * integerValue;
      out->integerValue = CreateInteger(env,integerValue);
    }
  else /* the type must be FLOAT */
    {
      double floatValue = theArg.floatValue->contents;
      floatValue = floatValue * floatValue * floatValue;
      out->floatValue = CreateFloat(env,floatValue);
    }
}
