
#include "polymake/client.h"
#include "polymake/SparseMatrix.h"
#include "polymake/Graph.h"
#include "polymake/linalg.h"
#include "polymake/graph/incidence_matrix.h"

namespace polymake { 
   namespace graph {

      template <typename Dir>
      Matrix<Rational> laplacian(perl::Object p)
      {
         SparseMatrix<Rational> IncidenceM= convert_to<Rational>(signed_incidence_matrix<Dir>(p));
         return (IncidenceM*T(IncidenceM));
      }

      template <typename Dir>
      Vector<double> eigenvalues_laplacian(perl::Object p)
      {
         SparseMatrix<double> laplacianM=convert_to<double>(laplacian<Dir>(p));
         return eigenvalues(laplacianM);
      }
      
      template<typename TGraph>
      Matrix<Rational> laplacian(const GenericGraph<TGraph>& p)
      {
         SparseMatrix<Rational> IncidenceM= convert_to<Rational>(signed_incidence_matrix(p));
         return (IncidenceM*T(IncidenceM));
      }

      template<typename TGraph>
      Vector<double> eigenvalues_laplacian(const GenericGraph<TGraph>& p)
      {
         SparseMatrix<double> laplacianM=convert_to<double>(laplacian(p));
         return eigenvalues(laplacianM);
      }
         

      UserFunctionTemplate4perl("# @category Combinatorics"
                        "# Compute the unsigned vertex-edge incidence matrix of the graph."
                        "# @param Graph G"
                        "# @return SparseMatrix<Rational>"
                        "# @example > $I = laplacian(cycle_graph(4));"
                        "# > print $I;"
                        "# | 2 -1 0 -1"
                        "# | -1 2 -1 0"
                        "# | 0 -1 2 -1"
                        "# | -1 0 -1 2",
                        "laplacian<Dir>(Graph<Dir>)");
   
      UserFunctionTemplate4perl("# @category Combinatorics"
                        "# Compute the eigenvalues of the discrete laplacian a graph."
                        "# @param Graph G"
                        "# @return Vector<Float>"
                        "# @example > $v = eigenvalues_laplacian(cycle_graph(4));"
                        "# > print $v;"
                        "# | 4 2 2 0",
                        "eigenvalues_laplacian<Dir>(Graph<Dir>)");
      
      UserFunctionTemplate4perl("# @category Combinatorics"
                        "# Compute the unsigned vertex-edge incidence matrix of the graph."
                        "# @param Graph G"
                        "# @return SparseMatrix<Rational>"
                        "# @example > $I = laplacian(cycle_graph(4)->ADJACENCY);"
                        "# > print $I;"
                        "# | 2 -1 0 -1"
                        "# | -1 2 -1 0"
                        "# | 0 -1 2 -1"
                        "# | -1 0 -1 2",
                        "laplacian(props::Graph)");
      
      UserFunctionTemplate4perl("# @category Combinatorics"
                        "# Compute the eigenvalues of the discrete laplacian a graph."
                        "# @param Graph G"
                        "# @return Vector<Float>"
                        "# @example > $v = eigenvalues_laplacian(cycle_graph(4)->ADJACENCY);"
                        "# > print $v;"
                        "# | 4 2 2 0",
                        "eigenvalues_laplacian(props::Graph)");
   } 
}

// Local Variables:
// mode:C++
// c-basic-offset:3
// indent-tabs-mode:nil
// End:
