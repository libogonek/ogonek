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
# Unicode normalization tests compiler

import sys
import os
import string
from datetime import datetime

if len(sys.argv) != 3:
    print('usage: ' + os.path.basename(sys.argv[0]) + ' <UCD folder> <output folder>')
    sys.exit(17)

ucd = sys.argv[1]
destination = sys.argv[2]

def filtertests(lines):
    for l in lines:
        if not l.startswith('#') and not l.startswith('@'):
            x = l.split('#')[0]
            if not x.strip() == '':
                yield x

def parseform(item):
    return ('\\x' + u.strip() for u in item.strip().split())

def parsetests(lines):
    return (['U"' + ''.join([str(x) for x in parseform(u)]) + '"' for u in l.split(';')] for l in lines)

copyrighttmpl = string.Template('''// Ogonek
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

// Unicode normalization test data
''')

headertmpl = string.Template('''
#ifndef OGONEK_TEST_NORMALIZATION_HPP
#define OGONEK_TEST_NORMALIZATION_HPP

#include <string>

namespace test {
    struct normalization_test {
        std::u32string input;
        std::u32string nfc;
        std::u32string nfd;
        std::u32string nfkc;
        std::u32string nfkd;
    };

    extern normalization_test normalization_test_data[${count}];
} // namespace test

#endif // OGONEK_TEST_SEGMENTATION_HPP
''')

impltmpl = string.Template('''
#include "normalization.g.h++"

namespace test {
    normalization_test normalization_test_data[] = {
        ${data}
    };
} // namespace test
''')

with open(os.path.join(ucd, 'NormalizationTest.txt'), 'r') as sourcefile:
    tests = list(parsetests(filtertests(sourcefile.readlines())))

with open(os.path.join(destination, 'normalization.g.h++'), 'w') as headerfile:
    headerfile.write(copyrighttmpl.substitute(date=datetime.utcnow().isoformat()+'Z'))
    headerfile.write(headertmpl.substitute(count=len(tests)))

with open(os.path.join(destination, 'normalization_test_data.g.c++'), 'w') as implfile:
    implfile.write(copyrighttmpl.substitute(date=datetime.utcnow().isoformat()+'Z'))
    entries = '\n        '.join('{{ {0}, {1}, {2}, {3}, {4} }},'.format(*t) for t in tests)
    implfile.write(impltmpl.substitute(data=entries))

