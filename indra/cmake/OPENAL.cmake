# -*- cmake -*-
include(Linking)
include(Prebuilt)

if(NOT FMOD)
if (LINUX)
  set(OPENAL ON CACHE BOOL "Enable OpenAL")
else (LINUX)
  set(OPENAL OFF CACHE BOOL "Enable OpenAL")
endif (LINUX)

if (OPENAL)
  if (USESYSTEMLIBS)
    include(FindPkgConfig)
    include(FindOpenAL)
    pkg_check_modules(OPENAL_LIB REQUIRED openal)
    pkg_check_modules(FREEALUT_LIB REQUIRED freealut)
  else (USESYSTEMLIBS)
    use_prebuilt_binary(openal)
  endif (USESYSTEMLIBS)
  set(OPENAL_LIBRARIES 
    openal
    alut
    )
    set(OPENAL_INCLUDE_DIRS ${LIBS_PREBUILT_DIR}/include)
endif (OPENAL)

if (OPENAL)
  message(STATUS "Building with OpenAL audio support")
endif (OPENAL)
endif(NOT FMOD)
