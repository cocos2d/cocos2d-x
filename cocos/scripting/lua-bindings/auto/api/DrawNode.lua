
--------------------------------
-- @module DrawNode
-- @extend Node
-- @parent_module cc

--------------------------------
--  draw a quadratic bezier curve with color and number of segments 
-- @function [parent=#DrawNode] drawQuadraticBezier 
-- @param self
-- @param #vec2_table from
-- @param #vec2_table control
-- @param #vec2_table to
-- @param #unsigned int segments
-- @param #color4f_table color
        
--------------------------------
-- 
-- @function [parent=#DrawNode] onDraw 
-- @param self
-- @param #mat4_table transform
-- @param #unsigned int flags
        
--------------------------------
--  Clear the geometry in the node's buffer. 
-- @function [parent=#DrawNode] clear 
-- @param self
        
--------------------------------
--  draw a triangle with color 
-- @function [parent=#DrawNode] drawTriangle 
-- @param self
-- @param #vec2_table p1
-- @param #vec2_table p2
-- @param #vec2_table p3
-- @param #color4f_table color
        
--------------------------------
--  draw a dot at a position, with a given radius and color 
-- @function [parent=#DrawNode] drawDot 
-- @param self
-- @param #vec2_table pos
-- @param #float radius
-- @param #color4f_table color
        
--------------------------------
--  draw a cubic bezier curve with color and number of segments 
-- @function [parent=#DrawNode] drawCubicBezier 
-- @param self
-- @param #vec2_table from
-- @param #vec2_table control1
-- @param #vec2_table control2
-- @param #vec2_table to
-- @param #unsigned int segments
-- @param #color4f_table color
        
--------------------------------
--  draw a segment with a radius and color 
-- @function [parent=#DrawNode] drawSegment 
-- @param self
-- @param #vec2_table from
-- @param #vec2_table to
-- @param #float radius
-- @param #color4f_table color
        
--------------------------------
--  creates and initialize a DrawNode node 
-- @function [parent=#DrawNode] create 
-- @param self
-- @return DrawNode#DrawNode ret (return value: cc.DrawNode)
        
--------------------------------
-- 
-- @function [parent=#DrawNode] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
        
return nil
