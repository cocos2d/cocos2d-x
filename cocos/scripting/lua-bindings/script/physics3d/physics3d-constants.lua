if nil == cc.Physics3DComponent then
    return
end

cc.Physics3DComponent.PhysicsSyncFlag =
{
    NONE = 0,
    NODE_TO_PHYSICS = 1, 
    PHYSICS_TO_NODE = 2,
    NODE_AND_NODE   = 3,
}

cc.Physics3DObject.PhysicsObjType =
{
    UNKNOWN = 0,
	RIGID_BODY = 1,
}