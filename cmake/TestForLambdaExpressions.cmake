# - Test for compiler support of lambda expressions

INCLUDE(CheckCXXSourceCompiles)

IF (CMAKE_COMPILER_IS_GNUCC)
    SET(CMAKE_REQUIRED_FLAGS "-std=c++0x -std=gnu++0x")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

FILE(READ "${CMAKE_SOURCE_DIR}/cmake/TestForLambdaExpressions.cpp" TESTFORLAMBDAEXPRESSIONS_SRC)

CHECK_CXX_SOURCE_COMPILES("${TESTFORLAMBDAEXPRESSIONS_SRC}" HAS_LAMBDA_EXPRESSIONS)

IF(NOT HAS_LAMBDA_EXPRESSIONS)
    # atm no way to continue without lambda expressions
	MESSAGE (FATAL_ERROR "lambda expressions not available. Change to a decent c++11 compiler!")
ENDIF(NOT HAS_LAMBDA_EXPRESSIONS)
