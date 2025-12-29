##==================================================================================================
## Fluxion - Post-Modern Automatic Derivation
## Copyright : Fluxion Project Contributors
## SPDX-License-Identifier: BSL-1.0
##==================================================================================================
include(GNUInstallDirs)
set(MAIN_DEST     "${CMAKE_INSTALL_LIBDIR}/fluxion-${PROJECT_VERSION}")
set(INSTALL_DEST  "${CMAKE_INSTALL_INCLUDEDIR}/fluxion-${PROJECT_VERSION}")
set(DOC_DEST      "${CMAKE_INSTALL_DOCDIR}-${PROJECT_VERSION}")

## =================================================================================================
## Exporting target for external use
## =================================================================================================
add_library(fluxion_lib INTERFACE)
target_include_directories( fluxion_lib INTERFACE
                            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                            $<INSTALL_INTERFACE:${INSTALL_DEST}>
                          )
target_compile_features(fluxion_lib INTERFACE cxx_std_20)
set_target_properties(fluxion_lib PROPERTIES EXPORT_NAME fluxion)
add_library(fluxion::fluxion ALIAS fluxion_lib)

## =================================================================================================
## Install target with versioned folder
## =================================================================================================
install(TARGETS   fluxion_lib EXPORT fluxion-targets                  DESTINATION "${MAIN_DEST}"    )
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/fluxion               DESTINATION "${INSTALL_DEST}" )
install(FILES     ${PROJECT_SOURCE_DIR}/cmake/fluxion-config.cmake    DESTINATION "${MAIN_DEST}"    )
install(FILES     ${PROJECT_SOURCE_DIR}/LICENSE.md                    DESTINATION "${DOC_DEST}"     )
install(EXPORT    fluxion-targets NAMESPACE "fluxion::" DESTINATION "${MAIN_DEST}")
