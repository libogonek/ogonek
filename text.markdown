---
layout: default
title: Text
---

Several algorithms on ogonek take ranges of code points as input. Some classes
in the standard library can be used as ranges of code points: containers like
`std::vector<ogonek::code_point>` or `std::u32string`. However those aren't
always useful since they don't allow the use of other encodings for storing the
data. Ogonek provides a generic class template named `text` to create ranges of
codepoints with various underlying encodings.

{% highlight cpp %}
template <typename Encoding,
          typename Container = std::basic_string<typename Encoding::code_unit>>
class text;
{% endhighlight %}

*Requires*: `Encoding::code_unit` shall be convertible to
`Container::value_type` and vice-versa.

`text` classes are basically wrappers that tag a container with an encoding.
This allows the compiler to prevent certain mistakes like passing data in a
certain encoding to functions expecting another.

### Invariants

All `text` classes maintain the invariant of holding a stream that is valid
according to the respective encoding.

### Custom encoding

The interface of `text` exposes iteration over code points for use in the
algorithms, but the data is stored using some known encoding. This way one can
use the algorithms with data in any encoding.

The [encoding] can be customized by changing the first template parameter. Being
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
code unit. This means that by default `text` instances use null-terminated
storage.

*Example*:
{% highlight cpp %}
using utf8_deque = ogonek::text<ogonek::utf8, std::deque<ogonek::utf8::code_unit>>;
using latin1_vector = ogonek::text<ogonek::latin1, std::vector<char>>;
{% endhighlight %}

In order to be usable as custom storage, a type must fulfill the standard
requirements for [sequence containers].

 [sequence containers]: http://en.cppreference.com/w/cpp/concept/SequenceContainer

### Interop aliases

There are two aliases defined for easy interop: `posix_text` and `windows_text`.
The former uses UTF-8 and `std::string`, while the latter uses UTF-16 and
`std::wstring`.

*Example*:
{% highlight cpp %}
ogonek::windows_text message { u"Hello World!" };
ogonek::windows_text title { u"Ogonek" };
::MessageBox(hwnd, message.storage().data(), title.storage().data(), MB_OK);
{% endhighlight %}

There is also a `native_text` alias that is equal to `windows_text` if
`OGONEK_WINDOWS` is defined, or to `posix_text` if `OGONEK_POSIX` is defined
instead.

### Construction and assignment

Instances of `text` can be constructed from a pointer to a `char32_t`
null-terminated string, from a range of codepoints, or from an instance of the
underlying container.

{% highlight cpp %}
text();
{% endhighlight %}

*Requires*: `Container` is default-constructible.

*Effects*: Initialises an instance of `text` with default-constructed storage
\[*Note*: the intent is that this results an empty string &mdash; *end note*].

---

{% highlight cpp %}
text(text const& that); // (1)
text& operator=(text const& that); // (2)
{% endhighlight %}

*Requires*: `Container` is copyable.

*Effects*: (1) Initialises an instance of `text` with a copy of the underlying
storage of `that`; (2) copy-assigns the underlying storage of `that` into this
instance's underlying storage. No validation is performed in either case.

{% highlight cpp %}
text(text&& that); // 1
text& operator=(text&& that); // 2
{% endhighlight %}

*Requires*: `Container` is movable.

*Effects*: (1) Initialises an instance of `text` by moving the underlying
storage of `that`; (2) move-assigns the underlying storage of `that` into this
instance's underlying storage. No validation is performed in either case.

---

{% highlight cpp %}
text(code_point const* str); // 1
template <typename Validation>
text(code_point const* str, Validation policy); // 2

text& operator=(code_point const* str); // 3
void assign(code_point const* str); // 4
template <typename Validation>
void assign(code_point const* str, Validation policy); // 5
{% endhighlight %}

*Requires*: `str` points to a null-terminated string of code points and `policy`
is a [validation policy object][validation].

*Effects*: (1-2) Initialises an instance of `text` by encoding the given code
points (not including the null-terminator) into the underlying storage,
validating with, respectively, `throw_validation_error` or `policy`;
(3-5) like (1-2) but assign to the current instance's storage instead.

---

{% highlight cpp %}
template <typename CodepointRange>
text(CodepointRange const& range); // 1
template <typename CodepointRange, typename Validation>
text(CodepointRange const& range, Validation policy); // 2

template <typename CodepointRange>
text& operator=(CodepointRange const& str); // 3
template <typename CodepointRange>
void assign(CodepointRange const& str); // 4
template <typename CodepointRange, typename Validation>
void assign(CodepointRange const& str, Validation policy); // 5
{% endhighlight %}

*Requires*: `range` is a range of code points and `policy` is a [validation
policy object][validation].

*Effects*: (1-2) Initialises an instance of `text` by encoding the given code
points (not including the null-terminator) into the underlying storage,
validating with, respectively, `throw_validation_error` or `policy`; (3-5)
like (1-2) but assign to the current instance's storage instead.

---

{% highlight cpp %}
text(Container const& container); // 1
text(Container&& container); // 1
{% endhighlight %}

### Iteration

`text` provides basic iteration support as a sequence of code points. As do the
standard containers, it provides `iterator` and `const_iterator` nested types,
as well as `begin()` and `end()` members. This is useful to implement any
algorithms that don't depend on the encoding, like most Unicode algorithms.
There is no reason for stuff.

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

### See Also

- [Validation][validation]
- [Encoding][encoding]

 [validation]: validation.html
 [encoding]: encoding.html

