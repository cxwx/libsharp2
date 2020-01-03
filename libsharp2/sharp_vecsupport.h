/*
 *  This file is part of libsharp2.
 *
 *  libsharp2 is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  libsharp2 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with libsharp2; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/* libsharp2 is being developed at the Max-Planck-Institut fuer Astrophysik */

/*  \file sharp_vecsupport.h
 *  Convenience functions for vector arithmetics
 *
 *  Copyright (C) 2012-2019 Max-Planck-Society
 *  Author: Martin Reinecke
 */

#ifndef SHARP2_VECSUPPORT_H
#define SHARP2_VECSUPPORT_H

#include <cmath>
#include <complex>
using std::complex;


#include <experimental/simd>
using std::experimental::native_simd;
using std::experimental::reduce;
using Tv=native_simd<double>;
using Tm=Tv::mask_type;
using Ts=Tv::value_type;
static constexpr size_t VLEN=Tv::size();

#define vload(a) (a)
#define vzero 0.
#define vone 1.

#define vaddeq_mask(mask,a,b) where(mask,a)+=b;
#define vsubeq_mask(mask,a,b) where(mask,a)-=b;
#define vmuleq_mask(mask,a,b) where(mask,a)*=b;
#define vneg(a) (-(a))
#define vabs(a) abs(a)
#define vsqrt(a) sqrt(a)
#define vlt(a,b) ((a)<(b))
#define vgt(a,b) ((a)>(b))
#define vge(a,b) ((a)>=(b))
#define vne(a,b) ((a)!=(b))
#define vand_mask(a,b) ((a)&&(b))
#define vor_mask(a,b) ((a)||(b))
static inline Tv vmin (Tv a, Tv b) { return min(a,b); }
static inline Tv vmax (Tv a, Tv b) { return max(a,b); }
#define vanyTrue(a) (any_of(a))
#define vallTrue(a) (all_of(a))

static inline void vhsum_cmplx_special (Tv a, Tv b, Tv c, Tv d,
  complex<double> * restrict cc)
  {
  cc[0] += complex<double>(reduce(a,std::plus<>()),reduce(b,std::plus<>()));
  cc[1] += complex<double>(reduce(c,std::plus<>()),reduce(d,std::plus<>()));
  }

#endif
