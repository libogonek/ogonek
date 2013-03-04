// Wheels - various C++ utilities
//
// Generated: 2012-06-15 04:47:45.989000
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

// Enum manipulation features

#ifndef WHEELS_ENUMS_HPP
#define WHEELS_ENUMS_HPP

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

namespace wheels {
    //! Enables the bitwise operators for an enum.
    template <typename Enum>
    struct is_flags : Bool<false> {};

    //! Enables the arithmetic operators for an enum.
    template <typename Enum>
    struct is_arithmetic : Bool<false> {};

    //! Returns the underlying value of an given enum value
    template <typename Enum>
    constexpr UnderlyingType<Enum> to_underlying(Enum e) {
        return static_cast<UnderlyingType<Enum>>(e);
    }
} // namespace wheels

#define WHEELS_ENUM_UNARY_OPERATOR(OP, KIND) \
    template <typename Enum, \
              ::wheels::EnableIf< ::std::is_enum<Enum>, ::wheels::is_##KIND<Enum>> = ::wheels::_> \
    constexpr Enum operator OP(Enum const& value) { \
        return static_cast<Enum>(OP wheels::to_underlying(value)); \
    }

#define WHEELS_ENUM_BINARY_OPERATOR(OP, KIND) \
    template <typename Enum, \
              ::wheels::EnableIf< ::std::is_enum<Enum>, ::wheels::is_##KIND<Enum>> = ::wheels::_> \
    constexpr Enum operator OP(Enum const& lhs, Enum const& rhs) { \
        return static_cast<Enum>(wheels::to_underlying(lhs) OP wheels::to_underlying(rhs)); \
    } \
    template <typename Enum, \
              ::wheels::EnableIf< ::std::is_enum<Enum>, ::wheels::is_##KIND<Enum>> = ::wheels::_> \
    Enum operator OP##=(Enum& lhs, Enum const& rhs) { \
        return lhs = lhs OP rhs; \
    }

WHEELS_ENUM_BINARY_OPERATOR(|, flags)
WHEELS_ENUM_BINARY_OPERATOR(&, flags)
WHEELS_ENUM_BINARY_OPERATOR(^, flags)
WHEELS_ENUM_UNARY_OPERATOR(~, flags)

namespace wheels {
    //! Tests if an enum value has all the given flags set
    template <typename Enum,
              EnableIf<std::is_enum<Enum>, is_flags<Enum>> = _>
    constexpr bool has_flag(Enum value, Enum flag) {
        return (value & flag) == flag;
    }
    //! Returns enum value, but with the given flags set
    template <typename Enum,
              EnableIf<std::is_enum<Enum>, is_flags<Enum>> = _>
    constexpr Enum set_flag(Enum value, Enum flag) {
        return value | flag;
    }
    //! Returns enum value, but with the given flags cleared
    template <typename Enum,
              EnableIf<std::is_enum<Enum>, is_flags<Enum>> = _>
    constexpr Enum clear_flag(Enum value, Enum flag) {
        return value & ~flag;
    }
    //! Returns enum value, but with the given flags toggled
    template <typename Enum,
              EnableIf<std::is_enum<Enum>, is_flags<Enum>> = _>
    constexpr Enum toggle_flag(Enum value, Enum flag) {
        return value ^ flag;
    }
} // namespace wheels

WHEELS_ENUM_BINARY_OPERATOR(+, arithmetic)
WHEELS_ENUM_BINARY_OPERATOR(-, arithmetic)
WHEELS_ENUM_BINARY_OPERATOR(*, arithmetic)
WHEELS_ENUM_BINARY_OPERATOR(/, arithmetic)
WHEELS_ENUM_BINARY_OPERATOR(%, arithmetic)
WHEELS_ENUM_UNARY_OPERATOR(+, arithmetic)
WHEELS_ENUM_UNARY_OPERATOR(-, arithmetic)

#undef WHEELS_ENUM_UNARY_OPERATOR
#undef WHEELS_ENUM_BINARY_OPERATOR

template <typename Enum,
          wheels::EnableIf<std::is_enum<Enum>, wheels::is_arithmetic<Enum>> = wheels::_>
Enum& operator++(Enum& value) {
    return value = static_cast<Enum>(wheels::to_underlying(value) + 1);
}

template <typename Enum,
          wheels::EnableIf<std::is_enum<Enum>, wheels::is_arithmetic<Enum>> = wheels::_>
Enum& operator--(Enum& value) {
    return value = static_cast<Enum>(wheels::to_underlying(value) - 1);
}

template <typename Enum,
          wheels::EnableIf<std::is_enum<Enum>, wheels::is_arithmetic<Enum>> = wheels::_>
Enum operator++(Enum& value, int) {
    auto temp = value;
    value = static_cast<Enum>(wheels::to_underlying(value) + 1);
    return temp;
}

template <typename Enum,
          wheels::EnableIf<std::is_enum<Enum>, wheels::is_arithmetic<Enum>> = wheels::_>
Enum operator--(Enum& value,int) {
    auto temp = value;
    value = static_cast<Enum>(wheels::to_underlying(value) - 1);
    return temp;
}

#endif // WHEELS_ENUMS_HPP

