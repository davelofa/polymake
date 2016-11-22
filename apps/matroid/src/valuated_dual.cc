/* Copyright (c) 1997-2015
   Ewgenij Gawrilow, Michael Joswig (Technische Universitaet Berlin, Germany)
   http://www.polymake.org

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version: http://www.gnu.org/licenses/gpl.txt.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
--------------------------------------------------------------------------------
*/

#include "polymake/client.h"
#include "polymake/Rational.h"
#include "polymake/Vector.h"
#include "polymake/Matrix.h"
#include "polymake/Array.h"
#include "polymake/Set.h"
#include "polymake/TropicalNumber.h"



namespace polymake { namespace matroid {
  
  //FIXME: Write dualizing method, keeping as much data as possible
  // and using matroid's dual(..)?
  
  template
  <typename Addition, typename Scalar>
  perl::Object dual(perl::Object vm) {
    //Extract values
    int n = vm.give("N_ELEMENTS");
    Array<Set<int> > bases = vm.give("BASES");
    Vector<TropicalNumber<Addition,Scalar> > valuation = vm.give("VALUATION_ON_BASES");
    
    //Convert bases
    Array<Set<int> > dual_bases(bases.size());
    for(int b = 0; b < bases.size(); b++) {
	dual_bases[b] = sequence(0,n) - bases[b];
    }
    
    perl::ObjectType t = vm.type();
    
    perl::Object dvm(t);
      dvm.take("N_ELEMENTS") << n;
      dvm.take("BASES") << dual_bases;
      dvm.take("VALUATION_ON_BASES") << valuation;
      
    return dvm;
    
  }

  UserFunctionTemplate4perl(
	 "# @category Producing a matroid from matroids"
    "# Computes the dual of a valuated matroid."
    "# @param ValuatedMatroid<Addition,Scalar> M A valuated matroid"
    "# @return ValuatedMatroid<Addition,Scalar> The dual valuated matroid.",
    "dual<Addition,Scalar>(ValuatedMatroid<Addition,Scalar>)");
  
}}