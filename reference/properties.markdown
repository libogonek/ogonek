---
layout: default
title: Character properties reference
---

### Header `<ogonek/properties.h++>` synopsis

{% highlight cpp %}
namespace ogonek {
    // Classification
    bool is_graphic(code_point u);
    bool is_format(code_point u);
    bool is_control(code_point u);
    bool is_private_use(code_point u);
    bool is_surrogate(code_point u);
    bool is_noncharacter(code_point u);
    bool is_reserved(code_point u);

    bool is_assigned(code_point u);

    // Numbers
    bool is_numeric(code_point u);
    bool is_digit(code_point u);
    bool is_decimal(code_point u);
    double numeric_value(code_point u);
    int digit_value(code_point u);

    // Other properties
    bool is_alphabetic(code_point u);
    bool is_ideographic(code_point u);

    bool is_white_space(code_point u);
    bool is_hex_digit(code_point u);
    bool is_ascii_hex_digit(code_point u);
    bool is_quotation_mark(code_point u);
    bool is_dash(code_point u);
    bool is_diacritic(code_point u);
    bool is_mathematical(code_point u);
} // namespace ogonek
{% endhighlight %}

All the functions in this header *require* their argument to be in the range
U+0000..U+10FFFF.

### Names

{% highlight cpp %}
/* unspecified */ name(code_point u);
{% endhighlight %}

*Returns*: the Name property of `u`, as a sequence of code points. If `u` has a
correction or control alias, that is returned instead of the Name property;
otherwise, if `!is_graphic(u) || !is_format(u)`, a label constructed according
to section 4.8 of the Unicode Standard is returned instead of the Name property.

### Classification

{% highlight cpp %}
bool is_graphic(code_point u);
{% endhighlight %}

*Returns*: `true` if the General\_Category of `u` is L, M, N, P, S, or Zs;
`false` otherwise.

---

{% highlight cpp %}
bool is_format(code_point u);
{% endhighlight %}

*Returns*: `true` if the General\_Category of `u` is Cf, Zl, Zp; `false`
otherwise.

---

{% highlight cpp %}
bool is_control(code_point u);
{% endhighlight %}

*Returns*: `true` if the General\_Category of `u` is Cc; `false` otherwise.

---

{% highlight cpp %}
bool is_private_use(code_point u);
{% endhighlight %}

*Returns*: `true` if the General\_Category of `u` is Co; `false` otherwise.

---

{% highlight cpp %}
bool is_surrogate(code_point u);
{% endhighlight %}

*Returns*: `true` if the General\_Category of `u` is Cs; `false` otherwise.

---

{% highlight cpp %}
bool is_noncharacter(code_point u);
{% endhighlight %}

*Returns*: `true` if `u` has the Noncharacter\_Code\_Point property; `false`
otherwise.

---

{% highlight cpp %}
bool is_reserved(code_point u);
{% endhighlight %}

*Returns*: `true` if `!is_noncharacter` and the General\_Category of `u` is Cn;
`false` otherwise.

---

{% highlight cpp %}
bool is_assigned(code_point u);
{% endhighlight %}

*Returns*: `true` if `u` is an assigned codepoint; `false` otherwise.

### Numbers

{% highlight cpp %}
bool is_numeric(code_point u);
{% endhighlight %}

*Returns*: `true` if `u` is a character with non-default Numeric\_Type property;
`false` otherwise.

---

{% highlight cpp %}
bool is_digit(code_point u);
{% endhighlight %}

*Returns*: `true` if `u` is a character with a Numeric\_Type property of digit
or decimal; `false` otherwise.

---

{% highlight cpp %}
bool is_decimal(code_point u);
{% endhighlight %}

*Returns*: `true` if `u` is a character with a Numeric\_Type property of
decimal; `false` otherwise.

---

{% highlight cpp %}
double numeric_value(code_point u);
{% endhighlight %}

*Requires*: `is_numeric(u)`.

*Returns*: The Numeric\_Value property of `u`.

---

{% highlight cpp %}
int digit_value(code_point u);
{% endhighlight %}

*Requires*: `is_digit(u)`.

*Returns*: The Numeric\_Value property of `u`.

### Other properties

{% highlight cpp %}
bool is_alphabetic(code_point u);
{% endhighlight %}

*Returns*: `true` if `u` has the Alphabetic property; `false` otherwise.

---

{% highlight cpp %}
bool is_ideographic(code_point u);
{% endhighlight %}

*Returns*: `true` if `u` has the Ideographic property; `false` otherwise.

---

{% highlight cpp %}
bool is_white_space(code_point u);
{% endhighlight %}

*Returns*: `true` if `u` has the White\_Space property; `false` otherwise.

---

{% highlight cpp %}
bool is_hex_digit(code_point u);
{% endhighlight %}

*Returns*: `true` if `u` has the Hex\_Digit property; `false` otherwise.

---

{% highlight cpp %}
bool is_ascii_hex_digit(code_point u);
{% endhighlight %}

*Returns*: `true` if `u` has the ASCII\_Hex\_Digit property; `false` otherwise.

---

{% highlight cpp %}
bool is_quotation_mark(code_point u);
{% endhighlight %}

*Returns*: `true` if `u` has the Quotation\_Mark property; `false` otherwise.

---

{% highlight cpp %}
bool is_dash(code_point u);
{% endhighlight %}

*Returns*: `true` if `u` has the Dash property; `false` otherwise.

---

{% highlight cpp %}
bool is_diacritic(code_point u);
{% endhighlight %}

*Returns*: `true` if `u` has the Diacritic property; `false` otherwise.

---

{% highlight cpp %}
bool is_mathematical(code_point u);
{% endhighlight %}

*Returns*: `true` if `u` has the Math property; `false` otherwise.

