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
#include "polymake/Integer.h"
#include "polymake/Matrix.h"
#include "polymake/QuadraticExtension.h"
#include "polymake/Rational.h"
#include "polymake/Set.h"
#include "polymake/SparseMatrix.h"
#include "polymake/Vector.h"
#include "polymake/client.h"

namespace polymake { namespace common { namespace {
///==== Automatically generated contents follow.    Please do not delete this line. ====
   template <typename T0>
   FunctionInterface4perl( transpose_X32, T0 ) {
      perl::Value arg0(stack[0]);
      WrapperReturn( (T(arg0.get<T0>())), arg0 );
   };

   FunctionInstance4perl(transpose_X32, perl::Canned< const Matrix< Rational > >);
   FunctionInstance4perl(transpose_X32, perl::Canned< const Matrix< double > >);
   FunctionInstance4perl(transpose_X32, perl::Canned< const IncidenceMatrix< NonSymmetric > >);
   FunctionInstance4perl(transpose_X32, perl::Canned< const Matrix< Integer > >);
   FunctionInstance4perl(transpose_X32, perl::Canned< const SparseMatrix< Rational, NonSymmetric > >);
   FunctionInstance4perl(transpose_X32, perl::Canned< const SparseMatrix< QuadraticExtension< Rational >, NonSymmetric > >);
///==== Automatically generated contents end here.  Please do not delete this line. ====
} } }
