/* -*- mode: C++; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
// vim:sts=8:sw=8:ts=8:noet:sr:cino=>s,f0,{0,g0,(0,\:0,t0,+0,=s

/* fflas/fflas_finit.inl
 * Copyright (C) 2014 FFLAS FFPACK group
 *
 * Written by Pascal Giorgi <pascal.giorgi@lirmm.fr>
 *
 *
 * ========LICENCE========
 * This file is part of the library FFLAS-FFPACK.
 *
 * FFLAS-FFPACK is free software: you can redistribute it and/or modify
 * it under the terms of the  GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * ========LICENCE========
 *.
 */

#ifndef __FFLASFFPACK_fflas_init_mp_INL
#define __FFLASFFPACK_fflas_init_mp_INL


// activate only if FFLAS-FFPACK haves multiprecision integer
#ifdef __FFLASFFPACK_HAVE_INTEGER
#include "fflas-ffpack/field/rns-integer.h"
#include "fflas-ffpack/field/rns-integer-mod.h"


namespace FFLAS {

	// specialization of the level1 finit function for the field RNSInteger<rns_double>
	template<>
	void finit(const FFPACK::RNSIntegerMod<FFPACK::rns_double> &F, const size_t n, FFPACK::rns_double::Element_ptr A, size_t inc)
	{
		//cout<<"finit: "<<n<<" with "<<inc<<endl;
		if (inc==1)
			F.reduce_modp(n,A._ptr,A._stride);
		else
			F.reduce_modp(n,1,A._ptr,inc,A._stride);
		//throw FFPACK::Failure(__func__,__FILE__,__LINE__,"finit RNSIntegerMod  -> (inc!=1) NOT SUPPORTED");
	}
	// specialization of the level2 finit function for the field RNSInteger<rns_double>
	template<>
	void finit(const FFPACK::RNSIntegerMod<FFPACK::rns_double> &F, const size_t m, const size_t n, FFPACK::rns_double::Element_ptr A, size_t lda)
	{
		//cout<<"finit: "<<m<<" x "<<n<<" "<<lda<<endl;
		if (lda == n)
			F.reduce_modp(m*n,A._ptr,A._stride);
		else
			F.reduce_modp(m,n,A._ptr,lda,A._stride); // seems to be buggy
	}



} // end of namespace FFLAS

#endif

#endif
