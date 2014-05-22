/* Copyright (c) 1997-2014
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

#include "polymake/client.h"
#include "polymake/Graph.h"

namespace polymake { namespace common { namespace {
///==== Automatically generated contents follow.    Please do not delete this line. ====
   template <typename T0>
   FunctionInterface4perl( out_adjacent_nodes_f1, T0 ) {
      perl::Value arg0(stack[0]);
      WrapperReturn( arg0.get<T0>().out_adjacent_nodes() );
   };

   FunctionInstance4perl(out_adjacent_nodes_f1, perl::Canned< const pm::unary_transform_iterator<pm::graph::valid_node_iterator<pm::iterator_range<pm::graph::node_entry<pm::graph::Undirected, (pm::sparse2d::restriction_kind)0> const*>, pm::BuildUnary<pm::graph::valid_node_selector> >, pm::BuildUnaryIt<pm::operations::index2element> > >);
   FunctionInstance4perl(out_adjacent_nodes_f1, perl::Canned< const pm::unary_transform_iterator<pm::graph::valid_node_iterator<pm::iterator_range<pm::graph::node_entry<pm::graph::Directed, (pm::sparse2d::restriction_kind)0> const*>, pm::BuildUnary<pm::graph::valid_node_selector> >, pm::BuildUnaryIt<pm::operations::index2element> > >);
   FunctionInstance4perl(out_adjacent_nodes_f1, perl::Canned< const pm::unary_transform_iterator<pm::graph::valid_node_iterator<pm::iterator_range<pm::graph::node_entry<pm::graph::DirectedMulti, (pm::sparse2d::restriction_kind)0> const*>, pm::BuildUnary<pm::graph::valid_node_selector> >, pm::BuildUnaryIt<pm::operations::index2element> > >);
///==== Automatically generated contents end here.  Please do not delete this line. ====
} } }