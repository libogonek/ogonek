% The Ogonek Library

# Concepts and types 

## Ranges

The range concepts are borrowed from Boost.Range.

## `ByteOrder`

A type with operations for serializing multi-byte integrals into sequences of
bytes in a particular order. There are two models of this concept:
`little_endian` and `big_endian`.

In the following table `Order` is a model of `ByteOrder`, `u16` is a `uint16_t`
value, `u32` is a `uint32_t` value, `l16` is a `uint16_t` lvalue, `l32` is a
`uint32_t` lvalue, and `it` is an `InputIterator` of bytes.

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
| `Order::unmap(it, l32)` | `InputIterator`       | *Returns*: a `uint32_t` with  |
|                         |                       | four bytes read from `it`.    |
|                         |                       |                               |
|                         |                       | *Effects*: the value of `l32` |
|                         |                       | consists of four bytes read   |
|                         |                       | from `it` in order.           |
+-------------------------+-----------------------+-------------------------------+

Table: Requirements for `ByteOrder`

## `byte`

The `byte` type is an 8-bit integral type capable of holding values in the range
[00, FF]. It is an alias of `uint8_t`.

## `codepoint`

The `codepoint` type is an integral type capable of holding any Unicode
codepoint (integers in the range [0, 10FFFF]). It is an alias of `char32_t`.

## `CodeUnit`

An integral type capable of holding the values used by a particular encoding.

## `ValidationCallback`

A function object `f` for which the following expression is valid and returns a
sub range of `source`:

    f(reason, source, out)

where:

 - `reason` is a `validation_result`;
 - `source` is a range of code units;
 - `out` is an output iterator of codepoints;

## `EncodingForm`

An encoder/decoder that converts between `codepoint`s and code units. At least
three models of `EncodingForm` are provided: `utf8`, `utf16`, and `utf32`.

In the following table, `E` is a model of `EncodingForm`, `s` is an instance of
`E::state`, `u` is a `codepoint`, `v` is a `codepoint` lvalue, `cr` is a range
of `E::code_unit`s, `ur` is a range of `codepoint`s, `co` is an
`OutputIterator` on `E::code_unit`s, `uo` is an `OutputIterator` on
`codepoints`, and `call` is a `ValidationCallback`.

+---------------------------+----------------------+-------------------------+
| Expression                | Return type          | Semantics               |
+===========================+======================+=========================+
| `E::code_unit`            | `typename CodeUnit`  | type of a code unit     |
+---------------------------+----------------------+-------------------------+
| `E::is_fixed_width`       | `constexpr bool`     | true iff is fixed width |
+---------------------------+----------------------+-------------------------+
| `E::max_width`            | `constexpr size_t`   | maximum width in code   |
|                           |                      | units                   |
+---------------------------+----------------------+-------------------------+
| `E::self_synchronizing`   | `constexpr bool`     | true iff the start of a |
|                           |                      | multi-unit sequence can |
|                           |                      | be found in O(1) time   |
+---------------------------+----------------------+-------------------------+
| `E::state`                | `typename Trivial`   | type of the state (an   |
|                           |                      | empty type iff `E` is   |
|                           |                      | stateless)              |
+---------------------------+----------------------+-------------------------+
| `E::encode(ur, co)`       | `Range`              | encodes codepoints      |
+---------------------------+----------------------+-------------------------+
| `E::decode(cr, uo)`       | `Range`              | decodes codepoints      |
+---------------------------+----------------------+-------------------------+
| `E::decode(cr, uo, call)` | `Range`              | decodes codepoints with |
|                           |                      | validation              |
+---------------------------+----------------------+-------------------------+
| `E::encode_one(u, co)`    |                      | encodes one codepoint   |
|                           |                      | (only available if `E`  |
|                           |                      | is stateless)           |
+---------------------------+----------------------+-------------------------+
| `E::decode_one(cr, v)`    | `Range`              | decodes one codepoint   |
|                           |                      | (only available if `E`  |
|                           |                      | is stateless)           |
+---------------------------+----------------------+-------------------------+
| `E::validate_one(cr)`     | `validation_result`  | validates one codepoint |
|                           |                      | (only available if `E`  |
|                           |                      | is stateless)           |
+---------------------------+----------------------+-------------------------+
| `E::encode_one(u, co, s)` |                      | encodes one codepoint   |
+---------------------------+----------------------+-------------------------+
| `E::decode_one(cr, v, s)` | `Range`              | decodes one codepoint   |
+---------------------------+----------------------+-------------------------+
| `E::validate_one(cr, s)`  | `validation_result`  | validates one codepoint |
+---------------------------+----------------------+-------------------------+

Table: Requirements for `EncodingForm`

## `EncodingScheme`

An encoder/decoder that converts between `codepoint`s and bytes. Some
`EncodingForm`s, like UTF-8, are naturally `EncodingScheme`s because their code
units are bytes. Others can be created by putting together an `EncodingForm` and
a `ByteOrder`. Five models of `EncodingScheme` are provided: `utf8`, `utf16be`,
`utf16le`, `utf32be`, and `utf32le`.

In the following table, `E` is a model of `EncodingForm`, `s` is an instance of
`E::state`, `u` is a `codepoint`, `v` is a `codepoint` lvalue, `br` is a range
of bytes, `ur` is a range of `codepoint`s, `bo` is an `OutputIterator` of
bytes, `uo` is an `OutputIterator` of `codepoints`, and `call` is a
`ValidationCallback`.

+---------------------------+--------------------+-------------------------+
| Expression                | Return type        | Semantics               |
+===========================+====================+=========================+
| `E::is_fixed_width`       | `constexpr bool`   | true iff is fixed width |
+---------------------------+--------------------+-------------------------+
| `E::max_width`            | `constexpr size_t` | maximum width in bytes  |
+---------------------------+--------------------+-------------------------+
| `E::state`                | `typename Trivial` | type of the state (an   |
|                           |                    | empty type iff `E` is   |
|                           |                    | stateless)              |
+---------------------------+--------------------+-------------------------+
| `E::encode(ur, bo)`       |                    | encodes codepoints      |
+---------------------------+--------------------+-------------------------+
| `E::decode(br, uo, call)` | `Range`            | decodes codepoints      |
+---------------------------+--------------------+-------------------------+
| `E::encode_one(u, bo)`    |                    | encodes one codepoint   |
|                           |                    | (only available if `E`  |
|                           |                    | is stateless)           |
+---------------------------+--------------------+-------------------------+
| `E::decode_one(br, v)`    | `Range`            | decodes one codepoint   |
|                           |                    | (only available if `E`  |
|                           |                    | is stateless)           |
+---------------------------+--------------------+-------------------------+
| `E::encode_one(u, bo, s)` |                    | encodes one codepoint   |
+---------------------------+--------------------+-------------------------+
| `E::decode_one(br, v, s)` | `Range`            | decodes one codepoint   |
+---------------------------+--------------------+-------------------------+

Table: Requirements for `EncodingScheme`

## `Locale`

Ouch.

## `basic_text` and `text`



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

