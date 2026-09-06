# FLUXION

Post-Modern Automatic Derivation based on generalized hyperdual numbers

[![Release](https://img.shields.io/github/v/release/codereckons/fluxion?style=plastic&label=release)](https://github.com/codereckons/fluxion/releases/latest)
[![License](https://img.shields.io/badge/license-BSL-green?style=plastic)](./LICENSE.md)
[![Discord](https://img.shields.io/discord/692734675726237696?style=plastic)](https://discord.gg/MEJg3zzt7)
[![Integration](https://github.com/codereckons/fluxion/actions/workflows/integration.yml/badge.svg)](https://github.com/codereckons/fluxion/actions/workflows/integration.yml)
[![Coverage](https://img.shields.io/endpoint?url=https://codereckons.github.io/fluxion/coverage/badge.json&style=plastic&cacheSeconds=1800)](https://codereckons.github.io/fluxion/coverage/)
[![CI](https://github.com/codereckons/fluxion/actions/workflows/ci.yml/badge.svg?event=schedule)](https://github.com/codereckons/fluxion/actions/workflows/ci.yml?query=event%3Aschedule)

## Getting it

```cmake
CPMAddPackage(NAME FLUXION GIT_REPOSITORY https://github.com/codereckons/fluxion GIT_TAG main)
target_link_libraries(mine PRIVATE fluxion::fluxion)
```

Or point CMake at an installed copy:

```cmake
find_package(fluxion REQUIRED)
target_link_libraries(mine PRIVATE fluxion::fluxion)
```

## Building it

```bash
cmake -S . -B build -G Ninja
cmake --build build --target fluxion-test
ctest --test-dir build
```

`FLUXION_BUILD_DOCUMENTATION=ON` adds the `fluxion-doxygen` target, `FLUXION_ENABLE_SANITIZERS=ON`
builds the tests under ASan and UBSan, and `FLUXION_ENABLE_COVERAGE=ON` adds `fluxion-coverage-report`.
