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

#include "polymake/Graph.h"
#include "polymake/IncidenceMatrix.h"
#include "polymake/Matrix.h"
#include "polymake/Rational.h"
#include "polymake/SparseMatrix.h"

namespace polymake { namespace graph { namespace {
///==== Automatically generated contents follow.    Please do not delete this line. ====
   template <typename T0, typename T1>
   FunctionInterface4perl( edge_lengths_X_X, T0,T1 ) {
      perl::Value arg0(stack[0]), arg1(stack[1]);
      WrapperReturn( (edge_lengths(arg0.get<T0>(), arg1.get<T1>())) );
   };

   FunctionInstance4perl(edge_lengths_X_X, perl::Canned< const Graph< Undirected > >, perl::Canned< const Matrix< Rational > >);
   FunctionInstance4perl(edge_lengths_X_X, perl::Canned< const Graph< Undirected > >, perl::Canned< const SparseMatrix< Rational, NonSymmetric > >);
///==== Automatically generated contents end here.  Please do not delete this line. ====
} } }
