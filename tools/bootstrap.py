#! /usr/bin/python
#
# Ogonek
#
# Written in 2016 by Martinho Fernandes <rmf@rmf.io>
#
# To the extent possible under law, the author(s) have dedicated all copyright and related
# and neighboring rights to this software to the public domain worldwide. This software is
# distributed without any warranty.
#
# You should have received a copy of the CC0 Public Domain Dedication along with this software.
# If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
#
# Build bootstrap script

import vallus
import transforms.ucd

v = vallus.Vallus()
v.depend_include('catch')
v.depend_include('range-v3')

v.documentation()
v.static_library('lib', 'ogonek_data')
v.library('ogonek_data')
v.test_runner()

def gen_ucd(tools, ninja):
    abi = 'abiv0' #TODO ABI name
    ucd_dir = 'data/ucd/'
    inc_dir = 'include/'
    src_dir = 'src/ucd/'
    inc_outputs = ['{1}ogonek/ucd/{0}.g.h++'.format(o, inc_dir) for o in transforms.ucd.output_defs]
    src_outputs = ['{1}{0}.g.c++'.format(o, src_dir) for o in transforms.ucd.output_defs]
    inputs = ['{1}{0}'.format(i, ucd_dir) for i in transforms.ucd.input_defs]
    ucd_script = 'tools/transforms/ucd.py'
    ninja.rule('ucd',
            command = '{0} $abi $ucd_dir $inc_dir $src_dir'.format(ucd_script),
            description = 'UCD $abi $ucd_dir')
    ninja.build(inc_outputs + src_outputs, 'ucd',
            inputs = inputs,
            variables = {'abi': abi, 'ucd_dir': ucd_dir, 'inc_dir': inc_dir, 'src_dir': src_dir},
            implicit = ucd_script)

v.bootstrap(default = 'lib', custom = gen_ucd)

