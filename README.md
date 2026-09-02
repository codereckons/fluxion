# FLUXION

Post-Modern Automatic Derivation based on generalized hyperdual numbers

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
