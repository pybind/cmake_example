set(ARUGULA_HEADER_FILES arugula.h)

add_library(arugula SHARED arugula.cpp ${ARUGULA_HEADER_FILES})

install(TARGETS arugula LIBRARY DESTINATION lib)
install(FILES ${ARUGULA_HEADER_FILES} DESTINATION include/arugula)
