
cocos_target_sources(${COCOS2D_TARGET} GROUP "storage" FILES
    ${CMAKE_CURRENT_LIST_FILE}
    "storage/local-storage/LocalStorage.cpp"
    )

# Find sqlite on needed platform.
if(COCOS_TARGET_SYSTEM_MACOSX OR
        COCOS_TARGET_SYSTEM_IOS)
    find_library(SQLITE3_LIBRARIES sqlite3)
    if(SQLITE3_LIBRARIES)
        mark_as_advanced(SQLITE3_LIBRARIES)
    else()
        message(FATAL_ERROR "sqlite3 Not Found")
    endif()
    target_link_libraries(${COCOS2D_TARGET} ${SQLITE3_LIBRARIES})
elseif(COCOS_TARGET_SYSTEM_WINDOWS OR COCOS_TARGET_SYSTEM_LINUX)
    cocos_use_package(${COCOS2D_TARGET} SQLITE3 REQUIRED)
elseif(COCOS_TARGET_SYSTEM_ANDROID)
    set(storage_src "storage/local-storage/LocalStorage-android.cpp")
    target_sources(${COCOS2D_TARGET} PRIVATE ${storage_src})
    source_group(storage FILES ${storage_src})
else()
    message(FATAL_ERROR "${CMAKE_CURRENT_LIST_FILE} linked library hasn't been set.")
endif()

