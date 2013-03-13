---
layout: default
title: Character properties reference
---

### Header `<ogonek/properties.h++>` synopsis

{% highlight cpp %}
namespace ogonek {
    // Names
    /* unspecified */ name(code_point u);
    /* unspecified */ label(code_point u);

    // Numbers
    bool is_numeric(code_point u);
    bool is_digit(code_point u);
    bool is_decimal(code_point u);
    double numeric_value(code_point u);
    int digit_value(code_point u);

    // Casing
    bool is_uppercase(code_point u);
    bool is_lowercase(code_point u);
    code_point simple_uppercase(code_point u);
    code_point simple_lowercase(code_point u);
    code_point simple_titlecase(code_point u);
    /* unspecified */ uppercase(code_point u);
    /* unspecified */ lowercase(code_point u);
    /* unspecified */ titlecase(code_point u);

    // Classification
    bool is_graphic(code_point u);
    bool is_format(code_point u);
    bool is_control(code_point u);
    bool is_private_use(code_point u);
    bool is_surrogate(code_point u);
    bool is_noncharacter(code_point u);
    bool is_reserved(code_point u);

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

    bool is_designated(code_point u);
} // namespace ogonek
{% endhighlight %}

All the functions in this header *require* their argument to be in the range
0000-10FFFF.

### Names

{% highlight cpp %}
/* unspecified */ name(code_point u);
{% endhighlight %}

*Returns*: The Name property of `u`, as a sequence of code points.

---

{% highlight cpp %}
/* unspecified */ label(code_point u);
{% endhighlight %}

*Returns*: The code point label for `u`, as described in the Unicode Standard
section 4.8.

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

### Casing

{% highlight cpp %}
bool is_uppercase(code_point u);
{% endhighlight %}

*Returns*: `true` if `u` has the Uppercase property; `false` otherwise.

---

{% highlight cpp %}
bool is_lowercase(code_point u);
{% endhighlight %}

*Returns*: `true` if `u` has the Lowercase property; `false` otherwise.

---

{% highlight cpp %}
code_point simple_uppercase(code_point u);
{% endhighlight %}

*Returns*: The Simple\_Uppercase property of `u`.

---

{% highlight cpp %}
code_point simple_lowercase(code_point u);
{% endhighlight %}

*Returns*: The Simple\_Lowercase property of `u`.

---

{% highlight cpp %}
code_point simple_titlecase(code_point u);
{% endhighlight %}

*Returns*: The Simple\_Titlecase property of `u`.

---

{% highlight cpp %}
/* unspecified */ uppercase(code_point u);
{% endhighlight %}

*Returns*: The Uppercase\_Mapping property of `u`, as a sequence of code
points.

---

{% highlight cpp %}
/* unspecified */ lowercase(code_point u);
{% endhighlight %}

*Returns*: The Lowercase\_Mapping property of `u`, as a sequence of code
points.

---

{% highlight cpp %}
/* unspecified */ titlecase(code_point u);
{% endhighlight %}

*Returns*: The Titlecase\_Mapping property of `u`, as a sequence of code
points.

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

---

{% highlight cpp %}
bool is_designated(code_point u);
{% endhighlight %}

*Returns*: `true` if `u` is a designated codepoint; `false` otherwise.

