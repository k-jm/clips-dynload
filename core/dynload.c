  /*******************************************************/
   /*      "C" Language Integrated Production System      */
   /*                                                     */
   /*            CLIPS Version 6.40  10/19/17             */
   /*                                                     */
   /*           DYNAMIC LIBRARY FUNCTIONS MODULE          */
   /*******************************************************/


/*************************************************************/
/* Purpose: Contains the code for several I/O functions      */
/*   including printout, read, open, close, remove, rename,  */
/*   format, and readline.                                   */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Jean-Marie Kubek                                     */
/*      Gary D. Riley                                             */
/*                                                           */
/* Contributing Programmer(s):                               */
/*                                                           */
/* Revision History:                                        */
/*      6.40: Initial implementation of dynload function     */
/*                                                           */
/*************************************************************/                             
#include "setup.h"

#if DL_FUNCTIONS
#include <dlfcn.h>
#include <string.h>
#endif
#include "clips.h"
#if DL_FUNCTIONS
void DynLoadCommand (
  Environment *env,
  UDFContext *udfc,
  UDFValue *out);

static bool MaybeLoadAndInitLib(Environment *theEnv,const char * libname);
static bool LoadAndInitLib(Environment *theEnv,const char * libname);
static void * LoadLib(const char * libname, char** error);
static bool InitLib(Environment *theEnv,void *handle,char** error);
static char * strdup(const char * theString);
static void myfree(Environment *theEnv,char * p);
static bool IsAlreadyLoaded(const char * libname);
static void UnloadLib(void *handle);
static void PrintError(Environment *theEnv, char * error);
#endif

void DLFunctionDefinitions(
  Environment *theEnv)
{
#if DL_FUNCTIONS
  AddUDF(theEnv,"dynload","b",1,1,";s",DynLoadCommand,"DynLoadCommand",NULL);
#endif
}
#if DL_FUNCTIONS

void DynLoadCommand (
  Environment *theEnv,
  UDFContext *udfc,
  UDFValue *out)
{
  UDFValue theArg;
  bool result=1;
  if (! UDFFirstArgument(udfc,STRING_BIT,&theArg))
    { return; }
  const char *libname = theArg.lexemeValue->contents;
  result = MaybeLoadAndInitLib(theEnv,libname);
  out->lexemeValue = CreateBoolean(theEnv,result);
}
static bool MaybeLoadAndInitLib(Environment *theEnv,const char * libname){
  bool result = 1;
  if (! IsAlreadyLoaded(libname)){
    result = LoadAndInitLib(theEnv,libname);
  }
  return result;
}

static bool LoadAndInitLib(Environment *theEnv,const char * libname){
  char * error = NULL;
  void *handle = LoadLib(libname,&error);
  
  bool result = (NULL != handle);
  
  if (! result){
    PrintError(theEnv,error);
  } else {
    result = InitLib(theEnv,handle,&error);
    if (! result){
      PrintError(theEnv,error);
      UnloadLib(handle);
    } else {
    }
  }
  return result;
}

static bool IsAlreadyLoaded(const char * libname){
  void * result = dlopen(libname,RTLD_NOW|RTLD_NOLOAD);
  return NULL != result;
}


static void * LoadLib(const char * libname, char** error){
  dlerror();
  void * result = dlopen(libname,RTLD_NOW);
  
  if (NULL == result){
    char * err = dlerror();
    if (NULL != err){
      *error = strdup(err);
    }
  }
  
  return result;
}

static void UnloadLib(void *handle){
  if (handle != NULL){
    dlclose(handle);
  }
}



static bool InitLib(Environment *theEnv,void *handle, char**error){
  void (*InitUserFunctions) (Environment *);
  
  dlerror();
  *(void **) (&InitUserFunctions) = dlsym(handle, "InitUserFunctions");
  char * err = dlerror();
  bool result  = (NULL == err);
  if (!result )  {
    *error=strdup(err);
  } else {
    if (NULL != InitUserFunctions){
      (*InitUserFunctions)(theEnv) ;
    } else {
      result = 0;
      *error = strdup("symbol 'InitUserFunctions' is not a function in dyn. lib.");
    }
  }
  return result;
}
static void myfree(Environment *theEnv,char * p){
  if (p!= NULL){
    free(p);
    p=NULL;
  } else {
    WriteString(theEnv,STDERR,"Tried to unallocate a null pointer");
  }
}
static char * strdup(const char * theString){
  char  * result = NULL;
  if (NULL != theString){
    result = (char*) malloc(strlen(theString)+1);
    strcpy(result,theString);
    return  result;
  } else {
    return NULL;
  }
}

static void PrintError(Environment *theEnv, char * error){
  WriteString(theEnv,STDERR,"Some Error occured :");
  if (NULL != error){
    WriteString(theEnv,STDERR,error);
    WriteString(theEnv,STDERR,"\n");
    myfree(theEnv,error);
  } else {
    WriteString(theEnv,STDERR,"Unknown cause\n");
  }
  
}

#endif
