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

#include "polymake/Graph.h"
#include "polymake/IncidenceMatrix.h"
#include "polymake/Integer.h"
#include "polymake/PuiseuxFraction.h"
#include "polymake/QuadraticExtension.h"
#include "polymake/Rational.h"
#include "polymake/SparseMatrix.h"
#include "polymake/SparseVector.h"
#include "polymake/TropicalNumber.h"
#include "polymake/client.h"
#include "polymake/linalg.h"

namespace polymake { namespace common { namespace {
///==== Automatically generated contents follow.    Please do not delete this line. ====
   template <typename T0>
   FunctionInterface4perl( index_f1, T0 ) {
      perl::Value arg0(stack[0]);
      WrapperReturn( arg0.get<T0>().index() );
   };

   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::AVL::tree_iterator<pm::sparse2d::it_traits<pm::Rational, true, false> const, (pm::AVL::link_index)1>, std::pair<pm::BuildUnary<pm::sparse2d::cell_accessor>, pm::BuildUnaryIt<pm::sparse2d::cell_index_accessor> > > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::AVL::tree_iterator<pm::sparse2d::it_traits<double, true, false> const, (pm::AVL::link_index)1>, std::pair<pm::BuildUnary<pm::sparse2d::cell_accessor>, pm::BuildUnaryIt<pm::sparse2d::cell_index_accessor> > > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::AVL::tree_iterator<pm::sparse2d::it_traits<int, true, false> const, (pm::AVL::link_index)1>, std::pair<pm::BuildUnary<pm::sparse2d::cell_accessor>, pm::BuildUnaryIt<pm::sparse2d::cell_index_accessor> > > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::AVL::tree_iterator<pm::AVL::it_traits<int, double, pm::operations::cmp> const, (pm::AVL::link_index)1>, std::pair<pm::BuildUnary<pm::sparse_vector_accessor>, pm::BuildUnary<pm::sparse_vector_index_accessor> > > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::AVL::tree_iterator<pm::AVL::it_traits<int, pm::Rational, pm::operations::cmp> const, (pm::AVL::link_index)1>, std::pair<pm::BuildUnary<pm::sparse_vector_accessor>, pm::BuildUnary<pm::sparse_vector_index_accessor> > > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::AVL::tree_iterator<pm::sparse2d::it_traits<pm::Rational, false, true> const, (pm::AVL::link_index)1>, std::pair<pm::BuildUnary<pm::sparse2d::cell_accessor>, pm::BuildUnaryIt<pm::sparse2d::cell_index_accessor> > > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::AVL::tree_iterator<pm::sparse2d::it_traits<pm::Integer, true, false> const, (pm::AVL::link_index)1>, std::pair<pm::BuildUnary<pm::sparse2d::cell_accessor>, pm::BuildUnaryIt<pm::sparse2d::cell_index_accessor> > > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::AVL::tree_iterator<pm::AVL::it_traits<int, int, pm::operations::cmp> const, (pm::AVL::link_index)1>, std::pair<pm::BuildUnary<pm::sparse_vector_accessor>, pm::BuildUnary<pm::sparse_vector_index_accessor> > > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::range_folder<pm::unary_transform_iterator<pm::AVL::tree_iterator<pm::graph::it_traits<pm::graph::DirectedMulti, true> const, (pm::AVL::link_index)1>, std::pair<pm::graph::edge_accessor, pm::BuildUnaryIt<pm::sparse2d::cell_index_accessor> > >, pm::equal_index_folder> >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::AVL::tree_iterator<pm::sparse2d::it_traits<pm::QuadraticExtension<pm::Rational>, true, false> const, (pm::AVL::link_index)1>, std::pair<pm::BuildUnary<pm::sparse2d::cell_accessor>, pm::BuildUnaryIt<pm::sparse2d::cell_index_accessor> > > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::AVL::tree_iterator<pm::AVL::it_traits<int, pm::QuadraticExtension<pm::Rational>, pm::operations::cmp> const, (pm::AVL::link_index)1>, std::pair<pm::BuildUnary<pm::sparse_vector_accessor>, pm::BuildUnary<pm::sparse_vector_index_accessor> > > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::AVL::tree_iterator<pm::AVL::it_traits<int, pm::Integer, pm::operations::cmp> const, (pm::AVL::link_index)1>, std::pair<pm::BuildUnary<pm::sparse_vector_accessor>, pm::BuildUnary<pm::sparse_vector_index_accessor> > > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::AVL::tree_iterator<pm::sparse2d::it_traits<pm::TropicalNumber<pm::Min, pm::Rational>, false, true> const, (pm::AVL::link_index)1>, std::pair<pm::BuildUnary<pm::sparse2d::cell_accessor>, pm::BuildUnaryIt<pm::sparse2d::cell_index_accessor> > > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::AVL::tree_iterator<pm::AVL::it_traits<int, pm::TropicalNumber<pm::Min, pm::Rational>, pm::operations::cmp> const, (pm::AVL::link_index)1>, std::pair<pm::BuildUnary<pm::sparse_vector_accessor>, pm::BuildUnary<pm::sparse_vector_index_accessor> > > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::AVL::tree_iterator<pm::sparse2d::it_traits<pm::TropicalNumber<pm::Max, pm::Rational>, false, true> const, (pm::AVL::link_index)1>, std::pair<pm::BuildUnary<pm::sparse2d::cell_accessor>, pm::BuildUnaryIt<pm::sparse2d::cell_index_accessor> > > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::unary_transform_iterator<pm::single_value_iterator<int>, std::pair<pm::nothing, pm::operations::identity<int> > >, std::pair<pm::apparent_data_accessor<pm::Rational const&, false>, pm::operations::identity<int> > > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::AVL::tree_iterator<pm::sparse2d::it_traits<long, true, false> const, (pm::AVL::link_index)1>, std::pair<pm::BuildUnary<pm::sparse2d::cell_accessor>, pm::BuildUnaryIt<pm::sparse2d::cell_index_accessor> > > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::range_folder<pm::unary_transform_iterator<pm::AVL::tree_iterator<pm::graph::it_traits<pm::graph::UndirectedMulti, false> const, (pm::AVL::link_index)1>, std::pair<pm::graph::edge_accessor, pm::BuildUnaryIt<pm::sparse2d::cell_index_accessor> > >, pm::equal_index_folder> >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::AVL::tree_iterator<pm::AVL::it_traits<int, pm::PuiseuxFraction<pm::Min, pm::Rational, pm::Rational>, pm::operations::cmp> const, (pm::AVL::link_index)1>, std::pair<pm::BuildUnary<pm::sparse_vector_accessor>, pm::BuildUnary<pm::sparse_vector_index_accessor> > > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::AVL::tree_iterator<pm::sparse2d::it_traits<pm::PuiseuxFraction<pm::Max, pm::Rational, pm::Rational>, true, false> const, (pm::AVL::link_index)1>, std::pair<pm::BuildUnary<pm::sparse2d::cell_accessor>, pm::BuildUnaryIt<pm::sparse2d::cell_index_accessor> > > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::graph::valid_node_iterator<pm::iterator_range<pm::ptr_wrapper<pm::graph::node_entry<pm::graph::Undirected, (pm::sparse2d::restriction_kind)0> const, false> >, pm::BuildUnary<pm::graph::valid_node_selector> >, pm::graph::line_factory<std::integral_constant<bool, true>, pm::incidence_line, void> > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::graph::valid_node_iterator<pm::iterator_range<pm::ptr_wrapper<pm::graph::node_entry<pm::graph::Directed, (pm::sparse2d::restriction_kind)0> const, false> >, pm::BuildUnary<pm::graph::valid_node_selector> >, pm::graph::line_factory<std::integral_constant<bool, true>, pm::incidence_line, void> > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::graph::valid_node_iterator<pm::iterator_range<pm::ptr_wrapper<pm::graph::node_entry<pm::graph::DirectedMulti, (pm::sparse2d::restriction_kind)0> const, false> >, pm::BuildUnary<pm::graph::valid_node_selector> >, pm::graph::line_factory<std::integral_constant<bool, true>, pm::graph::multi_adjacency_line, void> > >);
   FunctionInstance4perl(index_f1, perl::Canned< const pm::unary_transform_iterator<pm::graph::valid_node_iterator<pm::iterator_range<pm::ptr_wrapper<pm::graph::node_entry<pm::graph::UndirectedMulti, (pm::sparse2d::restriction_kind)0> const, false> >, pm::BuildUnary<pm::graph::valid_node_selector> >, pm::graph::line_factory<std::integral_constant<bool, true>, pm::graph::multi_adjacency_line, void> > >);
///==== Automatically generated contents end here.  Please do not delete this line. ====
} } }
