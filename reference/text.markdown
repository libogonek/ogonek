---
layout: default
title: ogonek::text reference
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

        template <typename CodePointRange>
        explicit text(CodePointRange&& range);
        template <typename CodePointRange, typename Validation>
        text(CodePointRange&& range, Validation validation);

        explicit text(Container const& storage);
        explicit text(Container&& storage);

        // Assignment
        text& operator=(text const& that);
        text& operator=(text&& that);
        template <typename EncodingForm1, typename Container1>
        text& operator=(text<EncodingForm1, Container1> const& that);
        text& operator=(code_point const* literal);

        template <typename CodePointRange>
        void assign(CodePointRange&& range);
        template <typename CodePointRange, typename Validation>
        void assign(CodePointRange&& range, Validation validation);

        void assign(Container const& storage);
        void assign(Container&& storage);

        // Iteration
        using const_iterator = /* unspecified */;
        using iterator = const_iterator;

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;

        // Interoperation
        Container const& storage() const;
        Container extract_storage();

        // Test for emptiness
        bool empty() const;

        // Appending
        template <typename CodePointRange>
        iterator append(CodePointRange&& that);
        template <typename CodePointRange, typename Validation>
        iterator append(CodePointRange&& range, Validation validation);

        // Erasure
        iterator erase(iterator first, iterator last);
        template <typename Range>
        iterator erase(Range const& range);

        // Insertion
        template <typename CodePointRange>
        iterator insert(iterator at, CodePointRange&& that);
        template <typename CodePointRange, typename Validation>
        iterator insert(iterator at, CodePointRange&& that, Validation validation);

        // Replacement
        template <typename Range, typename CodePointRange>
        void replace(Range const& range, CodePointRange&& range);
        template <typename Range, typename CodePointRange, typename Validation>
        void replace(Range const& range, CodePointRange&& range, Validation validation);

        template <typename CodePointRange>
        void replace(iterator from, iterator to, CodePointRange&& range);
        template <typename CodePointRange, typename Validation>
        void replace(iterator from, iterator to, CodePointRange&& range, Validation validation);
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
} // namespace ogonek
{% endhighlight %}
