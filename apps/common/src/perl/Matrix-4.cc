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

///==== this line controls the automatic file splitting: max.instances=20

#include "polymake/client.h"
#include "polymake/Matrix.h"
#include "polymake/Rational.h"
#include "polymake/Set.h"
#include "polymake/Vector.h"
#include "polymake/Integer.h"
#include "polymake/IncidenceMatrix.h"
#include "polymake/linalg.h"
#include "polymake/SparseMatrix.h"

namespace polymake { namespace common { namespace {
///==== Automatically generated contents follow.    Please do not delete this line. ====
   template <typename T0, typename T1>
   FunctionInterface4perl( new_X, T0,T1 ) {
      perl::Value arg0(stack[1]);
      WrapperReturnNew(T0, (arg0.get<T1>()) );
   };

   OperatorInstance4perl(BinaryAssign_div, perl::Canned< Wary< Matrix< Rational > > >, perl::Canned< const Matrix< Rational > >);
   FunctionInstance4perl(new_X, Matrix< Rational >, perl::Canned< const Set< Vector< Integer > > >);
   OperatorInstance4perl(Binary_mul, perl::Canned< const Wary< Matrix< Integer > > >, int);
   OperatorInstance4perl(BinaryAssign_sub, perl::Canned< Wary< Matrix< Rational > > >, perl::Canned< const pm::RepeatedRow<pm::IndexedSlice<pm::masquerade<pm::ConcatRows, pm::Matrix_base<pm::Rational>&>, pm::Series<int, true>> const&> >);
   OperatorInstance4perl(Binary_sub, perl::Canned< const Wary< Matrix< Rational > > >, perl::Canned< const pm::RepeatedRow<pm::IndexedSlice<pm::masquerade<pm::ConcatRows, pm::Matrix_base<pm::Rational>&>, pm::Series<int, true>> const&> >);
   OperatorInstance4perl(Binary__eq, perl::Canned< const Wary< Matrix< Integer > > >, perl::Canned< const Matrix< int > >);
   FunctionInstance4perl(new_X, Matrix< double >, perl::Canned< const SparseMatrix< Rational, NonSymmetric > >);
   OperatorInstance4perl(BinaryAssign_div, perl::Canned< Wary< Matrix< Rational > > >, perl::Canned< const pm::SameElementSparseVector<pm::SingleElementSet<int>, pm::Rational> >);
   OperatorInstance4perl(Binary_mul, perl::Canned< const Wary< Matrix< Rational > > >, perl::Canned< const Vector< int > >);
   FunctionInstance4perl(new_X, Matrix< Rational >, perl::Canned< const pm::ColChain<pm::Matrix<pm::Rational> const&, pm::SingleCol<pm::Vector<pm::Rational> const&> > >);
   OperatorInstance4perl(BinaryAssign_div, perl::Canned< Wary< Matrix< Rational > > >, perl::Canned< const pm::RepeatedRow<pm::SameElementSparseVector<pm::SingleElementSet<int>, pm::Rational> const&> >);
   OperatorInstance4perl(BinaryAssign__or, perl::Canned< Wary< Matrix< Rational > > >, perl::Canned< const pm::SameElementSparseVector<pm::SingleElementSet<int>, pm::Rational> >);
   OperatorInstance4perl(BinaryAssign_div, perl::Canned< Wary< Matrix< Rational > > >, perl::Canned< const pm::Transposed<pm::Matrix<pm::Rational> > >);
   FunctionInstance4perl(new_X, Matrix< Rational >, perl::Canned< const pm::ColChain<pm::SingleCol<pm::VectorChain<pm::Vector<pm::Rational> const&, pm::Vector<pm::Rational> const&> const&>, pm::Matrix<pm::Rational> const&> >);
///==== Automatically generated contents end here.  Please do not delete this line. ====
} } }
