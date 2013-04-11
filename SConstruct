import os
import sys

# Metadata
project_name = 'ogonek'
macro_prefix = project_name.upper()
lib_name = 'ogonek_data'

# Command line variables
variables = [ EnumVariable('lib', 'kind of library to build', 'static', allowed_values=('static', 'shared'))
            , BoolVariable('icu', 'include ICU interop', False)
            , BoolVariable('boost_exception', 'include Boost.Exception support', True)
            ]

def apply_variables(env):
    if env['icu']:
        env.Append(CPPDEFINES = [ macro_prefix + '_ICU' ])
    if env['boost_exception']:
        env.Append(CPPDEFINES = [ macro_prefix + '_BOOST_EXCEPTION' ])

ignored_warnings = [ 'mismatched-tags' ]

info_files = ['README.md', 'COPYING.txt', 'ogonek.png']

# Standard variables
variables += [ BoolVariable('fatal', 'stop on first error', True)
             , EnumVariable('compiler', 'compiler to use', 'gcc', allowed_values=('gcc', 'clang'))
             , ('test', 'test cases to run', 'all')
             ]

# Build-transparent flags: changing these does not require rebuilds
norebuild = [ '-Wfatal-errors'
            ]

# ---- Mostly behaviour from here ----

# Hack to avoid rebuild on changing -Wfatal-errors
import SCons
import types
SCons.Action.ActionBase.get_contents_orig = SCons.Action.ActionBase.get_contents
def get_contents(self, *args, **kw):
    cnt = self.get_contents_orig(*args, **kw).split()
    cnt_norebuild = " ".join(i for i in cnt if i not in norebuild)
    return cnt_norebuild
SCons.Action.ActionBase.get_contents = types.MethodType(
        get_contents, None, SCons.Action.ActionBase)

# Set up variables
vars = Variables()
for var in variables:
    if isinstance(var, tuple):
        vars.Add(*var)
    else:
        vars.Add(var)

# Create a base environment
if sys.platform == 'win32':
    env = Environment(options = vars, ENV = os.environ, tools = ['mingw'])
else:
    env = Environment(options = vars, ENV = os.environ)

if env['compiler'] == 'clang':
    env['CXX'] = 'clang++'

Help(vars.GenerateHelpText(env))

# Default flags
compile_flags = [ '-Wall' , '-Wextra', '-pedantic-errors', '-Werror' # all warnings as errors
                , '-std=c++11'                                       # C++11 of course!
                , '-isystemdeps'                                     # system header paths
                ]
for warning in ignored_warnings:
    compile_flags += ['-Wno-' + warning]

env.MergeFlags(compile_flags)

# Stop on first error?
if env['fatal']:
    env.MergeFlags(['-Wfatal-errors'])

# Search paths
env.Append(CPPPATH = ['include'])

# Common library dependencies
env.Append(LIBS = [])

# Define platform macros
if env['PLATFORM'] == 'win32':
    env.Append(CPPDEFINES = [macro_prefix + '_WINDOWS'])
else:
    env.Append(CPPDEFINES = [macro_prefix + '_POSIX'])

# Utils
def stringify(list):
    return map(str, list)
def prefix(p, list):
    return map(lambda e: p + e, list)

# List of files to build
sources = stringify(Glob('src/*.c++') + Glob('src/*/*.c++'))
test_sources = stringify(Glob('test/*.c++'))

# Define visibility macros for shared libs
if env['lib'] == 'static':
    lib_defines = [macro_prefix + '_BUILD']
if env['lib'] == 'shared':
    lib_defines = [macro_prefix + '_BUILD', macro_prefix + '_SHARED']
lib_flags = []

apply_variables(env)

# Setup the debug target
debug_builddir = 'obj/debug/'
debug_target = 'bin/debug/' + lib_name
debug_defines = lib_defines + ['_GLIBCXX_DEBUG']
debug_flags = lib_flags + ['-g']
debug_libs = []

debug = env.Clone()
debug.MergeFlags(debug_flags)
debug.Append(CPPDEFINES = debug_defines)
debug.Append(LIBS = debug_libs)
debug.VariantDir(debug_builddir, '.', duplicate=0)
if env['lib'] == 'static':
    debug_lib = debug.StaticLibrary(debug_target, prefix(debug_builddir, sources))
if env['lib'] == 'shared':
    debug_lib = debug.SharedLibrary(debug_target, prefix(debug_builddir, sources))
debug.Alias('debug', debug_lib)

# Setup the release target
release_builddir = 'obj/release/'
release_target = 'bin/release/' + lib_name
release_defines = lib_defines + ['NDEBUG']
release_flags = lib_flags + ['-flto' , '-O3']
release_libs = []

release = env.Clone()
release.MergeFlags(release_flags)
release.Append(CPPDEFINES = release_defines)
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
test_flags = []
test_libs = [ lib_name ]
if env['icu']:
    test_libs += [ 'icuuc', 'icudata' ]
if env['boost_exception']:
    test_libs += [ 'boost_exception' ]

test = debug.Clone()
test.MergeFlags(test_flags)
test.Append(CPPPATH = ['test'])
test.Append(LIBS = test_libs)
test.Append(LIBPATH = 'bin/debug')
test.VariantDir(test_builddir, '.', duplicate=0)
test_program = test.Program(test_target, prefix(test_builddir, test_sources))
if env['test'] == 'all':
    test_arguments = ''
else:
    test_arguments = ' -t "' + env['test'] + '"'
test_alias = test.Alias('runtest', [test_program], test_target + test_arguments)
test.AlwaysBuild(test_alias)

# Setup the distribution target
dist = release.Clone()
# TODO remove directory before putting stuff in
dist.Install(project_name, info_files)
dist.Install(project_name, 'include')
dist.Install(project_name + '/lib', release_lib)
dist.Install(project_name + '/include', Glob('deps/wheels'))
binary_zip = Zip('dist/' + project_name + '-dist-' + env['lib'] + '.zip', project_name)
dist.Alias('dist', binary_zip)

if env['test'] == 'none':
    Default('debug')
else:
    Default('runtest')

# vim:set ft=python:
