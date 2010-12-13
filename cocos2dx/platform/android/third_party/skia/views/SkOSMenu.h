/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SkOSMenu_DEFINED
#define SkOSMenu_DEFINED

#include "SkEvent.h"
#include "SkTDArray.h"

class SkOSMenu {
public:
    explicit SkOSMenu(const char title[]);
    ~SkOSMenu();

    const char* getTitle() const { return fTitle; }

    void    appendItem(const char title[], const char eventType[], int32_t eventData);

    // called by SkOSWindow when it receives an OS menu event
    int         countItems() const;
    const char* getItem(int index, uint32_t* cmdID) const;

    SkEvent* createEvent(uint32_t os_cmd);

private:
    const char* fTitle;

    struct Item {
        const char* fTitle;
        const char* fEventType;
        uint32_t    fEventData;
        uint32_t    fOSCmd; // internal
    };
    SkTDArray<Item> fItems;

    // illegal
    SkOSMenu(const SkOSMenu&);
    SkOSMenu& operator=(const SkOSMenu&);
};

#endif

