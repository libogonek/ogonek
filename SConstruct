import os

# set up command line variables
vars = Variables()
vars.Add(EnumVariable('lib', 'Select the kind of library to build', 'static', allowed_values=('static', 'shared')))
vars.Add(BoolVariable('fatal', 'Stop on first error', True))

# Create a base environment; no MSVC
env = Environment(options = vars, ENV = os.environ, tools = ['mingw', 'gcc'])
Help(vars.GenerateHelpText(env))

# Default flags
env.MergeFlags([ '-Wall' , '-Wextra', '-pedantic-errors', '-Werror' # all warnings as errors
               , '-Wno-mismatched-tags'                             # ignored warnings
               , '-std=c++11'                                       # C++11 of course!
               , '-Iinclude', '-isystemdeps'                        # header paths
               ])

# Stop on first error?
if env['fatal']:
    env.MergeFlags(['-Wfatal-errors'])

# Common library dependencies
env.Append(LIBS = [])

# Define platform macros
if env['PLATFORM'] == 'win32':
    env.MergeFlags(['-DOGONEK_WINDOWS'])
else:
    env.MergeFlags(['-DOGONEK_POSIX'])

# Utils
def stringify(list):
    return map(str, list)
def prefix(p, list):
    return map(lambda e: p + e, list)

# List of files to build
sources = stringify(Glob('src/*.c++'))
test_sources = sources + stringify(Glob('test/*.c++'))

# Define visibility flags for shared libs
if env['lib'] == 'static':
    lib_flags = ['-DOGONEK_BUILD']
if env['lib'] == 'shared':
    lib_flags = ['-DOGONEK_BUILD', '-DOGONEK_SHARED']

# Setup the debug target
debug_builddir = 'obj/debug/'
debug_target = 'bin/debug/ogonek'
debug_flags = lib_flags + ['-g', '-D_GLIBCXX_DEBUG']
debug_libs = []

debug = env.Clone()
debug.MergeFlags(debug_flags)
debug.Append(LIBS = debug_libs)
debug.VariantDir(debug_builddir, '.', duplicate=0)
if env['lib'] == 'static':
    debug_lib = debug.StaticLibrary(debug_target, prefix(debug_builddir, sources))
if env['lib'] == 'shared':
    debug_lib = debug.SharedLibrary(debug_target, prefix(debug_builddir, sources))
debug.Alias('debug', debug_lib)

# Setup the release target
release_builddir = 'obj/release/'
release_target = 'bin/release/ogonek'
release_flags = lib_flags + ['-flto' , '-O3', '-DNDEBUG']
release_libs = []

release = env.Clone()
release.MergeFlags(release_flags)
release.Append(LIBS = release_libs)
release['LINKFLAGS'] += [ '-flto' ] # link-time optimization needs to be passed to the linker
release.VariantDir(release_builddir, '.', duplicate=0)
if env['lib'] == 'static':
    release_lib = release.StaticLibrary(release_target, prefix(release_builddir, sources))
if env['lib'] == 'shared':
    release_lib = release.SharedLibrary(release_target, prefix(release_builddir, sources))
release.Alias('release', release_lib)

# Setup the test target, based on debug
test_builddir = 'obj/test/'
if env['PLATFORM'] == 'win32':
    test_target = 'bin\\test\\runtest' # FFS
else:
    test_target = 'bin/test/runtest'
test_flags = ['-Itest']
test_libs = []

test = debug.Clone()
test.MergeFlags(test_flags)
test.Append(LIBS = test_libs)
test.VariantDir(test_builddir, '.', duplicate=0)
test_program = test.Program(test_target, prefix(test_builddir, test_sources), LIBS='ogonek', LIBPATH='bin/debug')
test_alias = test.Alias('test', [test_program], test_target)
test.AlwaysBuild(test_alias)

# Setup the distribution targets
info_files = ['README.md', 'COPYING.txt', 'ogonek.png']
build_files = ['SConstruct'] + Glob('scons*.py') + Glob('scons-local-2.2.0/*')
header_files = Glob('include/ogonek/*.h++') + Glob('include/ogonek/*/*.h++')
source_files = Glob('src/*.c++') + Glob('src/ucd/*.g.inl')
source_zip = 'dist/ogonek-src.zip'
Zip(source_zip, info_files)
Zip(source_zip, build_files)
Zip(source_zip, header_files)
Zip(source_zip, source_files)
srcdist_alias = Alias('distsrc', source_zip)

dist = release.Clone()
dist.Install('ogonek', ['README.md', 'COPYING.txt', 'ogonek.png'])
dist.Install('ogonek', 'include')
dist.Install('ogonek/lib', Glob('bin/release/*'))
binary_zip = Zip('dist/ogonek-dist-' + env['lib'] + '.zip', 'ogonek')
dist.Alias('dist', binary_zip)

Default('test')

# vim:set ft=python:
