# - Test for compiler support of auto keyword

INCLUDE(CheckCXXSourceCompiles)

IF (CMAKE_COMPILER_IS_GNUCC)
    SET(CMAKE_REQUIRED_FLAGS "-std=c++0x -std=gnu++0x")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

FILE(READ "${CMAKE_SOURCE_DIR}/cmake/TestForAutoKeyword.cpp" TESTFORAUTOKEYWORD_SRC)

CHECK_CXX_SOURCE_COMPILES("${TESTFORAUTOKEYWORD_SRC}" HAS_AUTO_KEYWORD)

IF(NOT HAS_AUTO_KEYWORD)
    # atm no way to continue without auto keyword
	MESSAGE (FATAL_ERROR "auto keyword not available. Change to a decent c++11 compiler!")
ENDIF(NOT HAS_AUTO_KEYWORD)
