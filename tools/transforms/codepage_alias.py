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
# Codepage alias generator

import sys
import os
import string
import re
from datetime import datetime

if len(sys.argv) != 4:
    print('usage: ' + os.path.basename(sys.argv[0]) + ' <target> <header> <name>')
    sys.exit(17)

target = sys.argv[1]
header = sys.argv[2]
name = sys.argv[3]

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

#include <ogonek/encoding/${target}.h++>

namespace ogonek {
    using ${identifier} = ${target};
} // namespace ogonek

#endif // OGONEK_${pp_symbol}_HPP
''')

with open(header, 'w') as header_file:
    header_file.write(copyright_tmpl.substitute(name=name, date=datetime.utcnow().isoformat()+'Z'))
    header_file.write(header_tmpl.substitute(pp_symbol=name_caps, identifier=name_lower, target=target))

