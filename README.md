Ogonek is mostly the result of me playing around with Unicode. It is turning
into something real.

Here's a list of what's implemented so far:

 - facilities for converting between ranges of codepoints to ranges of code
   units or bytes in UTF encodings, and vice-versa;

 - importing of data from the Unicode Character Database (UAX #44);

 - some text segmentation algorithms (UAX #29);

And a list of what's planned for the near future:

 - the rest of the segmentation algorithms (UAX #29);

 - text classes; aka string, but I'm leaving "string" to mean "array of code
   units", as it's what a `string` class often turns out to be. These are not.
   These represent text, regardless of encoding and regardless of container type.

   - a class template with template parameters for the underlying encoding and container;

   - an alias template of that class template with utf8 on Linux and utf16 on Windows.

   - a class similar to the above template, but with the encoding type erased;

 - normalization algorithms (UAX #15);

