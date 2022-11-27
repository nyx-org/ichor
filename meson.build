project('ichor', 'c')

sources = files('src/exec.c', 'src/syscalls.c')

inc = include_directories('include')
lib = static_library('ichor',sources: sources, include_directories: inc)
dep = declare_dependency(link_with: lib, include_directories: inc)
