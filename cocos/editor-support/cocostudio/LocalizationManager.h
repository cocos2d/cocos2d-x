#ifndef __LOCALLIZATION_MANAGER_H__
#define __LOCALLIZATION_MANAGER_H__

#include <string>
#include "json/document.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {
    /**
    *@brief Localization string manager for output data file by cocostudio localization editor.
    *  Note: If changed localization data file manually, please make sure the data file save as
    *    text file format with encoding as 'UTF8 no BOM', otherwise the localization data may 
    *    not been parse successfully.
    */
    class CC_STUDIO_DLL LocalizationManager
    {
    public:
        LocalizationManager();
        ~LocalizationManager();

    public:
        /* Init manager with special localize data file.
        * @param file Name of localize file.
        * @return If manager initialize success return true.
        */
        bool initLanguageData(std::string file);

        /* Get localization string for special key.
        * @param key Special key to search in localization data.
        * @return If manager find the key in localization data, return value 
        *  set to key, otherwise return key itself.
        */
        std::string getLocalizationString(std::string key);

    protected:
        rapidjson::Document * languageData;
    };
}

#endif //__LOCALLIZATION_MANAGER_H__