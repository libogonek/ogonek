---
layout: default
title: Encodings
---

### Baseic encoding/decoding functions

#### `encode`

This function takes an encoding form/scheme as a template parameter, a sequence
of code points and an error handler and returns a range that when iterated
produces the corresponding code units for the input sequence according to the
encoding specified. Invalid input is processed according to the error handler
given.

*Example*:
{% highlight cpp %}
auto encoded = make_vector(ogonek::encode<ogonek::utf8>(decoded, ogonek::discard_errors));
{% endhighlight %}

---

#### `decode`

This function takes an encoding form/scheme as a template parameter, a sequence
of code units and an error handler and returns a range that when iterated
produces the corresponding code points for the input sequence according to the
encoding specified. Invalid input is processed according to the error handler
given.

*Example*:
{% highlight cpp %}
auto decoded = make_vector(ogonek::decode<ogonek::utf8>(encoded, ogonek::discard_errors));
{% endhighlight %}

---

### Encoding forms

Each encoding form specifies how a code point is expressed as a sequence of one
or more code units. In ogonek these are realised as classes with static
functions for encoding and decoding.

Ogonek includes the following encoding forms:

- [UTF-8] as `utf8` in `<ogonek/encoding/utf8.h++>`;
- [UTF-16] as `utf16` in `<ogonek/encoding/utf16.h++>`;
- [UTF-32] as `utf32` in `<ogonek/encoding/utf32.h++>`;
- [ASCII] as `ascii` in `<ogonek/encoding/ascii.h++>`;
- All [ISO-8859-n] encodings, as `iso8859_n` in
  `<ogonek/encoding/iso8859_n.h++>` (replace *n* as appropriate);
- [CP-1252] as `windows1252` in `<ogonek/encoding/windows1252.h++>`;

Most users don't need to deal directly with an encoding form's class members and
can treat them as opaque tag types. The higher-level parts of ogonek, like
[`text`][text], are preferred for most purposes.

---

Each encoding form shall provide the following members.

#### `code_unit`

The type of the code unit that the encoding form uses. This must be an integral
type.

*Example*:
{% highlight cpp %}
std::vector<ogonek::utf8::code_unit> utf8_data;
{% endhighlight %}

---

#### `is_fixed_width`

A `bool` constant expression with value `true` if all code points are encoded
using the same number of code units; or `false` otherwise.

*Example*:
{% highlight cpp %}
static_assert(!ogonek::utf8::is_fixed_width,
              "UTF-8 does not have fixed width");
{% endhighlight %}

---

#### `max_width`

A `std::size_t` constant expression with value equal to the maximum number of
code units required to encode any Unicode code point.

*Example*:
{% highlight cpp %}
static_assert(ogonek::utf16::max_width == 2,
              "UTF-16 uses at most 2 code units per code point");
{% endhighlight %}

---

#### `is_self_synchronising`

A `bool` constant expression with value `true` if the start of a multiple code
unit sequence can be found in constant time; or `false` otherwise.

*Example*:
{% highlight cpp %}
static_assert(ogonek::utf8::is_self_synchronising,
              "UTF-8 is self-synchronising");
{% endhighlight %}

---

#### `state`

A trivial type that can hold any state needed to encode or decode a sequence
with this encoding form. Value-initialising an instance of this type shall
produce the initial state for any conversion.

This shall be an empty type if the encoding form is stateless.

*Example*:
{% highlight cpp %}
static_assert(std::is_empty<ogonek::utf8::state>(),
              "UTF-8 is stateless");
{% endhighlight %}

#### `encode_one`

A static function template that accepts as arguments a code point, an lvalue
reference to the current encoding state, and a validation strategy, and returns
the sequence of code units corresponding to the given code point. The sequence
returned is materialised. It shall update the encoding state according to the
codepoint that was encoded. Invalid data is handled according to the validation
strategy given. 

*Example*:
{% highlight cpp %}
ogonek::utf8::state s{};
auto encoded = ogonek::utf8::encode_one(u, s, ogonek::discard_errors);
{% endhighlight %}

---

#### `decode_one`

A static function template that accepts as arguments any sequence of code units,
an lvalue reference to a `code_point`, an lvalue reference to the current
encoding state, and a validation strategy. This function shall decode the first
code point from the given sequence, store that result in the second argument,
and update the encoding state accordingly. It shall return the remaining
sequence of code units, without the code units that where decoded. Invalid data
is handled according to the validation strategy given.

*Example*:
{% highlight cpp %}
ogonek::utf8::state s{};
ogonek::code_point result;
auto remaining = ogonek::utf8::decode_one(source, result, s, ogonek::discard_errors);
{% endhighlight %}

<!-- TODO: flush state -->

---

#### `replacement_character`

This member is optional if the encoding form can use U+FFFD
&#640;&#7431;&#7448;&#671;&#7424;&#7428;&#7431;&#7437;&#7431;&#628;&#7451;
&#7428;&#668;&#7424;&#640;&#7424;&#7428;&#7451;&#7431;&#640; as a replacement
character. If present, it shall be a `code_point` constant expression and its
value shall be an adequate replacement character for the encoding form.

*Example*:
{% highlight cpp %}
static_assert(ogonek::ascii::replacement_character == '\x1A',
              "ASCII uses a custom replacement character");
{% endhighlight %}

---

### Encoding schemes

Encoding schemes are similar to encoding forms, but they specify ways to
serialise code points into bytes instead of some particular code unit. Encoding
schemes shall provide the same interface as encoding forms, but the `code_unit`
nested type shall have size 1.

Ogonek includes the following encoding schemes.

- [UTF-16BE] as `utf16be` in `<ogonek/encoding/utf16be.h++>`;
- [UTF-16LE] as `utf16le` in `<ogonek/encoding/utf16le.h++>`;
- [UTF-32BE] as `utf32be` in `<ogonek/encoding/utf32be.h++>`;
- [UTF-32LE] as `utf32le` in `<ogonek/encoding/utf32le.h++>`.

In addition, any encoding form with a byte-sized code unit can work as an
encoding scheme (this includes `ogonek::utf8`).

#### `encoding_scheme`

The class template `encoding_scheme` can be used to define encoding schemes by
combining an encoding form with a byte order. The two byte orders supported are
represented by the types `big_endian` and `little_endian`. These three types are
in the header `<ogonek/encoding/encoding_scheme.h++>`.

*Example*:
{% highlight cpp %}
using utf16be = ogonek::encoding_scheme<ogonek::utf16, ogonek::big_endian>;
{% endhighlight %}

---

### See Also

- [Text][text]
- [Error handling][error]

 [text]: text.html
 [error]: error.html
 [UTF-8]: http://en.wikipedia.org/wiki/UTF-8
 [UTF-16]: http://en.wikipedia.org/wiki/UTF-16
 [UTF-32]: http://en.wikipedia.org/wiki/UTF-32
 [ASCII]: http://en.wikipedia.org/wiki/ASCII
 [ISO-8859]: http://en.wikipedia.org/wiki/ISO/IEC-8859
 [CP-1252]: http://en.wikipedia.org/wiki/Windows-1252
 [GB18030]: http://en.wikipedia.org/wiki/GB18030
 [UTF-16BE]: http://en.wikipedia.org/wiki/UTF-16BE
 [UTF-16LE]: http://en.wikipedia.org/wiki/UTF-16LE
 [UTF-32BE]: http://en.wikipedia.org/wiki/UTF-32BE
 [UTF-32LE]: http://en.wikipedia.org/wiki/UTF-32LE
