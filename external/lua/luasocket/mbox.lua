local _M = {}

if module then
    mbox = _M
end 

function _M.split_message(message_s)
    local message = {}
    message_s = string.gsub(message_s, "\r\n", "\n")
    string.gsub(message_s, "^(.-\n)\n", function (h) message.headers = h end)
    string.gsub(message_s, "^.-\n\n(.*)", function (b) message.body = b end)
    if not message.body then
        string.gsub(message_s, "^\n(.*)", function (b) message.body = b end)
    end
    if not message.headers and not message.body then
        message.headers = message_s
    end
    return message.headers or "", message.body or ""
end

function _M.split_headers(headers_s)
    local headers = {}
    headers_s = string.gsub(headers_s, "\r\n", "\n")
    headers_s = string.gsub(headers_s, "\n[ ]+", " ")
    string.gsub("\n" .. headers_s, "\n([^\n]+)", function (h) table.insert(headers, h) end)
    return headers
end

function _M.parse_header(header_s)
    header_s = string.gsub(header_s, "\n[ ]+", " ")
    header_s = string.gsub(header_s, "\n+", "")
    local _, __, name, value = string.find(header_s, "([^%s:]-):%s*(.*)")
    return name, value
end

function _M.parse_headers(headers_s)
    local headers_t = _M.split_headers(headers_s)
    local headers = {}
    for i = 1, #headers_t do
        local name, value = _M.parse_header(headers_t[i])
        if name then
            name = string.lower(name)
            if headers[name] then
                headers[name] = headers[name] .. ", " .. value
            else headers[name] = value end
        end
    end
    return headers
end

function _M.parse_from(from)
    local _, __, name, address = string.find(from, "^%s*(.-)%s*%<(.-)%>")
    if not address then
        _, __, address = string.find(from, "%s*(.+)%s*")
    end
    name = name or ""
    address = address or ""
    if name == "" then name = address end
    name = string.gsub(name, '"', "")
    return name, address
end

function _M.split_mbox(mbox_s)
    mbox = {}
    mbox_s = string.gsub(mbox_s, "\r\n", "\n") .."\n\nFrom \n"
    local nj, i, j = 1, 1, 1
    while 1 do
        i, nj = string.find(mbox_s, "\n\nFrom .-\n", j)
        if not i then break end
        local message = string.sub(mbox_s, j, i-1)
        table.insert(mbox, message)
        j = nj+1
    end
    return mbox
end

function _M.parse(mbox_s)
    local mbox = _M.split_mbox(mbox_s)
    for i = 1, #mbox do
        mbox[i] = _M.parse_message(mbox[i])
    end
    return mbox
end

function _M.parse_message(message_s)
    local message = {}
    message.headers, message.body = _M.split_message(message_s)
    message.headers = _M.parse_headers(message.headers)
    return message
end

return _M
