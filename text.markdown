---
layout: default
title: Text
---

Several algorithms on ogonek take ranges of code points as input. Some classes
in the standard libary can be used as ranges of code points: containers like
`std::vector<ogonek::code_point>` or `std::u32string`. However those aren't
always useful since they don't allow the use of other encodings for storing the
data. Ogonek provides a generic class template named `text` to create ranges of
codepoints with various underlying encodings.

### Invariants

All `text` classes maintain the invariant of holding a stream that is valid
according to the respective encoding.

### Custom encoding

The interface of `text` exposes iteration over code points for use in the
algorithms, but the data is stored using some known encoding. This way one can
use the algorithms with data in any encoding.

The encoding can be customized by changing the first template parameter. Being
part of the type helps the compiler ensures the right conversions occur at the
right places.

*Example*:
{% highlight cpp %}
using utf8_text = ogonek::text<ogonek::utf8>;
using utf16_text = ogonek::text<ogonek::utf16>;
{% endhighlight %}

### Custom storage

The class also allows customization of the underlying storage, by means of the
second template parameter. Any container can be used to store the data. The
default storage used is a `std::basic_string` instantiated with the encoding's
code unit.

*Example*:
{% highlight cpp %}
using utf8_deque = ogonek::text<ogonek::utf8, std::deque<ogonek::utf8::code_unit>>;
using latin1_vector = ogonek::text<ogonek::latin1, std::vector<char>>;
{% endhighlight %}

### Interop aliases

There are two aliases defined for easy interop: `posix_text` and `windows_text`.
The former uses UTF-8 and `std::string`, while the latter uses UTF-16 and
`std::wstring`.

*Example*:
{% highlight cpp %}
ogonek::windows_text message { u"Hello World!" };
ogonek::windows_text caption { u"Ogonek" };
::MessageBox(hwnd, message.storage().data(), caption.storage().data(), MB_OK);
{% endhighlight %}

There is also a `native_text` alias that is equal to `windows_text` if
`OGONEK_WINDOWS` is defined, or to `posix_text` if `OGONEK_POSIX` is defined
instead.

### Constructors

`text` instances can be constructed from a variety of sources.

Blah blah incomplete.

### Iteration

`text` provides basic iteration support as a sequence of code points. As do the
standard containers, it provides `iterator` and `const_iterator` nested types,
as well as `begin()` and `end()` members. This is useful if you need to
implement any algorithms that don't depend on the encoding.

Such a range interface allows for creating `text` instances from `text` with
different encodings, since any range of code points can be used for construction.

### Storage access

The underlying code unit storage of a `text` instance can be accessed for
interoperation purposes.

The `storage()` member function returns a read-only view of the underlying
storage (as `const&`).

The `move_storage()` member function can be used to mutate the underlying
storage directly without violating the validity invariant. The function moves
the underlying storage and returns it by value. After a call to this function
the instance of `text` is now empty, and the returned value can be mutated at
will. To apply the changes afterwards, the mutated storage can simply be
moved back into the `text` instance, and it will re-validated.

### Equality

`text::operator==` and `text::operator!=` test whether two instances of `text`
are canonically equivalent or not. The Unicode standard requires that a
conformant process treat any two canonically equivalent strings the same way.

Instances of text with different template arguments can be compared with these
operators.

