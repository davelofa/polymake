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

#include "polymake/Rational.h"
#include "polymake/graph/Decoration.h"

namespace polymake { namespace topaz { namespace {
///==== Automatically generated contents follow.    Please do not delete this line. ====
   template <typename T0, typename T1, typename T2>
   FunctionInterface4perl( iterated_barycentric_subdivision_impl_T_x_x_o, T0,T1,T2 ) {
      perl::Value arg0(stack[0]), arg1(stack[1]), arg2(stack[2]);
      WrapperReturn( (iterated_barycentric_subdivision_impl<T0,T1,T2>(arg0, arg1, arg2)) );
   };

   template <typename T0, typename T1, typename T2>
   FunctionInterface4perl( barycentric_subdivision_impl_T_x_o, T0,T1,T2 ) {
      perl::Value arg0(stack[0]), arg1(stack[1]);
      WrapperReturn( (barycentric_subdivision_impl<T0,T1,T2>(arg0, arg1)) );
   };

   FunctionInstance4perl(barycentric_subdivision_impl_T_x_o, graph::lattice::BasicDecoration, graph::lattice::Sequential, Rational);
   FunctionInstance4perl(iterated_barycentric_subdivision_impl_T_x_x_o, graph::lattice::BasicDecoration, graph::lattice::Sequential, Rational);
   FunctionInstance4perl(barycentric_subdivision_impl_T_x_o, graph::lattice::BasicDecoration, graph::lattice::Nonsequential, Rational);
   FunctionInstance4perl(iterated_barycentric_subdivision_impl_T_x_x_o, graph::lattice::BasicDecoration, graph::lattice::Nonsequential, Rational);
///==== Automatically generated contents end here.  Please do not delete this line. ====
} } }
