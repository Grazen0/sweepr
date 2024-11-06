# sweepr

Wacky Minesweeper game for the terminal written in C++, and also a final project for a university course.

Está en español, por cierto.

## Dependencies

- [GCC](https://gcc.gnu.org/) (or some other C++ compiler?)
- [CMake](https://cmake.org/)

If you use [Nix](https://nixos.org/) (which is awesome btw), you can simply run `nix-shell` and the environment should be set up for you.

## Building

The following commands (when executed at the project's root directory) should compile everything.

```bash
mkdir build
cmake -S . -B build
cmake --build build
```

The final executable should then be located at `build/sweepr`.

## Testing

None performed.
