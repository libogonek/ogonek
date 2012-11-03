import os

vars = Variables()
vars.Add(EnumVariable('toolchain', 'Select the toolchain', 'gcc',
                      allowed_values=('clang', 'gcc')))
vars.Add(BoolVariable('fatal', 'Stop on first error', True))

env = Environment(options = vars, ENV = os.environ)
Help(vars.GenerateHelpText(env))
env.MergeFlags([ '-Wall' , '-Wextra', '-pedantic-errors', '-Werror'
               , '-Wno-mismatched-tags'
               , '-std=c++11'
               , '-Iinclude'
               , '-isystemdeps/wheels/include', '-isystemdeps'
               ])

if env['fatal']:
    env.MergeFlags(['-Wfatal-errors'])

env.Append(LIBS = [])

if env['toolchain'] == 'clang':
    env.Append(LIBS = [ 'c++', 'supc++' ])
    env.MergeFlags(['-stdlib=libc++'])

if env['toolchain'] == 'clang':
    env.Replace(CXX = 'clang++')
if env['toolchain'] == 'gcc':
    env.Replace(CXX = 'g++')

lib_flags = [ '-DVISIBILITY_LIBRARY', '-DVISIBILITY_SHARED' ]

debug_flags = lib_flags + [ '-g' ]
if env['toolchain'] == 'clang':
    debug_flags += [ '-D_LIBCPP_DEBUG_LEVEL=1' ]
if env['toolchain'] == 'gcc':
    debug_flags += [ '-D_GLIBCXX_DEBUG' ]

debug_libs = []

release_flags = lib_flags + [ '-flto' , '-O3', '-DNDEBUG' ]
release_libs = []

debug = env.Clone()
debug.MergeFlags(debug_flags)
debug.Append(LIBS = debug_libs)
if env['toolchain'] == 'clang':
    env.MergeFlags(['-fcatch-undefined-behavior'])


release = env.Clone()
release.MergeFlags(release_flags)
release.Append(LIBS = release_libs)
release['LINKFLAGS'] += [ '-flto' ] # Should fix


test_flags = debug_flags + [ '-Itest' ]

test_libs = debug_libs + []

test = env.Clone()
test.MergeFlags(test_flags)
test.Append(LIBS = test_libs)

def stringify(list):
    return map(str, list)

def prefix(p, list):
    return map(lambda e: p + e, list)

sources = stringify(Glob('src/*.c++'))
test_sources = sources + stringify(Glob('test/*.c++'))

debug_builddir = 'obj/debug/'
release_builddir = 'obj/release/'
test_builddir = 'obj/test/'

debug_target = 'bin/debug/libogonek'
release_target = 'bin/release/libogonek'
if env['PLATFORM'] == 'win32':
    test_target = 'bin\\test\\runtest'
else:
    test_target = 'bin/test/runtest'

debug.VariantDir(debug_builddir, '.', duplicate=0)
debug_lib = debug.StaticLibrary(debug_target, prefix(debug_builddir, sources))
debug.Alias('debug', debug_lib)

release.VariantDir(release_builddir, '.', duplicate=0)
release_lib = release.StaticLibrary(release_target, prefix(release_builddir, sources))
release.Alias('release', release_lib)

test.VariantDir(test_builddir, '.', duplicate=0)
test_program = test.Program(test_target, prefix(test_builddir, test_sources))
test_alias = test.Alias('test', [test_program], test_target)
test.AlwaysBuild(test_alias)

ci_alias = test.Alias('ci', [test_program], test_target + ' -s -o test-results.txt')

z = Zip('dist/ogonek.zip', ['README.md', 'COPYING.txt']
                           + Glob('include/ogonek/*.h++') + Glob('include/ogonek/*/*.h++')
                           + Glob('src/*.c++')
                           + Glob('src/ucd/*.g.inl'))
zip_alias = Alias('zip', z)

Default('test')

# vim:set ft=python:

