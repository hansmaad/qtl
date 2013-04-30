CMAKE_MINIMUM_REQUIRED(VERSION 2.8.3 FATAL_ERROR)

PROJECT(query-template-library)

# add our cmake folder to module path
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# perform some test to check if the compiler is valid
include(TestForAutoKeyword)
include(TestForLambdaExpressions)
include(TestForResultOfLambda)

ADD_SUBDIRECTORY(include)
ADD_SUBDIRECTORY(test)
