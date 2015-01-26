if nil == ccs then
    return
end

ccs.MovementEventType = {
    start = 0,
    complete = 1,
    loopComplete = 2,
}

ccs.InnerActionType = {
    LoopAction = 0,
    NoLoopAction = 1,
    SingleFrame = 2,
}
