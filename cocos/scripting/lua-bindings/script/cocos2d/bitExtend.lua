-- bit operation

bit = bit or {}
bit.data32 = {}

for i=1,32 do
    bit.data32[i]=2^(32-i)
end

function bit._b2d(arg)
    local nr=0
    for i=1,32 do
        if arg[i] ==1 then
            nr=nr+bit.data32[i]
        end
    end
    return  nr
end

function bit._d2b(arg)
    arg = arg >= 0 and arg or (0xFFFFFFFF + arg + 1)
    local tr={}
    for i=1,32 do
        if arg >= bit.data32[i] then
            tr[i]=1
            arg=arg-bit.data32[i]
        else
            tr[i]=0
        end
    end
    return   tr
end

function    bit._and(a,b)
    local op1=bit._d2b(a)
    local op2=bit._d2b(b)
    local r={}

    for i=1,32 do
        if op1[i]==1 and op2[i]==1  then
            r[i]=1
        else
            r[i]=0
        end
    end
    return  bit._b2d(r)

end

function    bit._rshift(a,n)
    local op1=bit._d2b(a)
    n = n <= 32 and n or 32
    n = n >= 0 and n or 0

    for i=32, n+1, -1 do
        op1[i] = op1[i-n]
    end
    for i=1, n do
        op1[i] = 0
    end

    return  bit._b2d(op1)
end

function bit._not(a)
    local op1=bit._d2b(a)
    local r={}

    for i=1,32 do
        if  op1[i]==1   then
            r[i]=0
        else
            r[i]=1
        end
    end
    return bit._b2d(r)
end

function bit._or(a,b)
    local op1=bit._d2b(a)
    local op2=bit._d2b(b)
    local r={}

    for i=1,32 do
        if op1[i]==1 or op2[i]==1  then
            r[i]=1
        else
            r[i]=0
        end
    end
    return bit._b2d(r)
end

bit.band   = bit.band or bit._and
bit.rshift = bit.rshift or bit._rshift
bit.bnot   = bit.bnot or bit._not
