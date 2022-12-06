project('ichor', 'c')

sources = files('src/exec.c', 'src/syscalls.c')

stdc = subproject('stdc-shim')

deps = [stdc.get_variable('dep')]

inc = include_directories('include')
lib = static_library('ichor',sources: sources, include_directories: inc)
dep = declare_dependency(link_with: lib, include_directories: inc, dependencies: deps)