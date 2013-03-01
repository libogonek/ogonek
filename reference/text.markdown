---
layout: default
title: ogonek::text reference
---

### Header `<ogonek/text.h++>` synopsis

{% highlight cpp %}
namespace ogonek {
    template <typename EncodingForm,
              typename Container = std::basic_string<CodeUnit<EncodingForm>>>
    class text {
        // Construction
        text(); 
        text(text const& that); 
        text(text&& that); 
        template <typename EncodingForm1, typename Container1>
        text(text<EncodingForm1, Container1> const& that);

        text(code_point const* literal);
        template <typename Validation>
        text(code_point const* literal, Validation validation);

        template <typename CodePointRange>
        explicit text(CodePointRange const& range);
        template <typename CodePointRange, typename Validation>
        text(CodePointRange const& range, Validation validation);

        explicit text(Container const& storage);
        explicit text(Container&& storage);

        // Assignment
        text& operator=(text const& that);
        text& operator=(text&& that);
        template <typename EncodingForm1, typename Container1>
        text& operator=(text<EncodingForm1, Container1> const& that);

        text& operator=(code_point const* literal);
        void assign(code_point const* literal);
        template <typename Validation>
        void assign(code_point const* literal, Validation validation);

        template <typename CodePointRange>
        void assign(CodePointRange const& range);
        template <typename CodePointRange, typename Validation>
        void assign(CodePointRange const& range, Validation validation);

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
        iterator append(text const& that);
        iterator append(text&& that);
        template <typename EncodingForm1, typename Container1>
        iterator append(text<EncodingForm1, Container1> const& that);

        iterator append(code_point const* literal);
        template <typename Validation>
        iterator append(code_point const* literal, Validation validation);

        template <typename CodePointRange>
        iterator append(CodePointRange const& range);
        template <typename CodePointRange, typename Validation>
        iterator append(CodePointRange const& range, Validation validation);

        // Erasure
        iterator erase(iterator first, iterator last);

        // Insertion
        iterator insert(iterator at, text const& that);
        iterator insert(iterator at, text&& that);
        template <typename EncodingForm1, typename Container1>
        iterator insert(iterator at, text<EncodingForm1, Container1> const& that);

        iterator insert(iterator at, code_point const* literal);
        template <typename Validation>
        iterator insert(iterator at, code_point const* literal, Validation validation);

        template <typename CodePointRange>
        iterator insert(iterator at, CodePointRange const& range);
        template <typename CodePointRange, typename Validation>
        iterator insert(iterator at, CodePointRange const& range, Validation validation);

        // Replacement
        void replace(iterator from, iterator to, text const& that);
        void replace(iterator from, iterator to, text&& that);
        template <typename EncodingForm1, typename Container1>
        void replace(iterator from, iterator to, text<EncodingForm1, Container1> const& that);

        void replace(iterator from, iterator to, code_point const* literal);
        template <typename Validation>
        void replace(iterator from, iterator to, code_point const* literal, Validation validation);

        template <typename CodePointRange>
        void replace(iterator from, iterator to, CodePointRange const& range);
        template <typename CodePointRange, typename Validation>
        void replace(iterator from, iterator to, CodePointRange const& range, Validation validation);
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
