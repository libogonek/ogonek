#! /usr/bin/python
#
# Ogonek
#
# Written in 2015 by Martinho Fernandes <rmf@rmf.io>
#
# To the extent possible under law, the author(s) have dedicated all copyright and related
# and neighboring rights to this software to the public domain worldwide. This software is
# distributed without any warranty.
#
# You should have received a copy of the CC0 Public Domain Dedication along with this software.
# If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
#
# Unicode segmentations tests compiler

import sys
import os
import re
import string
import os
from datetime import datetime

if len(sys.argv) != 3:
    print('usage: ' + os.path.basename(sys.argv[0]) + ' <UCD folder> <output folder>')
    sys.exit(17)

ucd = sys.argv[1]
output = sys.argv[2]

def filtertests(lines):
    return list(l.split('#')[0] for l in lines if not l.startswith('#'))

def parsestring(line):
    def makeescapes(ss):
        for s in ss:
            t = s.strip()
            if t != '':
                yield '\\x' + t

    escapes = ''.join(''.join(makeescapes(re.split('×|÷', line))))
    return 'U"' + escapes + '"'

def parsebreaks(line):
    def fn(l):
        for i, c in enumerate(c for c in l if c == '×' or c == '÷'):
            if c == '÷':
                yield i

    return list(fn(line))[1:]

copyrighttmpl = string.Template('''// Ogonek
//
// Written in 2015 by Martinho Fernandes <martinho.fernandes@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// This file was automatically generated on ${date}
''')

impltmpl = string.Template('''
// Test data for ${description} tests

#include "segmentation.g.h++"

namespace test {
    break_test ${kind}_test_data[] = {
        ${entries}
    };
} // namespace test
''')

headertmpl = string.Template('''
// Types for segmentation tests

#ifndef OGONEK_TEST_SEGMENTATION_HPP
#define OGONEK_TEST_SEGMENTATION_HPP

#include "utils.h++"
#include <vector>

namespace test {
    struct break_test {
        test::ustring input;
        std::vector<int> breaks;
    };

    extern break_test grapheme_test_data[${graphemes}];
    extern break_test word_test_data[${words}];
    extern break_test sentence_test_data[${sentences}];
    extern break_test line_test_data[${lines}];
} // namespace test

#endif // OGONEK_TEST_SEGMENTATION_HPP
''')

def writedata(file, kind, description, tests):
    strings = list(map(parsestring, tests))
    breaks = list(map(parsebreaks, tests))
    breakstrings = list(', '.join(map(str, b)) for b in  breaks)

    file.write(copyrighttmpl.substitute(date=datetime.utcnow().isoformat()+'Z'))
    entries = '\n        '.join('{{ {0}, {{ {1} }} }},'.format(*t) for t in zip(strings, breakstrings))
    file.write(impltmpl.substitute(kind=kind, description=description, entries=entries))

with open(os.path.join(ucd, 'auxiliary/GraphemeBreakTest.txt'), 'r') as graphemefile:
    graphemes = list(filtertests(graphemefile.readlines()))
with open(os.path.join(ucd, 'auxiliary/GraphemeBreakTest.txt'), 'r') as wordfile:
    words = list(filtertests(wordfile.readlines()))
with open(os.path.join(ucd, 'auxiliary/GraphemeBreakTest.txt'), 'r') as sentencefile:
    sentences = list(filtertests(sentencefile.readlines()))
with open(os.path.join(ucd, 'auxiliary/GraphemeBreakTest.txt'), 'r') as linefile:
    lines = list(filtertests(linefile.readlines()))

with open(os.path.join(output, 'segmentation.g.h++'), 'w') as headerfile:
    headerfile.write(copyrighttmpl.substitute(date=datetime.utcnow().isoformat()+'Z'))
    headerfile.write(headertmpl.substitute(graphemes=len(graphemes), words=len(words), sentences=len(sentences), lines=len(lines)))

with open(os.path.join(output, 'grapheme_test_data.g.c++'), 'w') as graphemefile:
    writedata(graphemefile, 'grapheme', 'grapheme clusters', graphemes)
with open(os.path.join(output, 'word_test_data.g.c++'), 'w') as wordfile:
    writedata(wordfile, 'word', 'words', words)
with open(os.path.join(output, 'sentence_test_data.g.c++'), 'w') as sentencefile:
    writedata(sentencefile, 'sentence', 'sentences', sentences)
with open(os.path.join(output, 'line_test_data.g.c++'), 'w') as linefile:
    writedata(linefile, 'line', 'lines', lines)

