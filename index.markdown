---
layout: default
title: About ogonek
---

Ogonek  is a C++11 library that implements various Unicode algorithms.

Ogonek version numbers use the [semantic versioning] rules 2.0.0-rc.1.

 [semantic versioning]: http://semver.org/

### Current features ({{ site.doc_version }})

 - algorithms that support any range, with any encoding;

 - character property queries

 - string with compile-time checked encoding conversions and built-in
   validation;

 - Unicode normalization forms;

 - canonical and compatibility equivalence comparisons;

 - boundary analysis algorithms (currently grapheme clusters and words);

### Design goals

Ogonek's design is driven by the following principles.

#### Validity and correctness first

Ogonek will value validity and correctness above speed and other concerns.
Ideally it shall be impossible to obtain invalid Unicode data after any
operation provided by ogonek.

#### Modern C++

Ogonek will use modern C++ techniques as much as possible, and fully embrace
C++11.

#### Explicit is better than implicit

Ogonek will perform as little as possible implicitly. If the users don't want to
care about some details, they don't care about correctness, and thus they don't
need ogonek.

Ogonek will not silently perform encoding conversions, and won't assume any
encoding except for `char16_t` and `char32_t` (which are clearly intended by the
standard as UTF-16 and UTF-32 code units); anything else needs to be made
explicit.

#### Fail fast

Ogonek will not let errors go away silently. When appropriate, the API will
accept error handling callbacks; in all other scenarios exceptions will be
thrown.

#### Be a good citizen

Ogonek will work well with the standard library, by providing and using models
of the existing standard concepts, like iterators and containers.

### History and trivia

#### The name

Ogonek means "little tail" in Polish. It's the name of a diacritic used in
several European and Native American languages. It exists in the Unicode
repertoire as a combining character (U+0328 &#7428;&#7439;&#7437;&#665;&#618;&#628;&#618;&#628;&#610;
&#7439;&#610;&#7439;&#628;&#7431;&#7435;), as an isolated character (U+02DB
&#7439;&#610;&#7439;&#628;&#7431;&#7435;), or precomposed with Latin alphabet
letters (like U+01EA &#671;&#7424;&#7451;&#618;&#628;
&#7428;&#7424;&#7448;&#618;&#7451;&#7424;&#671; &#671;&#7431;&#7451;&#7451;&#7431;&#640;
&#7439; &#7457;&#618;&#7451;&#668; &#7439;&#610;&#7439;&#628;&#7431;&#7435;).

In Russian (&#1086;&#1075;&#1086;&#1085;&#1105;&#1082;) it can mean "little
flame", which arguably makes it sound a lot cooler than "little tail".

The name was picked randomly and it has absolutely no special meaning as the
name of this project. It's just a label the author appropriated for it. In
English it is pronounced [/&#712;o&#650;&#609;&#601;n&#603;k/][pronounciation].

<!-- #### History -->

<!--Back in early 2012, Unicode become a recurring topic in the [Lounge<C++>][lounge]. -->

 [pronounciation]: ogonek.ogg
 [lounge]: http://chat.stackoverflow.com/rooms/10/loungec

