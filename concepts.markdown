% Concepts in the ogonek library

# `ByteOrder`

A type with operations for serializing multi-byte integrals into sequences of
bytes in a particular order. There are two models of this concept:
`little_endian` and `big_endian`.

In the following table `Order` is a model of `ByteOrder`, `out` is an
`OutputIterator` lvalue, `u16` is a `uint16_t` value, `u32` is a `uint32_t`
value, `it` is an `InputIterator` lvalue on bytes.

+-----------------------------+-------------+---------------------------------+
| Expression                  | Return type | Semantics                       |
+=============================+=============+=================================+
| `Order::write(out, u16)`    | `void`      | writes the bytes of `u16` to    |
|                             |             | `out` in the appropriate byte   |
|                             |             | order                           |
+-----------------------------+-------------+---------------------------------+
| `Order::write(out, u32)`    | `void`      | writes the bytes of `u32` to    |
|                             |             | `out` in the appropriate byte   |
|                             |             | order                           |
+-----------------------------+-------------+---------------------------------+
| `Order::read<uint16_t>(it)` | `uint16_t`  | reads the bytes of a `uint16_t` |
|                             |             | from `it` in the appropriate    |
|                             |             | byte order                      |
+-----------------------------+-------------+---------------------------------+
| `Order::read<uint32_t>(it)` | `uint32_t`  | reads the bytes of a `uint32_t` |
|                             |             | from `it` in the appropriate    |
|                             |             | byte order                      |
+-----------------------------+-------------+---------------------------------+

Table: Requirements for `ByteOrder`

# `codepoint`

The `codepoint` type is an integral type capable of holding any Unicode
codepoint (integers from 0 to 10FFFF). It is an alias of `char32_t`.

# `CodeUnit`

An integral type capable of holding the values used by a particular encoding.

# `EncodingForm`

An encoder/decoder that converts between `codepoint` and `CodeUnit`s.

In the following table, `E` is a model of `EncodingScheme`, `codec` is an
instance of `E`, `s` is an instance of `E::state`, `u` is a `codepoint`, `b` is
a byte, [`cb`, `ce`) is a range of `InputIterator`s on `E::code_unit`s, [`ub`,
`ue`) is a range of `InputIterator`s on `codepoint`s, `co` is an `OutputIterator`
on `E::code_unit`s, and `uo` is an `OutputIterator` on `codepoint`s.

+-------------------------------+---------------------+------------------------+
| Expression                    | Return type         | Semantics              |
+===============================+=====================+========================+
| `E::code_unit`                | `typename CodeUnit` | type of a code unit    |
+-------------------------------+---------------------+------------------------+
| `E::is_fixed_width`           | `constexpr bool`    | true iff is fixed      |
|                               |                     | width                  |
+-------------------------------+---------------------+------------------------+
| `E::max_width`                | `constexpr size_t`  | maximum width in code  |
|                               |                     | units                  |
+-------------------------------+---------------------+------------------------+
| `E::state`                    | `typename Trivial`  | type of the state (an  |
|                               |                     | empty type iff `E` is  |
|                               |                     | stateless)             |
+-------------------------------+---------------------+------------------------+
| `E codec;`                    | `E`                 | creates an instance    |
+-------------------------------+---------------------+------------------------+
| `E()`                         | `E`                 | creates an instance    |
+-------------------------------+---------------------+------------------------+
| `codec.encode(ub, ue, co)`    | `OutputIterator`    | encodes codepoints     |
+-------------------------------+---------------------+------------------------+
| `codec.decode(cb, ce, uo)`    | `OutputIterator`    | decodes codepoints     |
+-------------------------------+---------------------+------------------------+
| `codec.encode_one(u, co)`     | `void`              | encodes one codepoint  |
|                               |                     | (only available if `E` |
|                               |                     | is stateless)          |
+-------------------------------+---------------------+------------------------+
| `codec.decode_one(cb, ce)`    | `codepoint`         | decodes one codepoint  |
|                               |                     | (only available if `E` |
|                               |                     | is stateless)          |
+-------------------------------+---------------------+------------------------+
| `codec.encode_one(u, co, s)`  | `void`              | encodes one codepoint  |
+-------------------------------+---------------------+------------------------+
| `codec.decode_one(cb, ce, s)` | `codepoint`         | decodes one codepoint  |
+-------------------------------+---------------------+------------------------+

Table: Requirements for `EncodingForm`

# `EncodingScheme`

An encoder/decoder that converts between codepoints and bytes. Some
`EncodingForm`s are naturally `EncodingScheme`s because their code units are
bytes.  Others can be created by putting together an `EncodingForm` and a
`ByteOrder`.

In the following table, `E` is a model of `EncodingForm`, `codec` is an instance
of `E`, `s` is an instance of `E::state`, `u` is a `codepoint`, `b` is a byte,
[`bb`, `be`) is a range of `InputIterator`s on bytes, [`ub`, `ue`) is a range of
`InputIterator`s on `codepoint`s, `bo` is an `OutputIterator` on bytes, and `uo`
is an `OutputIterator` on `codepoint`s.

+-------------------------------+---------------------+------------------------+
| Expression                    | Return type         | Semantics              |
+===============================+=====================+========================+
| `E::is_fixed_width`           | `constexpr bool`    | true iff is fixed      |
|                               |                     | width                  |
+-------------------------------+---------------------+------------------------+
| `E::max_width`                | `constexpr size_t`  | maximum width in bytes |
+-------------------------------+---------------------+------------------------+
| `E::state`                    | `typename Trivial`  | type of the state (an  |
|                               |                     | empty type iff `E` is  |
|                               |                     | stateless)             |
+-------------------------------+---------------------+------------------------+
| `E codec;`                    | `E`                 | creates an instance    |
+-------------------------------+---------------------+------------------------+
| `E()`                         | `E`                 | creates an instance    |
+-------------------------------+---------------------+------------------------+
| `codec.encode(ub, ue, bo)`    | `OutputIterator`    | encodes codepoints     |
+-------------------------------+---------------------+------------------------+
| `codec.decode(bb, be, uo)`    | `OutputIterator`    | decodes codepoints     |
+-------------------------------+---------------------+------------------------+
| `codec.encode_one(u, bo)`     | `void`              | encodes one codepoint  |
|                               |                     | (only available if `E` |
|                               |                     | is stateless)          |
+-------------------------------+---------------------+------------------------+
| `codec.decode_one(bb, be)`    | `codepoint`         | decodes one codepoint  |
|                               |                     | (only available if `E` |
|                               |                     | is stateless)          |
+-------------------------------+---------------------+------------------------+
| `codec.encode_one(u, bo, s)`  | `void`              | encodes one codepoint  |
+-------------------------------+---------------------+------------------------+
| `codec.decode_one(bb, be, s)` | `codepoint`         | decodes one codepoint  |
+-------------------------------+---------------------+------------------------+

Table: Requirements for `EncodingScheme`

# `String`

An ordered sequence of `CodeUnit`s.

# `Text`

An ordered sequence of `codepoint`s.

