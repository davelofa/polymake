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

#ifndef POLYMAKE_POLYTOPE_CUBE_FACETS_H
#define POLYMAKE_POLYTOPE_CUBE_FACETS_H

#include "polymake/GenericSet.h"

namespace polymake { namespace polytope {

template <typename E>
class CubeFacet_iterator {
public:
   typedef std::forward_iterator_tag iterator_category;
   typedef E value_type;
   typedef const E& reference;
   typedef const E* pointer;
   typedef ptrdiff_t difference_type;
   typedef CubeFacet_iterator iterator;
   typedef iterator const_iterator;

   CubeFacet_iterator() { }
   CubeFacet_iterator(typename pm::function_argument<E>::type cur_arg,
                      typename pm::function_argument<E>::type step_arg,
                      typename pm::function_argument<E>::type end_arg)
      : cur(cur_arg), lim(cur_arg+step_arg), step(step_arg), end(end_arg) { }

   reference operator* () const { return cur; }
   pointer operator-> () const { return &cur; }

   iterator& operator++ () {
      if (++cur == lim) {
         cur += step;
         lim += (step<<1);
      }
      return *this;
   }
   const iterator operator++ (int) { iterator copy=*this; operator++(); return copy; }

   bool at_end() const { return cur==end; }
   bool operator== (const iterator& it) const { return cur==it.cur; }
   bool operator!= (const iterator& it) const { return !operator==(it); }
protected:
   E cur, lim, step, end;
};

/// Virtual container enumerating the verices in a facet of a cube
template <typename E>
class CubeFacet
   : public GenericSet< CubeFacet<E>, E, operations::cmp> {
public:
   typedef E value_type;
   typedef const E& const_reference;
   typedef const_reference reference;

   CubeFacet() { }
   CubeFacet(typename pm::function_argument<E>::type start_arg,
             typename pm::function_argument<E>::type step_arg,
             typename pm::function_argument<E>::type size_arg)
      : start(start_arg), step(step_arg), _size(size_arg) { }

   typedef CubeFacet_iterator<E> iterator;
   typedef iterator const_iterator;

   iterator begin() const { return iterator(start, step, start+_size); }
   iterator end() const { return iterator(start+_size, step, start+_size); }
   reference front() const { return start; }

   const E& size() const { return _size; }
   bool empty() const { return !_size; }

protected:
   E start, step, _size;
};

template <typename E>
class CubeFacets_iterator : protected CubeFacet<E> {
public:
   typedef std::forward_iterator_tag iterator_category;
   typedef CubeFacet<E> value_type;
   typedef const value_type& reference;
   typedef const value_type* pointer;
   typedef ptrdiff_t difference_type;
   typedef CubeFacets_iterator iterator;
   typedef iterator const_iterator;

   CubeFacets_iterator() { }
   CubeFacets_iterator(typename pm::function_argument<E>::type start_arg,
                       typename pm::function_argument<E>::type step_arg,
                       typename pm::function_argument<E>::type size_arg)
      : value_type(start_arg,step_arg,size_arg), start(start_arg) { }

   reference operator* () const { return *this; }
   pointer operator-> () const { return this; }

   iterator& operator++ () {
      if (value_type::start == start) {
         value_type::start += this->step;
      } else {
         value_type::start=start; this->step<<=1;
      }
      return *this;
   }
   const iterator operator++ (int) { iterator copy=*this; operator++(); return copy; }

   bool operator== (const iterator& it) const
   {
      return this->step==it.step && value_type::start==it.value_type::start;
   }
   bool operator!= (const iterator& it) const { return !operator==(it); }
   bool at_end() const { return this->step==this->_size; }
protected:
   E start;
};

template <typename E>
class CubeFacets {
public:
   typedef CubeFacets_iterator<E> iterator;
   typedef iterator const_iterator;
   typedef typename iterator::value_type value_type;
   typedef typename iterator::reference const_reference;
   typedef const_reference reference;

   /** @param dim_arg dimension of the cube
       @param start_arg index of the first vertex
   */
   explicit CubeFacets(int dim_arg, typename pm::function_argument<E>::type start_arg=E(0))
      : start(start_arg), dim(dim_arg) { }

   int size() const { return 2*dim; }
   bool empty() const { return dim==0; }

   iterator begin() const { return iterator(start, E(1), E(1)<<dim); }
   iterator end() const { return iterator(start, E(1)<<dim, E(1)<<dim); }

   const value_type front() const { return value_type(start, E(1), E(1)<<dim); }
protected:
   E start;
   int dim;
};

} }

namespace pm {

template <typename E>
struct check_iterator_feature<polymake::polytope::CubeFacet_iterator<E>, end_sensitive> : std::true_type { };

template <typename E>
struct check_iterator_feature<polymake::polytope::CubeFacets_iterator<E>, end_sensitive> : std::true_type { };
}

#endif // POLYMAKE_POLYTOPE_CUBE_FACETS_H

// Local Variables:
// mode:C++
// c-basic-offset:3
// indent-tabs-mode:nil
// End:
