---
layout: default
title: Normalization reference
---

### Header `<ogonek/normalization.h++>` synopsis

{% highlight cpp %}
namespace ogonek {
    // Normalization forms
    class nfc;
    class nfd;

    class nfkc;
    class nfkd;

    class fcd; // NOT IMPLEMENTED
    class fcc; // NOT IMPLEMENTED

    // Normalization
    template <typename NormalizationForm, typename CodePointRange,
    /* unspecified */ normalize(CodePointRange const& range);

    // Equivalence
    struct canonical_equivalence {
        template <typename CodePointRange1, typename CodePointRange2>
        bool operator()(CodePointRange1 const& range1, CodePointRange2 const& range2) const;
    };
    template <typename CodePointRange1, typename CodePointRange2>
    bool canonically_equivalent(CodePointRange1 const& range1, CodePointRange2 const& range2);
    struct canonical_hash {
        template <typename CodePointRange>
        std::size_t operator()(CodePointRange const& range) const;
    };

    struct compatibility_equivalence {
        template <typename CodePointRange1, typename CodePointRange2>
        bool operator()(CodePointRange1 const& range1, CodePointRange2 const& range2) const;
    };
    template <typename CodePointRange1, typename CodePointRange2>
    bool compatibility_equivalent(CodePointRange1 const& range1, CodePointRange2 const& range2);
    struct compatibility_hash {
        template <typename CodePointRange>
        std::size_t operator()(CodePointRange const& range) const;
    };
} // namespace ogonek
{% endhighlight %}

### Normalization forms

{% highlight cpp %}
class nfc;
{% endhighlight %}

Tag type for Normalization Form C.

---

{% highlight cpp %}
class nfd;
{% endhighlight %}

Tag type for Normalization Form D.

---

{% highlight cpp %}
class nfkc;
{% endhighlight %}

Tag type for Normalization Form Compatibility C.

---

{% highlight cpp %}
class nfkd;
{% endhighlight %}

Tag type for Normalization Form Compatibility D.

---

{% highlight cpp %}
class fcd;
{% endhighlight %}

Tag type for Normalization Form Fast C or D.

---

{% highlight cpp %}
class fcc;
{% endhighlight %}

Tag type for Normalization Form Fast C Contiguous.

### Normalization

{% highlight cpp %}
template <typename NormalizationForm, typename CodePointRange,
/* unspecified */ normalize(CodePointRange const& range);
{% endhighlight %}

*Requires*: `CodePointRange` is a range of code points, and `NormalizationForm`
is a normalization form tag type.

*Returns*: a range whose codepoints are the result of normalizing `range`
according to `NormalizationForm`.

### Equivalence

{% highlight cpp %}
struct canonical_equivalence {
    template <typename CodePointRange1, typename CodePointRange2>
    bool operator()(CodePointRange1 const& range1, CodePointRange2 const& range2) const;
};
{% endhighlight %}

*Requires*: `CodePointRange1` and `CodePointRange2` are ranges of code points.

*Returns*: `canonically_equivalent(range1, range2)`.

---

{% highlight cpp %}
template <typename CodePointRange1, typename CodePointRange2>
bool canonically_equivalent(CodePointRange1 const& range1, CodePointRange2 const& range2);
{% endhighlight %}

*Requires*: `CodePointRange1` and `CodePointRange2` are ranges of code points.

*Returns*: `boost::equal(normalize<nfd>(range1), normalize<nfd>(range2))`.

---

{% highlight cpp %}
struct compatibility_equivalence {
    template <typename CodePointRange1, typename CodePointRange2>
    bool operator()(CodePointRange1 const& range1, CodePointRange2 const& range2) const;
};
{% endhighlight %}

*Requires*: `CodePointRange1` and `CodePointRange2` are ranges of code points.

*Returns*: `compatibility_equivalent(range1, range2)`.

---

{% highlight cpp %}
template <typename CodePointRange1, typename CodePointRange2>
bool compatibility_equivalent(CodePointRange1 const& range1, CodePointRange2 const& range2);
{% endhighlight %}

*Requires*: `CodePointRange1` and `CodePointRange2` are ranges of code points.

*Returns*: `boost::equal(normalize<nfkd>(range1), normalize<nfkd>(range2))`.

### Hashing

{% highlight cpp %}
struct canonical_hash {
    template <typename CodePointRange>
    std::size_t operator()(CodePointRange const& range) const;
};
{% endhighlight %}

*Requires*: `CodePointRange` is a range of code points.

*Returns*: a value such that if `a` and `b` are canonically equivalent ranges,
`canonical_hash{}(a) == canonical_hash{}(b)`.

---

{% highlight cpp %}
struct compatibility_hash {
    template <typename CodePointRange>
    std::size_t operator()(CodePointRange const& range) const;
};
{% endhighlight %}

*Requires*: `CodePointRange` is a range of code points.

*Returns*: a value such that if `a` and `b` are compatibility equivalent ranges,
`compatibility_hash{}(a) == compatibility_hash{}(b)`.

