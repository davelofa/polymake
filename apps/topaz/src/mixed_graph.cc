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
#include "polymake/Graph.h"

namespace polymake { namespace topaz {

void mixed_graph(perl::Object p, perl::OptionSet options)
{
   const Array< Set<int> > C = p.give("FACETS");
   const Graph<> PG = p.give("GRAPH.ADJACENCY");
   const Graph<> DG = p.give("DUAL_GRAPH.ADJACENCY");
   const int dim = p.give("DIM");

   // default for weight = sqrt((dim+1)/(12*Pi))
   // approximation for the radius of the embedding-sphere of a springembedded d-simplex
   double weight=1;
   options["edge_weight"] >> weight;
   weight*= sqrt(dim+1) / 6.14;

   Graph<Undirected> MG(PG.nodes() + DG.nodes());
   EdgeMap<Undirected, double> WT(MG);

   // add primal edges
   for (auto e=entire(edges(PG)); !e.at_end(); ++e)
      WT(e.from_node(), e.to_node())=1.0;

   // add dual edges
   const int diff = PG.nodes();
   for (auto e=entire(edges(DG)); !e.at_end(); ++e)
      WT(e.from_node()+diff, e.to_node()+diff)=1.0;

   // add mixed edges
   int c=diff;
   for (const auto& f : C) {
      for (int v : f) WT(c,v)=weight;
      ++c;
   }

   p.take("MIXED_GRAPH.ADJACENCY", perl::temporary) << MG;
   p.take("MIXED_GRAPH.EDGE_WEIGHTS", perl::temporary) << WT;
}

UserFunction4perl("# @category Other"
                  "# Produces the mixed graph of a //complex//.\n"
                  "# @param SimplicialComplex complex"
                  "# @option Float edge_weight",
                  &mixed_graph, "mixed_graph(SimplicialComplex { edge_weight=>undef })");

} }

// Local Variables:
// mode:C++
// c-basic-offset:3
// indent-tabs-mode:nil
// End:
