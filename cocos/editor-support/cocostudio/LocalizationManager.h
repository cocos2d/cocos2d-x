#ifndef __LOCALLIZATION_MANAGER_H__
#define __LOCALLIZATION_MANAGER_H__

#include <string>
#include <unordered_map>
#include "json/document.h"
#include "cocostudio/CocosStudioExport.h"

namespace cocostudio {
    /**
    *@brief Localization string manager interface template.
    */
    class ILocalizationManager
    {
    public:
        virtual bool initLanguageData(std::string file) = 0;
        virtual std::string getLocalizationString(std::string key) = 0;
    };

    /**
    *@brief Localization string manager for output Json data file by cocostudio localization editor.
    *  Note: If changed localization data file manually, please make sure the data file save as
    *    text file format with encoding as 'UTF8 no BOM', otherwise the localization data may
    *    not been parse successfully.
    */
    class CC_STUDIO_DLL JsonLocalizationManager : ILocalizationManager
    {
    public:
        static ILocalizationManager* getInstance();

        JsonLocalizationManager();
        ~JsonLocalizationManager();

    public:
        /* Init manager with special localize json data file.
        * @param file Name of localize file.
        * @return If manager initialize success return true.
        */
        virtual bool initLanguageData(std::string file);

        /* Get localization string for special key.
        * @param key Special key to search in localization data.
        * @return If manager find the key in localization data, return value
        *  set to key, otherwise return key itself.
        */
        virtual std::string getLocalizationString(std::string key);

    protected:
        rapidjson::Document * languageData;
    };

    class CC_STUDIO_DLL BinLocalizationManager : ILocalizationManager
    {
    public:
        static ILocalizationManager* getInstance();

        BinLocalizationManager();
        ~BinLocalizationManager();

        /* Init manager with special localize binary data file.
        * @param file Name of localize file.
        * @return If manager initialize success return true.
        */
        virtual bool initLanguageData(std::string file);

        /* Get localization string for special key.
        * @param key Special key to search in localization data.
        * @return If manager find the key in localization data, return value
        *  set to key, otherwise return key itself.
        */
        virtual std::string getLocalizationString(std::string key);

    protected:
        std::unordered_map<std::string, std::string> languageData;
    };

    class CC_STUDIO_DLL LocalizationHelper
    {
    public:
        /* Get current localization manager.
        * @return If the manager has been set, return current localization manager, 
        * otherwise return the singleton instance of BinLocalizationManager.
        */
        static ILocalizationManager* getCurrentManager();

        /* Set current localization manager.
        * @param manager Instance of current localization manager.
        */
        static void setCurrentManager(ILocalizationManager* manager);
    };
}

#endif //__LOCALLIZATION_MANAGER_H__