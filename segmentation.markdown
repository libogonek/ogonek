---
layout: doc-ogonek
title: Segmentation
---

Sometimes it is necessary to break text down into pieces. Unicode acknowledges
this need and defines several algorithms for this in [Annex #29][UAX29].
Currently, ogonek includes the canonical Unicode segmentation algorithms for
extended grapheme clusters and for words. These are provided in the header
`<ogonek/segmentation.h++>`.

### `grapheme_clusters`

This function takes a range of code points as argument and returns a range of
sub-ranges of the input. Each of those sub-ranges comprises an extended grapheme
cluster according to the Unicode canonical algorithm.

*Example*:
{% highlight cpp %}
// ogonek::text<ogonek::utf8> input;
for(auto cluster : ogonek::grapheme_clusters(input)) {
    // cluster.begin() and cluster.end() are iterators to input
    do_stuff_with(cluster);
}
{% endhighlight %}

### `words`

This function takes a range of code points as argument and returns a range of
sub-ranges of the input. Each of those sub-ranges comprises a word according to
the Unicode canonical algorithm.

*Example*:
{% highlight cpp %}
// ogonek::text<ogonek::utf8> input;
for(auto word : ogonek::words(input)) {
    // word.begin() and word.end() are iterators to input
    do_stuff_with(word);
}
{% endhighlight %}

 [UAX29]: http://www.unicode.org/reports/tr29/

