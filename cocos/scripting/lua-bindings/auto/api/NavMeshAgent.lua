
--------------------------------
-- @module NavMeshAgent
-- @extend Component
-- @parent_module cc

--------------------------------
--  set maximal speed of agent 
-- @function [parent=#NavMeshAgent] setMaxSpeed 
-- @param self
-- @param #float maxSpeed
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
--------------------------------
--  synchronize parameter to node. 
-- @function [parent=#NavMeshAgent] syncToNode 
-- @param self
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
--------------------------------
-- Traverse OffMeshLink manually
-- @function [parent=#NavMeshAgent] completeOffMeshLink 
-- @param self
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
--------------------------------
--  get separation weight 
-- @function [parent=#NavMeshAgent] getSeparationWeight 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Set automatic Traverse OffMeshLink 
-- @function [parent=#NavMeshAgent] setAutoTraverseOffMeshLink 
-- @param self
-- @param #bool isAuto
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
--------------------------------
--  get current velocity 
-- @function [parent=#NavMeshAgent] getCurrentVelocity 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
--  synchronize parameter to agent. 
-- @function [parent=#NavMeshAgent] syncToAgent 
-- @param self
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
--------------------------------
-- Check agent arrived OffMeshLink 
-- @function [parent=#NavMeshAgent] isOnOffMeshLink 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  set separation weight 
-- @function [parent=#NavMeshAgent] setSeparationWeight 
-- @param self
-- @param #float weight
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
--------------------------------
--  pause movement 
-- @function [parent=#NavMeshAgent] pause 
-- @param self
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
--------------------------------
-- 
-- @function [parent=#NavMeshAgent] getUserData 
-- @param self
-- @return void#void ret (return value: void)
        
--------------------------------
-- Set automatic Orientation 
-- @function [parent=#NavMeshAgent] setAutoOrientation 
-- @param self
-- @param #bool isAuto
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
--------------------------------
--  get agent height 
-- @function [parent=#NavMeshAgent] getHeight 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  get maximal speed of agent 
-- @function [parent=#NavMeshAgent] getMaxSpeed 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Get current OffMeshLink information
-- @function [parent=#NavMeshAgent] getCurrentOffMeshLinkData 
-- @param self
-- @return OffMeshLinkData#OffMeshLinkData ret (return value: cc.OffMeshLinkData)
        
--------------------------------
--  get agent radius 
-- @function [parent=#NavMeshAgent] getRadius 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- synchronization between node and agent is time consuming, you can skip some synchronization using this function
-- @function [parent=#NavMeshAgent] setSyncFlag 
-- @param self
-- @param #int flag
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
--------------------------------
-- 
-- @function [parent=#NavMeshAgent] getSyncFlag 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  resume movement 
-- @function [parent=#NavMeshAgent] resume 
-- @param self
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
--------------------------------
--  stop movement 
-- @function [parent=#NavMeshAgent] stop 
-- @param self
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
--------------------------------
--  set maximal acceleration of agent
-- @function [parent=#NavMeshAgent] setMaxAcceleration 
-- @param self
-- @param #float maxAcceleration
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
--------------------------------
-- Set the reference axes of agent's orientation<br>
-- param rotRefAxes The value of reference axes in local coordinate system.
-- @function [parent=#NavMeshAgent] setOrientationRefAxes 
-- @param self
-- @param #vec3_table rotRefAxes
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
--------------------------------
--  get maximal acceleration of agent
-- @function [parent=#NavMeshAgent] getMaxAcceleration 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  set agent height 
-- @function [parent=#NavMeshAgent] setHeight 
-- @param self
-- @param #float height
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
--------------------------------
-- 
-- @function [parent=#NavMeshAgent] setUserData 
-- @param self
-- @param #void data
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
--------------------------------
--  get obstacle avoidance type 
-- @function [parent=#NavMeshAgent] getObstacleAvoidanceType 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
--  get current velocity 
-- @function [parent=#NavMeshAgent] getVelocity 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
--  set agent radius 
-- @function [parent=#NavMeshAgent] setRadius 
-- @param self
-- @param #float radius
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
--------------------------------
--  set obstacle avoidance type 
-- @function [parent=#NavMeshAgent] setObstacleAvoidanceType 
-- @param self
-- @param #unsigned char type
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
--------------------------------
-- 
-- @function [parent=#NavMeshAgent] getNavMeshAgentComponentName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Create agent<br>
-- param param The parameters of agent.
-- @function [parent=#NavMeshAgent] create 
-- @param self
-- @param #cc.NavMeshAgentParam param
-- @return NavMeshAgent#NavMeshAgent ret (return value: cc.NavMeshAgent)
        
--------------------------------
-- 
-- @function [parent=#NavMeshAgent] onEnter 
-- @param self
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
--------------------------------
-- 
-- @function [parent=#NavMeshAgent] onExit 
-- @param self
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
--------------------------------
-- 
-- @function [parent=#NavMeshAgent] NavMeshAgent 
-- @param self
-- @return NavMeshAgent#NavMeshAgent self (return value: cc.NavMeshAgent)
        
return nil
