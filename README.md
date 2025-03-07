# sweepr &middot; ![Status badge](https://github.com/Grazen0/sweepr/actions/workflows/build.yml/badge.svg)

Funky Minesweeper game for the terminal written in C++, and also a final project for a university class.

Está en español, por cierto.

![Demo screenshot](https://github.com/Grazen0/sweepr/blob/main/.github/demo.png?raw=true)

## Try it out!

If you use [Nix](https://nixos.org/) (which is awesome btw), just do `nix run github:Grazen0/sweepr`.

## Dependencies

- [GCC](https://gcc.gnu.org/) (or some other C++ compiler?)
- [CMake](https://cmake.org/)

If you use Nix (which is awesome btw, again), you can simply run `nix develop` and the environment should be set up for you.

## Building

The following commands (when executed at the project's root directory) should compile everything.

```sh
cmake . -B build
cmake --build build
```

The final executable should then be located at `build/sweepr`.

If you use Nix (which is awesome btw, for the last time), just run `nix build` and the executable should be located at `result/bin/sweepr`.

Either that, or just run the thing with `nix run`.

## Testing

None performed.
