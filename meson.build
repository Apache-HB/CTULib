project('Cthulhu', 'cpp',
    default_options : [ 
        'cpp_std=c++17',
        'cpp_eh=none'
    ],
    version : '0.2.0',
    license : 'Apache'
)

version = '0.2.0'
license = 'Apache'

inc = include_directories('Cthulhu')
pkg_mod = import('pkgconfig')

defs = []

if meson.get_compiler('cpp').get_id() == 'gcc'
    defs += '-DGCC_WORKAROUND_BULLSHIT' # this is hacky but it fixes GCC's retardation and actually lets the library build
endif

meta_sources = [ 'Cthulhu/Meta/System.cpp' ]
meta = static_library('meta',
    meta_sources,
    include_directories : inc,
    install : true,
    cpp_args : defs
)

meta_dep = declare_dependency(link_with : meta, include_directories : inc)
pkg_mod.generate(meta, version : version, name : 'cthulhumeta', filebase : 'meta', description : 'Code that helps code be code. confusing isnt it')


core_sources = [
    'Cthulhu/Core/Collections/CthulhuString.cpp',
    'Cthulhu/Core/Collections/Range.cpp',
    'Cthulhu/Core/Types/Errno.cpp'
]
core = static_library('core', core_sources, include_directories : inc, link_with : meta, install : true, cpp_args : defs)

core_dep = declare_dependency(link_with : core, include_directories : inc)
pkg_mod.generate(core, version : version, name : 'cthulhucore', filebase : 'core', description : 'Core libraries to replace the C++ standard library')


fs_sources = [
    'Cthulhu/FileSystem/File.cpp',
    'Cthulhu/FileSystem/BufferedFile.cpp'
]
fs = static_library('fs', fs_sources, include_directories : inc, link_with : core, install : true, cpp_args : defs)

fs_dep = declare_dependency(link_with : fs, include_directories : inc)
pkg_mod.generate(libraries : fs, version : version, name : 'cthulhufs', filebase : 'fs', description : 'Multiplatform file managing')
