
Purpose of branch "clipsdynamiclib" is to create a shared library 'libclips.so' 
and an associated 'clips' executable when BUILD_DYNAMIC = 1 in 'makefile'.
   Launch clips with 'LD_LIBRARY_PATH=. ./clips' or else move libclips.so to 
   /usr/local/lib.

Purpose of branch "dynload" is to define a new clips function "dynload" which
load a dynamic library then execute a c entry point ("InitUserFunctions") in this 
library to register new functions. For example :

CLIPS>
(dynload "addons/euler.so")
;; returns TRUE
(dynload "addons/cube.so")
;; returns TRUE
(cube (e))
;; returns 20.0855369231877



=========================================================================
CLIPS License Information

Permission is hereby granted, free of charge, to any person obtaining a 
copy of this software (the "Software"), to deal in the Software without 
restriction, including without limitation the rights to use, copy, modify, 
merge, publish, distribute, and/or sell copies of the Software, and to 
permit persons to whom the Software is furnished to do so.                             

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS. 
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL 
INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM 
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE 
OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR 
PERFORMANCE OF THIS SOFTWARE.
