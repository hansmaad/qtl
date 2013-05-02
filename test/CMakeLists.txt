
MESSAGE(STATUS "Setting up qtl unit testing ...")

# set a list with all unit test source and header files
SET (UNIT_TEST_HEADER
     test_tools.hpp
     )

SET (UNIT_TEST_SRC 
     all_test.cpp
     any_test.cpp
     from_test.cpp
     order_by_test.cpp
     predicate_test.cpp
     select_test.cpp
     selector_test.cpp
     sum_test.cpp
     test.cpp
     where_test.cpp
	 )

# Set include for qtl headers for <qtl/from.hpp> or <from.hpp>
INCLUDE_DIRECTORIES ("${CMAKE_SOURCE_DIR}/include")
# INCLUDE_DIRECTORIES ("${CMAKE_SOURCE_DIR}/include/qtl")

# And the same for the binary dir to access qtl_config.h
INCLUDE_DIRECTORIES ("${CMAKE_BINARY_DIR}/include")
INCLUDE_DIRECTORIES ("${CMAKE_BINARY_DIR}/include/qtl")

# Set usage for Boost
SET(Boost_USE_STATIC_LIBS        ON)
SET(Boost_USE_MULTITHREADED      ON)

# Find boost. Uncomment the following line for debug purposes
# SET(Boost_DEBUG TRUE)
FIND_PACKAGE (Boost REQUIRED COMPONENTS unit_test_framework)

INCLUDE_DIRECTORIES (${Boost_INCLUDE_DIRS})
ADD_DEFINITIONS (${Boost_DEFINITIONS})
LINK_DIRECTORIES ( ${Boost_LIBRARY_DIRS} )

# enable c++11 for GNU derivates
IF (CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ENDIF (CMAKE_COMPILER_IS_GNUCXX)

add_executable (qtl_test ${UNIT_TEST_HEADER} ${UNIT_TEST_SRC} ${QTL_HEADERS})
SET_TARGET_PROPERTIES(qtl_test PROPERTIES LINKER_LANGUAGE CXX)
TARGET_LINK_LIBRARIES(qtl_test ${Boost_LIBRARIES} ${LINKFLAGS})
ADD_DEPENDENCIES(qtl_test qtl)

MESSAGE(STATUS "Done!")


MESSAGE(STATUS "Setting up unit test runner ...")

# run test as custom target post_build command
ADD_CUSTOM_TARGET(qtl_test_runner DEPENDS qtl_test COMMENT "Running unit tests")
ADD_CUSTOM_COMMAND(TARGET qtl_test_runner COMMAND $<TARGET_FILE:qtl_test> VERBATIM)

MESSAGE(STATUS "Done!")
