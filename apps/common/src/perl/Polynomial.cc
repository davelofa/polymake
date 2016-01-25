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

///==== this line controls the automatic file splitting: max.instances=40

#include "polymake/IncidenceMatrix.h"
#include "polymake/Matrix.h"
#include "polymake/Polynomial.h"
#include "polymake/PuiseuxFraction.h"
#include "polymake/Rational.h"
#include "polymake/Ring.h"
#include "polymake/Set.h"
#include "polymake/SparseMatrix.h"
#include "polymake/TropicalNumber.h"
#include "polymake/Vector.h"
#include "polymake/client.h"

namespace polymake { namespace common { namespace {
///==== Automatically generated contents follow.    Please do not delete this line. ====
   template <typename T0>
   FunctionInterface4perl( new, T0 ) {
      WrapperReturnNew(T0, () );
   };

   template <typename T0, typename T1>
   FunctionInterface4perl( new_X, T0,T1 ) {
      perl::Value arg0(stack[1]);
      WrapperReturnNew(T0, (arg0.get<T1>()) );
   };

   template <typename T0, typename T1, typename T2, typename T3>
   FunctionInterface4perl( new_X_X_X, T0,T1,T2,T3 ) {
      perl::Value arg0(stack[1]), arg1(stack[2]), arg2(stack[3]);
      WrapperReturnNew(T0, (arg0.get<T1>(), arg1.get<T2>(), arg2.get<T3>()) );
   };

   template <typename T0, typename T1, typename T2>
   FunctionInterface4perl( new_X_X, T0,T1,T2 ) {
      perl::Value arg0(stack[1]), arg1(stack[2]);
      WrapperReturnNew(T0, (arg0.get<T1>(), arg1.get<T2>()) );
   };

   FunctionInstance4perl(new_X_X, Polynomial< Rational, int >, int, perl::Canned< const Ring< Rational, int > >);
   FunctionInstance4perl(new_X_X_X, Polynomial< TropicalNumber< Max, Rational >, int >, perl::Canned< const pm::MatrixMinor<pm::SparseMatrix<int, pm::NonSymmetric>&, pm::all_selector const&, pm::Complement<pm::SingleElementSet<int>, int, pm::operations::cmp> const&> >, perl::Canned< const Vector< TropicalNumber< Max, Rational > > >, perl::Canned< const Ring< TropicalNumber< Max, Rational >, int > >);
   OperatorInstance4perl(Binary__eq, perl::Canned< const Polynomial< Rational, int > >, int);
   OperatorInstance4perl(Binary_add, perl::Canned< const Polynomial< TropicalNumber< Min, Rational >, int > >, perl::Canned< const Monomial< TropicalNumber< Min, Rational >, int > >);
   FunctionInstance4perl(new_X, Polynomial< TropicalNumber< Min, Rational >, int >, perl::Canned< const Monomial< TropicalNumber< Min, Rational >, int > >);
   OperatorInstance4perl(Binary_add, perl::Canned< const Polynomial< TropicalNumber< Max, Rational >, int > >, perl::Canned< const Monomial< TropicalNumber< Max, Rational >, int > >);
   FunctionInstance4perl(new_X, Polynomial< TropicalNumber< Max, Rational >, int >, perl::Canned< const Monomial< TropicalNumber< Max, Rational >, int > >);
   OperatorInstance4perl(Binary_add, perl::Canned< const Polynomial< PuiseuxFraction< Min, Rational, Rational >, int > >, perl::Canned< const Polynomial< PuiseuxFraction< Min, Rational, Rational >, int > >);
   FunctionInstance4perl(new, Polynomial< PuiseuxFraction< Min, Rational, Rational >, int >);
   Class4perl("Polymake::common::Polynomial_A_PuiseuxFraction_A_Min_I_Rational_I_Rational_Z_I_Int_Z", Polynomial< PuiseuxFraction< Min, Rational, Rational >, int >);
   OperatorInstance4perl(Binary__eq, perl::Canned< const Polynomial< PuiseuxFraction< Min, Rational, Rational >, int > >, perl::Canned< const Polynomial< PuiseuxFraction< Min, Rational, Rational >, int > >);
///==== Automatically generated contents end here.  Please do not delete this line. ====
} } }
