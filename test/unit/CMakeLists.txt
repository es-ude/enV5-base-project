#############################################
## region UNIT-TEST: unit-test_first
add_executable(unit-test_first
        ${CMAKE_CURRENT_LIST_DIR}/UnittestFirst.c
#        ${CMAKE_SOURCE_DIR}/src/yourFileToTest.c
        )
target_include_directories(unit-test_first PUBLIC
#        ${CMAKE_SOURCE_DIR}/src/yourDependency
        ${CMAKE_SOURCE_DIR}/extern/elastic-ai.runtime.enV5/extern
#        ${CMAKE_SOURCE_DIR}/src
        )
target_link_libraries(unit-test_first unity)
add_test(unit-test_first unit-test_first)
## endregion