/* Copyright (c) 1997-2017
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
#include "polymake/fan/hasse_diagram.h"

/*
#include "polymake/PowerSet.h"
#include "polymake/graph/Closure.h"
#include "polymake/graph/Lattice.h"
#include "polymake/graph/BasicLatticeTypes.h"
#include "polymake/graph/lattice_builder.h"
*/

namespace polymake { namespace fan { 
   
   template <typename Coord>
   perl::Object k_skeleton(perl::Object fan, const int k){
      perl::Object result(perl::ObjectType::construct<Coord>("PolyhedralFan"));
      bool is_pure = fan.give("PURE");
      bool is_complete = fan.give("COMPLETE");
      Matrix<Coord> rays = fan.give("RAYS");
	   perl::Object hasseDiagram = lower_hasse_diagram(fan, k, is_pure, is_complete);
      result.take("RAYS") << rays;
      result.take("HASSE_DIAGRAM") << hasseDiagram;
      return result;
   }

UserFunctionTemplate4perl("# @category Producing a fan"
                          "# Computes the //k//-skeleton of the polyhedral fan //F//,"
                          "# i.e. the subfan of //F// consisting of all cones of dimension <=//k//."
                          "# @tparam Coord"
                          "# @param PolyhedralFan F"
                          "# @param Int k the desired top dimension"
                          "# @return PolyhedralFan",
                          "k_skeleton<Coord>(fan::PolyhedralFan<Coord>, $)");
   

} // namespace fan
} // namespace polymake
