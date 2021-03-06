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

#include "polymake/client.h"
#include "polymake/Matrix.h"
#include "polymake/SparseMatrix.h"
#include "polymake/polytope/transform.h"
#include <cmath>

namespace polymake { namespace polytope {

double minimal_vertex_angle(perl::Object p)
{
   const Matrix<double> V=p.give("VERTICES");
   const Vector<double> origin=p.give("VERTEX_BARYCENTER");   // must be affine
   const int d = origin.dim();
  
   SparseMatrix<double> tau=unit_matrix<double>(d);
   tau[0].slice(1)=-origin.slice(1);
   perl::Object spherical_p=transform<double>(p, tau, false);
   Matrix<double> spherical_V=spherical_p.give("VERTICES");
   spherical_V=spherical_V.minor(All,range(1,d-1));
  
   const int n=spherical_V.rows();
   for (int i=0; i<n; ++i)
      spherical_V[i]/=sqrt(sqr(spherical_V[i]));
  
   double min_angle=2.0*acos(0.0); // pi
  
   for (int i=0; i<n; ++i)
      for (int j=i+1; j<n; ++j) {
         double phi=acos(V[i]*V[j]); // phi==0 means opposite
         if (0<phi && phi<min_angle) min_angle=phi; 
      }
  
   return min_angle;
}

UserFunction4perl("# @category Geometry"
                  "# Computes the minimal angle between two vertices of the input polytope //P//."
                  "# @param Polytope P"
                  "# @return Float"
                  "# @example"
                  "# > print minimal_vertex_angle(simplex(3));"
                  "# | 3.14159265358979",
                  &minimal_vertex_angle,"minimal_vertex_angle");
} }

// Local Variables:
// mode:C++
// c-basic-offset:3
// indent-tabs-mode:nil
// End:
