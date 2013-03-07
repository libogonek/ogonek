---
layout: default
title: Character properties reference
---

### Header `<ogonek/properties.h++>` synopsis

{% highlight cpp %}
namespace ogonek {
    /* unspecified */ name(code_point u);

    bool is_numeric(code_point u);
    double numeric_value(code_point u);

    bool is_digit(code_point u);
    int digit_value(code_point u);

    bool is_decimal(code_point u);
    int decimal_value(code_point u);

    bool is_uppercase(code_point u);
    /* unspecified */ uppercase(code_point u);

    bool is_lowercase(code_point u);
    /* unspecified */ lowercase(code_point u);

    /* unspecified */ titlecase(code_point u);

    bool is_alphabetic(code_point u);
    bool is_white_space(code_point u);
    bool is_control(code_point u);
    bool is_hex_digit(code_point u);
    bool is_ascii_hex_digit(code_point u);
    bool is_letter(code_point u);
    bool is_punctuation(code_point u);
    bool is_separator(code_point u);
    bool is_symbol(code_point u);
    bool is_quotation_mark(code_point u);
    bool is_dash(code_point u);
    bool is_diacritic(code_point u);
    bool is_mathematical(code_point u);
    bool is_ideographic(code_point u);
    bool is_defined(code_point u);
    bool is_noncharacter(code_point u);

    // east_asian_width(code_point u);
    // directionality(code_point u);
    //bool is_mirrored(code_point u);
} // namespace ogonek
{% endhighlight %}

### 

{% highlight cpp %}
{% endhighlight %}

