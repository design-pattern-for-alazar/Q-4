cmake_minimum_required(VERSION 3.8)

project (mdview)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

set(QT_MINIMUM_VERSION 5.5.1)

set(FILESYSTEM_LIBRARY "stdc++fs")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5WebKit  REQUIRED)
find_package(Qt5WebKitWidgets REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories("include/" , ${Qt5Widgets_INCLUDES}, ${Qt5WebKit_INCLUDES}, ${Qt5WebKitWidgets_INCLUDES})
add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(${Qt5WebKit_DEFINITIONS})
add_definitions(${Qt5WebKitWidgets_DEFINITIONS})

find_program(HAS_PDF2HTML pdftohtml)
if(HAS_PDF2HTML)
  add_definitions(-DHAS_PDF2HTML)
endif()

find_program(HAS_GROFF groff)
if(HAS_GROFF)
  add_definitions(-DHAS_GROFF)
endif()

set ( SOURCES
  main.cpp
  mainwindow.cpp
  documentstab.cpp
  webview.cpp
  src/documentfactory.cpp
  src/document.cpp
  src/htmldocument.cpp
  src/manpagedocument.cpp
  src/markdowndocument.cpp
  src/textdocument.cpp
  src/pdfdocument.cpp
  src/filewatcher.cpp
  src/bsdfilewatcher.cpp
  src/linuxfilewatcher.cpp
  src/windowsfilewatcher.cpp
  src/manpageparser.cpp
  src/markdownparser.cpp
  src/pdfparser.cpp
  src/textparser.cpp
  )

set ( MOC_HEADERS
  mainwindow.h
  webview.h
  documentstab.h
  )

set ( UIS
  mainwindow.ui
  webview.ui
  )

set ( RESOURCES
  main.qrc
  )

add_executable(${PROJECT_NAME} ${SOURCES} ${UIS})
target_link_libraries(${PROJECT_NAME} ${FILESYSTEM_LIBRARY} ${Qt5Widgets_LIBRARIES}  ${Qt5WebKit_LIBRARIES} ${Qt5WebKitWidgets_LIBRARIES})
