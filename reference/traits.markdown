---
layout: default
title: Traits reference
---

### Header `<ogonek/traits.h++>` synopsis

{% highlight cpp %}
namespace ogonek {
    template <typename EncodingForm>
    using CodeUnit = typename EncodingForm::code_unit;
    template <typename EncodingForm>
    using StateType = typename EncodingForm::state;
    template <typename EncodingForm>
    using is_stateless = std::is_empty<StateType<EncodingForm>>;
} // namespace ogonek
{% endhighlight %}

