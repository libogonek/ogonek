#!/usr/bin/python

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
# Unicode character property metadata

import sys
import os
import errno
import math
import string
from contextlib import contextmanager
from itertools import chain
if sys.version_info[0] > 2:
    from itertools import zip_longest
else:
    from itertools import izip_longest
    zip_longest = izip_longest
from fractions import Fraction

list_files = False
if __name__ != '__main__':
    dry_run = True
elif len(sys.argv) == 5:
    abi = sys.argv[1]
    ucd_dir = sys.argv[2]
    inc_dir = sys.argv[3]
    src_dir = sys.argv[4]
    dry_run = False
elif len(sys.argv) == 3 and sys.argv[1] == '--files':
    dry_run = True
    list_files = True
    src_dir = sys.argv[2]
else:
    print('usage: ' + os.path.basename(sys.argv[0]) + ' <ABI label> <UCD directory> <header output> <src output>')
    sys.exit(17)

def distinct(l):
    s = set()
    for x in l:
        if x not in s:
            s.add(x)
            yield x

def canonical_of(value, aliases):
    if len(aliases) == 0:
        return value
    canon = {p[0] for p in aliases if (p[0] == value or p[1] == value) and not isinstance(p[0], int)}
    if len(canon) == 0:
        return value
    assert len(canon) == 1
    return canon.pop()

def aliases_of(value, aliases):
    if len(aliases) == 0:
        return []
    first = list(distinct(p[0] for p in aliases if p[1] == value))
    second = list(distinct(p[1] for p in aliases if p[0] == value))
    return first + second

def to_camel_case(x):
    def impl():
        yield x[0].lower()
        last = x[0]
        for c in x[1:]:
            if c in string.ascii_uppercase and last in string.ascii_lowercase:
                yield '_'
            yield c.lower()
            last = c
    return ''.join(impl())

def cpp_ize(x):
    x = to_camel_case(x)
    if x[0].isdigit():
        x = '_' + x
    return x.replace('.', '_').replace(' ', '_').replace('-', '_')

@contextmanager
def report_action(description):
    #sys.stdout.write('{0}... '.format(description))
    #sys.stdout.flush()
    yield 1
    #sys.stdout.write('done.\n')
    #sys.stdout.flush()

class Type:
    def all_aliases(self):
        """Returns all aliases for this type's values.
           This is a list of pairs (canonical, alias)."""
        return []

    def all_flag_aliases(self):
        """Returns all the aliases of multi-bit values for flag enums"""
        return []

    def cpp(self, value):
        """Returns the C++ representation of this value."""
        return value

    def py(self, value):
        """Returns a representation of this value using Python types."""
        return value

    def parse(self, string):
        """Parses a representation of a value of this type from the UCD.
           Defaults to the canonical form of the string."""
        if string is None:
            return string
        return self.canonical(string.strip())

    def aliases(self, value):
        """Returns the aliases for this one value."""
        all = self.all_aliases()
        noncanon = [p[1] for p in all if p[0] == value] 
        canon = self.canonical(value)
        return noncanon + ([canon] if canon != value else [])

    def canonicals(self):
        """Returns all canonical values of this type."""
        all = self.all_aliases()
        if any(p for p in all if isinstance(p[0], int) or isinstance(p[1], int)):
            return []
        return list(distinct(p[0] for p in all))

    def canonical(self, value):
        """Returns the canonical alias of this value."""
        all = self.all_aliases()
        return canonical_of(value, self.all_aliases())

    def parse_default(self, value):
        """Parses the special default value markers for this type"""
        return value

class Types:
    class Binary(Type):
        def all_aliases(self):
            return [('Y', 'Yes'), ('Y', 'T'), ('Y', 'True' ),
                    ('N', 'No' ), ('N', 'F'), ('N', 'False')]

        def cpp(self, value):
            canon = self.canonical(value)
            if canon == 'Y':
                return 'true'
            else:
                return 'false'

        def py(self, value):
            canon = self.canonical(value)
            return canon == 'Y'

        def __repr__(self):
            return 'BINARY'

    class Trinary(Type):
        def all_aliases(self):
            return [('Y', 'Yes'),
                    ('N', 'No' ),
                    ('M', 'Maybe')]

        def cpp(self, value):
            canon = self.canonical(value)
            if canon == 'Y':
                return '{ 1 }'
            elif canon == 'N':
                return '{ 0 }'
            else:
                return '{ -1 }'

        def py(self, value):
            canon = self.canonical(value)
            if canon == 'Y':
                return True
            elif canon == 'N':
                return False
            else:
                return None

        def __repr__(self):
            return 'TRINARY'

    class CodePoint(Type):
        def cpp(self, value):
            code_point = self.py(value)
            return "U'\\x{0:X}'".format(code_point)

        def py(self, value):
            is_valid = value and len(value) > 0 and value != '<none>' and value != '<code point>'
            return int(value, 16) if is_valid else 0xFFFFFFFF

        def __repr__(self):
            return 'CODE_POINT'

    class String(Type):
        def cpp(self, value):
            code_points = self.py(value)
            if code_points is None or len(code_points) == 0:
                return 'nullptr'
            else:
                return 'U"{0}"'.format(''.join('\\x{0:X}'.format(u) for u in code_points))

        def py(self, value):
            if not value or value == '<code point>':
                return None
            else:
                return [int(u, 16) for u in value.split(' ') if len(u) > 0]

        def __repr__(self):
            return 'STRING'

    class Numeric(Type):
        def cpp(self, value):
            num = self.py(value)
            if math.isnan(num):
                return 'std::numeric_limits<double>::quiet_NaN()'
            return '{0}.'.format(num)

        def py(self, value):
            return int(value) if value or len(value) > 0 else float('NaN')

        def __repr__(self):
            return 'NUMBER'

    class Fractional(Type):
        def cpp(self, value):
            frac = self.py(value)
            if frac is None:
                return '{ 0, 0 }'
            else:
                return '{{ {0}, {1} }}'.format(frac.numerator, frac.denominator)

        def py(self, value):
            if value == 'NaN':
                return None
            else:
                return Fraction(value) if value or len(value) > 0 else None

        def __repr__(self):
            return 'FRACTION'

    class Catalog(Type):
        def __init__(self, typename, aliases):
            self.typename = typename
            self.aliases = aliases

        def all_aliases(self):
            return self.aliases

        def cpp(self, value):
            canon = self.canonical(value)
            return '{0}::{1}'.format(self.typename, cpp_ize(canon))

        def py(self, value):
            canon = self.canonical(value)
            return (typename, canon)

        def __repr__(self):
            return 'C[{0}]'.format(self.typename)

    class Enumeration(Type):
        def __init__(self, typename, aliases, flag_aliases=[]):
            self.typename = typename
            self.aliases = aliases
            self.flag_aliases = flag_aliases

        def all_aliases(self):
            return self.aliases

        def all_flag_aliases(self):
            return self.flag_aliases

        def cpp(self, value):
            canon = self.canonical(value)
            return '{0}::{1}'.format(self.typename, cpp_ize(canon))

        def py(self, value):
            canon = self.canonical(value)
            return (typename, canon)

        def __repr__(self):
            return 'E[{0}]'.format(self.typename)

    class NamedNumbers(Type):
        def __init__(self, typename, aliases):
            self.typename = typename
            self.aliases = aliases

        def all_aliases(self):
            return self.aliases

        def cpp(self, value):
            canon = self.canonical(value)
            return '{0}({1})'.format(self.typename, canon.lower())

        def py(self, value):
            return int(value)

        def __repr__(self):
            return 'N[{0}]'.format(self.typename)

    class Name(Type):
        def cpp(self, value):
            name = self.py(value)
            if name:
                if name == '<control>':
                    return 'u8""'
                else:
                    return 'u8"{0}"'.format(value)
            else:
                return 'nullptr'

        def py(self, value):
            if value == '<none>':
                return None
            return value

        def __repr__(self):
            return 'NAME'

    class Ignored(Type):
        def cpp(self, value):
            pass
        def py(self, value):
            pass
        def __repr__(self):
            return "IGNORED"

    class Raw(Type):
        def __repr__(self):
            return 'RAW'

    class Range(Type):
        def cpp(self, value):
            tup = self.py(value)
            return '0x{0:X}'.format(tup[0])

        def py(self, value):
            def remove_uplus(x):
                return x[2:] if x.startswith('U+') else x
            split = [remove_uplus(x) for x in value.strip().split('..')]
            if len(split) == 1:
                split = [split[0], split[0]]
            return tuple(int(u, 16) for u in split)

        def __repr__(self):
            return 'RANGE'

    class DoubleByte(Type):
        def cpp(self, value):
            num = self.py(value)
            return '0x{0:X}u'.format(num)

        def py(self, value):
            return int(value, 16) if value or len(value) > 0 else 0xFFFF

        def __repr__(self):
            return '2BYTES'

    class Multiple(Type):
        def __init__(self, typename, type):
            self.typename = typename
            self.type = type

        def all_aliases(self):
            return self.type.all_aliases()

        def cpp(self, value):
            return self.type.cpp(value)

        def py(self, value):
            return self.type.py(value)

        def parse(self, array):
            return [self.type.parse(s) for s in array]

        def __repr__(self):
            return '{0}*'.format(self.type)

class Value:
    def __init__(self, type, value):
        self.type = type
        self.value = value
    def cpp(self):
        return self.type.cpp(self.value)
    def py(self):
        return self.type.py(self.value)
    def __repr__(self):
        return '{0}({1})'.format(self.type, self.value)

def parse_field(split):
    return [Value(t, t.parse(p)) for t, p in split if t]

missing_string = '# @missing: '

def parse_file(source, sep, fields, custom_field=None):
    def strip_comments(f):
        for l in f.readlines():
            comment = l.find('#')
            stripped = (l[0:comment] if not l.startswith('# @missing:') else l).strip()
            if len(stripped) > 0:
                yield stripped

    lines = list(strip_comments(source))
    value_lines = [l for l in lines if not l.startswith(missing_string)]
    default_lines = [l[len(missing_string):] for l in lines if l.startswith(missing_string)]

    value_splits = ([s.strip() for s in l.split(sep)] for l in value_lines)
    default_splits = ([s.strip() for s in l.split(sep)] for l in default_lines)

    field_parser = custom_field or parse_field

    default_fields = list(fields)
    default_fields[0] = Types.Range()
    values = [field_parser(list(zip_longest(fields, s))) for s in value_splits]
    defaults = [field_parser(list(zip_longest(default_fields, s))) for s in default_splits]

    return (values, defaults)

def fill_defaults(prop, parsed_defaults, default_values):
    for p in parsed_defaults:
        if prop:
            default_values[prop] = p
        else:
            default_values[p[1].value] = [p[0], p[2]]

default_values = {}
def parse_all(ucd_dir, file_defs):
    global default_values

    def rel_path(path):
        r = os.path.relpath(path, ucd_dir)
        return r[2:] if r.startswith('./') else r

    def iterate_txt_files(root):
        for path, dirs, files in os.walk(root):
            for file in files:
                if file.endswith('.txt'):
                    yield rel_path(os.path.join(path, file))

    parsed_files = dict()
    for path in sorted(iterate_txt_files(ucd_dir)):
        if path not in file_defs:
            continue
        definition = file_defs[path]
        prop   = definition[0]
        fields = definition[1]
        custom = definition[2] if len(definition) > 2 else None
        sep = '\t' if path.startswith('Unihan_') else ';'
        with report_action('Loading {0}'.format(path)):
            with open(os.path.join(ucd_dir, path), 'r') as file:
                parsed_values, parsed_defaults = parse_file(file, sep, fields, custom)
                parsed_files[path] = parsed_values
                fill_defaults(prop, parsed_defaults, default_values)
    return parsed_files

def pair_up(a):
    done = set()
    pairs = []
    for x in a[1:]:
        if a[0] != x and cpp_ize(x) not in done:
            done.add(cpp_ize(x))
            pairs.append((a[0], x))
    if len(pairs) == 0:
        pairs = [(a[0], a[0])]
    return pairs
def build_aliases(records):
    tuples = [pair_up([v.value for v in r if v.value]) for r in records]
    flat = list(chain(*tuples))
    return flat
def build_value_aliases(prop_aliases, records):
    tuples = [(r[0].value, pair_up([v.value for v in r[1:] if v.value])) for r in records]
    by_prop = {canonical_of(r[0], prop_aliases): [] for r in tuples}
    for r in tuples:
        by_prop[r[0]] += r[1]
    return by_prop
def build_case_fold_statuses(records):
    return [(x, x) for x in {r[1].value for r in records} if len(x) > 0]
def build_name_alias_types(records):
    return [(x, x) for x in {r[2].value for r in records} if len(x) > 0]
def build_case_conditions(records):
    return [(x, x) for x in {r[4].value for r in records} if len(x) > 0]

def parse_aliases(ucd_dir, file_defs):
    meta_info = parse_all(ucd_dir, file_defs)

    def extract_gc_flags(value_aliases):
        raw = value_aliases['gc']
        combos = distinct(x[0] for x in raw if len(x[0]) == 1)
        canons = [x[0] for x in raw if len(x[0]) == 2]
        flags = { c: list(distinct(can for can in canons if can.startswith(c))) for c in combos }
        return flags

    def rearrange_ccc(value_aliases):
        def reorder(alias):
            return [(int(x) if x[0].isdigit() else x) for x in sorted(alias, key=lambda x: x[0].isdigit())]
        reordered = [reorder(a) for a in value_aliases['ccc']]
        grouped = { a[1]: [] for a in reordered }
        for a in reordered:
            grouped[a[1]].append(a[0])
        for n in grouped:
            g = grouped[n]
            g.sort(key = lambda x: len(x))
            grouped[n] = (g[0], g[1:])
        value_aliases['ccc'] = []
        for n in grouped:
            value_aliases['ccc'].append((n, grouped[n][0]))
            for g in grouped[n][1]:
                value_aliases['ccc'].append((grouped[n][0], g))

    with report_action('Extracting aliases'):
        prop_aliases = build_aliases(meta_info['PropertyAliases.txt'])
        value_aliases = build_value_aliases(prop_aliases, meta_info['PropertyValueAliases.txt'])

        value_aliases['$case_folding_status'] = build_case_fold_statuses(meta_info['CaseFolding.txt'])
        value_aliases['$name_alias_type'] = build_name_alias_types(meta_info['NameAliases.txt'])
        value_aliases['$case_condition'] = build_case_conditions(meta_info['SpecialCasing.txt'])

        flag_aliases = { 'gc': extract_gc_flags(value_aliases) }

        rearrange_ccc(value_aliases)

    return (prop_aliases, value_aliases, flag_aliases)

def parse_pva(split):
    if '..' not in split[0][1]:
        return parse_field(split)
    else:
        split[2] = (Types.Raw(), split[2][1])
        split = split[:3]
        return parse_field(split)

meta_defs = {
    'PropertyAliases.txt':      (None, [Types.Name(), Types.Name(), Types.Name(), Types.Name(), Types.Name()]),
    'PropertyValueAliases.txt': (None, [Types.Name(), Types.Name(), Types.Name(), Types.Name(), Types.Name()],
                                 parse_pva),
    'CaseFolding.txt':          (None, [Types.Ignored(), Types.Name(), Types.Ignored()]),
    'NameAliases.txt':          (None, [Types.Ignored(), Types.Ignored(), Types.Name()]),
    'SpecialCasing.txt':        (None, [Types.Ignored(), Types.Ignored(), Types.Ignored(), Types.Ignored(), Types.Name()]),
}

def dry_aliases():
    enum_catalog_props = ['sc', 'bc', 'ccc', 'dt', 'ea', 'gc', 'jg', 'jt', 'lb', 'nt', 'bpt', 'blk', '$case_folding_status', 'age', 'hst', 'InPC', 'InSC', '$name_alias_type', '$case_condition', 'GCB', 'SB', 'WB']
    return {}, { x: [] for x in enum_catalog_props }, { 'gc': [] }

if dry_run:
    prop_aliases, value_aliases, flag_aliases = dry_aliases()
else:
    prop_aliases, value_aliases, flag_aliases = parse_aliases(ucd_dir, meta_defs)

script_type                    = Types.Catalog('script', value_aliases['sc'])
bidi_class_type                = Types.Enumeration('bidi_class', value_aliases['bc'])
combining_class_type           = Types.NamedNumbers('combining_class', value_aliases['ccc'])
decomposition_type_type        = Types.Enumeration('decomposition_type', value_aliases['dt'])
east_asian_width_type          = Types.Enumeration('east_asian_width', value_aliases['ea'])
general_category_type          = Types.Enumeration('general_category', value_aliases['gc'], flag_aliases['gc'])
joining_group_type             = Types.Enumeration('joining_group', value_aliases['jg'])
joining_type_type              = Types.Enumeration('joining_type', value_aliases['jt'])
line_break_type                = Types.Enumeration('line_break', value_aliases['lb'])
numeric_type_type              = Types.Enumeration('numeric_type', value_aliases['nt'])
bracket_type_type              = Types.Enumeration('bracket_type', value_aliases['bpt'])
block_type                     = Types.Catalog('block', value_aliases['blk'])
case_folding_status_type       = Types.Enumeration('$case_folding_status', value_aliases['$case_folding_status'])
version_type                   = Types.Catalog('version', value_aliases['age'])
hangul_syllable_type_type      = Types.Enumeration('hangul_syllable_type', value_aliases['hst'])
indic_positional_category_type = Types.Enumeration('indic_positional_category', value_aliases['InPC'])
indic_syllabic_category_type   = Types.Enumeration('indic_syllabic_category', value_aliases['InSC'])
alias_type_type                = Types.Enumeration('$name_alias_type', value_aliases['$name_alias_type'])
case_condition_type            = Types.Catalog('$case_condition', value_aliases['$case_condition'])
grapheme_cluster_break_type    = Types.Enumeration('grapheme_cluster_break', value_aliases['GCB'])
sentence_break_type            = Types.Enumeration('sentence_break', value_aliases['SB'])
word_break_type                = Types.Enumeration('word_break', value_aliases['WB'])
multiple_script_type           = Types.Multiple('script_list', script_type)

def parse_unidata(split):
    parts = split[5][1].split('>')
    split[5] = (Types.String(), parts[1].strip() if len(parts) > 1 else parts[0])
    return parse_field(split)

def parse_dnorm(split):
    a, b = split[2]
    if split[1][1] == 'Full_Composition_Exclusion':
        a, b = (Types.Binary(), 'Y')
    elif split[1][1] == 'NFD_QC':
        a = Types.Binary()
    elif split[1][1] == 'NFC_QC':
        a = Types.Trinary()
    elif split[1][1] == 'NFKD_QC':
        a = Types.Binary()
    elif split[1][1] == 'NFKC_QC':
        a = Types.Trinary()
    elif split[1][1] == 'NFKC_CF':
        a = Types.String()
    elif split[1][1] == 'Changes_When_NFKC_Casefolded':
        a, b = (Types.Binary(), 'Y')

    split[2] = (a, b)
    return parse_field(split)

def parse_scriptex(split):
    return parse_field([split[0], (multiple_script_type, split[1][1].split(' '))])

input_defs = {
    'auxiliary/GraphemeBreakProperty.txt':    ('Grapheme_Cluster_Break',    [Types.Range(), grapheme_cluster_break_type]),
    'auxiliary/SentenceBreakProperty.txt':    ('Sentence_Break',            [Types.Range(), sentence_break_type]),
    'auxiliary/WordBreakProperty.txt':        ('Word_Break',                [Types.Range(), word_break_type]),
    'extracted/DerivedBidiClass.txt':         ('Bidi_Class',                [Types.Range(), bidi_class_type]),
    'extracted/DerivedBinaryProperties.txt':  (None,                        [Types.Range(), Types.Binary()]),
    'extracted/DerivedCombiningClass.txt':    ('Canonical_Combining_Class', [Types.Range(), combining_class_type]),
    'extracted/DerivedDecompositionType.txt': ('Decomposition_Type',        [Types.Range(), decomposition_type_type]),
    'extracted/DerivedEastAsianWidth.txt':    ('East_Asian_Width',          [Types.Range(), east_asian_width_type]),
    'extracted/DerivedGeneralCategory.txt':   ('General_Category',          [Types.Range(), general_category_type]),
    'extracted/DerivedJoiningGroup.txt':      ('Joining_Group',             [Types.Range(), joining_group_type]),
    'extracted/DerivedJoiningType.txt':       ('Joining_Type',              [Types.Range(), joining_type_type]),
    'extracted/DerivedLineBreak.txt':         ('Line_Break',                [Types.Range(), line_break_type]),
    'extracted/DerivedNumericType.txt':       ('Numeric_Type',              [Types.Range(), numeric_type_type]),
    'extracted/DerivedNumericValues.txt':     ('Numeric_Value',             [Types.Range(), Types.Ignored(), Types.Ignored(), Types.Fractional()]),
    'BidiBrackets.txt':                       (None,                        [Types.Range(), Types.CodePoint(), bracket_type_type]),
    'BidiMirroring.txt':                      ('Bidi_Mirroring_Glyph',      [Types.Range(), Types.CodePoint()]),
    'Blocks.txt':                             ('Block',                     [Types.Range(), block_type]),
    'CaseFolding.txt':                        (None,                        [Types.Range(), case_folding_status_type, Types.String()]),
    'CJKRadicals.txt':                        (None,                        [Types.Numeric(), Types.CodePoint(), Types.CodePoint()]),
    'DerivedAge.txt':                         ('Age',                       [Types.Range(), version_type]),
    'DerivedCoreProperties.txt':              (None,                        [Types.Range(), Types.Name()]),
    'DerivedNormalizationProps.txt':          (None,                        [Types.Range(), Types.Name(), Types.Raw()],
                                               parse_dnorm),
    'EmojiSources.txt':                       (None,                        [Types.String(), Types.DoubleByte(), Types.DoubleByte(), Types.DoubleByte()]),
    'HangulSyllableType.txt':                 ('Hangul_Syllable_Type',      [Types.Range(), hangul_syllable_type_type]),
    'IndicPositionalCategory.txt':            ('Indic_Positional_Category', [Types.Range(), indic_positional_category_type]),
    'IndicSyllabicCategory.txt':              ('Indic_Syllabic_Category',   [Types.Range(), indic_syllabic_category_type]),
    'Jamo.txt':                               ('Jamo_Short_Name',           [Types.Range(), Types.Name()]),
    'NameAliases.txt':                        ('Name_Alias',                [Types.Range(), Types.Name(), alias_type_type]),
    'NamedSequences.txt':                     (None,                        [Types.Name(), Types.String()]),
    'PropList.txt':                           (None,                        [Types.Range(), Types.Name()]),
    'ScriptExtensions.txt':                   ('Script_Extensions',         [Types.Range(), Types.Raw()],
                                               parse_scriptex),
    'Scripts.txt':                            ('Script',                    [Types.Range(), script_type]),
    'SpecialCasing.txt':                      (None,                        [Types.Range(), Types.String(), Types.String(), Types.String(), case_condition_type]),
#    'Unihan_DictionaryIndices.txt':           (None,                        [Types.Range(), Types.Name(), Types.Raw()]),
#                                               parse_uhan_dix),
#    'Unihan_DictionaryLikeData.txt':          (None,                        [Types.Range(), Types.Name(), Types.Raw()]),
#                                               parse_uhan_dld),
#    'Unihan_IRGSources.txt':                  (None,                        [Types.Range(), Types.Name(), Types.Raw()]),
#                                               parse_uhan_irgs),
#    'Unihan_NumericValues.txt':               (None,                        [Types.Range(), Types.Name(), Types.Numeric()]),
#    'Unihan_OtherMappings.txt':               (None,                        [Types.Range(), Types.Name(), Types.Raw()]),
#                                               parse_uhan_other),
#    'Unihan_RadicalStrokeCounts.txt':         (None,                        [Types.Range(), Types.Name(), Types.Raw()]),
#                                               parse_uhan_stcnt),
#    'Unihan_Readings.txt':                    (None,                        [Types.Range(), Types.Name(), Types.Raw()]),
#                                               parse_uhan_reading),
#    'Unihan_Variants.txt':                    (None,                        [Types.Range(), Types.Name(), Types.Raw()]),
#                                               parse_uhan_variant),
    'UnicodeData.txt':                        (None,                        [Types.Range(), Types.Name(), Types.Ignored(), Types.Ignored(), Types.Ignored(), Types.Raw(), Types.Ignored(), Types.Ignored(), Types.Ignored(), Types.Ignored(), Types.Ignored(), Types.Ignored(), Types.CodePoint(), Types.CodePoint(), Types.CodePoint()],
                                               parse_unidata),
}

class Props:
    def __init__(self, aliases):
        self.d = dict()
        self.aliases = aliases
    def __getitem__(self, key):
        return self.d[canonical_of(key, self.aliases)]
    def __setitem__(self, key, item):
        self.d[canonical_of(key, self.aliases)] = item
    def __iter__(self):
        return self.d.__iter__()
    def __repr__(self):
        return self.d.__repr__()

def extract_props(aliases, parsed):
    props = Props(aliases)

    def gen_names(gen):
        try:
            while True:
                r = next(gen)
                if r[1].value.startswith('<') and r[1].value.endswith(', First>'):
                    r2 = next(gen)
                    start = r[1].value.split(',')[0]
                    assert r2[1].value.startswith(start)
                    assert r2[1].value.endswith(', Last>')
                    yield [Value(Types.Range(), '{0}..{1}'.format(r[0].value, r2[0].value)), Value(Types.Name(), start[0:]+'>')]
                else:
                    yield r
        except StopIteration:
            pass

    def gen_indexed_prop(records, index):
        return ([r[0], r[index]] for r in records)

    def gen_aliases(name_aliases):
        grouped = {a[0].value: (a[0], []) for a in name_aliases}
        for a in name_aliases:
            grouped[a[0].value][1].append((a[2], a[1]))
        return grouped.values()

    def canon_equal(a, b):
        return canonical_of(a, aliases) == canonical_of(b, aliases)

    def gen_listed_bool_prop(listed, name):
        return ([r[0], Value(Types.Binary(), 'Y')] for r in listed if canon_equal(r[1].value, name))

    def gen_listed_prop(listed, name):
        return ([r[0], r[2]] for r in listed if canon_equal(r[1].value, name))

    def gen_unconditional_special_casing():
        return (r for r in parsed['SpecialCasing.txt'] if r[4].value == '')

    prop_defs = {
        'Age':                          parsed['DerivedAge.txt'],
        'Name':                         gen_names(gen_indexed_prop(parsed['UnicodeData.txt'], 1)), # (Range, Name)
#        'Name_Alias':                   gen_aliases(parsed['NameAliases.txt']), # (Range, [(Name_Alias_Type, Name_Alias)])
        'Block':                        parsed['Blocks.txt'],
        'General_Category':             parsed['extracted/DerivedGeneralCategory.txt'],
        'Canonical_Combining_Class':    parsed['extracted/DerivedCombiningClass.txt'],
        'Bidi_Class':                   parsed['extracted/DerivedBidiClass.txt'],
        'Bidi_Mirrored':                gen_listed_bool_prop(parsed['extracted/DerivedBinaryProperties.txt'], 'Bidi_Mirrored'),
        'Bidi_Mirroring_Glyph':         parsed['BidiMirroring.txt'],
        'Bidi_Control':                 gen_listed_bool_prop(parsed['PropList.txt'], 'Bidi_Control'),
        'Bidi_Paired_Bracket':          gen_indexed_prop(parsed['BidiBrackets.txt'], 1),
        'Bidi_Paired_Bracket_Type':     gen_indexed_prop(parsed['BidiBrackets.txt'], 2),
        'Decomposition_Mapping':        gen_indexed_prop(parsed['UnicodeData.txt'], 5),
        'Decomposition_Type':           parsed['extracted/DerivedDecompositionType.txt'],
        'Full_Composition_Exclusion':   gen_listed_bool_prop(parsed['DerivedNormalizationProps.txt'], 'Full_Composition_Exclusion'),
        'NFC_Quick_Check':              gen_listed_prop(parsed['DerivedNormalizationProps.txt'], 'NFC_Quick_Check'),
        'NFD_Quick_Check':              gen_listed_prop(parsed['DerivedNormalizationProps.txt'], 'NFD_Quick_Check'),
        'NFKC_Quick_Check':             gen_listed_prop(parsed['DerivedNormalizationProps.txt'], 'NFKC_Quick_Check'),
        'NFKD_Quick_Check':             gen_listed_prop(parsed['DerivedNormalizationProps.txt'], 'NFKD_Quick_Check'),
        'Numeric_Type':                 parsed['extracted/DerivedNumericType.txt'],
        'Numeric_Value':                gen_indexed_prop(parsed['extracted/DerivedNumericValues.txt'], 3),
        'Joining_Type':                 parsed['extracted/DerivedJoiningType.txt'],
        'Joining_Group':                parsed['extracted/DerivedJoiningGroup.txt'],
        'Join_Control':                 gen_listed_bool_prop(parsed['PropList.txt'], 'Join_Control'),
        'Line_Break':                   parsed['extracted/DerivedLineBreak.txt'],
        'East_Asian_Width':             parsed['extracted/DerivedEastAsianWidth.txt'],
        'Uppercase':                    gen_listed_bool_prop(parsed['DerivedCoreProperties.txt'], 'Uppercase'),
        'Lowercase':                    gen_listed_bool_prop(parsed['DerivedCoreProperties.txt'], 'Lowercase'),
        'Simple_Uppercase_Mapping':     gen_indexed_prop(parsed['UnicodeData.txt'], 12),
        'Simple_Lowercase_Mapping':     gen_indexed_prop(parsed['UnicodeData.txt'], 13),
        'Simple_Titlecase_Mapping':     gen_indexed_prop(parsed['UnicodeData.txt'], 14), # TODO null
        'Uppercase_Mapping':            gen_indexed_prop(gen_unconditional_special_casing(), 3),
        'Lowercase_Mapping':            gen_indexed_prop(gen_unconditional_special_casing(), 1),
        'Titlecase_Mapping':            gen_indexed_prop(gen_unconditional_special_casing(), 2), # TODO contextual casing
        'Simple_Case_Folding':          ((r[0], Value(Types.CodePoint(), r[2].value)) for r in parsed['CaseFolding.txt'] if r[1].value in {'C', 'S'}),
        'Case_Folding':                 ((r[0], r[2]) for r in parsed['CaseFolding.txt'] if r[1].value == 'F'),
        '$Turkic_Case_Folding':         ((r[0], r[2]) for r in parsed['CaseFolding.txt'] if r[1].value == 'T'),
        'Case_Ignorable':               gen_listed_bool_prop(parsed['DerivedCoreProperties.txt'], 'Case_Ignorable'),
        'Cased':                        gen_listed_bool_prop(parsed['DerivedCoreProperties.txt'], 'Cased'),
        'Changes_When_Lowercased':      gen_listed_bool_prop(parsed['DerivedCoreProperties.txt'], 'Changes_When_Lowercased'),
        'Changes_When_Uppercased':      gen_listed_bool_prop(parsed['DerivedCoreProperties.txt'], 'Changes_When_Uppercased'),
        'Changes_When_Titlecased':      gen_listed_bool_prop(parsed['DerivedCoreProperties.txt'], 'Changes_When_Titlecased'),
        'Changes_When_Casefolded':      gen_listed_bool_prop(parsed['DerivedCoreProperties.txt'], 'Changes_When_Casefolded'),
        'Changes_When_Casemapped':      gen_listed_bool_prop(parsed['DerivedCoreProperties.txt'], 'Changes_When_Casemapped'),
        'Changes_When_NFKC_Casefolded': gen_listed_bool_prop(parsed['DerivedNormalizationProps.txt'], 'Changes_When_NFKC_Casefolded'),
        'NFKC_Casefold':                gen_listed_prop(parsed['DerivedNormalizationProps.txt'], 'NFKC_Casefold'),
        'Script':                       parsed['Scripts.txt'],
        'Script_Extensions':            parsed['ScriptExtensions.txt'], # (Range, [Script])
        'Hangul_Syllable_Type':         parsed['HangulSyllableType.txt'],
        'Jamo_Short_Name':              parsed['Jamo.txt'],
        'Indic_Positional_Category':    parsed['IndicPositionalCategory.txt'],
        'Indic_Syllabic_Category':      parsed['IndicSyllabicCategory.txt'],
        'ID_Start':                     gen_listed_bool_prop(parsed['DerivedCoreProperties.txt'], 'ID_Start'),
        'ID_Continue':                  gen_listed_bool_prop(parsed['DerivedCoreProperties.txt'], 'ID_Continue'),
        'XID_Start':                    gen_listed_bool_prop(parsed['DerivedCoreProperties.txt'], 'XID_Start'),
        'XID_Continue':                 gen_listed_bool_prop(parsed['DerivedCoreProperties.txt'], 'XID_Continue'),
        'Pattern_Syntax':               gen_listed_bool_prop(parsed['PropList.txt'], 'Pattern_Syntax'),
        'Pattern_White_Space':          gen_listed_bool_prop(parsed['PropList.txt'], 'Pattern_White_Space'),
        'Dash':                         gen_listed_bool_prop(parsed['PropList.txt'], 'Dash'),
        'Quotation_Mark':               gen_listed_bool_prop(parsed['PropList.txt'], 'Quotation_Mark'),
        'Terminal_Punctuation':         gen_listed_bool_prop(parsed['PropList.txt'], 'Terminal_Punctuation'),
        'STerm':                        gen_listed_bool_prop(parsed['PropList.txt'], 'STerm'),
        'Diacritic':                    gen_listed_bool_prop(parsed['PropList.txt'], 'Diacritic'),
        'Extender':                     gen_listed_bool_prop(parsed['PropList.txt'], 'Extender'),
        'Soft_Dotted':                  gen_listed_bool_prop(parsed['PropList.txt'], 'Soft_Dotted'),
        'Hex_Digit':                    gen_listed_bool_prop(parsed['PropList.txt'], 'Hex_Digit'),
        'ASCII_Hex_Digit':              gen_listed_bool_prop(parsed['PropList.txt'], 'ASCII_Hex_Digit'),
        'Logical_Order_Exception':      gen_listed_bool_prop(parsed['PropList.txt'], 'Logical_Order_Exception'),
        'White_Space':                  gen_listed_bool_prop(parsed['PropList.txt'], 'White_Space'),
        'Variation_Selector':           gen_listed_bool_prop(parsed['PropList.txt'], 'Variation_Selector'),
        'Alphabetic':                   gen_listed_bool_prop(parsed['DerivedCoreProperties.txt'], 'Alphabetic'),
        'Math':                         gen_listed_bool_prop(parsed['DerivedCoreProperties.txt'], 'Math'),
        'Default_Ignorable_Code_Point': gen_listed_bool_prop(parsed['DerivedCoreProperties.txt'], 'Default_Ignorable_Code_Point'),
        'Grapheme_Base':                gen_listed_bool_prop(parsed['DerivedCoreProperties.txt'], 'Grapheme_Base'),
        'Grapheme_Extend':              gen_listed_bool_prop(parsed['DerivedCoreProperties.txt'], 'Grapheme_Extend'),
        'Grapheme_Cluster_Break':       parsed['auxiliary/GraphemeBreakProperty.txt'],
        'Word_Break':                   parsed['auxiliary/WordBreakProperty.txt'],
        'Sentence_Break':               parsed['auxiliary/SentenceBreakProperty.txt'],
        'Ideographic':                  gen_listed_bool_prop(parsed['PropList.txt'], 'Ideographic'),
        'Unified_Ideograph':            gen_listed_bool_prop(parsed['PropList.txt'], 'Unified_Ideograph'),
        'IDS_Binary_Operator':          gen_listed_bool_prop(parsed['PropList.txt'], 'IDS_Binary_Operator'),
        'IDS_Trinary_Operator':         gen_listed_bool_prop(parsed['PropList.txt'], 'IDS_Trinary_Operator'),
        'Radical':                      gen_listed_bool_prop(parsed['PropList.txt'], 'Radical'),
        'Deprecated':                   gen_listed_bool_prop(parsed['PropList.txt'], 'Deprecated'),
        'Noncharacter_Code_Point':      gen_listed_bool_prop(parsed['PropList.txt'], 'Noncharacter_Code_Point'),
    }

    for p in sorted(prop_defs):
        with report_action('Extracting {0}'.format(p)):
            props[p] = list(prop_defs[p])

    return props

def coalesce_props(props, defaults):
    def sort_prop(prop):
        prop.sort(key = lambda t: t[0].py()[0])
    def coalesce_prop(prop, default):
        # TODO multiple default ranges
        full_range = Value(Types.Range(), '0000..10FFFF')

        last = None
        next_cp = 0
        for p in prop:
            this_range = p[0].py()
            this = p[1]
            if this_range[0] > next_cp and (last is None or default.value != last.value):
                last = default
                yield [Value(Types.Range(), '{0:X}..{1:X}'.format(next_cp, this_range[0]-1)), default]
            if last is None or this.value != last.value: # TODO normalize props to always be Values
                last = this
                yield p
            next_cp = this_range[1]+1

        if next_cp < 0x110000:
            yield [Value(Types.Range(), '{0:X}..{1:X}'.format(next_cp, 0x10FFFF)), default]

    def compute_default(p):
        type = props[p][0][1].type
        default_raw = defaults[p][1].value if p in defaults else None
        return Value(type, type.parse_default(default_raw))

    for p in props:
        sort_prop(props[p])
        props[p] = list(coalesce_prop(props[p], compute_default(p)))

def write_file_header(f, description):
    template = string.Template("""// Ogonek
//
// Written in 2016 by Martinho Fernandes <ogonek@rmf.io>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

// This file was automatically generated.

// Unicode character database - ${description}
""")
    text = template.substitute(description = description)
    f.write(text)

def write_header_file(f, name, abi, file_info):
    template = string.Template("""
#ifndef OGONEK_UCD_${all_caps_name}_HPP
#define OGONEK_UCD_${all_caps_name}_HPP

#include <ogonek/detail/visibility.h++>
#include <ogonek/types.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        inline namespace ${abi} {
            ${type_defs}

            struct ${cpp_name}_properties {
                code_point start;
                ${fields}
            };

            extern OGONEK_PUBLIC ${cpp_name}_properties const* ${cpp_name}_data;
            extern OGONEK_PUBLIC std::size_t ${cpp_name}_data_size;
        } // namespace ${abi}
    } // namespace ucd
} // namespace ogonek

#endif // OGONEK_UCD_${all_caps_name}_HPP
""")
    write_file_header(f, file_info['description'])
    text = template.substitute(all_caps_name = name.upper(),
                               cpp_name = name,
                               abi = abi,
                               **file_info)
    f.write(text)

def write_impl_file(f, name, abi, file_info):
    template = string.Template("""
#include <ogonek/ucd/${cpp_name}.g.h++>
#include <ogonek/detail/size.h++>

#include <cstddef>

namespace ogonek {
    namespace ucd {
        namespace {
            ${cpp_name}_properties const ${cpp_name}_data_raw[] {
                ${entries}
            };
        } // namespace
        inline namespace ${abi} {
            ${cpp_name}_properties const* ${cpp_name}_data = ${cpp_name}_data_raw;
            std::size_t ${cpp_name}_data_size = detail::size(${cpp_name}_data_raw);
        } // namespace ${abi}
    } // namespace ucd
} // namespace ogonek
""")
    write_file_header(f, file_info['description'])
    text = template.substitute(cpp_name = name,
                               abi = abi,
                               **file_info)
    f.write(text)

def cpp_aliases(aliases):
    def value(x):
        if isinstance(x, int):
            return x
        else:
            return cpp_ize(x)
    strings = ['{1} = {0},\n'.format(value(alias[0]), cpp_ize(alias[1])) for alias in aliases if value(alias[0]) != cpp_ize(alias[1])]
    return '\n'.join(strings)

def cpp_enumerators(canonicals, flags):
    def flagless():
        return ['{0},\n'.format(cpp_ize(canon)) for canon in canonicals]
    def flaggy():
        strings = []
        i = 1
        for canon in canonicals:
            if canon not in flags:
                strings.append('{0} = 0x{1:X},\n'.format(cpp_ize(canon), 2 << i))
                i += 1
        return strings

    return '\n'.join(flaggy() if len(flags) else flagless())

def cpp_flags(flags):
    strings = ['{0} = {1},\n'.format(cpp_ize(f), ' | '.join(cpp_ize(bit) for bit in flags[f])) for f in flags]
    return '\n'.join(strings)

def cpp_entries(entries):
    def cpp_entry(entry):
        strings = [v.cpp() for v in entry]
        return '{{ {0} }},'.format(', '.join(strings))

    strings = [cpp_entry(entry) for entry in entries]
    return '\n'.join(strings)

def indent(lines, level = 1):
    lead = '    ' * level
    splits = lines.split('\n')
    def leaded():
        yield splits[0]
        for l in splits[1:]:
            if len(l.strip()) > 0:
                yield lead + l
    return '\n'.join(leaded())

def enum_def(type):
    e = cpp_enumerators(type.canonicals(), type.all_flag_aliases())
    f = cpp_flags(type.all_flag_aliases())
    a = cpp_aliases(type.all_aliases())
    num_flags = len(type.all_flag_aliases())
    num_canons = len(type.canonicals())
    underlying = '' if num_flags == 0 else ' : unsigned long long'
    enumerators = indent(e + f + a)
    type_def = indent("""enum{3} {0}{2} {{
    {1}
}};""".format(type.typename, enumerators, underlying, ' class' if num_canons else ''), 3)
    return type_def

def type_field(type):
    return '{0} value;'.format(type)

def prop_entries(prop):
    return indent(cpp_entries(prop), 4)

def gen_enum(prop, type):
    return {
        'description': '{0} property'.format(prop),
        'type_defs': enum_def(type),
        'fields': type_field(type.typename),
        'entries': prop_entries(props[prop])
    }

def alias_def(type, alias):
    return indent('using {1} = {0};'.format(type, alias), 3)

def gen_builtin(prop, type):
    return {
        'description': '{0} property'.format(prop),
        'type_defs': '',
        'fields': type_field(type),
        'entries': prop_entries(props[prop])
    }

output_defs = {
    'age':                          lambda: gen_enum(   'Age',                          version_type),
    'name':                         lambda: gen_builtin('Name',                         'char const*'),
# TODO name_alias
    'block':                        lambda: gen_enum(   'Block',                        block_type),
    'general_category':             lambda: gen_enum(   'General_Category',             general_category_type),
    'canonical_combining_class':    lambda: gen_enum(   'Canonical_Combining_Class',    combining_class_type),
    'bidi_class':                   lambda: gen_enum(   'Bidi_Class',                   bidi_class_type),
    'bidi_mirrored':                lambda: gen_builtin('Bidi_Mirrored',                'bool'),
    'bidi_mirroring_glyph':         lambda: gen_builtin('Bidi_Mirroring_Glyph',         'code_point'),
    'bidi_control':                 lambda: gen_builtin('Bidi_Control',                 'bool'),
    'bidi_paired_bracket':          lambda: gen_builtin('Bidi_Paired_Bracket',          'code_point'),
    'bidi_paired_bracket_type':     lambda: gen_enum(   'Bidi_Paired_Bracket_Type',     bracket_type_type),
    'decomposition_mapping':        lambda: gen_builtin('Decomposition_Mapping',        'code_point const*'),
    'decomposition_type':           lambda: gen_enum(   'Decomposition_Type',           decomposition_type_type),
    'full_composition_exclusion':   lambda: gen_builtin('Full_Composition_Exclusion',   'bool'),
    'nfc_quick_check':              lambda: gen_builtin('NFC_Quick_Check',              'detail::trinary'),
    'nfd_quick_check':              lambda: gen_builtin('NFD_Quick_Check',              'bool'),
    'nfkc_quick_check':             lambda: gen_builtin('NFKC_Quick_Check',             'detail::trinary'),
    'nfkd_quick_check':             lambda: gen_builtin('NFKD_Quick_Check',             'bool'),
    'numeric_type':                 lambda: gen_enum(   'Numeric_Type',                 numeric_type_type),
    'numeric_value':                lambda: gen_builtin('Numeric_Value',                'detail::fraction'),
    'joining_type':                 lambda: gen_enum(   'Joining_Type',                 joining_type_type),
    'joining_group':                lambda: gen_enum(   'Joining_Group',                joining_group_type),
    'join_control':                 lambda: gen_builtin('Join_Control',                 'bool'),
    'line_break':                   lambda: gen_enum(   'Line_Break',                   line_break_type),
    'east_asian_width':             lambda: gen_enum(   'East_Asian_Width',             east_asian_width_type),
    'uppercase':                    lambda: gen_builtin('Uppercase',                    'bool'),
    'lowercase':                    lambda: gen_builtin('Lowercase',                    'bool'),
    'simple_uppercase_mapping':     lambda: gen_builtin('Simple_Uppercase_Mapping',     'code_point'),
    'simple_lowercase_mapping':     lambda: gen_builtin('Simple_Lowercase_Mapping',     'code_point'),
    'simple_titlecase_mapping':     lambda: gen_builtin('Simple_Titlecase_Mapping',     'code_point'),
    'uppercase_mapping':            lambda: gen_builtin('Uppercase_Mapping',            'code_point const*'),
    'lowercase_mapping':            lambda: gen_builtin('Lowercase_Mapping',            'code_point const*'),
    'titlecase_mapping':            lambda: gen_builtin('Titlecase_Mapping',            'code_point const*'),
    'simple_case_folding':          lambda: gen_builtin('Simple_Case_Folding',          'code_point'),
    'case_folding':                 lambda: gen_builtin('Case_Folding',                 'code_point const*'),
    'turkic_case_folding':          lambda: gen_builtin('$Turkic_Case_Folding',         'code_point const*'), # TODO fold into regular Case_Folding
    'case_ignorable':               lambda: gen_builtin('Case_Ignorable',               'bool'),
    'cased':                        lambda: gen_builtin('Cased',                        'bool'),
    'changes_when_lowercased':      lambda: gen_builtin('Changes_When_Lowercased',      'bool'),
    'changes_when_uppercased':      lambda: gen_builtin('Changes_When_Uppercased',      'bool'),
    'changes_when_titlecased':      lambda: gen_builtin('Changes_When_Titlecased',      'bool'),
    'changes_when_casefolded':      lambda: gen_builtin('Changes_When_Casefolded',      'bool'),
    'changes_when_casemapped':      lambda: gen_builtin('Changes_When_Casemapped',      'bool'),
    'changes_when_nfkc_casefolded': lambda: gen_builtin('Changes_When_NFKC_Casefolded', 'bool'),
    'nfkc_casefold':                lambda: gen_builtin('NFKC_Casefold',                'code_point const*'),
    'script':                       lambda: gen_enum(   'Script',                       script_type),
# TODO script_extensions
    'hangul_syllable_type':         lambda: gen_enum(   'Hangul_Syllable_Type',         hangul_syllable_type_type),
    'jamo_short_name':              lambda: gen_builtin('Jamo_Short_Name',              'char const*'),
    'indic_positional_category':    lambda: gen_enum(   'Indic_Positional_Category',    indic_positional_category_type),
    'indic_syllabic_category':      lambda: gen_enum(   'Indic_Syllabic_Category',      indic_syllabic_category_type),
    'id_start':                     lambda: gen_builtin('ID_Start',                     'bool'),
    'id_continue':                  lambda: gen_builtin('ID_Continue',                  'bool'),
    'xid_start':                    lambda: gen_builtin('XID_Start',                    'bool'),
    'xid_continue':                 lambda: gen_builtin('XID_Continue',                 'bool'),
    'pattern_syntax':               lambda: gen_builtin('Pattern_Syntax',               'bool'),
    'pattern_white_space':          lambda: gen_builtin('Pattern_White_Space',          'bool'),
    'dash':                         lambda: gen_builtin('Dash',                         'bool'),
    'quotation_mark':               lambda: gen_builtin('Quotation_Mark',               'bool'),
    'terminal_punctuation':         lambda: gen_builtin('Terminal_Punctuation',         'bool'),
    'sterm':                        lambda: gen_builtin('STerm',                        'bool'),
    'diacritic':                    lambda: gen_builtin('Diacritic',                    'bool'),
    'extender':                     lambda: gen_builtin('Extender',                     'bool'),
    'soft_dotted':                  lambda: gen_builtin('Soft_Dotted',                  'bool'),
    'hex_digit':                    lambda: gen_builtin('Hex_Digit',                    'bool'),
    'ascii_hex_digit':              lambda: gen_builtin('ASCII_Hex_Digit',              'bool'),
    'logical_order_exception':      lambda: gen_builtin('Logical_Order_Exception',      'bool'),
    'white_space':                  lambda: gen_builtin('White_Space',                  'bool'),
    'variation_selector':           lambda: gen_builtin('Variation_Selector',           'bool'),
    'alphabetic':                   lambda: gen_builtin('Alphabetic',                   'bool'),
    'math':                         lambda: gen_builtin('Math',                         'bool'),
    'default_ignorable_code_point': lambda: gen_builtin('Default_Ignorable_Code_Point', 'bool'),
    'grapheme_base':                lambda: gen_builtin('Grapheme_Base',                'bool'),
    'grapheme_extend':              lambda: gen_builtin('Grapheme_Extend',              'bool'),
    'grapheme_cluster_break':       lambda: gen_enum(   'Grapheme_Cluster_Break',       grapheme_cluster_break_type),
    'word_break':                   lambda: gen_enum(   'Word_Break',                   word_break_type),
    'sentence_break':               lambda: gen_enum(   'Sentence_Break',               sentence_break_type),
    'ideographic':                  lambda: gen_builtin('Ideographic',                  'bool'),
    'unified_ideograph':            lambda: gen_builtin('Unified_Ideograph',            'bool'),
    'ids_binary_operator':          lambda: gen_builtin('IDS_Binary_Operator',          'bool'),
    'ids_trinary_operator':         lambda: gen_builtin('IDS_Trinary_Operator',         'bool'),
    'radical':                      lambda: gen_builtin('Radical',                      'bool'),
    'deprecated':                   lambda: gen_builtin('Deprecated',                   'bool'),
    'noncharacter_code_point':      lambda: gen_builtin('Noncharacter_Code_Point',      'bool'),
}

def generate_all(inc_dir, src_dir, abi, file_defs):
    def mkdir(d):
        try:
            os.makedirs(d)
        except OSError as e:
            if e.errno != errno.EEXIST:
                raise

    inc_dir = os.path.join(inc_dir, 'ogonek/ucd')
    with report_action('Creating header directory'):
        mkdir(inc_dir)
    with report_action('Creating source directory'):
        mkdir(src_dir)

    for f in sorted(file_defs):
        header_name = '{0}.g.h++'.format(f)
        impl_name = '{0}.g.c++'.format(f)
        with report_action('Generating {0}'.format(header_name)):
            with open(os.path.join(inc_dir, header_name), 'w') as file:
                write_header_file(file, f, abi, file_defs[f]())
        with report_action('Generating {0}'.format(impl_name)):
            with open(os.path.join(src_dir, impl_name), 'w') as file:
                write_impl_file(file, f, abi, file_defs[f]())

def write_master_header(f, abi, file_defs):
    template = string.Template("""
#ifndef OGONEK_UCD_ALL_HPP
#define OGONEK_UCD_ALL_HPP

${headers}

#endif // OGONEK_UCD_ALL_HPP
""")
    write_file_header(f, 'all UCD headers')
    headers = '\n'.join('#include <ogonek/ucd/{0}.g.h++>'.format(f) for f in file_defs)
    text = template.substitute(headers=headers)
    f.write(text)

def generate_master(inc_dir, abi, file_defs):
    inc_dir = os.path.join(inc_dir, 'ogonek/ucd')
    with report_action('Generating ucd_all.g.h++'):
        with open(os.path.join(inc_dir, 'ucd_all.g.h++'), 'w') as file:
            write_master_header(file, abi, file_defs)

if not dry_run:
    parsed = parse_all(ucd_dir, input_defs)
    new_defaults = Props(prop_aliases)
    for p in default_values:
        new_defaults[p] = default_values[p]
    default_values = new_defaults
    props = extract_props(prop_aliases, parsed)

    with report_action('Coalescing property ranges'):
        coalesce_props(props, default_values)

    generate_all(inc_dir, src_dir, abi, output_defs)

    generate_master(inc_dir, abi, output_defs)

elif list_files:
    def filenames():
        for f in sorted(output_defs):
            impl_name = '{0}.g.c++'.format(f)
            yield os.path.join(src_dir, impl_name)

    sys.stdout.write(';'.join(filenames()))
