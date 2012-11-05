Ogonek is mostly the result of me playing around with Unicode. It is turning
into something real.

Check out the [wiki] for more detailed information.

# Setup

Ogonek is mostly header-only. The only part that needs compilation is the data
in the Unicode Character Database. Currently I am translating the database to
C++ source as static initializers (I am aware of the benefits and drawbacks of
this and other approaches and may or may not change in future versions). If
you want to get started quickly, you can find pre-generated source code for
various versions of the database in the [downloads] page. If you want to make
your own version of the database, you can find a translator from the XML UCD in
the `tools` folder.

Once you have source code for the UCD, you can compile the whole shebang by
running `scons` from the command line, which will also run the tests (for
obvious reasons, this requires having SCons installed).

# Status

Here's a list of what's implemented so far:

 - `basic_text`, a text class template, sometimes known as string. I'm leaving
   "string" to mean "array of code units", as it's what a `string` class often
   turns out to be (and also what strings in other languages turn out to be).
   This is not that.  This represents text, regardless of encoding. It's a
   class template with template parameters for the underlying encoding and
   container but the interface it offers is for a range of codepoints. This
   makes conversions at API boundaries simple and type-safe. See these documents
   for more info on the ideas behind this class: [motivation] and [design].

 - `any_text`, a type erased variant of `basic_text` for use in compiled
   boundaries, or whenever templates are not appropriate/desired;

 - facilities for converting between ranges of codepoints to ranges of code
   units or bytes in UTF encodings, and vice-versa;

 - importing of data from the Unicode Character Database (UAX #44);

 - canonical equivalence;

 - canonical normalization forms (UAX #15);

 - extended grapheme cluster segmentation (UAX #29);

And a list of what's planned for the near future:

 - the rest of the segmentation algorithms (UAX #29);

 - collation algorithm (UTS #10);

  [design]: http://gist.io/3166256
  [wiki]: http://bitbucket.org/martinhofernandes/ogonek/wiki/Home
  [downloads]: http://bitbucket.org/martinhofernandes/ogonek/downloads
  [motivation]: http://gist.io/3965622

