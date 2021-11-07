#--------------------------------------------------------------------------
# src 
#--------------------------------------------------------------------------

PROJECT(Hacker)

FILE(GLOB app_headers *.h)
FILE(GLOB app_sources *cc)

SET(src_files ${app_headers} ${app_sources})
SOURCE_GROUP("app" FILES ${src_files})

ADD_EXECUTABLE(app ${src_files})
TARGET_LINK_LIBRARIES(app PUBLIC exts)
