if nil == sp then
    return
end

sp.EventType =
{
    ANIMATION_START = 0, 
    ANIMATION_INTERRUPT = 1,
    ANIMATION_END = 2, 
    ANIMATION_COMPLETE = 3,
    ANIMATION_DISPOSE = 4,
    ANIMATION_EVENT = 5,
}
