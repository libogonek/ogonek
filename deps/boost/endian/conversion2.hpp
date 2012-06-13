//  boost/endian/conversion.hpp  -------------------------------------------------------//

//  Copyright Beman Dawes 2010, 2011

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_ENDIAN_CONVERSION2_HPP
#define BOOST_ENDIAN_CONVERSION2_HPP

#include <boost/detail/endian.hpp>
#include <boost/cstdint.hpp>
#include <algorithm>

//--------------------------------------------------------------------------------------//
// 
//  This header explores
//    -- value returning interface approach suggested by Phil Endecott.
//    -- additional reorder overloads for floating point types as requested by Vicente
//       Botet and others.
//    -- reorder implementation approach suggested by tymofey, with avoidance of
//       undefined behavior as suggested by Giovanni Piero Deretta, and a further
//       refinement suggested by Pyry Jahkola.
//    -- general reorder function template to meet requests for UDT support by
//       Vicente Botet and others. 
//    -- general reorder function template implementation approach using std::reverse
//       suggested by Mathias Gaunard
//
//--------------------------------------------------------------------------------------//

//------------------------------------- synopsis ---------------------------------------//

namespace boost
{
namespace endian2
{
  // reverse byte order (i.e. endianness)

  inline int16_t  reorder(int16_t x);
  inline int32_t  reorder(int32_t x);
  inline int64_t  reorder(int64_t x);
  inline uint16_t reorder(uint16_t x);
  inline uint32_t reorder(uint32_t x);
  inline uint64_t reorder(uint64_t x);

  // TODO: Need implementation
  // TODO: Need to verify the return does not invoke undefined behavior (as might happen
  // if there are unutterable floating point values, such as happens with the unutterable
  // pointer values on some architectures
  inline float    reorder(float x);    
  inline double   reorder(double x);   

  // TODO: Would pass by value be better for the following functions?

  template <class T>
  inline T reorder(const T& x);

  template <class T>
  inline T big(const T& x);    
    //  Return: x if native endianness is big, otherwise reorder(x);

  template <class T>
  inline T little(const T& x);
    //  Return: x if native endianness is little, otherwise reorder(x);

//----------------------------------- implementation -----------------------------------//
                                                
  inline int16_t reorder(int16_t x)
  {
    return (static_cast<uint16_t>(x) << 8)
      | (static_cast<uint16_t>(x) >> 8);
  }

  inline int32_t reorder(int32_t x)
  {
    uint32_t step16;
    step16 = static_cast<uint32_t>(x) << 16 | static_cast<uint32_t>(x) >> 16;
    return
        ((static_cast<uint32_t>(step16) << 8) & 0xff00ff00)
      | ((static_cast<uint32_t>(step16) >> 8) & 0x00ff00ff);
  }

  inline int64_t reorder(int64_t x)
  {
    uint64_t step32, step16;
    step32 = static_cast<uint64_t>(x) << 32 | static_cast<uint64_t>(x) >> 32;
    step16 = (step32 & 0x0000FFFF0000FFFF) << 16
           | (step32 & 0xFFFF0000FFFF0000) >> 16;
    return static_cast<int64_t>((step16 & 0x00FF00FF00FF00FF) << 8
           | (step16 & 0xFF00FF00FF00FF00) >> 8);
  }

  inline uint16_t reorder(uint16_t x)
  {
    return (x << 8)
      | (x >> 8);
  }

  inline uint32_t reorder(uint32_t x)
  {
    uint32_t step16;
    step16 = x << 16 | x >> 16;
    return
        ((step16 << 8) & 0xff00ff00)
      | ((step16 >> 8) & 0x00ff00ff);
  }

  inline uint64_t reorder(uint64_t x)
  {
    uint64_t step32, step16;
    step32 = x << 32 | x >> 32;
    step16 = (step32 & 0x0000FFFF0000FFFF) << 16
           | (step32 & 0xFFFF0000FFFF0000) >> 16;
    return (step16 & 0x00FF00FF00FF00FF) << 8
           | (step16 & 0xFF00FF00FF00FF00) >> 8;
  }


  template <class T>
  inline T reorder(const T& x)
  {
    T tmp;
    std::reverse(
      reinterpret_cast<const char*>(&x),
      reinterpret_cast<const char*>(&x) + sizeof(T),
      reinterpret_cast<char*>(&tmp));
    return tmp;
  }

  template <class T>
  inline T big(const T& x)
  {
#   ifdef BOOST_BIG_ENDIAN
      return x;
#   else
      return reorder(x);
#   endif
  }

  template <class T>
  inline T little(const T& x)    
  {
#   ifdef BOOST_LITTLE_ENDIAN
      return x;
#   else
      return reorder(x);
#   endif
  }

}  // namespace endian2
}  // namespace boost

#endif // BOOST_ENDIAN_CONVERSION2_HPP
