---
layout: default
title: `ogonek::text` reference
---

### Header `<ogonek/text.h++>` synopsis

{% highlight cpp %}
namespace ogonek {
    template <typename EncodingForm, typename Container = std::basic_string<CodeUnit<EncodingForm>>>
    class text {
        // Construction
        text(); 
        text(text const& that); 
        text(text&& that); 
        template <typename EncodingForm1, typename Container1>
        text(text<EncodingForm1, Container1> const& that);
        template <typename EncodingForm1, typename Container1, typename Validation>
        text(text<EncodingForm1, Container1> const& that, Validation validation);

        template <typename CodePointSequence>
        explicit text(CodePointSequence&& range);
        template <typename CodePointSequence, typename Validation>
        text(CodePointSequence&& range, Validation validation);

        explicit text(Container const& storage);
        explicit text(Container&& storage);

        // Assignment
        text& operator=(text const& that);
        text& operator=(text&& that);
        template <typename EncodingForm1, typename Container1>
        text& operator=(text<EncodingForm1, Container1> const& that);
        text& operator=(code_point const* literal);

        template <typename CodePointSequence>
        void assign(CodePointSequence&& range);
        template <typename CodePointSequence, typename Validation>
        void assign(CodePointSequence&& range, Validation validation);

        void assign(Container const& storage);
        void assign(Container&& storage);

        // Iteration
        using const_iterator = /* unspecified */;
        using iterator = const_iterator;

        const_iterator begin() const;
        const_iterator end() const;

        // Interoperation
        Container const& storage() const;
        Container extract_storage();

        // Test for emptiness
        bool empty() const;

        // Appending
        template <typename CodePointSequence>
        iterator append(CodePointSequence&& that);
        template <typename CodePointSequence, typename Validation>
        iterator append(CodePointSequence&& range, Validation validation);

        // Erasure
        template <typename Range>
        iterator erase(Range const& range);
        iterator erase(iterator first, iterator last);

        // Insertion
        template <typename CodePointSequence>
        iterator insert(iterator at, CodePointSequence&& that);
        template <typename CodePointSequence, typename Validation>
        iterator insert(iterator at, CodePointSequence&& that, Validation validation);

        // Replacement
        template <typename Range, typename CodePointSequence>
        void replace(Range const& range, CodePointSequence&& range);
        template <typename Range, typename CodePointSequence, typename Validation>
        void replace(Range const& range, CodePointSequence&& range, Validation validation);

        template <typename CodePointSequence>
        void replace(iterator from, iterator to, CodePointSequence&& range);
        template <typename CodePointSequence, typename Validation>
        void replace(iterator from, iterator to, CodePointSequence&& range, Validation validation);
    };

    // Canonical equivalence
    template <typename EncodingForm0, typename Container0, typename EncodingForm1, typename Container1>
    bool operator==(text<EncodingForm0, Container0> const& lhs, text<EncodingForm1, Container1> const& rhs);
    template <typename EncodingForm0, typename Container0, typename EncodingForm1, typename Container1>
    bool operator!=(text<EncodingForm0, Container0> const& lhs, text<EncodingForm1, Container1> const& rhs);

    // Default collation
    template <typename EncodingForm0, typename Container0, typename EncodingForm1, typename Container1>
    bool operator<(text<EncodingForm0, Container0> const& lhs, text<EncodingForm1, Container1> const& rhs);
    template <typename EncodingForm0, typename Container0, typename EncodingForm1, typename Container1>
    bool operator>(text<EncodingForm0, Container0> const& lhs, text<EncodingForm1, Container1> const& rhs);
    template <typename EncodingForm0, typename Container0, typename EncodingForm1, typename Container1>
    bool operator<=(text<EncodingForm0, Container0> const& lhs, text<EncodingForm1, Container1> const& rhs);
    template <typename EncodingForm0, typename Container0, typename EncodingForm1, typename Container1>
    bool operator>=(text<EncodingForm0, Container0> const& lhs, text<EncodingForm1, Container1> const& rhs);

    // Concatenation
    template <typename EncodingForm = /* magic */, typename Container = /* magic */, typename... Ranges>
    text<EncodingForm, Container> concat(Ranges&&... ranges);
} // namespace ogonek
{% endhighlight %}

### Constructors

{% highlight cpp %}
text();
{% endhighlight %}

*Requires*: `Container` is default-constructible.

*Effects*: Initialises an instance of `text` with an empty string.

---

{% highlight cpp %}
text(text const& that);
{% endhighlight %}

*Requires*: `Container` is copyable.

*Effects*: Initialises an instance of `text` with a copy of the underlying
storage of `that`.

*Validation*: no validation is performed.

---

{% highlight cpp %}
text(text&& that);
{% endhighlight %}

*Requires*: `Container` is movable.

*Effects*: Initialises an instance of `text` by moving the underlying storage of
`that`.

*Validation*: no validation is performed.

---

{% highlight cpp %}
template <typename EncodingForm1, typename Container1>
text(text<EncodingForm1, Container1> const& that);
{% endhighlight %}

*Effects*: Initialises an instance of `text` by encoding the code points from
`that` into the underlying storage according to `EncodingForm`.

*Validation*: if the sequence cannot be encoded a `validation_error` is thrown.

---

{% highlight cpp %}
template <typename EncodingForm1, typename Container1, typename Validation>
text(text<EncodingForm1, Container1> const& that, Validation validation);
{% endhighlight %}

*Requires*: `validation` is a validation strategy object.

*Effects*: Initialises an instance of `text` by encoding the code points from
`that` into the underlying storage according to `EncodingForm`.

*Validation*: invalid sequences are treated according to `validation`.

---

{% highlight cpp %}
template <typename CodePointSequence>
explicit text(CodePointSequence&& range);
{% endhighlight %}

*Requires*: `CodePointSequence` is a code point sequence.

*Effects*: Initialises an instance of `text` by encoding the code points from
`that` into the underlying storage according to `EncodingForm`.

*Validation*: if the sequence cannot be encoded a `validation_error` is thrown.

---

{% highlight cpp %}
template <typename CodePointSequence, typename Validation>
text(CodePointSequence&& range, Validation validation);
{% endhighlight %}

*Requires*: `CodePointSequence` is a code point sequence, and `validation` is a
validation strategy object.

*Effects*: Initialises an instance of `text` by encoding the code points from
`that` into the underlying storage according to `EncodingForm`.

*Validation*: invalid sequences are treated according to `validation`.

---

{% highlight cpp %}
explicit text(Container const& storage);
{% endhighlight %}

*Effects*: Initialises an instance of `text` with `storage` as the underlying
storage.

*Validation*: if the data is not valid a `validation_error` is thrown.

---

{% highlight cpp %}
explicit text(Container&& storage);
{% endhighlight %}

*Effects*: Initialises an instance of `text` with `storage` as the underlying
storage.

*Validation*: invalid data is treated according to `validation`.

### Assignment

{% highlight cpp %}
text& operator=(text const& that);
{% endhighlight %}

---

{% highlight cpp %}
text& operator=(text&& that);
{% endhighlight %}

---

{% highlight cpp %}
template <typename EncodingForm1, typename Container1>
text& operator=(text<EncodingForm1, Container1> const& that);
{% endhighlight %}

---

{% highlight cpp %}
text& operator=(code_point const* literal);
{% endhighlight %}

---

{% highlight cpp %}
template <typename CodePointSequence>
void assign(CodePointSequence&& range);
{% endhighlight %}

---

{% highlight cpp %}
template <typename CodePointSequence, typename Validation>
void assign(CodePointSequence&& range, Validation validation);
{% endhighlight %}

---

{% highlight cpp %}
void assign(Container const& storage);
{% endhighlight %}

---

{% highlight cpp %}
void assign(Container&& storage);
{% endhighlight %}

### Iteration

{% highlight cpp %}
using const_iterator = /* unspecified */;
using iterator = const_iterator;
{% endhighlight %}

---

{% highlight cpp %}
const_iterator begin() const;
{% endhighlight %}

---

{% highlight cpp %}
const_iterator end() const;
{% endhighlight %}

### Interoperation

{% highlight cpp %}
Container const& storage() const;
{% endhighlight %}

---

{% highlight cpp %}
Container extract_storage();
{% endhighlight %}

### Emptiness

{% highlight cpp %}
bool empty() const;
{% endhighlight %}

### Appending

{% highlight cpp %}
template <typename CodePointSequence>
iterator append(CodePointSequence&& that);
{% endhighlight %}

---

{% highlight cpp %}
template <typename CodePointSequence, typename Validation>
iterator append(CodePointSequence&& range, Validation validation);
{% endhighlight %}

### Erasure

{% highlight cpp %}
template <typename Range>
iterator erase(Range const& range);
{% endhighlight %}

---

{% highlight cpp %}
iterator erase(iterator first, iterator last);
{% endhighlight %}

### Insertion

{% highlight cpp %}
template <typename CodePointSequence>
iterator insert(iterator at, CodePointSequence&& that);
{% endhighlight %}

---

{% highlight cpp %}
template <typename CodePointSequence, typename Validation>
iterator insert(iterator at, CodePointSequence&& that, Validation validation);
{% endhighlight %}

### Replacement

{% highlight cpp %}
template <typename Range, typename CodePointSequence>
void replace(Range const& range, CodePointSequence&& range);
{% endhighlight %}

---

{% highlight cpp %}
template <typename Range, typename CodePointSequence, typename Validation>
void replace(Range const& range, CodePointSequence&& range, Validation validation);
{% endhighlight %}

---

{% highlight cpp %}
template <typename CodePointSequence>
void replace(iterator from, iterator to, CodePointSequence&& range);
{% endhighlight %}

---

{% highlight cpp %}
template <typename CodePointSequence, typename Validation>
void replace(iterator from, iterator to, CodePointSequence&& range, Validation validation);
{% endhighlight %}

### Canonical equivalence

{% highlight cpp %}
template <typename EncodingForm0, typename Container0, typename EncodingForm1, typename Container1>
bool operator==(text<EncodingForm0, Container0> const& lhs, text<EncodingForm1, Container1> const& rhs);
{% endhighlight %}

---

{% highlight cpp %}
template <typename EncodingForm0, typename Container0, typename EncodingForm1, typename Container1>
bool operator!=(text<EncodingForm0, Container0> const& lhs, text<EncodingForm1, Container1> const& rhs);
{% endhighlight %}

### Default collation

{% highlight cpp %}
template <typename EncodingForm0, typename Container0, typename EncodingForm1, typename Container1>
bool operator<(text<EncodingForm0, Container0> const& lhs, text<EncodingForm1, Container1> const& rhs);
{% endhighlight %}

---

{% highlight cpp %}
template <typename EncodingForm0, typename Container0, typename EncodingForm1, typename Container1>
bool operator>(text<EncodingForm0, Container0> const& lhs, text<EncodingForm1, Container1> const& rhs);
{% endhighlight %}

---

{% highlight cpp %}
template <typename EncodingForm0, typename Container0, typename EncodingForm1, typename Container1>
bool operator<=(text<EncodingForm0, Container0> const& lhs, text<EncodingForm1, Container1> const& rhs);
{% endhighlight %}

---

{% highlight cpp %}
template <typename EncodingForm0, typename Container0, typename EncodingForm1, typename Container1>
bool operator>=(text<EncodingForm0, Container0> const& lhs, text<EncodingForm1, Container1> const& rhs);
{% endhighlight %}

### Concatenation

{% highlight cpp %}
template <typename EncodingForm = /* magic */, typename Container = /* magic */, typename... Ranges>
text<EncodingForm, Container> concat(Ranges&&... ranges);
{% endhighlight %}

