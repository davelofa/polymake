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

#include "polymake/client.h"
#include "polymake/Set.h"
#include "polymake/hash_set"
#include "polymake/Matrix.h"
#include "polymake/Vector.h"
#include "polymake/linalg.h"
#include "polymake/IncidenceMatrix.h"
#include "polymake/common/lattice_tools.h"

namespace polymake { namespace polytope {
   
template <typename E>
perl::Object zonotope_tiling_lattice(perl::Object P, perl::OptionSet options)
{
   const Matrix<E> V = P.give("VERTICES");
   const int emb_d = V.cols(); 
   const IncidenceMatrix<> VIF = P.give("VERTICES_IN_FACETS");
   const Vector<E> 
      _b = P.give("VERTEX_BARYCENTER"),
      b = dehomogenize(_b);

   Matrix<E> lattice_gens(VIF.rows(), emb_d); 
   typename Entire<Rows<Matrix<E> > >::iterator rlit = entire(rows(lattice_gens));
   for (Entire<Rows<IncidenceMatrix<> > >::const_iterator rit = entire(rows(VIF)); !rit.at_end(); ++rit, ++rlit) {
      const Set<int> vif(*rit);
      const Vector<E> facet_barycenter = dehomogenize(ones_vector<E>(vif.size()) * V.minor(vif, All)); 
      *rlit = zero_vector<E>(1) | (2 * (facet_barycenter - b)); 
   }

   perl::Object L(perl::ObjectType::construct<E>("AffineLattice"));

   const bool lattice_origin_is_vertex = options["lattice_origin_is_vertex"];
   if (lattice_origin_is_vertex)
      L.take("ORIGIN") << V.row(0);
   else
      L.take("ORIGIN") << unit_vector<E>(emb_d,0);

   const Integer s = lcm(denominators(concat_rows(lattice_gens)));
   Matrix<E> integer_gens(lattice_gens);
   integer_gens *= s;
   const Matrix<E> B(common::lattice_basis(Matrix<Integer>(integer_gens))/s);
   L.take("BASIS") << (zero_vector<E>(B.rows()) | B);

   return L;
}

UserFunctionTemplate4perl("# @category Geometry"
                          "# Calculates a generating set for a tiling lattice for P, "
                          "# i.e., a lattice L such that P + L tiles the affine span of P. "
                          "# @param Polytope P the zonotope"
                          "# @option Bool lattice_origin_is_vertex true if the origin of the tiling lattice should be a vertex of P; default false, ie, the origin will be the barycenter of P"
                          "# @return AffineLattice"
                          "# @example This determines a tiling lattice for a parallelogram with the origin as its vertex barycenter and prints it base vectors:"
                          "# > $M = new Matrix([[1,1,0],[1,1,1]]);"
                          "# > $p = zonotope($M);"
                          "# > $A = zonotope_tiling_lattice($p);"
                          "# > print $A->BASIS;"
                          "# | 0 -1 -1"
                          "# | 0 0 1",
                          "zonotope_tiling_lattice<E>(Polytope<E> { lattice_origin_is_vertex => 0  } )");
    } }

// Local Variables:
// mode:C++
// c-basic-offset:3
// indent-tabs-mode:nil
// End:
