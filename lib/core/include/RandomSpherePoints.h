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

#ifndef POLYMAKE_RANDOM_SPHERE_POINTS_H
#define POLYMAKE_RANDOM_SPHERE_POINTS_H

#include "polymake/RandomGenerators.h"
#include <cmath>

namespace pm {

using std::log;

/** Generator of floating-point numbers normally distributed in (-1,1).
 *  The algorithm is taken from Donald E. Knuth, The Art of Computer Programming, vol. II, p117.
 */
template <typename Num=AccurateFloat>
class NormalRandom
   : public GenericRandomGenerator<NormalRandom<Num>, const Num&> {
public:
   static_assert(is_among<Num, AccurateFloat, double>::value, "wrong number type");

   explicit NormalRandom(const RandomSeed& seed=RandomSeed())
      : uni_src(seed)
   {
      fill();
   }

   explicit NormalRandom(const SharedRandomState& s)
      : uni_src(s)
   {
      fill();
   }

   const Num& get()
   {
      if (++index==2) fill();
      return x[index];
   }

protected:
   Num x[2];
   UniformlyRandom<Num> uni_src;
   int index;

   void fill()
   {
      Num v, u, s;
      do {
         v = 2*uni_src.get()-1;
         u = 2*uni_src.get()-1;
         s = u*u + v*v;
      } while (s >= 1);

      const Num scale = sqrt( (-2*log(s)) / s );
      x[0]=v * scale;
      x[1]=u * scale;
      index=0;
   }
};


/// Generator of uniformly distributed random points on the unit sphere in R^d
template <typename Num=AccurateFloat>
class RandomSpherePoints
   : public GenericRandomGenerator<RandomSpherePoints<Num>, const Vector<Num>&> {
public:
   explicit RandomSpherePoints(int dim, const RandomSeed& seed=RandomSeed())
      : point(dim), norm_src(seed) {}

   RandomSpherePoints(int dim, const SharedRandomState& s)
      : point(dim), norm_src(s) {}

   const Vector<Num>& get()
   {
      fill_vector();
      return point;
   }

   void set_precision(int precision)
   {
      static_assert(std::is_same<Num,AccurateFloat>::value, "RandomSpherePoints.set_precision is defined only for AccurateFloat");
      for(auto&& x: point)
         x.set_precision(precision);
   }

protected:
   Vector<Num> point;
   NormalRandom<Num> norm_src;

   void fill_vector()
   {
      Num norm;
      do {
         copy_range(norm_src.begin(), entire(point));
         norm = sqr(point);
      } while (norm == 0);        // this occurs with very low probability
      point /= sqrt(norm);
   }
};

} // end namespace pm

namespace polymake {

using pm::NormalRandom;
using pm::RandomSpherePoints;

}

#endif // POLYMAKE_RANDOM_SPHERE_POINTS_H

// Local Variables:
// mode:C++
// c-basic-offset:3
// indent-tabs-mode:nil
// End:
