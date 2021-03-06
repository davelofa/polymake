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

#include <gmpxx.h>
#include "libnormaliz/libnormaliz.h"
#include "libnormaliz/cone.h"
#include "libnormaliz/HilbertSeries.h"

#include "polymake/client.h"
#include "polymake/vector"
#include "polymake/Integer.h"
#include "polymake/Rational.h"
#include "polymake/Matrix.h"
#include "polymake/common/lattice_tools.h"
#include "polymake/Polynomial.h"
#include "polymake/RationalFunction.h"

namespace pm {

template<>
class conv<Integer,mpz_class> {
public:
   typedef Integer argument_type;
   typedef mpz_class result_type;

   result_type operator() (const argument_type& x) const { return x.gmp(); }
};

}

namespace polymake { namespace polytope {

namespace {

template <typename Scalar, typename TVector>
std::vector<Scalar> pmVector_to_stdvector(const GenericVector<TVector>& v)
{
  return std::vector<Scalar>(attach_converter<Scalar>(v.top()).begin(),
                             attach_converter<Scalar>(v.top()).end());
}

template <typename Scalar, typename FromScalar>
Matrix<Scalar> stdvectorvector_to_pmMatrix(const std::vector<std::vector<FromScalar>>& vec)
{
  return Matrix<Scalar>(vec.size(), vec.empty() ? 0 : vec.front().size(), vec.begin());
}

template <typename Scalar>
std::vector<std::vector<Scalar>> pmMatrix_to_stdvectorvector(const Matrix<Rational>& m)
{
  const auto pmdata = common::primitive(m);
  std::vector<std::vector<Scalar>> data;
  data.reserve(pmdata.rows());
  std::transform(rows(pmdata).begin(),rows(pmdata).end(),
                 std::back_inserter(data), [](const auto& v){ return pmVector_to_stdvector<Scalar>(v); });
  return data;
}

// create libnormaliz cone object based on given type
//  from rays or inequalities
template <typename Scalar>
libnormaliz::Cone<Scalar> libnormaliz_create_cone(perl::Object c, bool from_ineq, bool compute_facets, bool with_grading)
{
  std::map<libnormaliz::InputType, std::vector<std::vector<Scalar>>> inputmap;
  Matrix<Rational> data;
  if (from_ineq) {
    const Matrix<Rational>& f = c.give("FACETS | INEQUALITIES");
    inputmap[libnormaliz::Type::inequalities] = pmMatrix_to_stdvectorvector<Scalar>(f);
    if (c.lookup("LINEAR_SPAN | EQUATIONS") >> data)
      inputmap[libnormaliz::Type::equations] = pmMatrix_to_stdvectorvector<Scalar>(data);
  } else {
    const Matrix<Rational>& r = c.give("RAYS | INPUT_RAYS");
    inputmap[libnormaliz::Type::integral_closure] = pmMatrix_to_stdvectorvector<Scalar>(r);
    if(c.lookup("INPUT_LINEALITY | LINEALITY_SPACE") >> data){
       inputmap[libnormaliz::Type::subspace] = pmMatrix_to_stdvectorvector<Scalar>(data);
    }
    // lookup dual description if we do not want to compute it
    if (!compute_facets) {
      if (c.lookup("FACETS | INEQUALITIES") >> data)
        inputmap[libnormaliz::Type::inequalities] = pmMatrix_to_stdvectorvector<Scalar>(data);
      if (c.lookup("LINEAR_SPAN | EQUATIONS") >> data)
        inputmap[libnormaliz::Type::equations] = pmMatrix_to_stdvectorvector<Scalar>(data);
    }
  }
  if (with_grading) {
    const Vector<Integer>& v=c.give("MONOID_GRADING");
    inputmap[libnormaliz::Type::grading] = std::vector<std::vector<Scalar>>(1, pmVector_to_stdvector<Scalar>(v));
  }
  return libnormaliz::Cone<Scalar>(inputmap);
}

// hilbert series conversion:
// nmzHilb.getNum() vector<mpz_class>
// nmzHilb.getDenom() map<long,denom_t> (exponents of (1-t^i)^e) denom_t = long
RationalFunction<> nmz_convert_HS(const libnormaliz::HilbertSeries& nmzHilb)
{
  UniPolynomial<> HSnum(convert_to<Integer>(Vector<mpz_class>(nmzHilb.getNum())),
                        Vector<int>(sequence(0, nmzHilb.getNum().size())));
  const std::map<long,long>& HSdenomMap = nmzHilb.getDenom();
  UniPolynomial<> HSdenom(1);
  for (const auto& mapElem : HSdenomMap)
  {
    HSdenom *= (1 - UniPolynomial<>(1, mapElem.first))^mapElem.second;
  }
  return RationalFunction<>(HSnum,HSdenom);
}

template <typename Scalar>
perl::ListReturn normaliz_compute_with(perl::Object c, perl::OptionSet options,
                                       const libnormaliz::ConeProperties& todo, bool with_grading)
{
  perl::ListReturn result;
  libnormaliz::Cone<Scalar> nmzCone = libnormaliz_create_cone<Scalar>(c, options["from_facets"], options["facets"], with_grading);
  // in the first case we have done computation with long already or disabled it explicitly
  // the second case is for non-bundled libnormaliz where the long variant is handled
  // by libnormaliz directly
  if (std::is_same<Scalar,Integer>::value ||
        (std::is_same<Scalar,mpz_class>::value && options["skip_long"]))
     nmzCone.deactivateChangeOfPrecision();
  nmzCone.compute(todo);
  if (options["degree_one_generators"]){
       Integer d(nmzCone.getGradingDenom());
       if(d == 1){
          result << stdvectorvector_to_pmMatrix<Integer>(nmzCone.getDeg1Elements());
       } else {
          Matrix<Integer> empty(0, c.give("CONE_DIM"));
          result << empty;
       }
    }
  if (options["hilbert_basis"]){
     result << Matrix<Integer>(stdvectorvector_to_pmMatrix<Integer>(nmzCone.getHilbertBasis()));
     result << Matrix<Integer>(stdvectorvector_to_pmMatrix<Integer>(nmzCone.getMaximalSubspace()));
  }
  if (options["h_star_vector"])
    // adjust to correct length, especially for non-full-dimensional polytopes
    result << (convert_to<Integer>(Vector<mpz_class>(nmzCone.getHilbertSeries().getNum())) | zero_vector<Integer>(-1-nmzCone.getHilbertSeries().getDegreeAsRationalFunction()));
  if (options["hilbert_series"])
    result << nmz_convert_HS(nmzCone.getHilbertSeries());
  if (options["facets"]) {
    result << stdvectorvector_to_pmMatrix<Rational>(nmzCone.getSupportHyperplanes());
    result << stdvectorvector_to_pmMatrix<Rational>(nmzCone.getSublattice().getEquations());
  }
  if (options["rays"])
    result << stdvectorvector_to_pmMatrix<Rational>(nmzCone.getExtremeRays());
  return result;
}

}

perl::ListReturn normaliz_compute(perl::Object c, perl::OptionSet options)
{
  libnormaliz::verbose=options["verbose"];

  libnormaliz::ConeProperties todo;
  if (options["degree_one_generators"])
    todo.set(libnormaliz::ConeProperty::Deg1Elements);
  if (options["hilbert_basis"])
    todo.set(libnormaliz::ConeProperty::HilbertBasis);
  if (options["hilbert_series"] || options["h_star_vector"])
    todo.set(libnormaliz::ConeProperty::HilbertSeries);
  if (options["dual_algorithm"])
    todo.set(libnormaliz::ConeProperty::DualMode);
  if (options["facets"])
    todo.set(libnormaliz::ConeProperty::SupportHyperplanes);
  if (options["rays"])
    todo.set(libnormaliz::ConeProperty::ExtremeRays);

  const bool with_grading = c.exists("MONOID_GRADING");

#ifdef BUNDLED_LIBNORMALIZ
  if (!options["skip_long"]) {
    try {
      // try with long first
      return normaliz_compute_with<long>(c, options, todo, with_grading);
    }
    catch(const pm::GMP::error& ex) {
      if (libnormaliz::verbose)
        cerr << "libnormaliz: error converting coordinates to long, retrying with arbitrary precision" << endl;
    }
    catch(const libnormaliz::ArithmeticException& ex) {
      if (libnormaliz::verbose)
        cerr << "libnormaliz: arithmetic error detected, retrying with arbitrary precision" << endl;
    }
  }
  return normaliz_compute_with<Integer>(c, options, todo, with_grading);
#else
  /*
     * non-bundled installation of libnormaliz doesnt support using our own type
     * for mpz_class cones libnormaliz will first try to compute with long long,
       thus we do not need do it separately
  */
  return normaliz_compute_with<mpz_class>(c, options, todo, with_grading);
#endif

}

UserFunction4perl("# @category Geometry"
		  "# Compute degree one elements, Hilbert basis or Hilbert series of a cone C with libnormaliz"
                  "# Hilbert series and Hilbert h-vector depend on the given grading"
                  "# and will not work unless C is [[HOMOGENEOUS]] or a [[MONOID_GRADING]] is set"
                  "# @param Cone C"
                  "# @option Bool from_facets supply facets instead of rays to normaliz"
                  "# @option Bool degree_one_generators compute the generators of degree one, i.e. lattice points of the polytope"
                  "# @option Bool hilbert_basis compute Hilbert basis of the cone C"
                  "# @option Bool h_star_vector compute Hilbert h-vector of the cone C"
                  "# @option Bool hilbert_series compute Hilbert series of the monoid"
                  "# @option Bool facets compute support hyperplanes (=FACETS,LINEAR_SPAN)"
                  "# @option Bool rays compute extreme rays (=RAYS)"
                  "# @option Bool dual_algorithm use the dual algorithm by Pottier"
                  "# @option Bool skip_long do not try to use long coordinates first"
                  "# @option Bool verbose libnormaliz debug output"
                  "# @return List (Matrix<Integer> degree one generators, Matrix<Integer> Hilbert basis, Vector<Integer> Hilbert h-vector, RationalFunction Hilbert series, Matrix<Rational> facets, Matrix<Rational> linear_span, Matrix<Rational> rays) (only requested items)",
                  &normaliz_compute, "normaliz_compute(Cone { from_facets => 0, degree_one_generators=>0, hilbert_basis=>0, h_star_vector=>0, hilbert_series=>0, facets=>0, rays=>0, dual_algorithm=>0, skip_long=>0, verbose => 0 })");

} }
