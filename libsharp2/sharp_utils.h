/*
 *  This file is part of libc_utils.
 *
 *  libc_utils is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  libc_utils is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with libc_utils; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/* libc_utils is being developed at the Max-Planck-Institut fuer Astrophysik */

/*! \file c_utils.h
 *  Convenience functions
 *
 *  Copyright (C) 2008-2019 Max-Planck-Society
 *  \author Martin Reinecke
 *  \note This file should only be included from .c files, NOT from .h files.
 */

#ifndef SHARP_UTILS_H
#define SHARP_UTILS_H

#include <math.h>
#include <stdlib.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void sharp_fail_ (const char *file, int line, const char *func, const char *msg);
void *sharp_malloc_ (size_t sz);
void sharp_free_ (void *ptr);

#if defined (__GNUC__)
#define UTIL_FUNC_NAME__ __func__
#else
#define UTIL_FUNC_NAME__ "unknown"
#endif

/*! \def UTIL_ASSERT(cond,msg)
    If \a cond is false, print an error message containing function name,
    source file name and line number of the call, as well as \a msg;
    then exit the program with an error status. */
#define UTIL_ASSERT(cond,msg) \
  if(!(cond)) sharp_fail_(__FILE__,__LINE__,UTIL_FUNC_NAME__,msg)
/*! \def UTIL_WARN(cond,msg)
    If \a cond is false, print an warning containing function name,
    source file name and line number of the call, as well as \a msg. */
#define UTIL_FAIL(msg) \
  sharp_fail_(__FILE__,__LINE__,UTIL_FUNC_NAME__,msg)

/*! \def ALLOC(ptr,type,num)
    Allocate space for \a num objects of type \a type. Make sure that the
    allocation succeeded, else stop the program with an error. Return the
    resulting pointer in \a ptr. */
#define ALLOC(ptr,type,num) \
  do { (ptr)=(type *)sharp_malloc_((num)*sizeof(type)); } while (0)
/*! \def RALLOC(type,num)
    Allocate space for \a num objects of type \a type. Make sure that the
    allocation succeeded, else stop the program with an error. Cast the
    resulting pointer to \a (type*). */
#define RALLOC(type,num) \
  ((type *)sharp_malloc_((num)*sizeof(type)))
/*! \def DEALLOC(ptr)
    Deallocate \a ptr. It must have been allocated using \a ALLOC or
    \a RALLOC. */
#define DEALLOC(ptr) \
  do { sharp_free_(ptr); (ptr)=NULL; } while(0)
#define RESIZE(ptr,type,num) \
  do { sharp_free_(ptr); ALLOC(ptr,type,num); } while(0)
/*! \def SET_ARRAY(ptr,i1,i2,val)
    Set the entries \a ptr[i1] ... \a ptr[i2-1] to \a val. */
#define SET_ARRAY(ptr,i1,i2,val) \
  do { \
    ptrdiff_t cnt_; \
    for (cnt_=(i1);cnt_<(i2);++cnt_) (ptr)[cnt_]=(val); \
    } while(0)

#define ALLOC2D(ptr,type,num1,num2) \
  do { \
    size_t cnt_, num1_=(num1), num2_=(num2); \
    ALLOC((ptr),type *,num1_); \
    ALLOC((ptr)[0],type,num1_*num2_); \
    for (cnt_=1; cnt_<num1_; ++cnt_) \
      (ptr)[cnt_]=(ptr)[cnt_-1]+num2_; \
    } while(0)
#define DEALLOC2D(ptr) \
  do { if(ptr) DEALLOC((ptr)[0]); DEALLOC(ptr); } while(0)

#define FAPPROX(a,b,eps) \
  (fabs((a)-(b))<((eps)*fabs(b)))
#define IMAX(a,b) \
  (((a)>(b)) ? (a) : (b))
#define IMIN(a,b) \
  (((a)<(b)) ? (a) : (b))

#define SWAP(a,b,type) \
  do { type tmp_=(a); (a)=(b); (b)=tmp_; } while(0)

/*! Returns an approximation of the current wall time (in seconds).
    The first available of the following timers will be used:
    <ul>
    <li> \a omp_get_wtime(), if OpenMP is available
    <li> \a MPI_Wtime(), if MPI is available
    <li> \a gettimeofday() otherwise
    </ul>
    \note Only useful for measuring time differences.
    \note This function has an execution time between 10 and 100 nanoseconds. */
double sharp_wallTime(void);

#ifdef __cplusplus
}
#endif

#ifdef __GNUC__
#define NOINLINE __attribute__((noinline))
#else
#define NOINLINE
#endif

#endif
