# Foxxed
The missing CMake project manager, a tool for creating and maintaining CMake projects.

## Install

Grab the [latest release](https://github.com/FoxMoss/Foxxed/releases/tag/latest).

If your unsure what to pick download `foxxed-musl-linux-amd64` it's probably right.
And copy to `/usr/bin/` directory manually.

## Usage
To make a new CMake project with the barebones run:
```
foxxed init
```
Then follow the prompts!

## Todo:
- [ ] Configuration for project generation
- [ ] FetchContent manager
- [ ] Running projects via one command
- [ ] Building projects via one command
- [ ] Generating all files from CMake from a TOML or YAML config
- [ ] CPack generation
- [ ] On real package managers (apt aur etc)

## Building from source

Install c++ with 23 support, cmake, & ninja, then run:

```bash
mkdir build
cd build
cmake .. -GNinja
ninja
```

Then the binary is made at `src/foxxed`.
