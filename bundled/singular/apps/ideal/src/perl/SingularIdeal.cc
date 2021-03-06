/* Copyright (c) 1997-2018
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

#include "polymake/Array.h"
#include "polymake/IncidenceMatrix.h"
#include "polymake/Matrix.h"
#include "polymake/Rational.h"
#include "polymake/SparseMatrix.h"
#include "polymake/Vector.h"
#include "polymake/Polynomial.h"
#include "polymake/client.h"
#include "polymake/ideal/singularIdeal.h"

namespace polymake { namespace ideal { namespace {
///==== Automatically generated contents follow.    Please do not delete this line. ====
   template <typename T0, typename T1, typename T2>
   FunctionInterface4perl( new_X_X, T0,T1,T2 ) {
      perl::Value arg0(stack[1]), arg1(stack[2]);
      WrapperReturnNew(T0, (arg0.get<T1>(), arg1.get<T2>()) );
   };

   template <typename T0, typename T1>
   FunctionInterface4perl( new_X_std__string, T0,T1 ) {
      perl::Value arg0(stack[1]), arg1(stack[2]);
      WrapperReturnNew(T0, (arg0.get<T1>(), arg1.get<std::string>()) );
   };

   Class4perl("Polymake::ideal::SingularIdeal", SingularIdeal);
   FunctionInstance4perl(new_X_std__string, SingularIdeal, perl::Canned< const Array< Polynomial< Rational, int > > >);
   FunctionInstance4perl(new_X_X, SingularIdeal, perl::Canned< const Array< Polynomial< Rational, int > > >, perl::Canned< const Vector< int > >);
   FunctionInstance4perl(new_X_X, SingularIdeal, perl::Canned< const Array< Polynomial< Rational, int > > >, perl::Canned< const SparseMatrix< int, NonSymmetric > >);
   FunctionInstance4perl(new_X_X, SingularIdeal, perl::Canned< const Array< Polynomial< Rational, int > > >, perl::Canned< const Matrix< int > >);
///==== Automatically generated contents end here.  Please do not delete this line. ====
} } }
