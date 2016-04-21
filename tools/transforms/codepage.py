#! /usr/bin/python
#
# Ogonek
#
# Written in 2016 by Martinho Fernandes <ogonek@rmf.io>
#
# To the extent possible under law, the author(s) have dedicated all copyright and related
# and neighboring rights to this software to the public domain worldwide. This software is
# distributed without any warranty.
#
# You should have received a copy of the CC0 Public Domain Dedication along with this software.
# If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
#
# Codepage compiler

import sys
import string
import re
import os
import codecs
from datetime import datetime

if len(sys.argv) != 5:
    print('usage: ' + os.path.basename(sys.argv[0]) + ' <input> <header> <impl> <name>')
    sys.exit(17)

codepage = sys.argv[1]
header = sys.argv[2]
impl = sys.argv[3]
name = sys.argv[4]

source = codecs.open(codepage, 'r', 'utf-8')

mapping = {}
for line in source:
    line = line.split('#', 1)[0]
    parts = line.split()
    if(len(parts) < 2):
        continue

    l = int(parts[0], 16)
    r = int(parts[1], 16)
    mapping[l] = r

to_str = ''
for i in xrange(0, 256):
    if i in mapping.keys():
        to_str += '        ' + hex(mapping[i]) + ',\n'
    else:
        to_str += '        0xFFFFFFFF,\n'
to_str = to_str.rstrip()

from_str = sorted(mapping.iteritems(), key=lambda e: e[1])
from_str = map(lambda e: '        { char(' + hex(e[0]) + '), ' + hex(e[1]) + ' },', from_str)
from_str = '\n'.join(from_str)

name_lower = re.sub(r'((?<!\d)[ -](?!\d)|(?<=\d))[ -]', '_', name.lower());
name_lower = re.sub(r'(?<!\d)[ -](?=\d)', '', name_lower);
name_caps = name_lower.upper()

copyright_tmpl = string.Template('''// Ogonek
//
// Written in 2016 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// This file was automatically generated on ${date}

// ${name} encoding form

''')

header_tmpl = string.Template('''#ifndef OGONEK_${pp_symbol}_HPP
#define OGONEK_${pp_symbol}_HPP

#include <ogonek/types.h++>
#include <ogonek/encoding/codepage_encoding.h++>

namespace ogonek {
    struct ${identifier}_codepage {
        static code_point to_unicode[256];
        static codepage_entry from_unicode[${size}];
    };

    using ${identifier} = codepage_encoding<${identifier}_codepage>;
} // namespace ogonek

#endif // OGONEK_${pp_symbol}_HPP
''')

with open(header, 'w') as header_file:
    header_file.write(copyright_tmpl.substitute(name=name, date=datetime.utcnow().isoformat()+'Z'))
    header_file.write(header_tmpl.substitute(pp_symbol=name_caps, identifier=name_lower, size=len(mapping)))

impl_tmpl = string.Template('''#include <ogonek/types.h++>
#include <ogonek/encoding/${header}>

namespace ogonek {
    code_point ${identifier}_codepage::to_unicode[256] = {
$to_str
    };
    codepage_entry ${identifier}_codepage::from_unicode[] = {
$from_str
    };
} // namespace ogonek
''')

with open(impl, 'w') as impl_file:
    impl_file.write(copyright_tmpl.substitute(name=name, date=datetime.utcnow().isoformat()+'Z'))
    impl_file.write(impl_tmpl.substitute(header=os.path.basename(header), identifier=name_lower, from_str=from_str, to_str=to_str))

