
local errors = {}

errors.HAVE_UPDATE		= "HAVE_UPDATE"		-- 存在更新
errors.NO_UPDATE		= "NO_UPDATE"		-- 没有更新
errors.NO_WIFI    		= "NO_WIFI"			-- 有更新，但现在是不是wifi环境
errors.TIME_OUT 		= "TIME_OUT"		-- 超时
errors.IS_UPDATE    	= "IS_UPDATE"
errors.USER_UPDATE    	= "USER_UPDATE"		-- 用户选择了更新
errors.USER_IGNORE    	= "USER_IGNORE"		-- 用户选择了忽略
errors.USER_LATER    	= "USER_LATER"		-- 用户选择了现在暂时不更新

errors.DOWNLOAD_START   = "DOWNLOAD_START"	-- 更新下载开始
errors.DOWNLOADING    	= "DOWNLOADING"		-- 更新下载中
errors.DOWNLOAD_END    	= "DOWNLOAD_END"	-- 更新下载结束

errors.DOWNLOAD_FAIL    = "DOWNLOAD_FAIL"	-- 更新下载失败
errors.DOWNLOAD_SUC 	= "DOWNLOAD_SUC"	-- 更新下载成功
errors.DOWNLOAD_NEED_RESTART    = "DOWNLOAD_NEED_RESTART"	-- 增量更新请求全包更新

return errors
