---
layout: doc-ogonek
title: Normalization
---

Unicode defines [normalization forms][UAX15] which ensure that equivalent
strings have the same underlying representation. Currently, ogonek supports the
canonical Unicode normalization forms NFC and NFD. These are provided in the
header `<ogonek/normalization.h++>`.

#### `normalize`

This function template takes a range of code points as argument and returns a range of
code points. It also takes a normalization form as a template parameter. The
result is normalized according to the requested normalization form. Currently
the two canonical normalization forms are supported: Normalization Form C as
`nfc`, and Normalization Form D as `nfd`.

*Example*:
{% highlight cpp %}
// ogonek::text<ogonek::utf8> input;
auto normalized = make_vector(ogonek::normalize<ogonek::nfc>(input));
// normalized is a sequence equivalent to input, but in the NFC form
{% endhighlight %}

---

#### `canonically_equivalent`

This function takes two ranges of code points as arguments and return a bool
that indicates whether or not the two ranges are canonically equivalent, i.e.,
if their normalized forms are equal. Processes should give canonically
equivalent sequences the same interpretation.

*Example*:
{% highlight cpp %}
// ogonek::text<ogonek::utf8> a;
// std::u32string b;
bool are_same = ogonek::canonically_equivalent(a, b);
// are_same is true if a and b are canonical-equivalent sequences
{% endhighlight %}

---

#### `canonical_equivalence`

This class provides the same equivalence relation as the
`canonically_equivalent` function, but as an empty default constructible type,
so it can be easily used in template arguments of containers, or as predicates
for algorithms. Instances of `canonical_equivalence` are polymorphic function
objects that can be called with any type of range of code points.

{% highlight cpp %}
// std::vector<ogonek::text<ogonek::utf8>> v;
auto it = std::adjacent_find(v.begin(), v.end(), ogonek::canonical_equivalence{});
// finds a pair of adjacent canonical-equivalent sequences
{% endhighlight %}

---

 [UAX15]: http://www.unicode.org/reports/tr15/

