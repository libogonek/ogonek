---
layout: default
title: How to read this manual
---

### Unicode version

Ogonek {{ site.doc_version }} follows the Unicode standard version 6.2. Any reference to an Unicode
algorithm refers to the algorithm from version 6.2.

### Namespaces

Unless otherwise mentioned, all entities described are in namespace `ogonek`.

### Reference

In reference pages entities are described using following elements.

- *Invariants* sections describe conditions that always hold for any object of
a class;

- *Requires* sections describe preconditions that must hold before calling a
function; the behaviour is undefined if the preconditions do not hold;

- *Effects* sections describe the actions performed by a function;

- *Postconditions* sections describe the observable results established by a
function;

- *Returns* sections describe the value returned by a function;

- *Validation* sections describe what kind of data validation is performed by a
function, and how invalid data is treated;

- *Complexity* sections describe the time and/or space complexity of a function;

- *Remarks* sections describe additional semantics of a function;

- *Notes* sections provide additional information about the entity;

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

