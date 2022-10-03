# !!! WARNING !!! AUTO-GENERATED FILE, PLEASE DO NOT MODIFY IT AND USE
# https://docs.platformio.org/page/projectconf/section_env_build.html#build-flags
#
# If you need to override existing CMake configuration or add extra,
# please create `CMakeListsUser.txt` in the root of project.
# The `CMakeListsUser.txt` will not be overwritten by PlatformIO.

cmake_minimum_required(VERSION 3.13)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

project("christmaslights" C CXX)

include(CMakeListsPrivate.txt)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CMakeListsUser.txt)
include(CMakeListsUser.txt)
endif()

add_custom_target(
    Production ALL
    COMMAND platformio -c clion run "$<$<NOT:$<CONFIG:All>>:-e${CMAKE_BUILD_TYPE}>"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    Debug ALL
    COMMAND platformio -c clion run --target debug "$<$<NOT:$<CONFIG:All>>:-e${CMAKE_BUILD_TYPE}>"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(Z_DUMMY_TARGET ${SRC_LIST} src/general_functions/general.cpp src/general_functions/general.h src/general_functions/Serial.cpp src/general_functions/Serial.h src/effects/breathe/Breathe.cpp src/effects/breathe/Breathe.h src/effects/individual_chase/IndividualChase.cpp src/effects/individual_chase/IndividualChase.h src/effects/wave_chase/WaveChase.cpp src/effects/wave_chase/WaveChase.h src/effects/smooth_individual_chase/SmoothIndividualChase.cpp src/effects/smooth_individual_chase/SmoothIndividualChase.h src/effects/dual_colour_transition/DualColourTransition.cpp src/effects/dual_colour_transition/DualColourTransition.h src/effects/individual_crawl/IndividualCrawl.cpp src/effects/individual_crawl/IndividualCrawl.h src/effects/random_flicker/RandomFlicker.cpp src/effects/random_flicker/RandomFlicker.h src/effects/see_saw/SeeSaw.cpp src/effects/see_saw/SeeSaw.h)
