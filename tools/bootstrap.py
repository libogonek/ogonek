#! /usr/bin/python
#
# Ogonek
#
# Written in 2015 by Martinho Fernandes <martinho.fernandes@gmail.com>
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

v = vallus.Vallus()
v.depend_include('catch')

v.test_runner()
v.documentation()
v.static_library('lib', 'ogonek_data')
v.bootstrap(default = 'lib')

