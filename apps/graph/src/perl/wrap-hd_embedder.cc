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

#include "polymake/graph/Decoration.h"
#include "polymake/tropical/covectors.h"

namespace polymake { namespace graph { namespace {
///==== Automatically generated contents follow.    Please do not delete this line. ====
   template <typename T0, typename T1>
   FunctionInterface4perl( hd_embedder_T_x_x_o, T0,T1 ) {
      perl::Value arg0(stack[0]), arg1(stack[1]), arg2(stack[2]);
      WrapperReturn( (hd_embedder<T0,T1>(arg0, arg1, arg2)) );
   };

   FunctionInstance4perl(hd_embedder_T_x_x_o, graph::lattice::BasicDecoration, graph::lattice::Sequential);
   FunctionInstance4perl(hd_embedder_T_x_x_o, graph::lattice::BasicDecoration, graph::lattice::Nonsequential);
   FunctionCrossAppInstance4perl(hd_embedder_T_x_x_o, (1, "tropical"), CovectorDecoration, graph::lattice::Nonsequential);
///==== Automatically generated contents end here.  Please do not delete this line. ====
} } }
