% Concepts and types in the `ogonek` library

# `Range`

The `Range` concept is borrowed from Boost.Range.

# `ByteOrder`

A type with operations for serializing multi-byte integrals into sequences of
bytes in a particular order. There are two models of this concept:
`little_endian` and `big_endian`.

In the following table `Order` is a model of `ByteOrder`, `u16` is a `uint16_t`
value, `u32` is a `uint32_t` value, `r` is a `SinglePassRange` of bytes.

+----------------------+---------------------+--------------------------------+
| Expression           | Return type         | Semantics                      |
+======================+=====================+================================+
| `Order::map(u16)`    | `RandomAccessRange` | a range with the bytes of `u16 |
|                      |                     | in the appropriate order       |
+----------------------+---------------------+--------------------------------+
| `Order::map(u16)`    | `RandomAccessRange` | a range with the bytes of `u32 |
|                      |                     | in the appropriate order       |
+----------------------+---------------------+--------------------------------+
| `Order::unmap<2>(r)` | `uint16_t`          | a `uint16_t` with the bytes    |
|                      |                     | from `r` in the appropriate    |
|                      |                     | order                          |
+----------------------+---------------------+--------------------------------+
| `Order::unmap<4>(r)` | `uint32_t`          | a `uint32_t` with the bytes    |
|                      |                     | from `r` in the appropriate    |
|                      |                     | order                          |
+----------------------+---------------------+--------------------------------+

Table: Requirements for `ByteOrder`

# `byte`

The `byte` type is an 8-bit integral type capable of holding values in the range
[00, FF]. It is an alias of `uint8_t`.

# `codepoint`

The `codepoint` type is an integral type capable of holding any Unicode
codepoint (integers in the range [0, 10FFFF]). It is an alias of `char32_t`.

# `CodeUnit`

An integral type capable of holding the values used by a particular encoding.

# `EncodingForm`

An encoder/decoder that converts between `codepoint`s and code units. At least
three models of `EncodingForm` are provided: `utf8`, `utf16`, and `utf32`.

In the following table, `E` is a model of `EncodingForm`, `s` is an instance of
`E::state`, `u` is a `codepoint`, `b` is a byte, `cr` is a range of
`E::code_unit`s, `ur` is a range of `codepoint`s, and `co` is an
`OutputIterator` on `E::code_unit`s.

+---------------------------+-----------------------+-------------------------+
| Expression                | Return type           | Semantics               |
+===========================+=======================+=========================+
| `E::code_unit`            | `typename CodeUnit`   | type of a code unit     |
+---------------------------+-----------------------+-------------------------+
| `E::is_fixed_width`       | `constexpr bool`      | true iff is fixed width |
+---------------------------+-----------------------+-------------------------+
| `E::max_width`            | `constexpr size_t`    | maximum width in code   |
|                           |                       | units                   |
+---------------------------+-----------------------+-------------------------+
| `E::self_synchronizing`   | `constexpr bool`      | true iff the start of a |
|                           |                       | multi-unit sequence can |
|                           |                       | be found in O(1) time   |
+---------------------------+-----------------------+-------------------------+
| `E::state`                | `typename Trivial`    | type of the state (an   |
|                           |                       | empty type iff `E` is   |
|                           |                       | stateless)              |
+---------------------------+-----------------------+-------------------------+
| `E::encode(ur)`           | `Range` of code units | encodes codepoints      |
+---------------------------+-----------------------+-------------------------+
| `E::decode(cr)`           | `Range` of codepoints | decodes codepoints      |
+---------------------------+-----------------------+-------------------------+
| `E::encode_one(u, co)`    | `void`                | encodes one codepoint   |
|                           |                       | (only available if `E`  |
|                           |                       | is stateless)           |
+---------------------------+-----------------------+-------------------------+
| `E::decode_one(cr)`       | `codepoint`           | decodes one codepoint   |
|                           |                       | (only available if `E`  |
|                           |                       | is stateless)           |
+---------------------------+-----------------------+-------------------------+
| `E::encode_one(u, co, s)` | `void`                | encodes one codepoint   |
+---------------------------+-----------------------+-------------------------+
| `E::decode_one(cr, s)`    | `codepoint`           | decodes one codepoint   |
+---------------------------+-----------------------+-------------------------+

Table:-Requirements for `EncodingForm`

# `EncodingScheme`

An encoder/decoder that converts between `codepoint`s and bytes. Some
`EncodingForm`s, like UTF-8, are naturally `EncodingScheme`s because their code
units are bytes. Others can be created by putting together an `EncodingForm` and
a `ByteOrder`. Five models of `EncodingScheme` are provided: `utf8`, `utf16be`,
`utf16le`, `utf32be`, and `utf32le`.

In the following table, `E` is a model of `EncodingForm`, `s` is an instance of
`E::state`, `u` is a `codepoint`, `b` is a byte, `br` is a range of bytes, `ur`
is a range of `codepoint`s, `bo` is an `OutputIterator` on bytes.

+---------------------------+-----------------------+-------------------------+
| Expression                | Return type           | Semantics               |
+===========================+=======================+=========================+
| `E::is_fixed_width`       | `constexpr bool`      | true iff is fixed width |
+---------------------------+-----------------------+-------------------------+
| `E::max_width`            | `constexpr size_t`    | maximum width in bytes  |
+---------------------------+-----------------------+-------------------------+
| `E::state`                | `typename Trivial`    | type of the state (an   |
|                           |                       | empty type iff `E` is   |
|                           |                       | stateless)              |
+---------------------------+-----------------------+-------------------------+
| `E::encode(ur)`           | `Range` of bytes      | encodes codepoints      |
+---------------------------+-----------------------+-------------------------+
| `E::decode(br)`           | `Range` of codepoints | decodes codepoints      |
+---------------------------+-----------------------+-------------------------+
| `E::encode_one(u, bo)`    | `void`                | encodes one codepoint   |
|                           |                       | (only available if `E`  |
|                           |                       | is stateless)           |
+---------------------------+-----------------------+-------------------------+
| `E::decode_one(br)`       | `codepoint`           | decodes one codepoint   |
|                           |                       | (only available if `E`  |
|                           |                       | is stateless)           |
+---------------------------+-----------------------+-------------------------+
| `E::encode_one(u, bo, s)` | `void`                | encodes one codepoint   |
+---------------------------+-----------------------+-------------------------+
| `E::decode_one(br, s)`    | `codepoint`           | decodes one codepoint   |
+---------------------------+-----------------------+-------------------------+

Table: Requirements for `EncodingScheme`

# `codepoint_iterator`

An iterator adaptor that decodes a sequence of code units. It's a template with
two parameters: encoding form and underlying iterator over code units.

These are at least forward iterators, but depending on the underlying encoding
and iterator can have more capabilities:

    - if the encoding is self synchronizing, the iterator is bidirectional if
      the underlying iterator is too;
    - if the encoding has fixed width, the iterators are random-access if the
      underlying iterators are too.

# `text`

An ordered sequence of `codepoint`s. The encoding of the underlying storage is
system-dependent: UTF-16 on Windows, UTF-8 on Linux.

    #if WINDOWS
    using native_encoding_form = utf16;
    #elif
    using native_encoding_form = utf8;
    #endif

    template <template <typename...> class Container = std::vector>
    struct basic_text {
    public:
        basic_text() = default;
        basic_text(basic_text const&) = default;
        basic_text(basic_text&&) = default;
        template <typename Range,
                  EnableIf<is_range<Range>>...>
        basic_text(Range&&);
        ~basic_text() = default;

        basic_text& operator=(basic_text const&) = default;
        basic_text& operator=(basic_text&&) = default;
        template <typename Range,
                  EnableIf<is_range<Range>>...>
        basic_text& operator=(Range&&);

        using container = Container<native_encoding_form::code_unit>;
        using iterator = codepoint_iterator<native_encoding_form, typename container::iterator>;
        using const_iterator = codepoint_iterator<native_encoding_form, typename container::const_iterator>;

        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;

        native_encoding_form::code_unit* native(); // TODO: woah, woah, think about it carefully!
        native_encoding_form::code_unit const* native() const;
    };

# `CodepointRange`

A `CodepointRange` is a `Range` whose `value_type` is `codepoint`. `text` is a
`CodepointRange`.

Many Unicode algorithms are provided for working with `CodepointRange`s, like
the segmentation algorithms.

    template <typename CodepointRange>
    codepoint_range<CodepointRange> grapheme_clusters(CodepointRange);
    template <typename CodepointRange>
    grapheme_cluster_range<CodepointRange> grapheme_clusters(CodepointRange);
    template <typename CodepointRange>
    word_range<CodepointRange> words(CodepointRange);
    template <typename CodepointRange>
    sentence_range<CodepointRange> sentences(CodepointRange);
    template <typename CodepointRange>
    linebreak_opportunity_range<CodepointRange> linebreak_opportunities(CodepointRange);

The resulting ranges are either forward or bidirectional ranges, depending on
the underlying range's capabilities.

# `Locale`

Ouch.

