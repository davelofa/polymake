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
#include "polymake/Vector.h"
#include "polymake/Rational.h"
#include "polymake/topaz/complex_tools.h"
#include "polymake/IncidenceMatrix.h"

#include <sstream>

namespace polymake { namespace topaz {

template <typename Scalar>
perl::Object foldable_prism (perl::Object p_in, perl::OptionSet options)
{
   const IncidenceMatrix<> C_in = p_in.give("FACETS");
   const int n_vert = C_in.cols();
   const bool is_foldable = p_in.give("FOLDABLE");
   if (!is_foldable)
      throw std::runtime_error("foldable_prism: Complex not foldable.");

   const Array<int> Coloring = p_in.give("COLORING");
   std::list< Set<int> > C_out;

   int v=0;
   for (Entire< Cols< IncidenceMatrix<> > >::const_iterator star=entire( cols(C_in) );
        !star.at_end(); ++star, ++v)
      for (Entire< IncidenceMatrix<>::col_type >::const_iterator f=entire(*star); !f.at_end(); ++f) {
         Set<int> new_f;
         for (Entire< IncidenceMatrix<>::row_type >::const_iterator w=entire(C_in[f.index()]); !w.at_end(); ++w) {
            if (Coloring[v] <= Coloring[*w])
               new_f += *w + n_vert;
            if (Coloring[v] >= Coloring[*w])
               new_f += *w;
         }
         C_out.push_back(new_f);
      }

   const bool realize = options["geometric_realization"];
   perl::Object p_out = realize ?
      perl::Object(perl::ObjectType::construct<Scalar>("topaz::GeometricSimplicialComplex")) :
      perl::Object("topaz::SimplicialComplex");
   //   perl::Object p_out(perl::ObjectType::construct<Scalar>("topaz::GeometricSimplicialComplex"));
   p_out.set_description()  << "foldable prism of " << p_in.name() << "."<<endl;
   p_out.take("FACETS") << as_array(C_out);
   
   if (realize) {
      Matrix<Scalar> GR=p_in.give("COORDINATES");
      Matrix<Scalar> GR2 = Vector<Scalar>(n_vert, pm::choose_generic_object_traits<Scalar>::one()) | GR;
      GR = Vector<Scalar>(n_vert) | GR;

      p_out.take("COORDINATES") << GR/GR2;
   }
   return p_out;
}

UserFunctionTemplate4perl("# @category Producing a new simplicial complex from others\n"
                          "# Produce a __prism__ over a given [[SimplicialComplex]].\n"
                          "# @param GeometricSimplicialComplex complex"
                          "# @option Bool geometric_realization"
                          "# @return GeometricSimplicialComplex",
                          "foldable_prism<Scalar>(GeometricSimplicialComplex<Scalar> {geometric_realization => 0})");


} }

// Local Variables:
// mode:C++
// c-basic-offset:3
// indent-tabs-mode:nil
// End:
