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
#include "polymake/Array.h"
#include "polymake/SparseVector.h"

namespace polymake { namespace polytope {

template<typename Scalar>
perl::Object hypertruncated_cube(const int d, const Scalar k, const Scalar lambda)
{
   if (d < 2)
      throw std::runtime_error("hypertruncated_cube: dimension d >= 2 required");
   if (k <= 1 || k >=d)
      throw std::runtime_error("hypertruncated_cube: 1 < k < d required");
   if (lambda*d <= k)
      throw std::runtime_error("hypertruncated_cube: lambda > k/d required");

   perl::Object p(perl::ObjectType::construct<Scalar>("Polytope"));
   p.set_description() << "hypertruncated_cube(" << d << "," << k << "," << lambda << ")" << endl;

   const int n_ineqs=4*d;
   Matrix<Scalar> Inequalities(n_ineqs,d+1);
   int i=0;
  
   // facets through origin (= non-negativity constraints)
   for (int j=1; j<=d; ++j, ++i)
      Inequalities(i,j)=1;
  
   // opposite cube facets
   for (int j=1; j<=d; ++j, ++i) {
      Inequalities(i,0)=1; Inequalities(i,j)=-1;
   }
  
   // deletion facets through lambda(1,1,...,1)
   for (int j=1; j<=d; ++j, ++i) {
      Inequalities(i,0)=k;
      for (int jj=1; jj<j; ++jj)
         Inequalities(i,jj)=-1;
      Inequalities(i,j)=d-1-k/lambda;
      for (int jj=j+1; jj<=d; ++jj)
         Inequalities(i,jj)=-1;
   }
  
   // contraction facets through lambda(1,1,...,1)
   for (int j=1; j<=d; ++j, ++i) {
      Inequalities(i,0)=lambda*(d-k);
      for (int jj=1; jj<j; ++jj)
         Inequalities(i,jj)=lambda-1;
      Inequalities(i,j)=k-1-lambda*(d-1);
      for (int jj=j+1; jj<=d; ++jj)
         Inequalities(i,jj)=lambda-1;
   }
  
   p.take("CONE_AMBIENT_DIM") << d+1;
   p.take("INEQUALITIES") << Inequalities;
   p.take("BOUNDED") << true;
   p.take("FEASIBLE") << true;
   p.take("ONE_VERTEX") << unit_vector<Scalar>(d+1,0);

   // symmetric linear objective function
   perl::Object LP(perl::ObjectType::construct<Scalar>("LinearProgram"));
   LP.take("LINEAR_OBJECTIVE") << Vector<Scalar>(0|ones_vector<Scalar>(d));
   LP.attach("INTEGER_VARIABLES") << Array<bool>(d,true);
   p.take("LP") << LP;
  
   return p;
}

UserFunctionTemplate4perl("# @category Producing a polytope from scratch"
                          "# Produce a //d//-dimensional hypertruncated cube."
                          "# With symmetric linear objective function (0,1,1,...,1)."
                          "# "
                          "# @tparam Scalar Coordinate type of the resulting polytope.  Unless specified explicitly, deduced from the type of bound values, defaults to Rational."
                          "# @param Int d the dimension"
                          "# @param Scalar k cutoff parameter"
                          "# @param Scalar lambda scaling of extra vertex"
                          "# @return Polytope<Scalar>",
                          "hypertruncated_cube<Scalar> [ is_ordered_field(type_upgrade<Scalar, Rational>) ]"
                          "    (Int, type_upgrade<Scalar>, type_upgrade<Scalar>)");
} }

// Local Variables:
// mode:C++
// c-basic-offset:3
// indent-tabs-mode:nil
// End:
