##==================================================================================================
## Fluxion - Post-Modern Automatic Derivation
## Copyright : Fluxion Project Contributors
## SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Find Doxygen
##==================================================================================================
find_package(Doxygen)

if (DOXYGEN_FOUND)
  message( STATUS "[Fluxion] Doxygen available")
else (DOXYGEN_FOUND)
  message( STATUS "[Fluxion] Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

##==================================================================================================
## Add Doxygen building target
##==================================================================================================
if (DOXYGEN_FOUND)
  set(DOXYGEN_CONFIG ${PROJECT_SOURCE_DIR}/doc/Doxyfile)
  add_custom_target ( doxygen
                      COMMAND FLUXION_DOXYGEN_OUPUT=../docs ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG}
                      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/doc
                      COMMENT "[Fluxion] Generating API documentation with Doxygen"
                      VERBATIM
                    )

  add_custom_target ( doxygen-local
                      COMMAND FLUXION_DOXYGEN_OUPUT=${PROJECT_BINARY_DIR}/docs ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG}
                      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/doc
                      COMMENT "[Fluxion] Generating API documentation with Doxygen - Local version"
                      VERBATIM
                    )
endif (DOXYGEN_FOUND)
