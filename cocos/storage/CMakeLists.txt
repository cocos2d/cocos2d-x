set(COCOS_STORAGE_HEADER
    storage/local-storage/LocalStorage.h
    )

if(ANDROID)
    set(COCOS_STORAGE_SRC
        storage/local-storage/LocalStorage-android.cpp
        )
else()
    set(COCOS_STORAGE_SRC
        storage/local-storage/LocalStorage.cpp
        )
endif()
