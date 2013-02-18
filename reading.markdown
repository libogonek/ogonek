---
layout: default
title: How to read this manual
---

### Unicode version

Ogonek follows the Unicode standard version 6.2. Any reference to an Unicode
algorithm refers to the algorithm from version 6.2.

### Namespaces

Unless otherwise mentioned, all entities described are in namespace `ogonek`.

### Exposition functions

Some functions are used throughout this manual only for exposition purposes and
not really part of the library.

`make_vector` is a function that takes a range argument and returns a
`std::vector<T>` where `T` is the range's value type.

*Example implementation:*
{% highlight cpp %}
template <typename Range,
          typename ValueType = typename boost::range_value_type<Unqualified<Range>>::type>
std::vector<ValueType> make_vector(Range&& range) {
    return std::vector<ValueType>(boost::begin(range), boost::end(range));
}
{% endhighlight %}

