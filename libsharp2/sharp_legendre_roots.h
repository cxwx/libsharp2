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

/*! \file sharp_legendre_roots.h
 *
 *  Copyright (C) 2006-2019 Max-Planck-Society
 *  \author Martin Reinecke
 */

#ifndef SHARP2_LEGENDRE_ROOTS_H
#define SHARP2_LEGENDRE_ROOTS_H

#ifdef __cplusplus
extern "C" {
#endif

/*! Computes roots and Gaussian quadrature weights for Legendre polynomial
    of degree \a n.
    \param n Order of Legendre polynomial
    \param x Array of length \a n for output (root position)
    \param w Array of length \a w for output (weight for Gaussian quadrature)
 */
void sharp_legendre_roots(int n, double *x, double *w);

#ifdef __cplusplus
}
#endif

#endif
