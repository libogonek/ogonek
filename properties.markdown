---
layout: default
title: Properties
---

Ogonek provides ways to query character properties. The most useful properties
are provided in the header `<ogonek/data/properties.h++>`; the full set of properties
in the Unicode Character Database is also provided: under namespace
`ogonek::ucd`, in the header `<ogonek/data/ucd.h++>`.

### Classification

Code points can be separated into various types: graphic, format, control,
private use, surrogates, noncharacters, and reserved.

Graphic code points are assigned to abstract characters with a graphic
representation. These include letters, marks, numbers, punctuation, symbols, and
spaces.

Format code points are invisible but affect neighboring characters. These
include characters that control joining behaviour, bidirectional ordering, and
alternative formats for display; it also includes the line separator and
paragraph separator characters.

Control code points are the C0 and C1 control codes (U+0000..U+001F and
U+007F..U+009F).

Private use code points are those in the Private Use Area (U+E000..U+F8FF),
Supplemental Private Use Area-A (U+F0000..U+FFFFD) and Supplemental Private Use
Area-B (U+100000..U+10FFFD).

Surrogates are reserved code points for UTF-16 support (U+D800..DFFF).

Noncharacters are an immutable set of sixty-six code points reserved for
internal use.

Reserved are all the code points that are reserved for future assignment by the
Unicode Standard.

Ogonek provides functions to query these types: `is_graphic`, `is_format`,
`is_control`, `is_private_use`, `is_surrogate`, `is_noncharacter`, and
`is_reserved`.

*Example*:
{% highlight cpp %}
assert(ogonek::is_graphic(0x0041));
assert(ogonek::is_format(0x202D));
assert(ogonek::is_control(0x000A));
assert(ogonek::is_private_use(0xF8FF));
assert(ogonek::is_surrogate(0xD8FF));
assert(ogonek::is_noncharacter(0xFFFF));
assert(ogonek::is_reserved(0x0378));
{% endhighlight %}

Ogonek also provides the function `is_assigned` to query whether a code point is
assigned.

*Example*:
{% highlight cpp %}
assert(ogonek::is_assigned(0xFFFF));
assert(!ogonek::is_assigned(0x0379));
{% endhighlight %}

### Numbers

For characters that normally represent numbers, their numeric types and values
can be queried. For all numeric characters, `is_numeric` returns true.

Digit characters are those whose numeric value is an integer in the range 0..9.
For these `is_digit` returns true. Among these there is a subset of those that
are encoded in a contiguous ascending range 0..9. For those, `is_decimal`
returns true.

For all numeric characters, `numeric_value` returns its corresponding value as a
`double`. For digit characters, `digit_value` returns its value as an `int`.

*Example*:
{% highlight cpp %}
assert(ogonek::is_numeric(0x00BC)); // VULGAR FRACTION ONE QUARTER
assert(ogonek::is_digit(0x00B2)); // SUPERSCRIPT TWO
assert(ogonek::is_decimal(0x0031)); // DIGIT ONE

assert(ogonek::numeric_value(0x00BC) == 0.25); // VULGAR FRACTION ONE QUARTER
assert(ogonek::digit_value(0x00B2) == 2); // SUPERSCRIPT TWO
assert(ogonek::digit_value(0x0031) == 1); // DIGIT ONE
{% endhighlight %}

### Other properties

Ogonek provides simple queries for various character properties that classify
characters according to their function.

{% highlight cpp %}
bool is_alphabetic(code_point u);
{% endhighlight %}
{% highlight cpp %}
bool is_ideographic(code_point u);
{% endhighlight %}
{% highlight cpp %}
bool is_white_space(code_point u);
{% endhighlight %}
{% highlight cpp %}
bool is_hex_digit(code_point u);
{% endhighlight %}
{% highlight cpp %}
bool is_ascii_hex_digit(code_point u);
{% endhighlight %}
{% highlight cpp %}
bool is_quotation_mark(code_point u);
{% endhighlight %}
{% highlight cpp %}
bool is_dash(code_point u);
{% endhighlight %}
{% highlight cpp %}
bool is_diacritic(code_point u);
{% endhighlight %}
{% highlight cpp %}
bool is_mathematical(code_point u);
{% endhighlight %}

### Full UCD support

The header `<ogonek/data/ucd.h++>` provides various direct queries to the Unicode
normative propertiees in namespace `ucd`. These are intended for advanced users
and for internal use by the algorithms provided in ogonek. This API is not
stable yet, so it is not documented.

