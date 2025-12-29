# Setup

## CMake FetchContent

You can also use CMake FetchContent operation and use the `fluxion::fluxion` library
target that our CMake exports.

``` cmake
##==================================================================================================
## Your project setup
##==================================================================================================
cmake_minimum_required(VERSION 3.2)
project(test_fluxion LANGUAGES CXX)

include(FetchContent)

##==================================================================================================
## Fetch Kumi and disable its test targets
##==================================================================================================
set(KUMI_BUILD_TEST    OFF CACHE INTERNAL "OFF")
FetchContent_Declare( fluxion
                      GIT_REPOSITORY https://github.com/codereckons/fluxion.git
                      GIT_TAG main
                    )

FetchContent_MakeAvailable(fluxion)

##==================================================================================================
## Using fluxion
##==================================================================================================
add_executable( my_app my_app.cpp)
target_link_libraries(my_app fluxion::fluxion)
```

## CPM Integration
You can install **KUMI** directly via [CPM](https://github.com/cpm-cmake/CPM.cmake). After
[adding CPM to your CMake setup](https://github.com/cpm-cmake/CPM.cmake#adding-cpm), just
add the following commands:

```cmake
include(CPM)

CPMAddPackage ( NAME fluxion
                URL https://github.com/codereckons/fluxion/archive/refs/tags/v0.1.zip
                VERSION 0.1
                OPTIONS "FLUXION_BUILD_TEST OFF"
              )
```
