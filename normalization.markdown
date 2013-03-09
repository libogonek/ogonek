---
layout: default
title: Normalization
---

Unicode defines [normalization forms][UAX15] which ensure that equivalent
strings have the same underlying representation. Currently, ogonek supports both the 
canonical and compatibility Unicode normalization forms: NFC, NFD, NFKC, and
NFDK. These are provided in the header `<ogonek/normalization.h++>`.

#### `normalize`

This function template takes a range of code points as argument and returns a range of
code points. It also takes a normalization form as a template parameter. The
result is normalized according to the requested normalization form. All the four
standard normalization forms are supported, under the names `nfc`, `nfd`,
`nfkc`, and `nfkd`.

*Example*:
{% highlight cpp %}
// ogonek::text<ogonek::utf8> input;
auto normalized = make_vector(ogonek::normalize<ogonek::nfc>(input));
// normalized is a deferred sequence equivalent to input, but in the NFC form
{% endhighlight %}

---

#### Equivalence

Ogonek provides functions takes two ranges of code points as arguments and
return whether or not the two ranges are canonically or compatibility
equivalent, i.e., if their normalized forms are equal.

Processes should give canonically equivalent sequences the same interpretation.

*Example*:
{% highlight cpp %}
// ogonek::text<ogonek::utf8> a;
// std::u32string b;
bool are_same = ogonek::canonically_equivalent(a, b);
// are_same is true if a and b are canonical-equivalent sequences

bool are_same_compatibility = ogonek::compatibility_equivalent(a, b);
// are_same_compatibility is true if a and b are compatibility-equivalent sequences
{% endhighlight %}

Along with these two functions, there are also two polymorphic function object
types that are default-constructible and can be easily used in template
arguments of containers, or as predicates for algorithms. Instances of
these types can be called with sequence of code points of any type.

{% highlight cpp %}
// std::vector<ogonek::text<ogonek::utf8>> v;
auto it = std::adjacent_find(v.begin(), v.end(), ogonek::canonical_equivalence{});
// finds a pair of adjacent canonical-equivalent sequences

auto it = std::adjacent_find(v.begin(), v.end(), ogonek::compatibility_equivalence{});
// finds a pair of adjacent compatibility-equivalent sequences
{% endhighlight %}

Ogonek also provides hash function objects to match these two equivalence
relations, so that they can be used for keys in unordered associative
containers. These hash function objects are also polymorphic and accept any
sequence of code points.

{% highlight cpp %}
std::unordered_map<std::u32string, int, canonical_equivalence, canonical_hash> map;

std::unordered_map<std::u32string, int, compatibility_equivalence, compatibility_hash> map;
{% endhighlight %}

---

 [UAX15]: http://www.unicode.org/reports/tr15/

