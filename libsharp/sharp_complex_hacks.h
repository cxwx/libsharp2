/*
 *  This file is part of libsharp.
 *
 *  libsharp is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  libsharp is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with libsharp; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/*
 *  libsharp is being developed at the Max-Planck-Institut fuer Astrophysik
 *  and financially supported by the Deutsches Zentrum fuer Luft- und Raumfahrt
 *  (DLR).
 */

/*  \file sharp_complex_hacks.h
 *  support for converting vector types and complex numbers
 *
 *  Copyright (C) 2012-2018 Max-Planck-Society
 *  Author: Martin Reinecke
 */

#ifndef SHARP_COMPLEX_HACKS_H
#define SHARP_COMPLEX_HACKS_H

#include <math.h>
#include "sharp_vecsupport.h"

#define UNSAFE_CODE

#if (VLEN==1)

static inline void vhsum_cmplx_special (Tv a, Tv b, Tv c, Tv d,
  _Complex double * restrict cc)
  { cc[0] += a+_Complex_I*b; cc[1] += c+_Complex_I*d; }

#endif

#if (VLEN==2)

static inline void vhsum_cmplx2 (Tv a, Tv b, Tv c,
  Tv d, _Complex double * restrict c1, _Complex double * restrict c2)
  {
#ifdef UNSAFE_CODE
#if defined(__SSE3__)
  *((__m128d *)c1) += _mm_hadd_pd(a,b);
  *((__m128d *)c2) += _mm_hadd_pd(c,d);
#else
  *((__m128d *)c1) += _mm_shuffle_pd(a,b,_MM_SHUFFLE2(0,1)) +
                      _mm_shuffle_pd(a,b,_MM_SHUFFLE2(1,0));
  *((__m128d *)c2) += _mm_shuffle_pd(c,d,_MM_SHUFFLE2(0,1)) +
                      _mm_shuffle_pd(c,d,_MM_SHUFFLE2(1,0));
#endif
#else
  union {Tv v; _Complex double c; } u1, u2;
#if defined(__SSE3__)
  u1.v = _mm_hadd_pd(a,b); u2.v=_mm_hadd_pd(c,d);
#else
  u1.v = _mm_shuffle_pd(a,b,_MM_SHUFFLE2(0,1)) +
         _mm_shuffle_pd(a,b,_MM_SHUFFLE2(1,0));
  u2.v = _mm_shuffle_pd(c,d,_MM_SHUFFLE2(0,1)) +
         _mm_shuffle_pd(c,d,_MM_SHUFFLE2(1,0));
#endif
  *c1+=u1.c; *c2+=u2.c;
#endif
  }

static inline void vhsum_cmplx_special (Tv a, Tv b, Tv c, Tv d,
  _Complex double * restrict cc)
  { vhsum_cmplx2(a,b,c,d,cc,cc+1); }

#endif

#if (VLEN==4)

static inline void vhsum_cmplx_special (Tv a, Tv b, Tv c, Tv d,
  _Complex double * restrict cc)
  {
  Tv tmp1=_mm256_hadd_pd(a,b), tmp2=_mm256_hadd_pd(c,d);
  Tv tmp3=_mm256_permute2f128_pd(tmp1,tmp2,49),
     tmp4=_mm256_permute2f128_pd(tmp1,tmp2,32);
  tmp1=tmp3+tmp4;
#ifdef UNSAFE_CODE
  _mm256_storeu_pd((double *)cc,
    _mm256_add_pd(_mm256_loadu_pd((double *)cc),tmp1));
#else
  union {Tv v; _Complex double c[2]; } u;
  u.v=tmp1;
  cc[0]+=u.c[0]; cc[1]+=u.c[1];
#endif
  }

#endif

#if (VLEN==8)

static inline void vhsum_cmplx_special (Tv a, Tv b, Tv c, Tv d,
  _Complex double * restrict cc)
  { vhsum_cmplx2(a,b,c,d,cc,cc+1); }

#endif

#endif
