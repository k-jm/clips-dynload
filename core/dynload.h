   /*******************************************************/
   /*      "C" Language Integrated Production System      */
   /*                                                     */
   /*             CLIPS Version 6.40  10/19/17            */
   /*                                                     */
   /*         DYNAMIC LIBRARY  FUNCTIONS HEADER FILE      */
   /*******************************************************/

/*************************************************************/
/* Purpose:   Dynamic loading of libraries                   */
/*                                                           */
/* Principal Programmer(s):                               */
/*      Jean-Marie Kubek                                 */
/*      Gary D. Riley                                        */
/*                                                           */
/* Contributing Programmer(s):                                      */
/*                                                           */
/* Revision History:                                         */
/*      6.40: Initial implementation of dynload function     */
/*                                                           */
/*************************************************************/
#ifndef _H_dynload

#pragma once

#define _H_dynload

void                           DLFunctionDefinitions(Environment *);

#if DL_FUNCTIONS
void DynLoadCommand  (
  Environment *theEnv,
  UDFContext *udfc,
  UDFValue *out);
#endif

#endif /* _H_iofun */
