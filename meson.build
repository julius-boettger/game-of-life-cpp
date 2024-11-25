project(
    'game-of-life', 'cpp',
    version: '0.1',
)

executable(
    meson.project_name(),

    include_directories: 'src/include',
    sources: [
        'src/main.cpp'
    ],

    dependencies: [ dependency('ftxui') ],
    install: true, # necessary for nix build

    # compiler arguments (assuming gcc)
    cpp_args: [
        '-std=c++23',
        # throw errors when using compiler extensions
        '-pedantic-errors',
        # more warnings
        '-Wall', '-Weffc++', '-Wextra', '-Wconversion', '-Wsign-conversion', '-Wshadow',
        # ignore some warnings
        '-Wno-cpp', # "[...] requires compiling with optimization"
    ],
)