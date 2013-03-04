// Wheels - various C++ utilities
//
// Generated: 2012-06-15 04:48:14.941000
//
// -----------------------------------------------------

// Wheels - various C++ utilities
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// make_unique helper, similar to make_shared

#ifndef WHEELS_SMART_PTR_UNIQUE_PTR_HPP
#define WHEELS_SMART_PTR_UNIQUE_PTR_HPP

// #included from: ../allocator.h++
// Wheels - various C++ utilities
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Allocator utilities

#ifndef WHEELS_ALLOCATOR_HPP
#define WHEELS_ALLOCATOR_HPP

// #included from: type_traits.h++
// Wheels - various C++ utilities
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Type traits

#ifndef WHEELS_TYPE_TRAITS_HPP
#define WHEELS_TYPE_TRAITS_HPP

// #included from: detail/config.h++
// Wheels - various C++ utilities
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Configuration and compiler workarounds

#ifndef WHEELS_DETAIL_CONFIG_HPP
#define WHEELS_DETAIL_CONFIG_HPP

//! Feature test macro
#define WHEELS_HAS_FEATURE(X) (defined(WHEELS_HAS_FEATURE_##X) || ((WHEELS_COMPILER_FEATURES & (1 << WHEELS_##X)) != 0))
//! Bug test macro
#define WHEELS_HAS_ISSUE(X) (defined(WHEELS_ISSUE_##X))

// Bugs currently considered:
// INCOMPLETE_IS_CONVERTIBLE    : std::is_convertible is not complete in libstdc++
// DURATION_NO_CONSTEXPR        : std::duration has no constexpr members in libc++
// BROKEN_CONCEPT_CHECK         : clang doesn't seem to play nice with Boost.ConceptCheck
// BROKEN_OVERLOAD_MACRO        : clang doesn't seem to play nice with the use of Boost.Preprocessor in WHEELS_OVERLOAD

//! _Pragma helper that stringizes arguments
#define WHEELS_PRAGMA(...) _Pragma(#__VA_ARGS__)

#define WHEELS_EXPECT_SEMICOLON static_assert(true, "")

// Compiler dependent macros defined by this header:
// WHEELS_UNREACHABLE       : marks code that is not reachable
// WHEELS_WARNING(MESSAGE)  : generates a warning message with the given string literal

// Standard library dependent macros defined by this header:
// WHEELS_STD_TUPLE_LAYOUT_OPTIMAL  : if std::tuple already has optimal layout
// WHEELS_STD_TUPLE_LAYOUT_STRAIGHT : if std::tuple lays fields in order of template parameters
// WHEELS_STD_TUPLE_LAYOUT_REVERSED : if std::tuple lays fields in reverse order of template parameters
// WHEELS_STD_TUPLE_LAYOUT_UNKNOWN  : if std::tuple layout is unknown, or not one of the above

// C++11 features
//  from clang's list
#define WHEELS_CXX_ACCESS_CONTROL_SFINAE            1
#define WHEELS_CXX_ALIAS_TEMPLATES                  2
#define WHEELS_CXX_ALIGNAS                          3
#define WHEELS_CXX_ATTRIBUTES                       4
#define WHEELS_CXX_CONSTEXPR                        5
#define WHEELS_CXX_DECLTYPE                         6
#define WHEELS_CXX_DEFAULT_FUNCTION_TEMPLATE_ARGS   7
#define WHEELS_CXX_DEFAULTED_FUNCTIONS              8
#define WHEELS_CXX_DELEGATING_CONSTRUCTORS          9
#define WHEELS_CXX_DELETED_FUNCTIONS               10
#define WHEELS_CXX_EXPLICIT_CONVERSIONS            11
#define WHEELS_CXX_GENERALIZED_INITIALIZERS        12
#define WHEELS_CXX_IMPLICIT_MOVES                  13
#define WHEELS_CXX_INHERITING_CONSTRUCTORS         14
#define WHEELS_CXX_INLINE_NAMESPACES               15
#define WHEELS_CXX_LAMBDAS                         16
#define WHEELS_CXX_LOCAL_TYPE_TEMPLATE_ARGS        17
#define WHEELS_CXX_NOEXCEPT                        18
#define WHEELS_CXX_NONSTATIC_MEMBER_INIT           19
#define WHEELS_CXX_NULLPTR                         20
#define WHEELS_CXX_OVERRIDE_CONTROL                21
#define WHEELS_CXX_REFERENCE_QUALIFIED_FUNCTIONS   22
#define WHEELS_CXX_RANGE_FOR                       23
#define WHEELS_CXX_RAW_STRING_LITERALS             24
#define WHEELS_CXX_RVALUE_REFERENCES               25
#define WHEELS_CXX_STATIC_ASSERT                   26
#define WHEELS_CXX_AUTO_TYPE                       27
#define WHEELS_CXX_STRONG_ENUMS                    28
#define WHEELS_CXX_TRAILING_RETURN                 29
#define WHEELS_CXX_UNICODE_LITERALS                30
#define WHEELS_CXX_UNRESTRICTED_UNIONS             31
#define WHEELS_CXX_USER_LITERALS                   32
#define WHEELS_CXX_VARIADIC_TEMPLATES              33

// some standard libraries don't support aligned_union yet
#define WHEELS_CXX_ALIGNED_UNION                    0
// some standard libraries don't support threads yet
#define WHEELS_CXX_THREADS                          0

// Compiler detection
#if defined(__clang__)
// #included from: clang.h++
// Wheels - various C++ utilities
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Clang feature detection and workarounds

#ifndef WHEELS_DETAIL_CLANG_HPP
#define WHEELS_DETAIL_CLANG_HPP

// Clang feature set can be (mostly) computed :)
#define WHEELS_COMPILER_FEATURES (\
    (__has_feature(cxx_access_control_sfinae)          << WHEELS_CXX_ACCESS_CONTROL_SFINAE)            | \
    (__has_feature(cxx_alias_templates)                << WHEELS_CXX_ALIAS_TEMPLATES)                  | \
    (__has_feature(cxx_alignas)                        << WHEELS_CXX_ALIGNAS)                          | \
    (__has_feature(cxx_attributes)                     << WHEELS_CXX_ATTRIBUTES)                       | \
    (__has_feature(cxx_constexpr)                      << WHEELS_CXX_CONSTEXPR)                        | \
    (__has_feature(cxx_decltype)                       << WHEELS_CXX_DECLTYPE)                         | \
    (__has_feature(cxx_default_function_template_args) << WHEELS_CXX_DEFAULT_FUNCTION_TEMPLATE_ARGS)   | \
    (__has_feature(cxx_defaulted_functions)            << WHEELS_CXX_DEFAULTED_FUNCTIONS)              | \
    (__has_feature(cxx_delegating_constructors)        << WHEELS_CXX_DELEGATING_CONSTRUCTORS)          | \
    (__has_feature(cxx_deleted_functions)              << WHEELS_CXX_DELETED_FUNCTIONS)                | \
    (__has_feature(cxx_explicit_conversions)           << WHEELS_CXX_EXPLICIT_CONVERSIONS)             | \
    (__has_feature(cxx_generalized_initializers)       << WHEELS_CXX_GENERALIZED_INITIALIZERS)         | \
    (__has_feature(cxx_implicit_moves)                 << WHEELS_CXX_IMPLICIT_MOVES)                   | \
    (__has_feature(cxx_inheriting_constructors)        << WHEELS_CXX_INHERITING_CONSTRUCTORS)          | \
    (__has_feature(cxx_inline_namespaces)              << WHEELS_CXX_INLINE_NAMESPACES)                | \
    (__has_feature(cxx_lambdas)                        << WHEELS_CXX_LAMBDAS)                          | \
    (__has_feature(cxx_local_type_template_args)       << WHEELS_CXX_LOCAL_TYPE_TEMPLATE_ARGS)         | \
    (__has_feature(cxx_noexcept)                       << WHEELS_CXX_NOEXCEPT)                         | \
    (__has_feature(cxx_nonstatic_member_init)          << WHEELS_CXX_NONSTATIC_MEMBER_INIT)            | \
    (__has_feature(cxx_nullptr)                        << WHEELS_CXX_NULLPTR)                          | \
    (__has_feature(cxx_override_control)               << WHEELS_CXX_OVERRIDE_CONTROL)                 | \
    (__has_feature(cxx_reference_qualified_functions)  << WHEELS_CXX_REFERENCE_QUALIFIED_FUNCTIONS)    | \
    (__has_feature(cxx_range_for)                      << WHEELS_CXX_RANGE_FOR)                        | \
    (__has_feature(cxx_raw_string_literals)            << WHEELS_CXX_RAW_STRING_LITERALS)              | \
    (__has_feature(cxx_rvalue_references)              << WHEELS_CXX_RVALUE_REFERENCES)                | \
    (__has_feature(cxx_static_assert)                  << WHEELS_CXX_STATIC_ASSERT)                    | \
    (__has_feature(cxx_auto_type)                      << WHEELS_CXX_AUTO_TYPE)                        | \
    (__has_feature(cxx_strong_enums)                   << WHEELS_CXX_STRONG_ENUMS)                     | \
    (__has_feature(cxx_trailing_return)                << WHEELS_CXX_TRAILING_RETURN)                  | \
    (__has_feature(cxx_unicode_literals)               << WHEELS_CXX_UNICODE_LITERALS)                 | \
    (__has_feature(cxx_unrestricted_unions)            << WHEELS_CXX_UNRESTRICTED_UNIONS)              | \
    (__has_feature(cxx_user_literals)                  << WHEELS_CXX_USER_LITERALS)                    | \
    (__has_feature(cxx_variadic_templates)             << WHEELS_CXX_VARIADIC_TEMPLATES)               | \
0)

#define WHEELS_UNREACHABLE do { __builtin_unreachable(); } while(false)

#define WHEELS_WARNING(MESSAGE) \
    WHEELS_PRAGMA(message #MESSAGE) \
    WHEELS_EXPECT_SEMICOLON

#define WHEELS_ISSUE_BROKEN_CONCEPT_CHECK
#define WHEELS_ISSUE_BROKEN_OVERLOAD_MACRO

#endif // WHEELS_DETAIL_CLANG_HPP

#elif defined(__GNUC__)
// #included from: gcc.h++
// Wheels - various C++ utilities
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// GCC feature detection and workarounds

#ifndef WHEELS_DETAIL_GCC_HPP
#define WHEELS_DETAIL_GCC_HPP

#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

// GCC feature set has to be hardcoded per version
#if GCC_VERSION >= 40700
    #define WHEELS_COMPILER_FEATURES 0x3FFBFBFE6
#else
    #error "GCC >=4.7 is required"
#endif

#define WHEELS_UNREACHABLE do { __builtin_unreachable(); } while(false)

#define WHEELS_WARNING(MESSAGE) \
    WHEELS_PRAGMA(message #MESSAGE) \
    WHEELS_EXPECT_SEMICOLON

// alignas emulation
namespace wheels {
    namespace emulation_detail {
        using size_t = decltype(sizeof(0));

        constexpr size_t max(size_t n) { return n; }

        template <typename... Tail>
        constexpr size_t max(size_t a, size_t b, Tail... tail) {
            return max(a > b? a : b, tail...);
        }

        template <typename... T>
        constexpr size_t max_alignment() {
            return max_alignment<alignof(T)...>();
        }

        template <size_t... N>
        constexpr size_t max_alignment() {
            return max(N...);
        }
    }
}
#define alignas(...) \
    __attribute__((__aligned__(::wheels::emulation_detail::max_alignment<__VA_ARGS__>())))
#define WHEELS_HAS_FEATURE_CXX_ALIGNAS

#endif // WHEELS_DETAIL_GCC_HPP

#else
// #included from: compiler-generic.h++
// Wheels - various C++ utilities
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Generic compiler feature detection and workarounds

#ifndef WHEELS_DETAIL_COMPILER_GENERIC_HPP
#define WHEELS_DETAIL_COMPILER_GENERIC_HPP

#ifndef WHEELS_UNREACHABLE
    #define WHEELS_UNREACHABLE do { throw "the impossible happened!"; } while(false)
#endif

#ifndef WHEELS_WARNING
    #define WHEELS_WARNING(MESSAGE) WHEELS_EXPECT_SEMICOLON
#endif

#endif // WHEELS_DETAIL_COMPILER_GENERIC_HPP

#endif

// Standard library detection
// Needs to include a stdlib header for detection :(
#include <utility>
#if defined(__GLIBCXX__)
// #included from: libstdc++.h++
// Wheels - various C++ utilities
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// libstdc++ feature detection and workarounds

#ifndef WHEELS_DETAIL_LIBSTDCPP_HPP
#define WHEELS_DETAIL_LIBSTDCPP_HPP

#define WHEELS_STD_TUPLE_LAYOUT_REVERSED

#define WHEELS_ISSUE_INCOMPLETE_IS_CONVERTIBLE

#if defined(_GLIBCXX_HAS_GTHREADS)
#define WHEELS_HAS_FEATURE_CXX_THREADS
#endif

#endif // WHEELS_DETAIL_LIBSTDCPP_HPP

#elif defined(_LIBCPP_VERSION)
// #included from: libc++.h++
// Wheels - various C++ utilities
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// libc++ feature detection and workarounds

#ifndef WHEELS_DETAIL_LIBCPP_HPP
#define WHEELS_DETAIL_LIBCPP_HPP

#define WHEELS_STD_TUPLE_LAYOUT_STRAIGHT

#define WHEELS_ISSUE_DURATION_NO_CONSTEXPR

#define WHEELS_HAS_FEATURE_CXX_THREADS

#endif // WHEELS_DETAIL_LIBCPP_HPP

#else
// #included from: stdlib-generic.h++
// Wheels - various C++ utilities
// Wheels - various C++ utilities
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Generic standard library feature detection and workarounds

#ifndef WHEELS_DETAIL_STDLIB_GENERIC_HPP
#define WHEELS_DETAIL_STDLIB_GENERIC_HPP

#define WHEELS_STD_TUPLE_LAYOUT_UNKNOWN

#endif // WHEELS_DETAIL_STDLIB_GENERIC_HPP

#endif

#endif // WHEELS_DETAIL_CONFIG_HPP

// #included from: meta.h++
// Wheels - various C++ utilities
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Meta-programming facilities

#ifndef WHEELS_META_HPP
#define WHEELS_META_HPP

#include <type_traits>

namespace wheels {
    //! Metafunction invocation
    template <typename T>
    using Invoke = typename T::type;

    //! Identity metafunction
    template <typename T>
    struct identity {
        using type = T;
    };

    //! Identity template alias
    template <typename T>
    using Identity = Invoke<identity<T>>;
    //! Deducible identity template alias
    template <typename T>
    using Alias = T;
    //! Not deducible identity template alias
    template <typename T>
    using NotDeducible = Identity<T>;

    //! Meta-boolean type with parameters for when dependent contexts are needed
    template <bool B, typename...>
    struct dependent_bool_type : std::integral_constant<bool, B> {};

    //! Boolean integral_constant alias
    template <bool B, typename... T>
    using Bool = Invoke<dependent_bool_type<B, T...>>;

    //! Integer integral_constant alias
    template <int I>
    using Int = std::integral_constant<int, I>;

    template <typename... T>
    struct count : Int<0> {};
    template <typename Head, typename... Tail>
    struct count<Head, Tail...> : Int<(Head::value? 1 : 0) + count<Tail...>::value> {};

    //! If-then-else metafunction
    template <typename Condition, typename Then, typename Else>
    using Conditional = Invoke<std::conditional<Condition::value, Then, Else>>;

    //! Logical negation metafunction
    template <typename T>
    using Not = Bool<!T::value>;

    //! Logical disjunction metafunction
    template <typename... T>
    struct Any : Bool<false> {};
    template <typename Head, typename... Tail>
    struct Any<Head, Tail...> : Conditional<Head, Bool<true>, Any<Tail...>> {};

    //! Logical conjunction metafunction
    template <typename... T>
    struct All : Bool<true> {};
    template <typename Head, typename... Tail>
    struct All<Head, Tail...> : Conditional<Head, All<Tail...>, Bool<false>> {};

    //! Minimum metafunction
    template <typename Head, typename... Tail>
    struct min : Head {};
    template <typename T, typename U, typename... Tail>
    struct min<T, U, Tail...> : min<Conditional<Bool<(T::value < U::value)>, T, U>, Tail...> {};

    //! Maximum metafunction
    template <typename Head, typename... Tail>
    struct max : Head {};
    template <typename T, typename U, typename... Tail>
    struct max<T, U, Tail...> : max<Conditional<Bool<(T::value > U::value)>, T, U>, Tail...> {};

    namespace meta_detail {
        enum class enabler { _ };
    } // namespace meta_detail
    //! Dummy for defaulting EnableIf
    constexpr auto _ = meta_detail::enabler::_;
    //! SFINAE enabler
    template <typename... T>
    using EnableIf = Invoke<std::enable_if<All<T...>::value, decltype(_)>>;
    //! SFINAE disabler
    template <typename... T>
    using DisableIf = Invoke<std::enable_if<Not<All<T...>>::value, decltype(_)>>;

    //! Marker for deducible template type parameters
    struct deduced;

    //! Overload resolution-powered trait builder
    template <typename Tester, typename... T>
    using TraitOf = decltype(Tester::template test<T...>(0));
} // namespace wheels

#endif // WHEELS_META_HPP

#include <type_traits>
#include <functional>
#include <utility>

#if !WHEELS_HAS_FEATURE(CXX_ALIGNED_UNION)

    // aligned_union emulation
    namespace std {
        template <decltype(sizeof(0)) Len, typename... T>
        struct aligned_union;
    } // namespace std

#endif // !WHEELS_HAS_FEATURE(CXX_ALIGNED_UNION)

namespace wheels {
    // const-volatile modifications
    //! Removes top-level const
    template <typename T>
    using RemoveConst = Invoke<std::remove_const<T>>;
    //! Removes top-level volatile
    template <typename T>
    using RemoveVolatile = Invoke<std::remove_volatile<T>>;
    //! Removes top-level cv-qualifiers
    template <typename T>
    using RemoveCv = Invoke<std::remove_cv<T>>;
    //! Adds top-level const
    template <typename T>
    using AddConst = Invoke<std::add_const<T>>;
    //! Adds top-level volatile
    template <typename T>
    using AddVolatile = Invoke<std::add_volatile<T>>;
    //! Adds top-level const and volatile
    template <typename T>
    using AddCv = Invoke<std::add_cv<T>>;

    // reference modifications
    //! Removes reference qualifiers
    template <typename T>
    using RemoveReference = Invoke<std::remove_reference<T>>;
    //! Adds an lvalue reference qualifier
    template <typename T>
    using AddLvalueReference = Invoke<std::add_lvalue_reference<T>>;
    //! Adds an rvalue reference qualifier
    template <typename T>
    using AddRvalueReference = Invoke<std::add_rvalue_reference<T>>;

    // sign modifications
    //! Obtains the signed counterpart of a given type
    template <typename T>
    using MakeSigned = Invoke<std::make_signed<T>>;
    //! Obtains the unsigned counterpart of a given type
    template <typename T>
    using MakeUnsigned = Invoke<std::make_unsigned<T>>;

    // array modifications
    //! Removes an array type's top-level extent
    template <typename T>
    using RemoveExtent = Invoke<std::remove_extent<T>>;
    //! Removes all the extents of an array type
    template <typename T>
    using RemoveAllExtents = Invoke<std::remove_all_extents<T>>;

    // pointer modifications
    //! Removes a pointer qualifier
    template <typename T>
    using RemovePointer = Invoke<std::remove_pointer<T>>;
    //! Adds a pointer qualifier
    template <typename T>
    using AddPointer = Invoke<std::add_pointer<T>>;

    namespace traits_detail {
        template <typename>
        struct extract_alignment;
        template <std::size_t Len, std::size_t Align>
        struct extract_alignment<std::aligned_storage<Len, Align>> : std::integral_constant<std::size_t, Align> {};

        template <std::size_t Len>
        struct default_alignment : extract_alignment<std::aligned_storage<Len>> {};
    } // namespace traits_detail

    // other transformations
    //! Provides storage with the given length and alignment
    template <std::size_t Len, std::size_t Align = traits_detail::default_alignment<Len>::value>
    using AlignedStorage = Invoke<std::aligned_storage<Len, Align>>;
    //! Provides storage properly aligned for the given types
    template <std::size_t Len, typename... T>
    using AlignedUnion = Invoke<std::aligned_union<Len, T...>>;
    //! Emulates pass-by-value semantics
    template <typename T>
    using Decay = Invoke<std::decay<T>>;
    //! Removes all reference and cv qualifiers
    template <typename T>
    using Unqualified = RemoveCv<RemoveReference<T>>;

    //! ???
    template <typename... T>
    using CommonType = Invoke<std::common_type<T...>>;
    //! Obtains the underlying type of an enum
    template <typename T>
    using UnderlyingType = Invoke<std::underlying_type<T>>;

    // propagations
    //! Produces Destination as const if Source is const
    template <typename Source, typename Destination>
    using WithConstOf = Conditional<std::is_const<Source>, AddConst<Destination>, Destination>;
    //! Produces Destination as volatile if Source is volatile
    template <typename Source, typename Destination>
    using WithVolatileOf = Conditional<std::is_volatile<Source>, AddVolatile<Destination>, Destination>;
    //! Produces Destination as const if Source is const, and volatile if Source is volatile
    template <typename Source, typename Destination>
    using WithCvOf = WithConstOf<Source, WithVolatileOf<Source, Destination>>;

    //! Produces Destination with the same value category of Source
    template <typename Source, typename Destination>
    using WithValueCategoryOf =
        Conditional<std::is_lvalue_reference<Source>,
            AddLvalueReference<Destination>,
            Conditional<std::is_rvalue_reference<Source>,
                AddRvalueReference<Destination>,
                Destination
            >
        >;

    //! Produces Destination with the same reference and cv-qualifiers of Source
    template <typename Source, typename Destination>
    using WithQualificationsOf = WithValueCategoryOf<Source, WithCvOf<RemoveReference<Source>, Destination>>;

    // other traits
    //! Tests if two types are the same after stripping all qualifiers
    template <typename T, typename U>
    using is_related = std::is_same<Unqualified<T>, Unqualified<U>>;

    //! Obtains the value_type nested type of T
    template <typename T>
    struct value_type { using type = typename T::value_type; };

    //! Template alias to obtain the value_type nested type of T
    template <typename T>
    using ValueType = Invoke<value_type<T>>;

    //! Tests if T is a specialization of Template
    template <typename T, template <typename...> class Template>
    struct is_specialization_of : Bool<false> {};
    template <template <typename...> class Template, typename... Args>
    struct is_specialization_of<Template<Args...>, Template> : Bool<true> {};

    //! Provides storage properly aligned for any given T
    template <typename... T>
    struct storage_for : std::aligned_union<1, T...> {};
    template <typename T>
    struct storage_for<T> : std::aligned_storage<sizeof(T), alignof(T)> {};
    template <typename... T>
    using StorageFor = Invoke<storage_for<T...>>;

    //! Obtains the class of a member function pointer
    template <typename T>
    struct class_of : identity<T> {};
    template <typename Signature, typename Class>
    struct class_of<Signature Class::*> : identity<Class> {};
    template <typename T>
    using ClassOf = Invoke<class_of<T>>;
    //! Obtains the function type of a member function pointer
    template <typename T>
    struct signature_of : identity<T> {};
    template <typename Signature, typename Class>
    struct signature_of<Signature Class::*> : identity<Signature> {};
    template <typename T>
    using SignatureOf = Invoke<signature_of<T>>;

    namespace invoke_detail {
        template <typename Fun, typename Obj, typename... Args,
                  EnableIf<std::is_member_function_pointer<Unqualified<Fun>>,
                           std::is_base_of<ClassOf<Unqualified<Fun>>, Unqualified<Obj>>
                          > = _>
        auto invoke(Fun&& fun, Obj&& obj, Args&&... args)
        -> decltype((std::declval<Obj>().*std::declval<Fun>())(std::declval<Args>()...)) {
            return (std::forward<Obj>(obj).*std::forward<Fun>(fun))(std::forward<Args>(args)...);
        }

        template <typename Fun, typename Obj, typename... Args,
                  EnableIf<std::is_member_function_pointer<Unqualified<Fun>>,
                           Not<std::is_base_of<ClassOf<Unqualified<Fun>>, Unqualified<Obj>>>
                          > = _>
        auto invoke(Fun&& fun, Obj&& obj, Args&&... args)
        -> decltype(((*std::declval<Obj>()).*std::declval<Fun>())(std::declval<Args>()...)) {
            return ((*std::forward<Obj>(obj)).*std::forward<Fun>(fun))(std::forward<Args>(args)...);
        }

        template <typename Fun, typename Obj,
                  EnableIf<std::is_member_object_pointer<Unqualified<Fun>>,
                           std::is_base_of<ClassOf<Unqualified<Fun>>, Unqualified<Obj>>
                          > = _>
        auto invoke(Fun&& fun, Obj&& obj)
        -> decltype(std::declval<Obj>().*std::declval<Fun>()) {
            return std::forward<Obj>(obj).*std::forward<Fun>(fun);
        }

        template <typename Fun, typename Obj,
                  EnableIf<std::is_member_object_pointer<Unqualified<Fun>>,
                           Not<std::is_base_of<ClassOf<Unqualified<Fun>>, Unqualified<Obj>>>
                          > = _>
        auto invoke(Fun&& fun, Obj&& obj)
        -> decltype((*std::declval<Obj>()).*std::declval<Fun>()) {
            return (*std::forward<Obj>(obj)).*std::forward<Fun>(fun);
        }

        template <typename Fun, typename... Args,
                  DisableIf<std::is_member_pointer<Unqualified<Fun>>> = _>
        auto invoke(Fun&& fun, Args&&... args)
        -> decltype(std::declval<Fun>()(std::declval<Args>()...)) {
            return std::forward<Fun>(fun)(std::forward<Args>(args)...);
        }
    } // namespace invoke_detail

    //! Tests if a type is deduced
    template <typename T>
    using is_deduced = std::is_same<T, deduced>;

    //! INVOKE semantics from [func.require]
    template <typename Result = deduced, typename... T,
              EnableIf<is_deduced<Result>> = _>
    auto invoke(T&&... t)
    -> decltype(invoke_detail::invoke(std::declval<T>()...)) {
        return invoke_detail::invoke(std::forward<T>(t)...);
    }

    template <typename Result = deduced, typename... T,
              EnableIf<Not<is_deduced<Result>>,
                       Bool<true, decltype(invoke_detail::invoke(std::declval<T>()...))>,
                       std::is_void<Result>
                      > = _>
    void invoke(T&&... t) {
        invoke_detail::invoke(std::forward<T>(t)...);
    }

    template <typename Result = deduced, typename... T,
              EnableIf<Not<is_deduced<Result>>,
                       Not<std::is_void<Result>>,
                       std::is_convertible<decltype(invoke_detail::invoke(std::declval<T>()...)), Result>
                      > = _>
    Result invoke(T&&... t) {
        return invoke_detail::invoke(std::forward<T>(t)...);
    }

    namespace traits_detail {
        struct is_callable_tester {
            template <typename Fun, typename Ret, typename... Args>
            static Bool<true, decltype(invoke<Ret>(std::declval<Fun>(), std::declval<Args>()...))> test(int);
            template <typename, typename, typename...>
            static Bool<false> test(...);
        };
    } // namespace traits_detail

    //! Tests if T is callable with the given Signature
    template <typename T, typename Signature>
    struct is_callable : Bool<false> {
        static_assert(std::is_function<Signature>::value, "Signature must be a function type");
    };
    template <typename Fun, typename Ret, typename... Args>
    struct is_callable<Fun, Ret(Args...)> : TraitOf<traits_detail::is_callable_tester, Fun, Ret, Args...> {};

    namespace result_of_detail {
        template <typename T, bool Callable>
        struct impl {};
        template <typename Fun, typename... Args>
        struct impl<Fun(Args...), true> : identity<decltype(invoke(std::declval<Fun>(), std::declval<Args>()...))> {};
    } // namespace result_of_detail
    //! Computes the result of a functor given a set of arguments
    template <typename T>
    struct result_of; // { static_assert(Bool<false, T>::value, "Parameter must be a signature"); };
    template <typename Fun, typename... Args>
    struct result_of<Fun(Args...)> : result_of_detail::impl<Fun(Args...), is_callable<Fun, void(Args...)>::value> {};
    template <typename T>
    using ResultOf = Invoke<result_of<T>>;

    //! Tests if T is a function object type ([function.objects])
    template <typename T, typename Signature>
    struct is_function_object : All<std::is_object<T>, Not<std::is_member_pointer<T>>, is_callable<T, Signature>> {};

    //! Tests if T is a pointer to a function
    template <typename T>
    struct is_function_pointer : All<std::is_pointer<T>, std::is_function<RemovePointer<T>>> {};

    //! Obtains the first element of a parameter pack
    template <typename... T>
    struct pack_head {};
    template <typename Head, typename... Tail>
    struct pack_head<Head, Tail...> : identity<Head> {};
    template <typename... T>
    using PackHead = Invoke<pack_head<T...>>;

    //! Removes function qualifiers from a function or pointer to member function type
    template <typename T>
    struct remove_function_qualifiers : identity<T> {};
    template <typename Class, typename Signature>
    struct remove_function_qualifiers<Signature Class::*> : identity<Invoke<remove_function_qualifiers<Signature>> Class::*> {};
    template <typename Ret, typename... Args>
    struct remove_function_qualifiers<Ret(Args...)> : identity<Ret(Args...)> {};
    template <typename Ret, typename... Args>
    struct remove_function_qualifiers<Ret(Args...) const> : identity<Ret(Args...)> {};
    template <typename Ret, typename... Args>
    struct remove_function_qualifiers<Ret(Args...) volatile> : identity<Ret(Args...)> {};
    template <typename Ret, typename... Args>
    struct remove_function_qualifiers<Ret(Args...) const volatile> : identity<Ret(Args...)> {};
#if WHEELS_HAS_FEATURE(CXX_REFERENCE_QUALIFIED_FUNCTIONS)
    template <typename Ret, typename... Args>
    struct remove_function_qualifiers<Ret(Args...)&> : identity<Ret(Args...)> {};
    template <typename Ret, typename... Args>
    struct remove_function_qualifiers<Ret(Args...) const&> : identity<Ret(Args...)> {};
    template <typename Ret, typename... Args>
    struct remove_function_qualifiers<Ret(Args...) volatile&> : identity<Ret(Args...)> {};
    template <typename Ret, typename... Args>
    struct remove_function_qualifiers<Ret(Args...) const volatile&> : identity<Ret(Args...)> {};
    template <typename Ret, typename... Args>
    struct remove_function_qualifiers<Ret(Args...)&&> : identity<Ret(Args...)> {};
    template <typename Ret, typename... Args>
    struct remove_function_qualifiers<Ret(Args...) const&&> : identity<Ret(Args...)> {};
    template <typename Ret, typename... Args>
    struct remove_function_qualifiers<Ret(Args...) volatile&&> : identity<Ret(Args...)> {};
    template <typename Ret, typename... Args>
    struct remove_function_qualifiers<Ret(Args...) const volatile&&> : identity<Ret(Args...)> {};
#endif // WHEELS_HAS_FEATURE(CXX_REFERENCE_QUALIFIED_FUNCTIONS)
    template <typename T>
    using RemoveFunctionQualifiers = Invoke<remove_function_qualifiers<T>>;

    namespace qualifier_detail {
        struct carrier;
    } // namespace qualifier_detail

    //! Converts function qualifiers to object qualifiers
    template <typename T>
    struct from_function_qualifiers : identity<T> {};
    template <typename Class, typename Signature>
    struct from_function_qualifiers<Signature Class::*> : identity<from_function_qualifiers<Signature>>  {};
    template <typename Ret, typename... Args>
    struct from_function_qualifiers<Ret(Args...)> : identity<qualifier_detail::carrier>  {};
    template <typename Ret, typename... Args>
    struct from_function_qualifiers<Ret(Args...) const> : identity<qualifier_detail::carrier const>  {};
    template <typename Ret, typename... Args>
    struct from_function_qualifiers<Ret(Args...) volatile> : identity<qualifier_detail::carrier volatile>  {};
    template <typename Ret, typename... Args>
    struct from_function_qualifiers<Ret(Args...) const volatile> : identity<qualifier_detail::carrier const volatile>  {};
#if WHEELS_HAS_FEATURE(CXX_REFERENCE_QUALIFIED_FUNCTIONS)
    template <typename Ret, typename... Args>
    struct from_function_qualifiers<Ret(Args...)&> : identity<qualifier_detail::carrier>  {};
    template <typename Ret, typename... Args>
    struct from_function_qualifiers<Ret(Args...) const&> : identity<qualifier_detail::carrier const>  {};
    template <typename Ret, typename... Args>
    struct from_function_qualifiers<Ret(Args...) volatile&> : identity<qualifier_detail::carrier volatile>  {};
    template <typename Ret, typename... Args>
    struct from_function_qualifiers<Ret(Args...) const volatile&> : identity<qualifier_detail::carrier const volatile>  {};
    template <typename Ret, typename... Args>
    struct from_function_qualifiers<Ret(Args...)&&> : identity<qualifier_detail::carrier&&>  {};
    template <typename Ret, typename... Args>
    struct from_function_qualifiers<Ret(Args...) const&&> : identity<qualifier_detail::carrier const&&>  {};
    template <typename Ret, typename... Args>
    struct from_function_qualifiers<Ret(Args...) volatile&&> : identity<qualifier_detail::carrier volatile&&>  {};
    template <typename Ret, typename... Args>
    struct from_function_qualifiers<Ret(Args...) const volatile&&> : identity<qualifier_detail::carrier const volatile&&>  {};
#endif // WHEELS_HAS_FEATURE(CXX_REFERENCE_QUALIFIED_FUNCTIONS)
    template <typename Fun>
    using FromFunctionQualifiers = Invoke<from_function_qualifiers<Fun>>;

    //! Converts object qualifiers to function qualifiers
    template <typename Q>
    struct to_function_qualifiers : identity<qualifier_detail::carrier()> {};
    template <typename Q>
    struct to_function_qualifiers<Q const> : identity<qualifier_detail::carrier() const>  {};
    template <typename Q>
    struct to_function_qualifiers<Q volatile> : identity<qualifier_detail::carrier() volatile>  {};
    template <typename Q>
    struct to_function_qualifiers<Q const volatile> : identity<qualifier_detail::carrier() const volatile>  {};
#if WHEELS_HAS_FEATURE(CXX_REFERENCE_QUALIFIED_FUNCTIONS)
    template <typename Q>
    struct to_function_qualifiers<Q&> : identity<qualifier_detail::carrier()&> {};
    template <typename Q>
    struct to_function_qualifiers<Q const&> : identity<qualifier_detail::carrier() const&>  {};
    template <typename Q>
    struct to_function_qualifiers<Q volatile&> : identity<qualifier_detail::carrier() volatile&>  {};
    template <typename Q>
    struct to_function_qualifiers<Q const volatile&> : identity<qualifier_detail::carrier() const volatile&>  {};
    template <typename Q>
    struct to_function_qualifiers<Q&&> : identity<qualifier_detail::carrier()&&> {};
    template <typename Q>
    struct to_function_qualifiers<Q const&&> : identity<qualifier_detail::carrier() const&&>  {};
    template <typename Q>
    struct to_function_qualifiers<Q volatile&&> : identity<qualifier_detail::carrier() volatile&&>  {};
    template <typename Q>
    struct to_function_qualifiers<Q const volatile&&> : identity<qualifier_detail::carrier() const volatile&&>  {};
#endif // WHEELS_HAS_FEATURE(CXX_REFERENCE_QUALIFIED_FUNCTIONS)
    template <typename Q>
    using ToFunctionQualifiers = Invoke<to_function_qualifiers<Q>>;

    //! Unwraps a reference_wrapper type
    template <typename T>
    struct unwrap_reference : identity<T> {};
    template <typename T>
    struct unwrap_reference<std::reference_wrapper<T>> : identity<T&> {};
    template <typename T>
    using UnwrapReference = Invoke<unwrap_reference<T>>;
    //! Unwraps a reference_wrapper
    template <typename T>
    T&& unref(T&& t) { return std::forward<T>(t); }
    template <typename T>
    T& unref(std::reference_wrapper<T> t) { return t.get(); }

    //! Tests if a type is not a reference and has no cv-qualifiers
    template <typename T>
    struct is_unqualified : std::is_same<T, Unqualified<T>> {};
} // namespace wheels

#if !WHEELS_HAS_FEATURE(CXX_ALIGNED_UNION)

    // aligned_union emulation
    namespace std {
        template <decltype(sizeof(0)) Len, typename... T>
        struct aligned_union
        : ::std::aligned_storage<
              ::wheels::max< ::std::integral_constant<decltype(sizeof(0)), Len>, ::std::integral_constant<decltype(sizeof(0)), sizeof(T)>...>::value,
              ::wheels::max< ::std::integral_constant<decltype(sizeof(0)), alignof(T)>...>::value> {
            static constexpr size_t alignment_value = alignof(::wheels::Invoke<aligned_union>);
        };
    } // namespace std
    #define WHEELS_HAS_FEATURE_CXX_ALIGNED_UNION

#endif // !WHEELS_HAS_FEATURE(CXX_ALIGNED_UNION)

#endif // WHEELS_TYPE_TRAITS_HPP

#include <cstddef>
#include <memory>

namespace wheels {
    namespace allocator_detail {
        template <typename A>
        struct deallocate {
        public:
            deallocate(A& a, std::size_t n) : a(a), n(n) {}

            void operator()(typename std::allocator_traits<A>::pointer ptr) {
                a.deallocate(ptr, n);
            }

        private:
            A& a;
            std::size_t n;
        };

        template <typename A,
                  typename Pointer = std::unique_ptr<ValueType<A>, deallocate<A>>>
        Pointer allocate(A& a, std::size_t n) {
            return Pointer { a.allocate(n), deallocate<A> { a, n } };
        }
    } // namespace allocator_detail

    //! Allocator-based copier
    template <typename T, typename Alloc>
    struct allocator_cloner {
    public:
        allocator_cloner(Alloc a) : a(std::move(a)) {}

        T* operator()(T* ptr) {
            auto holder = allocator_detail::allocate(a, 1);
            ::new(holder.get()) T(*ptr);
            return holder.release();
        }

    private:
        Alloc a;
    };

    //! Allocator-based deleter
    template <typename T, typename Alloc>
    struct allocator_delete {
    public:
        allocator_delete(Alloc a) : a(std::move(a)) {}

        void operator()(T* ptr) {
            ptr->~T();
            a.deallocate(ptr, 1);
        }

    private:
        Alloc a;
    };
} // namespace wheels

#endif // WHEELS_ALLOCATOR_HPP

// #included from: ../named_param.h++
// Wheels - various C++ utilities
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Named parameter tools

#ifndef WHEELS_NAMED_PARAM_HPP
#define WHEELS_NAMED_PARAM_HPP

#define WHEELS_DEFINE_NAMED_PARAMETER(NAME) \
    struct NAME##_name : ::wheels::named_parameter_detail::name<NAME##_name> { \
        using ::wheels::named_parameter_detail::name<NAME##_name>::operator=; \
    } constexpr NAME {}; \
    template <typename T> \
    using NAME##_parameter = ::wheels::named_parameter<NAME##_name, T>; \
    WHEELS_EXPECT_SEMICOLON

namespace wheels {
    template <typename Name, typename T>
    struct named_parameter {
    public:
        static_assert(std::is_reference<T>::value, "T must be a reference type");
        static_assert(is_unqualified<Name>::value, "Name must be a bare type");

        using name = Name;
        using type = T;

        constexpr named_parameter(T t) : value(std::forward<T>(t)) {}

        named_parameter& operator=(named_parameter const&) = delete;

        T forward() const { return std::forward<T>(value); }

    private:
        T value;
    };

    template <typename Param>
    using ParameterName = typename Param::name;
    template <typename Param>
    using ParameterType = typename Param::type;

    template <typename Name, typename... T>
    struct has_parameter : Any<std::is_same<ParameterName<T>, Name>...> {};

    template <typename Name, typename... T>
    struct get_parameter {};
    template <typename Name, typename Head, typename... Tail>
    struct get_parameter<Name, Head, Tail...>
    : Conditional<
        std::is_same<ParameterName<Head>, Name>,
        identity<Head>,
        get_parameter<Name, Tail...>
    > {};
    template <typename Name, typename... T>
    using GetParameter = Invoke<get_parameter<Name, T...>>;
    template <typename Name, typename... T>
    using GetParameterType = ParameterType<GetParameter<Name, T...>>;

    namespace named_parameter_detail {
        template <typename Name>
        struct name {
            constexpr name() = default;
            template <typename T>
            constexpr named_parameter<Name, T&&> operator=(T&& t) const {
                return { std::forward<T>(t) };
            }
            name(name const&) = delete;
            name& operator=(name const&) = delete;
        };
    } // namespace named_parameter_detail

    template <typename T>
    struct is_named_parameter : is_specialization_of<T, named_parameter> {};

    template <typename... T>
    struct no_named_parameters : Not<Any<is_named_parameter<T>...>> {};

    template <typename... T>
    struct named_parameter_count : count<is_named_parameter<T>...> {};

    template <typename Name, typename Head, typename... Tail>
    Head forward_named(Name const&, named_parameter<Name, Head> const& param, Tail const&...) {
        return param.forward();
    }

    template <typename Name, typename Head, typename... Tail>
    auto forward_named(Name const& name, Head const&, Tail const&... tail)
    -> decltype(forward_named(name, tail...)) {
        return forward_named(name, tail...);
    }
} // namespace wheels

#endif // WHEELS_NAMED_PARAM_HPP

// #included from: ../detail/pointer_param.h++
// Wheels - various C++ utilities
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Pointer named parameters

#ifndef WHEELS_DETAIL_POINTER_PARAM_HPP
#define WHEELS_DETAIL_POINTER_PARAM_HPP

namespace wheels {
    inline namespace names {
        WHEELS_DEFINE_NAMED_PARAMETER(raw);
        WHEELS_DEFINE_NAMED_PARAMETER(cloner);
        WHEELS_DEFINE_NAMED_PARAMETER(deleter);
    } // namespace names
} // namespace wheels

#endif // WHEELS_DETAIL_POINTER_PARAM_HPP

// #included from: ../tuple.h++
// Wheels - various C++ utilities
//
// Written in 2012 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// Tuple utilities

#ifndef WHEELS_TUPLE_HPP
#define WHEELS_TUPLE_HPP

#include <cstddef>
#include <initializer_list>
#include <tuple>
#include <utility>

namespace wheels {
    // TODO: use a simple typelist instead of std::tuple for tag dispatching?

    //! Pack of indices
    template <int... Indices>
    struct indices {
        using next = indices<Indices..., sizeof...(Indices)>;
    };

    //! Indices pack construction
    template <int Size>
    struct build_indices : identity<typename Invoke<build_indices<Size-1>>::next> {};
    template <>
    struct build_indices<0> : identity<indices<>> {};
    template <int Size>
    using BuildIndices = Invoke<build_indices<Size>>;

    //! Indices pack for a given tuple
    template <typename Tuple>
    using IndicesFor = BuildIndices<std::tuple_size<Unqualified<Tuple>>::value>;

    template <std::size_t I, typename T>
    using TupleElement = Invoke<std::tuple_element<I, T>>;

#if defined(WHEELS_STD_TUPLE_LAYOUT_OPTIMAL) || defined(WHEELS_STD_TUPLE_LAYOUT_UNKNOWN)

    template <typename... T>
    using tuple = std::tuple<T...>;
    using std::make_tuple;
    using std::forward_as_tuple;
    using std::tie;
    using std::tuple_cat;
    using std::get;

#else
    template <typename... T>
    struct tuple;

    namespace tuple_detail {
        template <typename T, typename Tuple>
        struct cons_tuple;
        template <typename Head, typename... Tail>
        struct cons_tuple<Head, std::tuple<Tail...>> : identity<std::tuple<Head, Tail...>> {};
        template <typename T, typename Tuple>
        using ConsTuple = typename cons_tuple<T, Tuple>::type;

        template <typename T>
        struct member { T _; }; // need this to get "alignment of a reference"
        template <typename T, typename U>
        struct layout_compare_impl : Bool<
            std::is_empty<T>::value
            || (!std::is_empty<U>::value && alignof(member<T>) > alignof(member<U>))
        > {};
        template <typename T, typename U>
        struct layout_compare
    #if defined(WHEELS_STD_TUPLE_LAYOUT_STRAIGHT)
        : layout_compare_impl<T,U> {};
    #elif defined(WHEELS_STD_TUPLE_LAYOUT_REVERSED)
        : layout_compare_impl<U,T> {};
    #endif

        template <template <typename...> class Template, typename... T>
        struct apply_invoke : identity<Template<Invoke<T>...>> {};

        template <typename T, std::size_t I>
        struct indexed : identity<indexed<T,I>> {
            using t = T;
            static constexpr std::size_t i = I;
        };

        template <typename T, typename Tuple>
        struct insert_sorted
        : identity<std::tuple<T>> {};
        template <typename T, std::size_t I, typename THead, std::size_t IHead, typename... TTail, std::size_t... ITail>
        struct insert_sorted<indexed<T, I>, std::tuple<indexed<THead, IHead>, indexed<TTail, ITail>...>>
        : Conditional<
            layout_compare<T, THead>,
            identity<std::tuple<indexed<T, I>, indexed<THead, IHead>, indexed<TTail, ITail>...>>,
            apply_invoke<ConsTuple, indexed<THead, IHead>, insert_sorted<indexed<T, I>, std::tuple<indexed<TTail, ITail>...>>>
        > {};
        template <typename T, typename Tuple>
        using InsertSorted = Invoke<insert_sorted<T, Tuple>>;

        template <typename Acc, typename... T>
        struct with_indices_impl : identity<Acc> {};
        template <typename... Acc, typename Head, typename... Tail>
        struct with_indices_impl<std::tuple<Acc...>, Head, Tail...> : with_indices_impl<std::tuple<Acc..., indexed<Head, sizeof...(Acc)>>, Tail...> {};
        template <typename... T>
        struct with_indices : with_indices_impl<std::tuple<>, T...> {};
        template <typename... T>
        using WithIndices = Invoke<with_indices<T...>>;

        template <std::size_t Target, typename Tuple>
        struct find_index;
        template <std::size_t Target, typename THead, std::size_t From, std::size_t To, typename... Tail>
        struct find_index<Target, std::tuple<indexed<indexed<THead, To>,From>, Tail...>>
        : Conditional<
            Bool<Target == To>,
            std::integral_constant<std::size_t, From>,
            find_index<Target, std::tuple<Tail...>>
        > {};

        template <typename Tuple>
        struct reverse_layout_impl;
        template <typename... T, std::size_t... From, std::size_t... To>
        struct reverse_layout_impl<std::tuple<indexed<indexed<T,To>,From>...>>
        : identity<std::tuple<
            indexed<T, find_index<From, std::tuple<indexed<indexed<T,To>,From>...>>::value>...
        >> {};
        template <typename Tuple>
        struct reverse_layout;
        template <typename... T>
        struct reverse_layout<std::tuple<T...>> : reverse_layout_impl<WithIndices<T...>> {};
        template <typename Tuple>
        using ReverseLayout = Invoke<reverse_layout<Tuple>>;

        template <typename Tuple>
        struct split_impl;
        template <typename... T, std::size_t... I>
        struct split_impl<std::tuple<indexed<T, I>...>> {
            using tuple = std::tuple<T...>;
            using map = std::tuple<std::integral_constant<std::size_t, I>...>;
        };
        template <typename Tuple>
        struct split {
            using tuple = typename split_impl<Tuple>::tuple;
            using map = typename split_impl<Tuple>::map;
            using inverse_map = typename split_impl<ReverseLayout<Tuple>>::map;
        };

        template <typename Acc, typename T>
        struct optimal_layout_impl : split<Acc> {};

        template <typename Acc, typename Head, typename... Tail>
        struct optimal_layout_impl<Acc, std::tuple<Head, Tail...>>
        : optimal_layout_impl<InsertSorted<Head, Acc>, std::tuple<Tail...>> {};

        template <typename... T>
        struct optimal_layout : optimal_layout_impl<std::tuple<>, WithIndices<T...>> {};

        template <typename... T>
        using OptimalLayoutTuple = typename optimal_layout<T...>::tuple;
        template <typename... T>
        using OptimalLayoutMap = typename optimal_layout<T...>::map;
        template <typename... T>
        using OptimalLayoutInverseMap = typename optimal_layout<T...>::inverse_map;

        template <typename Acc, typename From, typename To>
        struct convert_layout_map_impl : identity<Acc> {};
        template <typename... Acc, typename From, typename THead, typename... TTail>
        struct convert_layout_map_impl<std::tuple<Acc...>, From, std::tuple<THead, TTail...>>
        : convert_layout_map_impl<std::tuple<Acc..., TupleElement<THead::value, From>>, From, std::tuple<TTail...>> {};
        template <typename From, typename To>
        struct convert_layout_map : convert_layout_map_impl<std::tuple<>, From, To> {};
        template <typename From, typename To>
        using ConvertLayoutMap = Invoke<convert_layout_map<From, To>>;

        template <typename... T, typename... Indices>
        std::tuple<TupleElement<Indices::value, std::tuple<T...>>...> forward_mapped_tuple(std::tuple<Indices...>, std::tuple<T...> t) {
            return std::forward_as_tuple(std::forward<TupleElement<Indices::value, std::tuple<T...>>>(std::get<Indices::value>(t))...);
        }

        template <typename... T, typename... Indices>
        std::tuple<TupleElement<Indices::value, std::tuple<T...>>...> forward_mapped(std::tuple<Indices...> i, T&&... t) {
            return forward_mapped_tuple(i, std::forward_as_tuple(std::forward<T>(t)...));
        }

        template <typename... N>
        struct sum : std::integral_constant<std::size_t, 0> {};
        template <typename Head, typename... Tail>
        struct sum<Head, Tail...> : std::integral_constant<std::size_t, Head::value + sum<Tail...>::value> {};

        template <std::size_t X, std::size_t Y>
        struct position : identity<position<X, Y>> {
            static constexpr std::size_t x = X;
            static constexpr std::size_t y = Y;
        };
        template <std::size_t I, std::size_t X, std::size_t Acc, typename... Tuples>
        struct position_of_impl;
        template <std::size_t I, std::size_t X, std::size_t Acc, typename Head, typename... Tail>
        struct position_of_impl<I, X, Acc, Head, Tail...>
        : Conditional<
            Bool<(std::tuple_size<Unqualified<Head>>::value + Acc > I)>,
            position<X, I - Acc>,
            position_of_impl<I, X+1, Acc + std::tuple_size<Unqualified<Head>>::value, Tail...>
        > {};
        template <std::size_t I, typename... Tuples>
        struct position_of : position_of_impl<I, 0, 0, Tuples...> {};
        template <std::size_t I, typename... Tuples>
        using PositionOf = Invoke<position_of<I, Tuples...>>;

        template <typename Tuple, typename Indices = IndicesFor<Tuple>>
        struct to_std_tuple;
        template <typename Tuple, int... Indices>
        struct to_std_tuple<Tuple, indices<Indices...>> : identity<std::tuple<TupleElement<Indices, Tuple>...>> {};
        template <typename Tuple>
        using ToStdTuple = Invoke<to_std_tuple<Tuple>>;

        template <typename Acc, typename... Tuples>
        struct concat_tuples_impl : identity<Acc> {};
        template <typename... Acc, typename... Heads, typename... Tail>
        struct concat_tuples_impl<tuple<Acc...>, std::tuple<Heads...>, Tail...>
        : concat_tuples_impl<tuple<Acc..., Heads...>, Tail...> {};
        template <typename... Tuples>
        struct concat_tuples : concat_tuples_impl<tuple<>, ToStdTuple<Unqualified<Tuples>>...> {};
        template <typename... Tuples>
        using ConcatTuples = Invoke<concat_tuples<Tuples...>>;

        template <typename P, typename Tuple,
                  typename Inner = TupleElement<P::x, Unqualified<Tuple>>,
                  typename Outer = TupleElement<P::y, Unqualified<Inner>>,
                  typename Result = WithQualificationsOf<Inner, Outer>>
        Result get_position(Tuple t) {
            using std::get;
            return get<P::y>(get<P::x>(t));
        }

        template <int... Indices, typename... Tuples>
        auto forward_cat(indices<Indices...>, Tuples&&... t)
        -> decltype(std::forward_as_tuple(
                        get_position<PositionOf<Indices, Tuples...>>(
                            std::forward_as_tuple(std::forward<Tuples>(t)...))...)) {
            return std::forward_as_tuple(
                        get_position<PositionOf<Indices, Tuples...>>(
                            std::forward_as_tuple(std::forward<Tuples>(t)...))...);
        }

        // Goat sacrifice for GCC
        template <typename Ts, typename Us>
        struct pairwise_convertible : Bool<false> {};
        template <>
        struct pairwise_convertible<std::tuple<>, std::tuple<>> : Bool<true> {};
        template <typename THead, typename... TTail, typename UHead, typename... UTail>
        struct pairwise_convertible<std::tuple<THead, TTail...>, std::tuple<UHead, UTail...>>
        : All<std::is_convertible<THead, UHead>, pairwise_convertible<std::tuple<TTail...>, std::tuple<UTail...>>> {};
    } // namespace tuple_detail

    template <typename... T>
    struct tuple {
    private:
        using layout_tuple = tuple_detail::OptimalLayoutTuple<T...>;
        using layout_map = tuple_detail::OptimalLayoutMap<T...>;
        using layout_inverse_map = tuple_detail::OptimalLayoutInverseMap<T...>;

        template <typename Other>
        using LayoutFor = tuple_detail::ConvertLayoutMap<typename Other::layout_map, layout_map>;

    public:
        constexpr tuple() = default;

        explicit tuple(T const&... t)
        : inner(tuple_detail::forward_mapped(layout_map{}, t...)) {
            static_assert(All<std::is_copy_constructible<T>...>::value, "all tuple element types must be copy constructible");
        }

        // TODO: get this to compile and remove the hack: EnableIf<std::is_convertible<U, T>...> = _>
        template <typename... U,
                  EnableIf<tuple_detail::pairwise_convertible<std::tuple<U...>, std::tuple<T...>>> = _>
        explicit tuple(U&&... u)
        : inner(tuple_detail::forward_mapped(layout_map{}, std::forward<U>(u)...)) {
            static_assert(sizeof...(T) == sizeof...(U), "number of constructor parameters must match tuple size");
        }

        tuple(tuple const&) = default;
        tuple(tuple&&) = default;

        template <typename... U,
                  EnableIf<std::is_constructible<T, U const&>...> = _>
        tuple(tuple<U...> const& t)
        : inner(tuple_detail::forward_mapped_tuple(LayoutFor<tuple<U...>>{}, t.inner)) {
            static_assert(sizeof...(T) == sizeof...(U), "number of constructor parameters must match tuple size");
        }
        template <typename... U,
                  EnableIf<std::is_constructible<T, U&&>...> = _>
        tuple(tuple<U...>&& t)
        : inner(tuple_detail::forward_mapped_tuple(LayoutFor<tuple<U...>>{}, std::move(t.inner))) {
            static_assert(sizeof...(T) == sizeof...(U), "number of constructor parameters must match tuple size");
        }

        template <typename U1, typename U2,
                  EnableIf<std::is_convertible<U1 const&, TupleElement<0, std::tuple<T...>>>,
                           std::is_convertible<U2 const&, TupleElement<1, std::tuple<T...>>>> = _>
        tuple(std::pair<U1, U2> const& pair)
        : tuple(pair.first, pair.second) {
            static_assert(sizeof...(T) == 2, "tuple size must be 2");
        }
        template <typename U1, typename U2,
                  EnableIf<std::is_convertible<U1, TupleElement<0, std::tuple<T...>>>,
                           std::is_convertible<U2, TupleElement<1, std::tuple<T...>>>> = _>
        tuple(std::pair<U1, U2>&& pair)
        : tuple(std::forward<U1>(pair.first), std::forward<U2>(pair.second)) {
            static_assert(sizeof...(T) == 2, "tuple size must be 2");
        }

        template <typename... U,
                  EnableIf<std::is_constructible<T, U const&>...> = _>
        tuple(std::tuple<U...> const& that)
        : inner(tuple_detail::forward_mapped_tuple(layout_map{}, that)) {
            static_assert(sizeof...(T) == sizeof...(U), "number of constructor parameters must match tuple size");
        }
        template <typename... U,
                  EnableIf<std::is_constructible<T, U&&>...> = _>
        tuple(std::tuple<U...>&& that)
        : inner(tuple_detail::forward_mapped_tuple(layout_map{}, std::move(that))) {
            static_assert(sizeof...(T) == sizeof...(U), "number of constructor parameters must match tuple size");
        }

        template <typename Alloc>
        tuple(std::allocator_arg_t tag, Alloc const& a)
        : inner(tag, a) {}

        template <typename Alloc>
        explicit tuple(std::allocator_arg_t tag, Alloc const& a, T const&... t)
        : inner(tag, a, tuple_detail::forward_mapped(layout_map{}, t...)) {
            static_assert(All<std::is_copy_constructible<T>...>::value, "all tuple element types must be copy constructible");
        }

        template <typename Alloc, typename... U,
                  EnableIf<tuple_detail::pairwise_convertible<std::tuple<U...>, std::tuple<T...>>> = _>
        explicit tuple(std::allocator_arg_t tag, Alloc const& a, U&&... u)
        : inner(tag, a, tuple_detail::forward_mapped(layout_map{}, std::forward<U>(u)...)) {
            static_assert(sizeof...(T) == sizeof...(U), "number of constructor parameters must match tuple size");
        }

        template <typename Alloc>
        tuple(std::allocator_arg_t tag, Alloc const& a, tuple const& that)
        : inner(tag, a, that.inner) {}

        template <typename Alloc>
        tuple(std::allocator_arg_t tag, Alloc const& a, tuple&& that)
        : inner(tag, a, std::move(that.inner)) {}

        template <typename Alloc, typename... U,
                  EnableIf<std::is_constructible<T, U const&>...> = _>
        tuple(std::allocator_arg_t tag, Alloc const& a, tuple<U...> const& t)
        : inner(tag, a, tuple_detail::forward_mapped_tuple(LayoutFor<tuple<U...>>{}, t.inner)) {
            static_assert(sizeof...(T) == sizeof...(U), "number of constructor parameters must match tuple size");
        }
        template <typename Alloc, typename... U,
                  EnableIf<std::is_constructible<T, U&&>...> = _>
        tuple(std::allocator_arg_t tag, Alloc const& a, tuple<U...>&& t)
        : inner(tag, a, tuple_detail::forward_mapped_tuple(LayoutFor<tuple<U...>>{}, std::move(t.inner))) {
            static_assert(sizeof...(T) == sizeof...(U), "number of constructor parameters must match tuple size");
        }

        template <typename Alloc, typename U1, typename U2,
                  EnableIf<std::is_convertible<U1 const&, TupleElement<0, std::tuple<T...>>>,
                           std::is_convertible<U2 const&, TupleElement<1, std::tuple<T...>>>> = _>
        tuple(std::allocator_arg_t tag, Alloc const& a, std::pair<U1, U2> const& pair)
        : tuple(tag, a, pair.first, pair.second) {
            static_assert(sizeof...(T) == 2, "tuple size must be 2");
        }
        template <typename Alloc, typename U1, typename U2,
                  EnableIf<std::is_convertible<U1, TupleElement<0, std::tuple<T...>>>,
                           std::is_convertible<U2, TupleElement<1, std::tuple<T...>>>> = _>
        tuple(std::allocator_arg_t tag, Alloc const& a, std::pair<U1, U2>&& pair)
        : tuple(tag, a, std::forward<U1>(pair.first), std::forward<U2>(pair.second)) {
            static_assert(sizeof...(T) == 2, "tuple size must be 2");
        }

        template <typename Alloc, typename... U,
                  EnableIf<std::is_constructible<T, U const&>...> = _>
        tuple(std::allocator_arg_t tag, Alloc const& a, std::tuple<U...> const& that)
        : inner(tag, a, tuple_detail::forward_mapped_tuple(layout_map{}, that)) {
            static_assert(sizeof...(T) == sizeof...(U), "number of constructor parameters must match tuple size");
        }
        template <typename Alloc, typename... U,
                  EnableIf<std::is_constructible<T, U&&>...> = _>
        tuple(std::allocator_arg_t tag, Alloc const& a, std::tuple<U...>&& that)
        : inner(tag, a, tuple_detail::forward_mapped_tuple(layout_map{}, std::move(that))) {
            static_assert(sizeof...(T) == sizeof...(U), "number of constructor parameters must match tuple size");
        }

        tuple& operator=(tuple const&) = default;
        tuple& operator=(tuple&&) = default;

        template <typename... U>
        tuple& operator=(tuple<U...> const& t) {
            static_assert(sizeof...(T) == sizeof...(U), "number of constructor parameters must match tuple size");
            static_assert(All<std::is_assignable<T&, U const&>...>::value,
                          "all arguments must be assignable to the corresponding element");

            inner = tuple_detail::forward_mapped_tuple(LayoutFor<tuple<U...>>{}, t.inner);
            return *this;
        }
        template <typename... U>
        tuple& operator=(tuple<U...>&& t) {
            static_assert(sizeof...(T) == sizeof...(U), "number of constructor parameters must match tuple size");
            static_assert(All<std::is_assignable<T&, U&&>...>::value,
                          "all arguments must be assignable to the corresponding element");

            inner = tuple_detail::forward_mapped_tuple(LayoutFor<tuple<U...>>{}, std::move(t.inner));
            return *this;
        }

        template <typename U1, typename U2>
        tuple& operator=(std::pair<U1, U2> const& pair) {
            static_assert(sizeof...(T) == 2, "tuple size must be 2");
            static_assert(std::is_assignable<TupleElement<0, std::tuple<T...>>&, U1 const&>::value
                          && std::is_assignable<TupleElement<1, std::tuple<T...>>&, U2 const&>::value,
                          "pair elements must be assignable to the corresponding element");
            inner = tuple_detail::forward_mapped(layout_map{}, pair.first, pair.second);
            return *this;
        }
        template <typename U1, typename U2>
        tuple& operator=(std::pair<U1, U2>&& pair) {
            static_assert(sizeof...(T) == 2, "tuple size must be 2");
            static_assert(std::is_assignable<TupleElement<0, std::tuple<T...>>&, U1&&>::value
                          && std::is_assignable<TupleElement<1, std::tuple<T...>>&, U2&&>::value,
                          "pair elements must be assignable to the corresponding element");
            inner = tuple_detail::forward_mapped(layout_map{}, std::forward<U1>(pair.first), std::forward<U2>(pair.second));
            return *this;
        }

        template <typename... U>
        tuple& operator=(std::tuple<U...> const& that) {
            static_assert(sizeof...(T) == sizeof...(U), "number of constructor parameters must match tuple size");
            static_assert(All<std::is_assignable<T&, U const&>...>::value,
                          "all arguments must be assignable to the corresponding element");
            inner = tuple_detail::forward_mapped_tuple(layout_map{}, that);
            return *this;
        }
        template <typename... U>
        tuple& operator=(std::tuple<U...>&& that) {
            static_assert(sizeof...(T) == sizeof...(U), "number of constructor parameters must match tuple size");
            static_assert(All<std::is_assignable<T&, U&&>...>::value,
                          "all arguments must be assignable to the corresponding element");
            inner = tuple_detail::forward_mapped_tuple(layout_map{}, std::move(that));
            return *this;
        }

        void swap(tuple& that)
        noexcept(noexcept(std::declval<layout_tuple>().swap(std::declval<layout_tuple>()))) {
            inner.swap(that.inner);
        }

        template <std::size_t I, typename... T1>
        friend TupleElement<I, std::tuple<T1...>>& get(tuple<T1...>& t) noexcept;
        template <std::size_t I, typename... T1>
        friend TupleElement<I, std::tuple<T1...>>&& get(tuple<T1...>&& t) noexcept;
        template <std::size_t I, typename... T1>
        friend TupleElement<I, std::tuple<T1...>> const& get(tuple<T1...> const& t) noexcept;
        template <typename... L, typename... R>
        friend bool operator==(tuple<L...> const& t, tuple<R...> const& u);
        template <typename... L, typename... R>
        friend bool operator<(tuple<L...> const& t, tuple<R...> const& u);
        template <typename...>
        friend class tuple;

    private:
        layout_tuple inner;
    };

    template <typename... T>
    tuple<UnwrapReference<Decay<T>>...> make_tuple(T&&... t) {
        return tuple<UnwrapReference<Decay<T>>...>(std::forward<T>(t)...);
    }

    template <typename... T>
    tuple<T&&...> forward_as_tuple(T&&... t) noexcept {
        return tuple<T&&...>(std::forward<T>(t)...);
    }

    template <typename... T>
    tuple<T&...> tie(T&... t) noexcept {
        return tuple<T&...>(t...);
    }

    template <typename... Tuples,
              typename Concatenated = tuple_detail::ConcatTuples<Tuples...>>
    Concatenated tuple_cat(Tuples&&... t) {
        return Concatenated {
                tuple_detail::forward_cat(
                    BuildIndices<tuple_detail::sum<std::tuple_size<Unqualified<Tuples>>...>::value>{},
                    std::forward<Tuples>(t)...)
        };
    }

    template <std::size_t I, typename... T>
    TupleElement<I, std::tuple<T...>>& get(tuple<T...>& t) noexcept {
        return std::get<TupleElement<I, typename tuple<T...>::layout_inverse_map>::value>(t.inner);
    }
    template <std::size_t I, typename... T>
    TupleElement<I, std::tuple<T...>>&& get(tuple<T...>&& t) noexcept {
        return std::get<TupleElement<I, typename tuple<T...>::layout_inverse_map>::value>(std::move(t.inner));
    }
    template <std::size_t I, typename... T>
    TupleElement<I, std::tuple<T...>> const& get(tuple<T...> const& t) noexcept {
        return std::get<TupleElement<I, typename tuple<T...>::layout_inverse_map>::value>(t.inner);
    }

    template <typename... T>
    void swap(tuple<T...>& x, tuple<T...>& y) noexcept(std::declval<tuple<T...>&>().swap(std::declval<tuple<T...>&>())) {
        x.swap(y);
    }

    template <typename... T, typename... U>
    bool operator==(tuple<T...> const& t, tuple<U...> const& u) {
        return t.inner == u.inner;
    }
    template <typename... T, typename... U>
    bool operator<(tuple<T...> const& t, tuple<U...> const& u) {
        return t.inner < u.inner;
    }
    template <typename... T, typename... U>
    bool operator!=(tuple<T...> const& t, tuple<U...> const& u) {
        return !(t == u);
    }
    template <typename... T, typename... U>
    bool operator>(tuple<T...> const& t, tuple<U...> const& u) {
        return u < t;
    }
    template <typename... T, typename... U>
    bool operator<=(tuple<T...> const& t, tuple<U...> const& u) {
        return !(u < t);
    }
    template <typename... T, typename... U>
    bool operator>=(tuple<T...> const& t, tuple<U...> const& u) {
        return !(t < u);
    }
#endif // defined(WHEELS_STD_TUPLE_LAYOUT_OPTIMAL) || defined(WHEELS_STD_TUPLE_LAYOUT_UNKNOWN)
} // namespace wheels

namespace std {
    template <typename... T>
    struct tuple_size< ::wheels::tuple<T...>> : tuple_size<tuple<T...>> {};

    template <size_t I, typename... T>
    struct tuple_element<I, ::wheels::tuple<T...>> : tuple_element<I, tuple<T...>> {};

    template <typename... T, typename Alloc>
    struct uses_allocator< ::wheels::tuple<T...>, Alloc> : true_type {};
} // namespace std

#endif // WHEELS_TUPLE_HPP

#include <cstddef>
#include <functional>
#include <memory>
#include <new>
#include <tuple>
#include <utility>

namespace wheels {
    //! Factory for unique_ptr
    //! Classic make_unique: just arguments to forward, default deleter
    template <typename T, typename... Args,
              EnableIf<Not<std::is_array<T>>,
                       no_named_parameters<Args...>
                      > = _,
              typename Pointer = std::unique_ptr<T>>
    Pointer make_unique(Args&&... args) {
        return Pointer { new T(std::forward<Args>(args)...) };
    }

    //! make_unique for arrays: both T[] and T[N] supported
    template <typename T,
              EnableIf<std::is_array<T>> = _,
              typename Pointee = RemoveExtent<T>,
              std::ptrdiff_t Extent = std::extent<T>::value,
              typename Pointer = std::unique_ptr<Pointee[]>>
    Pointer make_unique(std::ptrdiff_t size = 0) {
        return Pointer { new Pointee[Extent == 0? size : Extent] };
    }
    //! make_unique from a raw pointer (like `unique_ptr<T>(p)` but with deduction)
    template <typename T = deduced,
              typename Raw,
              typename Pointee = Conditional<is_deduced<T>, RemovePointer<Unqualified<Raw>>, T>,
              typename Pointer = std::unique_ptr<Pointee>>
    Pointer make_unique(names::raw_parameter<Raw> const& raw) {
        return Pointer { raw.forward() };
    }
    //! make_unique with value-initialization and a custom deleter
    template <typename T, typename Deleter,
              typename Pointer = std::unique_ptr<T, Decay<Deleter>>>
    Pointer make_unique(names::deleter_parameter<Deleter> const& deleter) {
        return Pointer { new T{}, deleter.forward() };
    }

    namespace unique_detail {
        //! make_unique from a tuple, with custom deleter (indices backend)
        template <typename T, typename Tuple, typename Deleter,
                  int... Indices,
                  typename Pointer = std::unique_ptr<T, Decay<Deleter>>>
        Pointer make(Tuple&& tuple, Deleter&& deleter, indices<Indices...>) {
            using std::get;
            return Pointer { new T(get<Indices>(tuple)...), std::forward<Deleter>(deleter) };
        }
    } // namespace unique_detail

    //! make_unique from a tuple, with custom deleter
    template <typename T, typename Tuple, typename Deleter,
              DisableIf<is_named_parameter<Tuple>> = _,
              typename Pointer = std::unique_ptr<T, Decay<Deleter>>>
    Pointer make_unique(Tuple&& tuple, names::deleter_parameter<Deleter> const& deleter) {
        return unique_detail::make<T>(std::forward<Tuple>(tuple), deleter.forward(), IndicesFor<Tuple>{});
    }
    //! make_unique from a raw pointer, with custom deleter
    template <typename T = deduced,
              typename Arg0, typename Arg1,
              EnableIf<is_named_parameter<Arg0>,
                       is_named_parameter<Arg1>,
                       has_parameter<names::raw_name, Arg0, Arg1>,
                       has_parameter<names::deleter_name, Arg0, Arg1>
                       > = _,
              typename Raw = GetParameterType<names::raw_name, Arg0, Arg1>,
              typename Deleter = GetParameterType<names::deleter_name, Arg0, Arg1>,
              typename Pointee = Conditional<is_deduced<T>, RemovePointer<Unqualified<Raw>>, T>,
              typename Pointer = std::unique_ptr<Pointee, Decay<Deleter>>>
    Pointer make_unique(Arg0 const& arg0, Arg1 const& arg1) {
        return Pointer { forward_named(names::raw, arg0, arg1), forward_named(names::deleter, arg0, arg1) };
    }

    //! Factory for unique_ptr from an allocator
    template <typename T, typename A, typename... Args,
              typename Deleter = allocator_delete<T, A>,
              typename Pointer = std::unique_ptr<T, Deleter>>
    Pointer allocate_unique(A const& a, Args&&... args) {
        A a2 { a };
        auto holder = allocator_detail::allocate(a2, 1);
        ::new(holder.get()) T(std::forward<Args>(args)...);
        return Pointer { holder.release(), Deleter { std::move(a2) } };
    }

    //! unique_ptr with type-erased deleter
    template <typename T>
    using exclusive_ptr = std::unique_ptr<T, std::function<void(T*)>>;
} // namespace wheels

#endif // WHEELS_SMART_PTR_UNIQUE_PTR_HPP

