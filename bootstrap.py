#!/usr/bin/python

import ninja_syntax
import itertools
import os
import fnmatch
import re
import sys
import argparse

# --- util functions

def flags(*iterables):
    return ' '.join(itertools.chain(*iterables))

def include(d):
    return '-I' + d;

def dependency_include(d):
    return '-isystem' + os.path.join('deps', d, 'include');

def get_files(root, pattern):
    pattern = fnmatch.translate(pattern)
    for dir, dirs, files in os.walk(root):
        for f in files:
            if re.match(pattern, f):
                yield os.path.join(dir, f)

def object_file(fn):
    return os.path.join('obj', re.sub(r'\.c\+\+', '.o', fn))

# --- variables

dependencies = ['catch', 'wheels', 'taussig']
include_flags = flags([include('include')], map(dependency_include, dependencies))
cxx_flags = flags(['-Wall', '-Wextra', '-Wfatal-errors', '-Werror', '-std=c++11', '-O3'])
ld_flags = flags(['-flto'])

parser = argparse.ArgumentParser()
parser.add_argument('--cxx', default='g++', metavar='executable', help='compiler name to use (default: g++)')
args = parser.parse_args()

# ---

ninja = ninja_syntax.Writer(open('build.ninja', 'w'))

ninja.variable('ninja_required_version', '1.3')
ninja.variable('builddir', 'obj')

# --- rules

ninja.rule('bootstrap',
        command = ' '.join(sys.argv),
        generator = True,
        description = 'BOOTSTRAP')

ninja.rule('cxx',
        command = args.cxx + ' -MMD -MF $out.d -c ' + cxx_flags + ' ' + include_flags + ' $in -o $out',
        deps = 'gcc',
        depfile = '$out.d',
        description = 'C++ $in')

ninja.rule('link',
        command = args.cxx + ' ' + cxx_flags + ' ' + ld_flags + ' $in -o $out',
        description = 'LINK $in')

ninja.rule('lib',
        command = 'ar rc $out $in && ranlib $out',
        description = 'AR $in')

test_runner = 'bin/test'
ninja.rule('test',
        command = test_runner,
        description = 'TEST')

# --- build edges

ninja.build('build.ninja', 'bootstrap',
        implicit = sys.argv[0])

src_files = list(get_files('src', '*.c++'))
obj_files = [object_file(fn) for fn in src_files]
for fn in src_files:
    ninja.build(object_file(fn), 'cxx',
            inputs = fn)

libogonek_data = 'bin/libogonek_data.a'
ninja.build(libogonek_data, 'lib',
        inputs = obj_files)

test_src_files = list(get_files('test', '*.c++'))
test_obj_files = [object_file(fn) for fn in test_src_files]
for fn in test_src_files:
    ninja.build(object_file(fn), 'cxx',
            inputs = fn)

ninja.build(test_runner, 'link',
        inputs = test_obj_files + [libogonek_data])
ninja.build('runtests', 'test',
        implicit = test_runner)
ninja.build('test', 'phony',
        inputs = 'runtests')
ninja.build('lib', 'phony',
        inputs = libogonek_data);

# --- default targets

ninja.default('lib')

