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

    class nfkc; // NOT IMPLEMENTED
    class nfkd; // NOT IMPLEMENTED

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

    /* NOT IMPLEMENTED
    struct compatibility_equivalence {
        template <typename CodePointRange1, typename CodePointRange2>
        bool operator()(CodePointRange1 const& range1, CodePointRange2 const& range2) const;
    };
    template <typename CodePointRange1, typename CodePointRange2>
    bool compatibility_equivalent(CodePointRange1 const& range1, CodePointRange2 const& range2);
    */
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

