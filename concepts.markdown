% The Ogonek Library

# Concepts and types 

## `ByteOrder`

A type with operations for serializing multi-byte integrals into sequences of
bytes in a particular order. There are two models of this concept:
`little_endian` and `big_endian`.

In the following table `Order` is a model of `ByteOrder`, `u16` is a `uint16_t`
value, `u32` is a `uint32_t` value, `it` is an `InputIterator` of bytes.

+-----------------------+-----------------------+------------------------------+
| Expression            | Return type           | Semantics                    |
+=======================+=======================+==============================+
| `Order::map(u16)`     | `std::array<byte, 2>` | *Returns*: an array with the |
|                       |                       | bytes of `u16` in order.     |
+-----------------------+-----------------------+------------------------------+
| `Order::map(u16)`     | `std::array<byte, 4>` | *Returns*: an array with the |
|                       |                       | bytes of `u32` in order      |
+-----------------------+-----------------------+------------------------------+
| `Order::unmap<2>(it)` | `uint16_t`            | *Returns*: a `uint16_t` with |
|                       |                       | two bytes read from `it`.    |
+-----------------------+-----------------------+------------------------------+
| `Order::unmap<4>(it)` | `uint32_t`            | *Returns*: a `uint32_t` with |
|                       |                       | four bytes read from `it`.   |
+-----------------------+-----------------------+------------------------------+

Table: Requirements for `ByteOrder`

## `byte`

The `byte` type is an 8-bit integral type capable of holding values in the range
[00, FF]. It is an alias of `uint8_t`.

## `codepoint`

The `codepoint` type is an integral type capable of holding any Unicode
codepoint (integers in the range [0, 10FFFF]). It is an alias of `char32_t`.

## `CodeUnit`

An integral type capable of holding the values used by a particular encoding.

## `EncodingForm`

An encoder/decoder that converts between `codepoint`s and code units. At least
three models of `EncodingForm` are provided: `utf8`, `utf16`, and `utf32`.

In the following table, `E` is a model of `EncodingForm`, `s` is an instance of
`E::state`, `u` is a `codepoint`, [`cb`, `ce`) is a range of `InputIterator`s of
`E::code_unit`s, [`ub`, `ue`) is a range of `InputIterators` of `codepoint`s,
`co` is an `OutputIterator` on `E::code_unit`s, and `uo` is an `OutputIterator`
on `codepoints`.

+----------------------------+----------------------+-------------------------+
| Expression                 | Return type          | Semantics               |
+============================+======================+=========================+
| `E::code_unit`             | `typename CodeUnit`  | type of a code unit     |
+----------------------------+----------------------+-------------------------+
| `E::is_fixed_width`        | `constexpr bool`     | true iff is fixed width |
+----------------------------+----------------------+-------------------------+
| `E::max_width`             | `constexpr size_t`   | maximum width in code   |
|                            |                      | units                   |
+----------------------------+----------------------+-------------------------+
| `E::self_synchronizing`    | `constexpr bool`     | true iff the start of a |
|                            |                      | multi-unit sequence can |
|                            |                      | be found in O(1) time   |
+----------------------------+----------------------+-------------------------+
| `E::state`                 | `typename Trivial`   | type of the state (an   |
|                            |                      | empty type iff `E` is   |
|                            |                      | stateless)              |
+----------------------------+----------------------+-------------------------+
| `E::encode(ub, ue, co)`    |                      | encodes codepoints      |
+----------------------------+----------------------+-------------------------+
| `E::decode(cb, ce, uo)`    |                      | decodes codepoints      |
+----------------------------+----------------------+-------------------------+
| `E::encode_one(u, co)`     |                      | encodes one codepoint   |
|                            |                      | (only available if `E`  |
|                            |                      | is stateless)           |
+----------------------------+----------------------+-------------------------+
| `E::decode_one(cb, ce)`    | `codepoint`          | decodes one codepoint   |
|                            |                      | (only available if `E`  |
|                            |                      | is stateless)           |
+----------------------------+----------------------+-------------------------+
| `E::encode_one(u, co, s)`  |                      | encodes one codepoint   |
+----------------------------+----------------------+-------------------------+
| `E::decode_one(cb, ce, s)` | `codepoint`          | decodes one codepoint   |
+----------------------------+----------------------+-------------------------+

Table: Requirements for `EncodingForm`

## `EncodingScheme`

An encoder/decoder that converts between `codepoint`s and bytes. Some
`EncodingForm`s, like UTF-8, are naturally `EncodingScheme`s because their code
units are bytes. Others can be created by putting together an `EncodingForm` and
a `ByteOrder`. Five models of `EncodingScheme` are provided: `utf8`, `utf16be`,
`utf16le`, `utf32be`, and `utf32le`.

In the following table, `E` is a model of `EncodingForm`, `s` is an instance of
`E::state`, `u` is a `codepoint`, [`bb`, `be`) is a range of `InputIterator`s of
bytes, [`ub`, `ue`) is a range of `InputIterators` of `codepoint`s, `bo` is an
`OutputIterator` of bytes, and `uo` is an `OutputIterator` of `codepoints`.

+----------------------------+--------------------+-------------------------+
| Expression                 | Return type        | Semantics               |
+============================+====================+=========================+
| `E::is_fixed_width`        | `constexpr bool`   | true iff is fixed width |
+----------------------------+--------------------+-------------------------+
| `E::max_width`             | `constexpr size_t` | maximum width in bytes  |
+----------------------------+--------------------+-------------------------+
| `E::state`                 | `typename Trivial` | type of the state (an   |
|                            |                    | empty type iff `E` is   |
|                            |                    | stateless)              |
+----------------------------+--------------------+-------------------------+
| `E::encode(ub, ue, bo)`    |                    | encodes codepoints      |
+----------------------------+--------------------+-------------------------+
| `E::decode(bb, be, uo)`    |                    | decodes codepoints      |
+----------------------------+--------------------+-------------------------+
| `E::encode_one(u, bo)`     |                    | encodes one codepoint   |
|                            |                    | (only available if `E`  |
|                            |                    | is stateless)           |
+----------------------------+--------------------+-------------------------+
| `E::decode_one(bb, be)`    | `codepoint`        | decodes one codepoint   |
|                            |                    | (only available if `E`  |
|                            |                    | is stateless)           |
+----------------------------+--------------------+-------------------------+
| `E::encode_one(u, bo, s)`  |                    | encodes one codepoint   |
+----------------------------+--------------------+-------------------------+
| `E::decode_one(bb, be, s)` | `codepoint`        | decodes one codepoint   |
+----------------------------+--------------------+-------------------------+

Table: Requirements for `EncodingScheme`

## `codepoint_iterator`

An iterator adaptor that decodes a sequence of code units. It's a template with
two parameters: encoding form and underlying iterator over code units.

These are at least forward iterators, but depending on the underlying encoding
and iterator can have more capabilities:

- if the encoding is self synchronizing, the iterator is bidirectional if
  the underlying iterator is bidirectional;
- if the encoding has fixed width, the iterators are random-access if the
  underlying iterators are random-access.

## `Locale`

Ouch.

# Unicode algorithms

## Text segmentation

    template <typename Range>
    codepoint_range<Range> grapheme_clusters(Range);
    template <typename Range>
    grapheme_cluster_range<Range> grapheme_clusters(Range);
    template <typename Range>
    word_range<Range> words(Range);
    template <typename CodepointRange>
    sentence_range<Range> sentences(Range);
    template <typename Range>
    linebreak_opportunity_range<Range> linebreak_opportunities(Range);

The resulting ranges are either forward or bidirectional ranges, depending on
the underlying range's capabilities.

