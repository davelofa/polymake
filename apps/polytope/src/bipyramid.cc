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

#include "polymake/client.h"
#include "polymake/vector"
#include "polymake/Rational.h"
#include "polymake/Matrix.h"
#include "polymake/Vector.h"
#include "polymake/IncidenceMatrix.h"

namespace polymake { namespace polytope {

template<typename Scalar>
perl::Object bipyramid(perl::Object p_in, const Scalar& z, const Scalar& z_prime, perl::OptionSet options)
{
   if (z*z_prime >= 0) 
      throw std::runtime_error("bipyramid: z and z' must have opposite signs and be non-zero");

   perl::Object p_out(perl::ObjectType::construct<Scalar>("Polytope"));
   p_out.set_description() << "Bipyramid over " << p_in.name() << endl;

   const bool noc = options["noc"],
          relabel = options["relabel"];

   int n_vertices=0;
   if (noc || p_in.exists("VERTICES_IN_FACETS")) {
      const IncidenceMatrix<> VIF=p_in.give("VERTICES_IN_FACETS");
      n_vertices=VIF.cols();
      const int n_facets=VIF.rows();
      const IncidenceMatrix<> VIF_out= (VIF / VIF) | sequence(0,n_facets) | sequence(n_facets,n_facets);

      p_out.take("N_VERTICES") << n_vertices+2;
      p_out.take("VERTICES_IN_FACETS") << VIF_out;
   }
   if (noc) {
      if (p_in.exists("COMBINATORIAL_DIM")) {
         const int dim=p_in.give("COMBINATORIAL_DIM");
         p_out.take("COMBINATORIAL_DIM") << dim+1;
      }
   } else {
      const bool pointed=p_in.give("POINTED");
      if (!pointed)
         throw std::runtime_error("bipyramid: input polyhedron not pointed");

      const Matrix<Scalar> V=p_in.give("VERTICES");
      const Vector<Scalar> z0=p_in.give("REL_INT_POINT");
      n_vertices=V.rows();
      const Matrix<Scalar> V_out=(V | zero_vector<Scalar>()) /
                                   (z0 | z) /
                                   (z0 | z_prime);
      p_out.take("VERTICES") << V_out;
      p_out.take("LINEALITY_SPACE") << Matrix<Scalar>();
   }
   if (relabel) {
      std::vector<std::string> labels(n_vertices+2);
      read_labels(p_in, "VERTEX_LABELS", labels);
      labels[n_vertices]="Apex";
      labels[n_vertices+1]="Apex'";
      p_out.take("VERTEX_LABELS") << labels;
   }
   return p_out;
}

UserFunctionTemplate4perl("# @category Producing a polytope from polytopes"
                          "# Make a bipyramid over a pointed polyhedron."
                          "# The bipyramid is the convex hull of the input polyhedron //P//"
                          "# and two points (//v//, //z//), (//v//, //z_prime//)"
                          "# on both sides of the affine span of //P//. For bounded polyhedra, the apex projections"
                          "# //v// to the affine span of //P// coincide with the vertex barycenter of //P//."
                          "# @param Polytope P"
                          "# @param Scalar z distance between the vertex barycenter and the first apex,"
                          "#  default value is 1."
                          "# @param Scalar z_prime distance between the vertex barycenter and the second apex,"
                          "#  default value is -//z//."
                          "# @option Bool noc : don't compute the coordinates, purely combinatorial description is produced."
                          "# @option Bool relabel copy the vertex labels from the original polytope,"
                          "#  label the new vertices with \"Apex\" and \"Apex'\".",
                          "bipyramid<Scalar>(Polytope<type_upgrade<Scalar>>; type_upgrade<Scalar>=1, type_upgrade<Scalar>=(-$_[1]), {noc => undef, relabel => undef})");
} }

// Local Variables:
// mode:C++
// c-basic-offset:3
// indent-tabs-mode:nil
// End:
