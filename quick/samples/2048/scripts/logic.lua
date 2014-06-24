--[[=============================================================================
#     FileName: logic.lua
#         Desc: the logic for 2048. you can run it on you console by lua
#               full edition in https://github.com/hanxi/quick-cocos2d-x-2048/tree/release
#       Author: hanxi
#        Email: hanxi.info@gmail.com
#     HomePage: http://www.hanxi.info
#      Version: 0.0.1
#   LastChange: 2014-05-09 09:16:26
#      History:
=============================================================================]]

math.randomseed(os.time())
local function printGrid(grid)
    local celllen = 8  -- one cell have character count
    local gridStrLines = {}
    table.insert(gridStrLines,"\n-------------------------------------")
    for i,row in ipairs(grid) do
        local line = {} 
        -- format the number in the center of the cell
        for _,num in ipairs(row) do
            if num==0 then
                local pres = ""
                for tmp=1,celllen do
                    pres = pres .. " "
                end
                local s = string.format("%s",pres)
                table.insert(line,s)
            else
                local s = tostring(num)
                local l = string.len(s)
                local l = (celllen-l)/2
                local prel = math.floor(l)
                local sufl = math.ceil(l)
                local pres = ""
                for tmp=1,prel do
                    pres = pres .. " "
                end
                local sufs = pres
                if sufl>prel then
                    sufs = pres.. " "
                end
                local s = string.format("%s%s%s",pres,s,sufs)
                table.insert(line,s)
            end
        end
        local line = table.concat(line,"|")
        line = "|" .. line .. "|"
        table.insert(gridStrLines,line)
        table.insert(gridStrLines,"-------------------------------------")
    end
    local gridStr = table.concat(gridStrLines,"\n")
    print(gridStr)
end

local function getRandomZeroPos(grid)
    local m = #grid
    local n = #grid[1]
    local zeros = {}
    for i=1,m do
        for j=1,n do
            if grid[i][j]==0 then
                table.insert(zeros,{i=i,j=j})
            end
        end
    end
    if #zeros>0 then
        local r = math.random(1,#zeros)
        return zeros[r].i,zeros[r].j
    end
end

local function randomNum(grid)
    local i,j = getRandomZeroPos(grid)
    if i and j then
        local r = math.random()
        if r<0.9 then
            grid[i][j] = 2
        else
            grid[i][j] = 4
        end
        return i,j
    end
end

local function moveLeft(grid)
    print("==============moveLeft===============")
    local score = 0
    local win = false
    local m = #grid
    local n = #grid[1]
    for i=1,m do
        local line = {}
        for j=1,n do
            if grid[i][j]~=0 then
                table.insert(line,grid[i][j])
            end
        end
        local k=#line
        for j=1,n do
            if j<=k then
                grid[i][j] = line[j]
            else
                grid[i][j] = 0
            end
        end
        for j=1,k-1 do
            if grid[i][j]==grid[i][j+1] then
                grid[i][j+1] = grid[i][j] + grid[i][j+1]
                if grid[i][j+1]==2048 then
                    win = true
                end
                score = score + grid[i][j+1]
                for x=j,n-1 do
                    grid[i][x] = grid[i][x+1]
                end
                grid[i][n] = 0
            end             
        end
    end
    return score,win
end

local function moveRight(grid)
    print("==============moveRight==============")
    local score = 0
    local win = false
	local m = #grid
	local n = #grid[1]
    for i=1,m do
		local line = {}
		for j=n,1,-1 do
			if grid[i][j]~=0 then
				table.insert(line,grid[i][j])
			end
		end
		local k = #line
		for j=n,1,-1 do
			if n-j+1<=k then
				grid[i][j] = line[n-j+1]
			else
				grid[i][j] = 0
			end
		end
		for j=n,n-k+2,-1 do
			if grid[i][j]==grid[i][j-1] then
				grid[i][j-1] = grid[i][j] + grid[i][j-1]
                if grid[i][j-1]==2048 then
                    win = true
                end
                score = score + grid[i][j-1]
				for x=j,2,-1 do
					grid[i][x] = grid[i][x-1]
				end
				grid[i][1] = 0
			end
		end
    end
    return score,win
end


local function moveUp(grid)
    print("===============moveUp================")
    local score = 0
    local win = false
	local m = #grid
	local n = #grid[1]
    for j=1,n do
		local line = {}
		for i=1,m do
			if grid[i][j]~=0 then
				table.insert(line,grid[i][j])
			end
		end
		local k = #line
		for i=1,m do
			if i<=k then
				grid[i][j] = line[i]
			else
				grid[i][j] = 0
			end
		end
		for i=1,k-1 do
			if grid[i][j]==grid[i+1][j] then
				grid[i+1][j] = grid[i][j] + grid[i+1][j]
                if grid[i+1][j]==2048 then
                    win = true
                end
                score = score + grid[i+1][j]
				for x=i,m-1 do
					grid[x][j] = grid[x+1][j]
				end
				grid[m][j] = 0
			end				
		end
    end
    return score,win
end

local function moveDown(grid)
    print("==============moveDown===============")
    local score = 0
    local win = false
	local m = #grid
	local n = #grid[1]
    for j=1,n do
		local line = {}
		for i=m,1,-1 do
			if grid[i][j]~=0 then
				table.insert(line,grid[i][j])
			end
		end
		local k = #line
		for i=m,1,-1 do
			if m-i+1<=k then
				grid[i][j] = line[m-i+1]
			else
				grid[i][j] = 0
			end
		end
		for i=m,m-k+2,-1 do
			if grid[i][j]==grid[i-1][j] then
				grid[i-1][j] = grid[i][j] + grid[i-1][j]
                if grid[i-1][j]==2048 then
                    win = true
                end
                score = score + grid[i-1][j]
				for x=i,2,-1 do
					grid[x][j] = grid[x-1][j]
				end
				grid[1][j] = 0
			end
		end
    end
    return score,win
end

local function copyGrid(grid)
    local m = #grid
    local n = #grid[1]
    local tmpGrid = {}
    for i=1,m do
        if not tmpGrid[i] then
            tmpGrid[i] = {}
        end
        for j=1,n do
            tmpGrid[i][j] = grid[i][j]
        end
    end
    return tmpGrid
end

local function getOpList(beforeGrid,grid)
    local m = #grid
    local n = #grid[1]
    local op_list = {}
    for i=1,m do
        for j=1,n do
            if beforeGrid[i][j]~=grid[i][j] then
                table.insert(op_list,{'setnum',i,j,grid[i][j]})
            end
        end
    end
    return op_list
end

-- serialize lua table. for save lua table in file
function serialize(t)
    local mark={}
    local assign={}
    
    local function ser_table(tbl,parent)
        mark[tbl]=parent
        local tmp={}
        for k,v in pairs(tbl) do
            local key= type(k)=="number" and "["..k.."]" or k
            if type(v)=="table" then
                local dotkey= parent..(type(k)=="number" and key or "."..key)
                if mark[v] then
                    table.insert(assign,dotkey.."="..mark[v])
                else
                    table.insert(tmp, key.."="..ser_table(v,dotkey))
                end
            else
                table.insert(tmp, key.."="..v)
            end
        end
        return "{"..table.concat(tmp,",").."}"
    end
 
    return ser_table(t,"ret")..table.concat(assign," ")
end

function initGrid(m,n)
    local grid = {}
    for i=1,m do
        if not grid[i] then
            grid[i] = {}
        end
        for j=1,n do
            grid[i][j] = 0
        end
    end
    randomNum(grid)
    randomNum(grid)
    return grid
end

function canMove(grid)
	local m = #grid
	local n = #grid[1]
    for i=1,m do
        for j=1,n do
            if grid[i][j]==0 then
                return true
            end
            if (i<m and grid[i][j]==grid[i+1][j] )
                or (j<n and grid[i][j]==grid[i][j+1]) then
                return true
            end
        end
    end
    return false
end

local ops = {
    left  = moveLeft,
    right = moveRight,
    up    = moveUp,
    down  = moveDown,
}
function touch_op(grid,op)
    local beforeGrid = copyGrid(grid)
    local score,win = ops[op](grid)
    randomNum(grid)
    printGrid(grid)
    local op_list = getOpList(beforeGrid,grid)
    return op_list,score,win
end

-------------------------------------------------------------------------------
-- for lua console 2048
-------------------------------------------------------------------------------
local function main()
    local grid = initGrid(4,4)
    randomNum(grid)
    printGrid(grid)
    io.write("next step 'a'[←],'w'[↑],'s'[↓],'d'[→],'q'[exit] >> ")
    local input = io.read()
    while input~="q" do
        if input=="a" or input=="w" or input=="s" or input=="d" then
            if input=="a" then
                moveLeft(grid)
            elseif input=="w" then
                moveUp(grid)
            elseif input=="s" then
                moveDown(grid)
            elseif input=="d" then
                moveRight(grid)
            end
            randomNum(grid)
            printGrid(grid)
        else
            print("error input. please input 'a'[←] or 'w'[↑] or 's'[↓] or 'd'[→] or 'q'[exit]")
        end
        io.write("next step 'a'[←],'w'[↑],'s'[↓],'d'[→],'q'[exit] >> ")
        input = io.read()
    end
end

-- uncomment this. you can in console run command to play console 2048. "$ lua logic.lua"
-- main()

