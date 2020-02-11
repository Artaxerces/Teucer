/*
 *  Copyright 2008-2012 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


/*! \file iterator_traits.inl
 *  \brief Inline file for iterator_traits.h.
 */

#include <thrust/iterator/iterator_categories.h>
#include <thrust/iterator/detail/iterator_category_to_traversal.h>
#include <thrust/detail/type_traits.h>

namespace thrust
{

template<typename Iterator>
  struct iterator_value
{
  typedef typename thrust::iterator_traits<Iterator>::value_type type;
}; // end iterator_value


template<typename Iterator>
  struct iterator_pointer
{
  typedef typename thrust::iterator_traits<Iterator>::pointer type;
}; // end iterator_pointer


template<typename Iterator>
  struct iterator_reference
{
  typedef typename iterator_traits<Iterator>::reference type;
}; // end iterator_reference


template<typename Iterator>
  struct iterator_difference
{
  typedef typename thrust::iterator_traits<Iterator>::difference_type type;
}; // end iterator_difference


template<typename Iterator>
  struct iterator_system
    : detail::iterator_category_to_system<
        typename thrust::iterator_traits<Iterator>::iterator_category
      >
{
}; // end iterator_system

// specialize iterator_system for void *, which has no category
template<>
  struct iterator_system<void *>
{
  typedef thrust::iterator_system<int*>::type type;
}; // end iterator_system<void*>

template<>
  struct iterator_system<const void *>
{
  typedef thrust::iterator_system<const int*>::type type;
}; // end iterator_system<void*>


template <typename Iterator>
  struct iterator_traversal
    : detail::iterator_category_to_traversal<
        typename thrust::iterator_traits<Iterator>::iterator_category
      >
{
}; // end iterator_traversal

namespace detail
{

template <typename T>
  struct is_iterator_traversal
    : thrust::detail::is_convertible<T, incrementable_traversal_tag>
{
}; // end is_iterator_traversal


template<typename T>
  struct is_iterator_system
    : detail::or_<
        detail::is_convertible<T, any_system_tag>,
        detail::or_<
          detail::is_convertible<T, host_system_tag>,
          detail::is_convertible<T, device_system_tag>
        >
      >
{
}; // end is_iterator_system


} // end namespace detail
} // end namespace thrust

