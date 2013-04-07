# UnicodeString

## Description

Type whose values can be unambiguously seen as Unicode strings are models of
UnicodeString. This only includes sequences of code points, or sequences of code
units with a known encoding.

## Models

The following are models of UnicodeString:

 - any Sequence of `char32_t` code units;
 - any Sequence of `char16_t` code units;
 - instances of `icu::UnicodeString`;

## Operations

Given an lvalue `u` of a model of UnicodeString `U`, the expression
`ogonek::forward_code_points(u)` is valid and returns a Sequence with a value
type of `code_point`.

