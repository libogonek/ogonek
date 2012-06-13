//  boost/io/detail/bin_manip.hpp  -----------------------------------------------------//

//  Copyright Beman Dawes 2009, 2011

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_BIN_MANIP_HPP
#define BOOST_BIN_MANIP_HPP

#include <boost/config.hpp>
#include <ostream>
#include <istream>
#include <string>
#include <cstring>  // for strlen

#ifndef BOOST_NO_CWCHAR
# include <cwchar>   // for wcslen
#endif

//  unformatted binary (as opposed to formatted character) input and output manipulator

//  Caution: Use only on streams opened with filemode std::ios_base::binary. Thus
//  unformatted binary I/O should not be with the standard streams (cout, cin, etc.)
//  since they are opened in text mode. Use on text streams may produce incorrect
//  results, such as insertion of unwanted characters or premature end-of-file.
//  For example, on Windows 0x0D would become 0x0D, 0x0A.

namespace boost
{

namespace detail
{
  template <class T>
  struct const_binary_data
  {
    const char* ptr;
    explicit const_binary_data(const T& x) : ptr(reinterpret_cast<const char*>(&x)) {}
  };
  template <class T>
  struct binary_data
  {
    char* ptr;
    explicit binary_data(T& x) : ptr(reinterpret_cast<char*>(&x)) {}
  };
}

template <class T>
inline detail::const_binary_data<T> bin(const T& x)
{
  return detail::const_binary_data<T>(x);
}

template <class T>
inline detail::binary_data<T> bin(T& x)
{
  return detail::binary_data<T>(x);
}

template <class T>
inline std::ostream& operator<<(std::ostream& os, detail::const_binary_data<T> x)
{
  return os.write(x.ptr, sizeof(T));
}

template <class T>
inline std::ostream& operator<<(std::ostream& os, detail::binary_data<T> x)
{
  return os.write(x.ptr, sizeof(T));
}

template <class T>
inline std::istream& operator>>(std::istream& is, detail::binary_data<T> x)
{
  return is.read(x.ptr, sizeof(T));
}

}  // namespace boost

#endif  // BOOST_BIN_MANIP_HPP
