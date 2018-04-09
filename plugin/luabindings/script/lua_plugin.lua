
plugin = plugin or {}
plugin.FacebookAgent = plugin.FacebookAgent or {}

plugin.FacebookAgent.HttpMethod = 
{
    GET    = 0,
    POST   = 1,
    DELETE = 2,
}

plugin.FacebookAgent.AppEvent = 
{
    ACTIVATED_APP = "fb_mobile_activate_app",
    COMPLETED_REGISTRATION = "fb_mobile_complete_registration",
    VIEWED_CONTENT = "fb_mobile_content_view",
    SEARCHED = "fb_mobile_search",
    RATED = "fb_mobile_rate",
    COMPLETED_TUTORIAL = "fb_mobile_tutorial_completion",
    ADDED_TO_CART = "fb_mobile_add_to_cart",
    ADDED_TO_WISHLIST = "fb_mobile_add_to_wishlist",
    INITIATED_CHECKOUT = "fb_mobile_initiated_checkout",
    ADDED_PAYMENT_INFO = "fb_mobile_add_payment_info",
    PURCHASED = "fb_mobile_purchase",
    ACHIEVED_LEVEL = "fb_mobile_level_achieved",
    UNLOCKED_ACHIEVEMENT = "fb_mobile_achievement_unlocked",
    SPENT_CREDITS = "fb_mobile_spent_credits",
}

plugin.FacebookAgent.AppEventParam =
{
    CURRENCY = "fb_currency",
    REGISTRATION_METHOD = "fb_registration_method",
    CONTENT_TYPE = "fb_content_type",
    CONTENT_ID = "fb_content_id",
    SEARCH_STRING = "fb_search_string",
    SUCCESS = "fb_success",
    MAX_RATING_VALUE = "fb_max_rating_value",
    PAYMENT_INFO_AVAILABLE = "fb_payment_info_available",
    NUM_ITEMS = "fb_num_items",
    LEVEL = "fb_level",
    DESCRIPTION = "fb_description",
}

plugin.FacebookAgent.AppEventParamValue =
{
    VALUE_YES = "1",
    VALUE_NO = "0",
}
