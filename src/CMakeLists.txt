set(SOURCE_FILES
    main.cpp
)

find_library(CUPS_LIBRARY cups)
find_library(CUPSIMAGE_LIBRARY cupsimage)
find_path(CUPS_INCLUDE_DIR cups/cups.h)

link_libraries(${CUPS_LIBRARY} ${CUPSIMAGE_LIBRARY})
include_directories(${CUPS_INCLUDE_DIR})

#add_subdirectory()

add_executable(rastertovkp80 ${SOURCE_FILES})

install(TARGETS rastertovkp80 DESTINATION /usr/lib/cups/filter)
