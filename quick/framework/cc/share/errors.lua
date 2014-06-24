
local errors = {}

errors.SUCCESS    		= 200  		-- "UMSResponseCodeSuccess" 成功
errors.TOKENINVALID    	= 400  		-- "UMSREsponseCodeTokenInvalid"			-- 授权用户token错误
errors.BANED			= 505  		--"UMSResponseCodeBaned"				-- 用户被封禁
errors.FAILD    		= 510  		--"UMSResponseCodeFaild"				-- 发送失败（由于内容不符合要求或者其他原因）
errors.EMPTYCONTENT 	= 5007 		--"UMSResponseCodeEmptyContent"			-- 发送内容为空
errors.SHAREREPEATED 	= 5016 		--"UMSResponseCodeShareRepeated"		-- 分享内容重复
errors.GETNOUIDFROMOAUTH= 5020 		--"UMSResponseCodeGetNoUidFromOauth"	-- 授权之后没有得到用户uid
errors.ACCESSTOKENEXPIRED=5027 		--"UMSResponseCodeAccessTokenExpired"	-- token过期
errors.NETWORKERROR 	= 5050 		--"UMSResponseCodeNetworkError"			-- 网络错误
errors.GETPROFILEFAILED = 5051 		--"UMSResponseCodeGetProfileFailed"		-- 获取账户失败
errors.CODECANCEL		= 5052 		--"UMSResponseCodeCancel"				-- 用户取消授权
errors.NOAPIAUTHORITY 	= 100031 	--"UMSResponseCodeNoApiAuthority"		-- QQ空间应用没有在QQ互联平台上申请上传图片到相册的权限

return errors
