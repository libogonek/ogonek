//  boost/endian/conversion.hpp  -------------------------------------------------------//

//  Copyright Beman Dawes 2010, 2011

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_ENDIAN_CONVERSION_HPP
#define BOOST_ENDIAN_CONVERSION_HPP

#include <boost/detail/endian.hpp>
#include <boost/cstdint.hpp>

//------------------------------------- synopsis ---------------------------------------//

namespace boost
{
namespace endian
{
  // unconditional modifying (i.e. in-place) reverse byte order

  inline void reorder(int16_t& x);
  inline void reorder(int32_t& x);
  inline void reorder(int64_t& x);
  inline void reorder(uint16_t& x);
  inline void reorder(uint32_t& x);
  inline void reorder(uint64_t& x);

  // unconditional non-modifying reverse byte order copy

  inline void reorder(int16_t source, int16_t& target);
  inline void reorder(int32_t source, int32_t& target);
  inline void reorder(int64_t source, int64_t& target);
  inline void reorder(uint16_t source, uint16_t& target);
  inline void reorder(uint32_t source, uint32_t& target);
  inline void reorder(uint64_t source, uint64_t& target);

  // conditional modifying (i.e. in-place) reverse byte order;
  //  no effect if native endianness and indicated endianness are the same

  template <class T> inline void native_to_big(T& x);       
  template <class T> inline void native_to_little(T& x);    
  template <class T> inline void big_to_native(T& x);     
  template <class T> inline void little_to_native(T& x);  

  // non-modifying conditional reverse byte order copy;
  //   copy the source argument to the target argument, converting to or from the
  //   indicated endianness if different than native endianness

  template <class T> inline void native_to_big(T source, T& target);
  template <class T> inline void native_to_little(T source, T& target);
  template <class T> inline void big_to_native(T source, T& target);
  template <class T> inline void little_to_native(T source, T& target);

//----------------------------------- implementation -----------------------------------//
                                                
  inline void reorder(int16_t& x)
  {
    char* rep = reinterpret_cast<char*>(&x);
    char tmp;
    tmp = *rep;
    *rep = *(rep+1);
    *(rep+1) = tmp;
  }

  inline void reorder(int32_t& x)
  {
    char* rep = reinterpret_cast<char*>(&x);
    char tmp;
    tmp = *rep;
    *rep = *(rep+3);
    *(rep+3) = tmp;
    tmp = *(rep+1);
    *(rep+1) = *(rep+2);
    *(rep+2) = tmp;
  }

  inline void reorder(int64_t& x)
  {
    char* rep = reinterpret_cast<char*>(&x);
    char tmp;
    tmp = *rep;
    *rep = *(rep+7);
    *(rep+7) = tmp;
    tmp = *(rep+1);
    *(rep+1) = *(rep+6);
    *(rep+6) = tmp;
    tmp = *(rep+2);
    *(rep+2) = *(rep+5);
    *(rep+5) = tmp;
    tmp = *(rep+3);
    *(rep+3) = *(rep+4);
    *(rep+4) = tmp;
  }

  inline void reorder(uint16_t& x)
  {
    char* rep = reinterpret_cast<char*>(&x);
    char tmp;
    tmp = *rep;
    *rep = *(rep+1);
    *(rep+1) = tmp;
  }

  inline void reorder(uint32_t& x)
  {
    char* rep = reinterpret_cast<char*>(&x);
    char tmp;
    tmp = *rep;
    *rep = *(rep+3);
    *(rep+3) = tmp;
    tmp = *(rep+1);
    *(rep+1) = *(rep+2);
    *(rep+2) = tmp;
  }

  inline void reorder(uint64_t& x)
  {
    char* rep = reinterpret_cast<char*>(&x);
    char tmp;
    tmp = *rep;
    *rep = *(rep+7);
    *(rep+7) = tmp;
    tmp = *(rep+1);
    *(rep+1) = *(rep+6);
    *(rep+6) = tmp;
    tmp = *(rep+2);
    *(rep+2) = *(rep+5);
    *(rep+5) = tmp;
    tmp = *(rep+3);
    *(rep+3) = *(rep+4);
    *(rep+4) = tmp;
  }

  inline void reorder(int16_t source, int16_t& target)
  {
    const char* s (reinterpret_cast<const char*>(&source));
    char * t (reinterpret_cast<char*>(&target) + sizeof(target) - 1);
    *t = *s;
    *--t = *++s;
  }

  inline void reorder(int32_t source, int32_t& target)
  {
    const char* s (reinterpret_cast<const char*>(&source));
    char * t (reinterpret_cast<char*>(&target) + sizeof(target) - 1);
    *t = *s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
  }

  inline void reorder(int64_t source, int64_t& target)
  {
    const char* s (reinterpret_cast<const char*>(&source));
    char * t (reinterpret_cast<char*>(&target) + sizeof(target) - 1);
    *t = *s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
  }

  inline void reorder(uint16_t source, uint16_t& target)
  {
    const char* s (reinterpret_cast<const char*>(&source));
    char * t (reinterpret_cast<char*>(&target) + sizeof(target) - 1);
    *t = *s;
    *--t = *++s;
  }

  inline void reorder(uint32_t source, uint32_t& target)
  {
    const char* s (reinterpret_cast<const char*>(&source));
    char * t (reinterpret_cast<char*>(&target) + sizeof(target) - 1);
    *t = *s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
  }

  inline void reorder(uint64_t source, uint64_t& target)
  {
    const char* s (reinterpret_cast<const char*>(&source));
    char * t (reinterpret_cast<char*>(&target) + sizeof(target) - 1);
    *t = *s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
    *--t = *++s;
  }

#ifdef BOOST_LITTLE_ENDIAN
  template <class T> inline void native_to_big(T& x)  { reorder(x); }
  template <class T> inline void native_to_little(T&) {}
  template <class T> inline void big_to_native(T& x)  { reorder(x); }
  template <class T> inline void little_to_native(T&) {}
  template <class T> inline void native_to_big(T source, T& target) { reorder(source, target); }
  template <class T> inline void native_to_little(T source, T& target) { target = source; }
  template <class T> inline void big_to_native(T source, T& target) { reorder(source, target); }
  template <class T> inline void little_to_native(T source, T& target) { target = source; }
#else
  template <class T> inline void native_to_big(T&)  {}
  template <class T> inline void native_to_little(T& x) { reorder(x); }
  template <class T> inline void big_to_native(T&)  {}
  template <class T> inline void little_to_native(T& x) { reorder(x); }
  template <class T> inline void native_to_big(T native, T& big) { target = source; }
  template <class T> inline void native_to_little(T native, T& little) { reorder(source, target); }
  template <class T> inline void big_to_native(T big, T& native) { target = source; }
  template <class T> inline void little_to_native(T little, T& native) { reorder(source, target); }
#endif

}  // namespace endian
}  // namespace boost

#endif // BOOST_ENDIAN_CONVERSION_HPP
