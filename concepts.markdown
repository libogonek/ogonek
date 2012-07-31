% The Ogonek Library

# Concepts and types 

## Ranges

The range concepts are borrowed from Boost.Range.

## `byte`

The `byte` type is an 8-bit integral type capable of holding values in the range
[00, FF]. It is an alias of `uint8_t`.

## `codepoint`

The `codepoint` type is an integral type capable of holding any Unicode
codepoint (integers in the range [0, 10FFFF]). It is an alias of `char32_t`.

## `CodeUnit`

An integral type capable of holding the values used by a particular encoding.

## `ByteOrder`

A type with operations for serializing multi-byte integrals into sequences of
bytes in a particular order. There are two models of this concept:
`little_endian` and `big_endian`.

The expressions in the following table must be valid and have the indicated
semantics. In the table `Order` is a model of `ByteOrder`, `u16` is a
`uint16_t` value, `u32` is a `uint32_t` value, `l16` is a `uint16_t` lvalue,
`l32` is a `uint32_t` lvalue, and `it` is an `InputIterator` of bytes.

+-------------------------+-----------------------+-------------------------------+
| Expression              | Return type           | Semantics                     |
+=========================+=======================+===============================+
| `Order::map(u16)`       | `std::array<byte, 2>` | *Returns*: an array with the  |
|                         |                       | bytes of `u16` in order.      |
+-------------------------+-----------------------+-------------------------------+
| `Order::map(u32)`       | `std::array<byte, 4>` | *Returns*: an array with the  |
|                         |                       | bytes of `u32` in order.      |
+-------------------------+-----------------------+-------------------------------+
| `Order::unmap(it, l16)` | `InputIterator`       | *Returns*: `it` advanced      |
|                         |                       | twice.                        |
|                         |                       |                               |
|                         |                       | *Effects*: the value of `l16` |
|                         |                       | consists of two bytes read    |
|                         |                       | from `it` in order.           |
+-------------------------+-----------------------+-------------------------------+
| `Order::unmap(it, l32)` | `InputIterator`       | *Returns*: `it` advanced four |
|                         |                       | times.                        |
|                         |                       |                               |
|                         |                       | *Effects*: the value of `l32` |
|                         |                       | consists of four bytes read   |
|                         |                       | from `it` in order.           |
+-------------------------+-----------------------+-------------------------------+

Table: Requirements for `ByteOrder`

## `ValidationCallback`

A callable object used to handle validation errors. Three instances of models
of this concept are provided:

 - `ignore_errors`: any invalid code units or bytes are ignored;
 - `use_replacement_character`: any invalid code units or bytes are replaced by
   U+FFFD;
 - `throw_validation_exception`: any invalid code units or bytes results in a
   `validation_exception` begin thrown.

A validation callback is invoked with three arguments:

 - a `validation_result` that explains the nature of the error;
 - a `boost::sub_range<Range>` where `Range` is a range of code units. This
   sub-range starts at the invalid element of the input;
 - a `codepoint` lvalue that the callback can use to replace part of the
   invalid input.

The callback shall return a `boost::sub_range<Range>` that starts at the first
element of the input following the error.

## `EncodingForm`

An encoder/decoder that converts between `codepoint`s and code units. At least
three models of `EncodingForm` are provided: `utf8`, `utf16`, and `utf32`.

The expressions in the following table must be valid and have the indicated
semantics. In the table, `E` is a model of `EncodingForm`, `s` is an instance
of `E::state`, `u` is a `codepoint`, `v` is a `codepoint` lvalue, `cr` is a
range of `E::code_unit`s, `ur` is a range of `codepoint`s, `co` is an
`OutputIterator` on `E::code_unit`s, `uo` is an `OutputIterator` on
`codepoints`, and `val` is a `ValidationCallback`. All returned ranges are
lazily evaluated.

+--------------------------------+-----------------------+-------------------------+
| Expression                     | Return type           | Semantics               |
+================================+=======================+=========================+
| `E::code_unit`                 | `typename CodeUnit`   | type of a code unit     |
+--------------------------------+-----------------------+-------------------------+
| `E::is_fixed_width`            | `constexpr bool`      | true iff is fixed width |
+--------------------------------+-----------------------+-------------------------+
| `E::max_width`                 | `constexpr size_t`    | maximum width in code   |
|                                |                       | units                   |
+--------------------------------+-----------------------+-------------------------+
| `E::self_synchronizing`        | `constexpr bool`      | true iff the start of a |
|                                |                       | multi-unit sequence can |
|                                |                       | be found in O(1) time   |
+--------------------------------+-----------------------+-------------------------+
| `E::state`                     | `typename Trivial`    | type of the state (an   |
|                                |                       | empty type iff `E` is   |
|                                |                       | stateless)              |
+--------------------------------+-----------------------+-------------------------+
| `E::encode(ur)`                | `Range` of code units | encodes codepoints      |
+--------------------------------+-----------------------+-------------------------+
| `E::decode(cr, val)`           | `Range` of codepoints | decodes codepoints with |
|                                |                       | validation              |
+--------------------------------+-----------------------+-------------------------+
| `E::decode(cr)`                | `Range` of codepoints | decodes codepoints; the |
|                                |                       | code units are assumed  |
|                                |                       | valid                   |
+--------------------------------+-----------------------+-------------------------+
| `E::encode_one(u, s)`          | `Range` of code units | encodes one codepoint   |
+--------------------------------+-----------------------+-------------------------+
| `E::decode_one(cr, v, s, val)` | `Range` of code units | decodes one codepoint   |
|                                |                       | with validation         |
+--------------------------------+-----------------------+-------------------------+
| `E::decode_one(cr, v, s)`      | `Range` of code units | decodes one codepoint;  |
|                                |                       | the code units are      |
|                                |                       | assumed valid;          |
+--------------------------------+-----------------------+-------------------------+

Table: Requirements for `EncodingForm`

## `EncodingScheme`

An encoder/decoder that converts between `codepoint`s and bytes. Some
`EncodingForm`s, like UTF-8, are naturally `EncodingScheme`s because their code
units are bytes. Others can be created by putting together an `EncodingForm` and
a `ByteOrder`. Five models of `EncodingScheme` are provided: `utf8`, `utf16be`,
`utf16le`, `utf32be`, and `utf32le`.

The expressions in the following table must be valid and have the indicated
semantics. In the table, `E` is a model of `EncodingForm`, `s` is an instance
of `E::state`, `u` is a `codepoint`, `v` is a `codepoint` lvalue, `br` is a
range of bytes, `ur` is a range of `codepoint`s, `bo` is an `OutputIterator` of
bytes, `uo` is an `OutputIterator` of `codepoints`, and `val` is a
`ValidationCallback`. All returned ranges are lazily evaluated.

+--------------------------------+-----------------------+-------------------------+
| Expression                     | Return type           | Semantics               |
+================================+=======================+=========================+
| `E::is_fixed_width`            | `constexpr bool`      | true iff is fixed width |
+--------------------------------+-----------------------+-------------------------+
| `E::max_width`                 | `constexpr size_t`    | maximum width in bytes  |
+--------------------------------+-----------------------+-------------------------+
| `E::state`                     | `typename Trivial`    | type of the state (an   |
|                                |                       | empty type iff `E` is   |
|                                |                       | stateless)              |
+--------------------------------+-----------------------+-------------------------+
| `E::encode(ur)`                | `Range` of bytes      | encodes codepoints      |
+--------------------------------+-----------------------+-------------------------+
| `E::decode(br, val)`           | `Range` of codepoints | decodes codepoints      |
+--------------------------------+-----------------------+-------------------------+
| `E::decode(br)`                | `Range` of codepoints | decodes codepoints      |
+--------------------------------+-----------------------+-------------------------+
| `E::encode_one(u, s)`          | `Range` of bytes      | encodes one codepoint   |
+--------------------------------+-----------------------+-------------------------+
| `E::decode_one(br, v, s, val)` | `Range` of bytes      | decodes one codepoint   |
+--------------------------------+-----------------------+-------------------------+
| `E::decode_one(br, v, s)`      | `Range` of bytes      | decodes one codepoint   |
+--------------------------------+-----------------------+-------------------------+

Table: Requirements for `EncodingScheme`

## `Locale`

Ouch.

## `basic_text` and `text`

See http://gist.io/3166256.

# Unicode algorithms

## Text segmentation

The following template functions are implement the standard Unicode text
segmentation algorithms. All returned ranges are evaluated lazily.

    template <typename Range>
    grapheme_cluster_range<Range> grapheme_clusters(Range const&);
    template <typename Range>
    word_range<Range> words(Range const&);
    template <typename CodepointRange>
    sentence_range<Range> sentences(Range const&);
    template <typename Range>
    linebreak_opportunity_range<Range> linebreak_opportunities(Range const&);

The resulting ranges are either forward or bidirectional ranges, depending on
the underlying range's capabilities.

