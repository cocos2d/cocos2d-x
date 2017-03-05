cmake_minimum_required(VERSION 2.8)
set(EXAMPLE_DIR "${CMAKE_CURRENT_LIST_DIR}/example")
if (NOT EXISTS ${EXAMPLE_DIR}/cocos2d)
	message("Downloading cocos2dx, this may take some time!")
	file(DOWNLOAD "http://cdn.cocos2d-x.org/cocos2d-x-3.13.zip" "${EXAMPLE_DIR}/cocos2dx.zip")
	execute_process(
		COMMAND ${CMAKE_COMMAND} -E tar x  ${EXAMPLE_DIR}/cocos2dx.zip
		WORKING_DIRECTORY ${EXAMPLE_DIR}
    )
    execute_process(
    	COMMAND ${CMAKE_COMMAND} -E rename
        "${EXAMPLE_DIR}/cocos2d-x-3.13" "${EXAMPLE_DIR}/cocos2d"
    )
    execute_process(
    	COMMAND ${CMAKE_COMMAND} -E remove_directory "${EXAMPLE_DIR}/cocos2d/cocos/editor-support/spine"
    )
endif()