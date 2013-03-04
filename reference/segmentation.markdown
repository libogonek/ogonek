---
layout: default
title: Segmentation reference
---

### Header `<ogonek/segmentation.h++>` synopsis

{% highlight cpp %}
namespace ogonek {
    template <typename CodePointRange>
    /* unspecified */ grapheme_clusters(CodePointRange const& range) {
    template <typename CodePointRange>
    /* unspecified */ words(CodePointRange const& range) {
    template <typename CodePointRange>
    /* unspecified */ sentences(CodePointRange const& range) {
    template <typename CodePointRange>
    /* unspecified */ line_break_opportunities(CodePointRange const& range) {
} // namespace ogonek
{% endhighlight %}

### Grapheme cluster iteration

{% highlight cpp %}
template <typename CodePointRange>
/* unspecified */ grapheme_clusters(CodePointRange const& range) {
{% endhighlight %}

*Requires*: `CodePointRange` is a range of code points.

*Returns*: a range of subranges of `range`. Each subrange is one extended
grapheme cluster according to the default algorithm in the Unicode Annex #29.

### Word iteration

{% highlight cpp %}
template <typename CodePointRange>
/* unspecified */ words(CodePointRange const& range) {
{% endhighlight %}

*Requires*: `CodePointRange` is a range of code points.

*Returns*: a range of subranges of `range`. Each subrange is one word according
to the default algorithm in the Unicode Annex #29.

### Sentence iteration

{% highlight cpp %}
template <typename CodePointRange>
/* unspecified */ sentences(CodePointRange const& range) {
{% endhighlight %}

*Requires*: `CodePointRange` is a range of code points.

*Returns*: a range of subranges of `range`. Each subrange is one sentence
according to the default algorithm in the Unicode Annex #29.

### Line break opportunities

{% highlight cpp %}
template <typename CodePointRange>
/* unspecified */ line_break_opportunities(CodePointRange const& range) {
{% endhighlight %}

*Requires*: `CodePointRange` is a range of code points.

*Returns*: A range of iterators from `range`. Each iterator points to a
potential line break position according to the default algorithm in Unicode
Annex #14.
