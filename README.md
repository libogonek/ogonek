Ogonek is mostly the result of me playing around with Unicode. It is turning
into something real.

Here's a list of what's implemented so far:

 - `basic_text`, a text class template aka string. I'm leaving "string" to mean
   "array of code units", as it's what a `string` class often turns out to be
   (and also what strings in other languages turn out to be). This is not that.
   This represents text, regardless of encoding. It's a class template with
   template parameters for the underlying encoding and container but the
   interface it offers is for a range of codepoints. This makes conversions at
   API boundaries simple and type-safe. See http://gist.io/3166256 for more
   info;

 - `any_text`, a type erased variant of `basic_text` for use in compiled
   boundaries, or whenever templates are not appropriate/desiredM

 - facilities for converting between ranges of codepoints to ranges of code
   units or bytes in UTF encodings, and vice-versa;

 - importing of data from the Unicode Character Database (UAX #44);

 - canonical decomposition

 - some text segmentation algorithms (UAX #29);

And a list of what's planned for the near future:

 - an alias of `basic_text` with utf8 on Linux and utf16 on Windows, for native
   interoperation;

 - a variant of `basic_text` that employs type erasure to hide encoding and
   container;

 - the rest of the segmentation algorithms (UAX #29);

 - normalization algorithms (UAX #15);

 - collation algorithm (UTS #10);

