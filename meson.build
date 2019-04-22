project('Cthulhu', 'cpp', 
    default_options : [ 'cpp_std=c++17' ], 
    version : '0.2.0', 
    license : 'Apache'
)

version = '0.2.0'
license = 'Apache'

inc = include_directories('Cthulhu')
pkg_mod = import('pkgconfig')



meta_sources = [ 'Cthulhu/Meta/System.cpp' ]
metalib = static_library('meta', meta_sources, include_directories : inc, install : true)
pkg_mod.generate(metalib, version : version, name : 'cthulhumeta', filebase : 'meta', description : 'Code that helps code be code. confusing isnt it')


core_sources = [ 
    'Cthulhu/Core/Collections/CthulhuString.cpp',
    'Cthulhu/Core/Collections/Range.cpp',
    'Cthulhu/Core/Types/Errno.cpp'
]
corelib = static_library('core', core_sources, include_directories : inc, link_with : metalib, install : true)
pkg_mod.generate(corelib, version : version, name : 'cthulhucore', filebase : 'core', description : 'Core libraries to replace the C++ standard library')



fs_sources = [ 
    'Cthulhu/FileSystem/File.cpp',
    'Cthulhu/FileSystem/BufferedFile.cpp'
]
fslib = static_library('fs', fs_sources, include_directories : inc, link_with : corelib, install : true)
pkg_mod.generate(libraries : fslib, version : version, name : 'cthulhufs', filebase : 'fs', description : 'Multiplatform file managing')
