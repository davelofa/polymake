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

#include "polymake/IncidenceMatrix.h"
#include "polymake/Set.h"

namespace polymake { namespace polytope { namespace {
///==== Automatically generated contents follow.    Please do not delete this line. ====
   template <typename T0>
   FunctionInterface4perl( lower_hasse_diagram_X_x, T0 ) {
      perl::Value arg0(stack[0]), arg1(stack[1]);
      WrapperReturn( (lower_hasse_diagram(arg0.get<T0>(), arg1)) );
   };

   template <typename T0>
   FunctionInterface4perl( upper_hasse_diagram_X_x_x, T0 ) {
      perl::Value arg0(stack[0]), arg1(stack[1]), arg2(stack[2]);
      WrapperReturn( (upper_hasse_diagram(arg0.get<T0>(), arg1, arg2)) );
   };

   template <typename T0, typename T1>
   FunctionInterface4perl( bounded_hasse_diagram_X_X_x, T0,T1 ) {
      perl::Value arg0(stack[0]), arg1(stack[1]), arg2(stack[2]);
      WrapperReturn( (bounded_hasse_diagram(arg0.get<T0>(), arg1.get<T1>(), arg2)) );
   };

   template <typename T0>
   FunctionInterface4perl( hasse_diagram_X_x, T0 ) {
      perl::Value arg0(stack[0]), arg1(stack[1]);
      WrapperReturn( (hasse_diagram(arg0.get<T0>(), arg1)) );
   };

   FunctionInstance4perl(hasse_diagram_X_x, perl::Canned< const IncidenceMatrix< NonSymmetric > >);
   FunctionInstance4perl(bounded_hasse_diagram_X_X_x, perl::Canned< const IncidenceMatrix< NonSymmetric > >, perl::Canned< const Set< int > >);
   FunctionInstance4perl(upper_hasse_diagram_X_x_x, perl::Canned< const IncidenceMatrix< NonSymmetric > >);
   FunctionInstance4perl(lower_hasse_diagram_X_x, perl::Canned< const IncidenceMatrix< NonSymmetric > >);
///==== Automatically generated contents end here.  Please do not delete this line. ====
} } }
