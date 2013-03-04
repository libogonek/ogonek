---
layout: default
title: Validation reference
---

### Header `<ogonek/validation.h++>` synopsis

{% highlight cpp %}
namespace ogonek {
    // Exceptions
    class validation_error : std::exception;

    // Validation strategies
    constexpr /* unspecified */ throw_validation_error = {};
    constexpr /* unspecified */ use_replacement_character = {};
    constexpr /* unspecified */ discard_errors = {};
    constexpr /* unspecified */ skip_validation = {};
} // namespace ogonek
{% endhighlight %}

### Exceptions

{% highlight cpp %}
class validation_error : std::exception;
{% endhighlight %}

This exception signals that validation of data according to the requested
encoding failed.

### Validation strategies

*Note*: All validation strategy objects have distinct types.

---

{% highlight cpp %}
constexpr /* unspecified */ throw_validation_error = {};
{% endhighlight %}

When this validation strategy is used and invalid data is found, an exception of
type `validation_error` is thrown.

---

{% highlight cpp %}
constexpr /* unspecified */ use_replacement_character = {};
{% endhighlight %}

When this validation strategy is used, invalid data is replaced by the
replacement character for the requested encoding, or U+FFFD if the encoding does
not explicitly specify one.

---

{% highlight cpp %}
constexpr /* unspecified */ discard_errors = {};
{% endhighlight %}

When this validation strategy is used, invalid data in the input is skipped.

---

{% highlight cpp %}
constexpr /* unspecified */ skip_validation = {};
{% endhighlight %}

When this validation strategy is used, the data is assumed valid. This allows
some functions to use optimised algorithms. Using this strategy with invalid
data results in undefined behaviour.

