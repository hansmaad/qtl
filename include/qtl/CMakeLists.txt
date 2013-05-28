
MESSAGE(STATUS "Setting up qtl library...")

# configuration header for compiler or os specific stuff
#SET (QTL_CONFIG_HEADER "${CMAKE_BINARY_DIR}/include/qtl/qtl_config.h")
#CONFIGURE_FILE(
#    "${CMAKE_SOURCE_DIR}/cmake/qtl_config.cmake.h.in"
#    "${QTL_CONFIG_HEADER}"
#    )

# set a list with all header files
SET (HEADER_FILES
     all_query.hpp
     any_query.hpp
     boolean_query.hpp
	 distinct.hpp
     empty_query.hpp
     iterator.hpp
     join.hpp
     order_by.hpp
     predicate.hpp
     qtl.hpp
     range.hpp
     return_type.hpp
     select.hpp
     selector.hpp
     sequence.hpp
     sum.hpp
     type_traits.hpp
     where.hpp)

SET (QTL_HEADERS "" CACHE INTERNAL "" FORCE)

FOREACH (header ${HEADER_FILES})
    LIST(APPEND QTL_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/${header}")
ENDFOREACH (header ${HEADER_FILES})

LIST(APPEND QTL_HEADERS "${QTL_CONFIG_HEADER}")

# dummy target since it does not build any code but
# looks nice in Visual Studio to have it in the solution tree
ADD_CUSTOM_TARGET(qtl ALL SOURCES ${QTL_HEADERS})

MESSAGE(STATUS "Done!")
