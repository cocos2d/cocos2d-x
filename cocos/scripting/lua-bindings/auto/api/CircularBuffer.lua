
--------------------------------
-- @module CircularBuffer
-- @parent_module cc

--------------------------------
--  Returns the number of bytes currently stored in the buffer.
-- @function [parent=#CircularBuffer] GetSize 
-- @param self
-- @return unsigned long#unsigned long ret (return value: unsigned long)
        
--------------------------------
--  Read bytes from the buffer<br>
-- param destination pointer to destination where bytes will be written<br>
-- param bytes number of bytes to read<br>
-- return true if there was enough data, false otherwise
-- @function [parent=#CircularBuffer] Read 
-- @param self
-- @param #void destination
-- @param #unsigned long bytes
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#CircularBuffer] clear 
-- @param self
-- @return CircularBuffer#CircularBuffer self (return value: cc.CircularBuffer)
        
--------------------------------
--  Removes len bytes from the front of the buffer<br>
-- param len the number of bytes to "cut"
-- @function [parent=#CircularBuffer] Remove 
-- @param self
-- @param #unsigned long len
-- @return CircularBuffer#CircularBuffer self (return value: cc.CircularBuffer)
        
--------------------------------
--  Write bytes to the buffer<br>
-- param data pointer to the data to be written<br>
-- param bytes number of bytes to be written<br>
-- return true if was successful, otherwise false
-- @function [parent=#CircularBuffer] Write 
-- @param self
-- @param #void data
-- @param #unsigned long bytes
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Allocate the buffer with room for size bytes<br>
-- param size the number of bytes to allocate
-- @function [parent=#CircularBuffer] Allocate 
-- @param self
-- @param #unsigned long size
-- @return CircularBuffer#CircularBuffer self (return value: cc.CircularBuffer)
        
--------------------------------
--  Returns a pointer at the "end" of the buffer, where new data can be written
-- @function [parent=#CircularBuffer] GetBuffer 
-- @param self
-- @return void#void ret (return value: void)
        
--------------------------------
-- 
-- @function [parent=#CircularBuffer] create 
-- @param self
-- @return CircularBuffer#CircularBuffer ret (return value: cc.CircularBuffer)
        
return nil
