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
        explicit text(CodePointSequence&& sequence);
        template <typename CodePointSequence, typename Validation>
        text(CodePointSequence&& sequence, Validation validation);

        explicit text(Container const& storage);
        template <typename Validation>
        text(Container const& storage, Validation validation);
        explicit text(Container&& storage);
        template <typename Validation>
        text(Container&& storage, Validation validation);

        // Assignment
        text& operator=(text const& that);
        text& operator=(text&& that);
        template <typename EncodingForm1, typename Container1>
        text& operator=(text<EncodingForm1, Container1> const& that);
        text& operator=(code_point const* literal);

        template <typename CodePointSequence>
        void assign(CodePointSequence&& sequence);
        template <typename CodePointSequence, typename Validation>
        void assign(CodePointSequence&& sequence, Validation validation);

        void assign(Container const& storage);
        template <typename Validation>
        void assign(Container const& storage, Validation validation);
        void assign(Container&& storage);
        template <typename Validation>
        void assign(Container&& storage, Validation validation);

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
        iterator append(CodePointSequence&& sequence);
        template <typename CodePointSequence, typename Validation>
        iterator append(CodePointSequence&& sequence, Validation validation);

        // Erasure
        template <typename Range>
        iterator erase(Range const& range);
        iterator erase(iterator from, iterator to);

        // Insertion
        template <typename CodePointSequence>
        iterator insert(iterator position, CodePointSequence&& sequence);
        template <typename CodePointSequence, typename Validation>
        iterator insert(iterator position, CodePointSequence&& sequence, Validation validation);

        // Replacement
        template <typename Range, typename CodePointSequence>
        void replace(Range const& range, CodePointSequence&& sequence);
        template <typename Range, typename CodePointSequence, typename Validation>
        void replace(Range const& range, CodePointSequence&& sequence, Validation validation);

        template <typename CodePointSequence>
        void replace(iterator from, iterator to, CodePointSequence&& sequence);
        template <typename CodePointSequence, typename Validation>
        void replace(iterator from, iterator to, CodePointSequence&& sequence, Validation validation);
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
    template <typename EncodingForm = /* magic */, typename Container = /* magic */, typename... CodePointSequences>
    text<EncodingForm, Container> concat(CodePointSequences&&... sequences);
} // namespace ogonek
{% endhighlight %}

### Text class template

`text` template classes hold a sequence of code units on an underlying
container, and expose it as a code point sequence.

{% highlight cpp %}
template <typename EncodingForm, typename Container = std::basic_string<CodeUnit<EncodingForm>>>
class text;
{% endhighlight %}

*Requires*: `EncodingForm::code_unit` is convertible to `Container::value_type`
and `Container::value_type` is convertible to `EncodingForm::code_unit`.

*Invariants*: the underlying storage holds a valid sequence of code units.

### Constructors

{% highlight cpp %}
text();
{% endhighlight %}

*Requires*: `Container` is default-constructible.

*Effects*: initialises an instance of `text` with an empty string.

---

{% highlight cpp %}
text(text const& that);
{% endhighlight %}

*Requires*: `Container` is copyable.

*Effects*: initialises an instance of `text` with a copy of the underlying
storage of `that`.

*Validation*: if the sequence cannot be encoded a `validation_error` is thrown.

---

{% highlight cpp %}
text(text&& that);
{% endhighlight %}

*Requires*: `Container` is movable.

*Effects*: initialises an instance of `text` by moving the underlying storage of
`that`.

*Validation*: no validation is performed.

---

{% highlight cpp %}
template <typename EncodingForm1, typename Container1>
text(text<EncodingForm1, Container1> const& that);
{% endhighlight %}

*Effects*: `text(that, throw_validation_error)`.

---

{% highlight cpp %}
template <typename EncodingForm1, typename Container1, typename Validation>
text(text<EncodingForm1, Container1> const& that, Validation validation);
{% endhighlight %}

*Requires*: `validation` is a validation strategy object.

*Effects*: initialises an instance of `text` by encoding the code points from
`that` into the underlying storage according to `EncodingForm`.

*Validation*: invalid sequences are treated according to `validation`.

---

{% highlight cpp %}
template <typename CodePointSequence>
explicit text(CodePointSequence&& sequence);
{% endhighlight %}

*Effects*: `text(std::forward<CodePointSequence>(sequence), throw_validation_error)`.

---

{% highlight cpp %}
template <typename CodePointSequence, typename Validation>
text(CodePointSequence&& sequence, Validation validation);
{% endhighlight %}

*Requires*: `CodePointSequence` is a code point sequence, and `validation` is a
validation strategy object.

*Effects*: initialises an instance of `text` by encoding the code points from
`that` into the underlying storage according to `EncodingForm`.

*Validation*: invalid sequences are treated according to `validation`.

---

{% highlight cpp %}
explicit text(Container const& storage);
{% endhighlight %}

*Effects*: `text(storage, throw_validation_error)`.

---

{% highlight cpp %}
template <typename Validation>
text(Container const& storage, Validation validation);
{% endhighlight %}

*Requires*: `Container` is copyable.

*Effects*: initialises an instance of `text` with a copy of `storage` as the
underlying storage.

*Validation*: invalid data is treated according to `validation`.

---

{% highlight cpp %}
explicit text(Container&& storage);
{% endhighlight %}

*Effects*: `text(std::move(storage), throw_validation_error)`.

---

{% highlight cpp %}
template <typename Validation>
text(Container&& storage, Validation validation);
{% endhighlight %}

*Requires*: `Container` is movable.

*Effects*: initialises an instance of `text` by moving `storage` into underlying
storage.

*Validation*: invalid data is treated according to `validation`.

### Assignment

{% highlight cpp %}
text& operator=(text const& that);
{% endhighlight %}

*Requires*: `Container` is copy-assignable.

*Effects*: copy-assigns the underlying storage of `that` into this instance's
underlying storage.

*Validation*: no validation is performed.

*Returns*: `*this`.

---

{% highlight cpp %}
text& operator=(text&& that);
{% endhighlight %}

*Requires*: `Container` is move-assignable.

*Effects*: move-assigns the underlying storage of `that` into this instance's
underlying storage.

*Validation*: no validation is performed.

*Returns*: `*this`.

---

{% highlight cpp %}
template <typename EncodingForm1, typename Container1>
text& operator=(text<EncodingForm1, Container1> const& that);
{% endhighlight %}

*Effects*: `assign(that)`.

*Returns*: `*this`.

---

{% highlight cpp %}
text& operator=(code_point const* literal);
{% endhighlight %}

*Requires*: `literal` is a pointer to a null-terminated array of code points.

*Effects*: `assign(literal)`.

*Returns*: `*this`.

---

{% highlight cpp %}
template <typename CodePointSequence>
void assign(CodePointSequence&& sequence);
{% endhighlight %}

*Effects*: `assign(std::forward<CodePointSequence>(sequence), throw_validation_error)`.

---

{% highlight cpp %}
template <typename CodePointSequence, typename Validation>
void assign(CodePointSequence&& sequence, Validation validation);
{% endhighlight %}

*Requires*: `CodePointSequence` is a code point sequence, and `validation` is a
validation strategy object.

*Effects*: encodes the code points from `sequence` into this instance's
underlying storage.

*Validation*: invalid sequences are treated according to `validation`.

---

{% highlight cpp %}
void assign(Container const& storage);
{% endhighlight %}

*Effects*: `assign(storage, throw_validation_error)`.

---

{% highlight cpp %}
template <typename Validation>
void assign(Container const& storage, Validation validation);
{% endhighlight %}

*Requires*: `Container` is copy-assignable.

*Effects*: copy-assigns `storage` into this instance's underlying storage.

*Validation*: invalid data is treated according to `validation`.

---

{% highlight cpp %}
void assign(Container&& storage);
{% endhighlight %}

*Effects*: `assign(std::move(storage), throw_validation_error)`.

---

{% highlight cpp %}
template <typename Validation>
void assign(Container&& storage, Validation validation);
{% endhighlight %}

*Requires*: `Container` is move-assignable.

*Effects*: move-assigns `storage` into this instance's underlying storage.

*Validation*: invalid data is treated according to `validation`.

### Iteration

{% highlight cpp %}
using const_iterator = /* unspecified */;
using iterator = const_iterator;
{% endhighlight %}

These types are at least forward iterators with `code_point` as their value
type.

---

{% highlight cpp %}
const_iterator begin() const;
{% endhighlight %}

*Returns*: an iterator to the beginning of this code point sequence.

---

{% highlight cpp %}
const_iterator end() const;
{% endhighlight %}

*Returns*: an iterator to the end of this code point sequence.

### Interoperation

{% highlight cpp %}
Container const& storage() const;
{% endhighlight %}

*Returns*: a reference to the underlying storage.

---

{% highlight cpp %}
Container extract_storage();
{% endhighlight %}

*Effects*: moves this instance's underlying storage out.

*Returns*: the underlying storage.

### Emptiness

{% highlight cpp %}
bool empty() const;
{% endhighlight %}

*Returns*: `true` is this instance is an empty sequence; `false` otherwise.

### Appending

{% highlight cpp %}
template <typename CodePointSequence>
iterator append(CodePointSequence&& sequence);
{% endhighlight %}

*Effects*: `append(std::forward<CodePointSequence>(sequence), throw_validation_error)`.

---

{% highlight cpp %}
template <typename CodePointSequence, typename Validation>
iterator append(CodePointSequence&& sequence, Validation validation);
{% endhighlight %}

*Requires*: `CodePointSequence` is a code point sequence, and `validation` is a
validation strategy object.

*Effects*: encodes the code points from `that` at the end of this instance's
underlying storage according to `EncodingForm`.

*Returns*: an iterator to the beginning of the inserted values.

*Validation*: invalid sequences are treated according to `validation`.

### Erasure

{% highlight cpp %}
template <typename Range>
iterator erase(Range const& range);
{% endhighlight %}

*Effects*: `erase(boost::begin(range), boost::end(range))`.

---

{% highlight cpp %}
iterator erase(iterator from, iterator to);
{% endhighlight %}

*Requires*: [`from`, `to`) is a range of iterators into this instance.

*Effects*: removes the code points in [`from`, `to`) from the underlying
storage.

*Returns*: an iterator to the code point after the removed range.

### Insertion

{% highlight cpp %}
template <typename CodePointSequence>
iterator insert(iterator position, CodePointSequence&& sequence);
{% endhighlight %}

*Effects*: `insert(position, std::forward<CodePointSequence>(sequence))`.

---

{% highlight cpp %}
template <typename CodePointSequence, typename Validation>
iterator insert(iterator position, CodePointSequence&& sequence, Validation validation);
{% endhighlight %}

*Requires*: `CodePointSequence` is a code point sequence, `validation` is a
validation strategy object, and `position` is an iterator into this instance.

*Effects*: inserts the code points from `sequence` at starting at `position`, by
encoding them into the underlying storage according to `EncodingForm`.

*Validation*: invalid sequences are treated according to `validation`.

### Replacement

{% highlight cpp %}
template <typename Range, typename CodePointSequence>
void replace(Range const& range, CodePointSequence&& sequence);
{% endhighlight %}

*Effects*: `replace(boost::begin(range), boost::end(range), std::forward<CodePointSequence>(sequence))`.

---

{% highlight cpp %}
template <typename Range, typename CodePointSequence, typename Validation>
void replace(Range const& range, CodePointSequence&& sequence, Validation validation);
{% endhighlight %}

*Effects*: `replace(boost::begin(range), boost::end(range), std::forward<CodePointSequence>(sequence), throw_validation_error)`.

---

{% highlight cpp %}
template <typename CodePointSequence>
void replace(iterator from, iterator to, CodePointSequence&& sequence);
{% endhighlight %}

*Effects*: `replace(from, to, std::forward<CodePointSequence>(sequence), throw_validation_error)`.

---

{% highlight cpp %}
template <typename CodePointSequence, typename Validation>
void replace(iterator from, iterator to, CodePointSequence&& sequence, Validation validation);
{% endhighlight %}

*Requires*: `CodePointSequence` is a code point sequence, `validation` is a
validation strategy object, and [`from`, `to`) is a range of iterators into this
instance.

*Effects*: replaces the code points in [`from`, `to`) in the underlying storage by
encoding the code points from `sequence` according to `EncodingForm`.

*Validation*: invalid sequences are treated according to `validation`.

### Canonical equivalence

{% highlight cpp %}
template <typename EncodingForm0, typename Container0, typename EncodingForm1, typename Container1>
bool operator==(text<EncodingForm0, Container0> const& lhs, text<EncodingForm1, Container1> const& rhs);
{% endhighlight %}

*Returns*: `true` if the sequence of code points in `lhs` is canonically
equivalent to the sequence of code points in `rhs`; `false` otherwise.

---

{% highlight cpp %}
template <typename EncodingForm0, typename Container0, typename EncodingForm1, typename Container1>
bool operator!=(text<EncodingForm0, Container0> const& lhs, text<EncodingForm1, Container1> const& rhs);
{% endhighlight %}

*Returns*: `!(lhs == rhs)`.

### Default collation

{% highlight cpp %}
template <typename EncodingForm0, typename Container0, typename EncodingForm1, typename Container1>
bool operator<(text<EncodingForm0, Container0> const& lhs, text<EncodingForm1, Container1> const& rhs);
{% endhighlight %}

*Returns*: `true` if `lhs` is ordered before `rhs` according to the Unicode
default collation algorithm.

---

{% highlight cpp %}
template <typename EncodingForm0, typename Container0, typename EncodingForm1, typename Container1>
bool operator>(text<EncodingForm0, Container0> const& lhs, text<EncodingForm1, Container1> const& rhs);
{% endhighlight %}

*Returns*: `rhs < lhs`.

---

{% highlight cpp %}
template <typename EncodingForm0, typename Container0, typename EncodingForm1, typename Container1>
bool operator<=(text<EncodingForm0, Container0> const& lhs, text<EncodingForm1, Container1> const& rhs);
{% endhighlight %}

*Returns*: `!(lhs > rhs)`.

---

{% highlight cpp %}
template <typename EncodingForm0, typename Container0, typename EncodingForm1, typename Container1>
bool operator>=(text<EncodingForm0, Container0> const& lhs, text<EncodingForm1, Container1> const& rhs);
{% endhighlight %}

*Returns*: `!(rhs > lhs)`.

### Concatenation

{% highlight cpp %}
template <typename EncodingForm = /* magic */, typename Container = /* magic */, typename... CodePointSequences>
text<EncodingForm, Container> concat(CodePointSequences&&... sequences);
{% endhighlight %}

*Effects*: `concat(throw_validation_error, std::forward<CodePointSequences>(sequences)...)`.

{% highlight cpp %}
template <typename EncodingForm = /* magic */, typename Container = /* magic */, typename Validation, typename... CodePointSequences>
text<EncodingForm, Container> concat(Validation validation, CodePointSequences&&... sequences);
{% endhighlight %}

*Requires*: all `CodePointSequences` are code point sequences. If `EncodingForm`
or `Container` are not explicitly provided, there must be at least one sequence
whose type is an instantiation of `text` and there must be no sequences with
types that are different instantiations of `text`; the default values of those
template parameters are those used in that instantiation.

*Returns*: an instance of `text` with the sequence of code points resulting from
the concatenation of `sequences`.

*Validation*: invalid sequences are treated according to `validation`.

