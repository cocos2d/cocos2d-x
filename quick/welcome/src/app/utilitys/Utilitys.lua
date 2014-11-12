
local Utilitys = class("Utilitys")

function Utilitys.stringIsNull(str)
	if not str then
		return true
	end

	if 0 == string.len(str) then
		return true
	end

	return false
end


return Utilitys
