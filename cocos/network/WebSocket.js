var LibraryCocosWebSocket = {
    WebSocket_init: function(thiz, address)
    {
        Module['cocoswebsocket'] = (Module['cocoswebsocket'] && 
                             ('object' === typeof Module['cocoswebsocket'])) ? Module['cocoswebsocket'] : 
        { 
            _socketMap : {}, 
            _callbacks : {},
            
            on : function(event, param, callback)
			{
				if ('function' === typeof callback)
				{
					this._callbacks[param][event] = callback;
				}

				return this;
			},

			emit : function(event, param, data)
			{
				if ('function' === typeof this._callbacks[param][event])
				{
					this._callbacks[param][event].call(this, data);
				}
			}
        };
        
        Module['cocoswebsocket']._callbacks[thiz] = {};

        var serverAddress = Pointer_stringify(address);
        var socket = new WebSocket(serverAddress);
        socket.binaryType = "arraybuffer";
    
        Module['cocoswebsocket']._socketMap[thiz] = socket;

        socket.onopen = function()
        {
            Module['cocoswebsocket'].emit('open', thiz, [null, 0]);
        };

        socket.onmessage = function(event)
        {
            if (typeof event.data === "string")
            {
                var sp = Runtime.stackSave();
                var array = intArrayFromString(event.data);
                var msg = allocate(array, 'i8', ALLOC_STACK);
                
                Module['cocoswebsocket'].emit('message', thiz, [msg, array.length]);
                Runtime.stackRestore(sp);
            }
            else if (event.data instanceof ArrayBuffer)
            {
                var byteArray = new Uint8Array(event.data);
                var buffer = _malloc(byteArray.length);
                HEAPU8.set(byteArray, buffer);

                Module['cocoswebsocket'].emit('message', thiz, [buffer, event.data.byteLength]);
                _free(buffer);
            }
        };

        socket.onclose = function(event)
        {
            var reason;
            // See http://tools.ietf.org/html/rfc6455#section-7.4.1
            if (event.code == 1000)
                reason = "Normal closure, meaning that the purpose for which the connection was established has been fulfilled.";
            else if(event.code == 1001)
                reason = "An endpoint is \"going away\", such as a server going down or a browser having navigated away from a page.";
            else if(event.code == 1002)
                reason = "An endpoint is terminating the connection due to a protocol error";
            else if(event.code == 1003)
                reason = "An endpoint is terminating the connection because it has received a type of data it cannot accept (e.g., an endpoint that understands only text data MAY send this if it receives a binary message).";
            else if(event.code == 1004)
                reason = "Reserved. The specific meaning might be defined in the future.";
            else if(event.code == 1005)
                reason = "No status code was actually present.";
            else if(event.code == 1006)
               reason = "The connection was closed abnormally, e.g., without sending or receiving a Close control frame";
            else if(event.code == 1007)
                reason = "An endpoint is terminating the connection because it has received data within a message that was not consistent with the type of the message (e.g., non-UTF-8 [http://tools.ietf.org/html/rfc3629] data within a text message).";
            else if(event.code == 1008)
                reason = "An endpoint is terminating the connection because it has received a message that \"violates its policy\". This reason is given either if there is no other sutible reason, or if there is a need to hide specific details about the policy.";
            else if(event.code == 1009)
               reason = "An endpoint is terminating the connection because it has received a message that is too big for it to process.";
            else if(event.code == 1010) // Note that this status code is not used by the server, because it can fail the WebSocket handshake instead.
                reason = "An endpoint (client) is terminating the connection because it has expected the server to negotiate one or more extension, but the server didn't return them in the response message of the WebSocket handshake. <br /> Specifically, the extensions that are needed are: " + event.reason;
            else if(event.code == 1011)
                reason = "A server is terminating the connection because it encountered an unexpected condition that prevented it from fulfilling the request.";
            else if(event.code == 1015)
                reason = "The connection was closed due to a failure to perform a TLS handshake (e.g., the server certificate can't be verified).";
            else
                reason = "Unknown reason";

            var sp = Runtime.stackSave();
            var msg = allocate(intArrayFromString(reason), 'i8', ALLOC_STACK);
            Module['cocoswebsocket'].emit('close', thiz, [event.code, msg, reason.length]);
            Runtime.stackRestore(sp);
        };
        
        socket.onerror = function(error)
        {
            socket.close();
            
            Module['cocoswebsocket'].emit('error', thiz, []);

            // var reason = "reason socket error";
            // var msg = allocate(intArrayFromString(reason), 'i8', ALLOC_STACK);
            // Module['cocoswebsocket'].emit('close', [1, msg, reason.length]);
        };
    },
    WebSocket_close: function(thiz)
    {
        if(Module['cocoswebsocket']._socketMap[thiz] != undefined)
        {
			var socket = Module['cocoswebsocket']._socketMap[thiz];
			socket.onopen = function(){ };
			socket.onmessage = function(event) { };
			socket.onclose = function(event){ };
			socket.onerror = function(error) { };
			socket.close();

            Module['cocoswebsocket']._callbacks[thiz] = {};
            Module['cocoswebsocket']._socketMap[thiz] = null;
        }
    },
    WebSocket_send: function(thiz, data)
    {
        if(Module['cocoswebsocket']._socketMap[thiz] != undefined)
        {
			var socket = Module['cocoswebsocket']._socketMap[thiz];
			var sendData = Pointer_stringify(data);
			socket.send(sendData);
		}
    },
    WebSocket_send_data: function(thiz, data, length)
    {
        if(Module['cocoswebsocket']._socketMap[thiz] != undefined)
        {
			var socket = Module['cocoswebsocket']._socketMap[thiz];
			var binary = new Uint8Array(length);
			for (var i = 0; i < length; i++)
			{
				binary[i] = getValue(data + i, 'i8');
			}

			socket.send(binary);
		}
    },
    __set_network_callback: function(event, thiz, callback)
    {
        function _callback(data)
        {
            try
            {
                if (event === 'error')
                {
                    var sp = Runtime.stackSave();
                    Runtime.dynCall('vi', callback, [thiz]);
                    Runtime.stackRestore(sp);
                }
                else if (event == 'close')
                {
                    var sp = Runtime.stackSave();
                    Runtime.dynCall('viiii', callback, [thiz, data[0], data[1], data[2]]);
                    Runtime.stackRestore(sp);
                }
                else
                {
                    var sp = Runtime.stackSave();
                    Runtime.dynCall('viii', callback, [thiz, data[0], data[1]]);
                    Runtime.stackRestore(sp);
                }
            }
            catch (e)
            {
                if (e instanceof ExitStatus)
                {
                    return;
                }
                else
                {
                    if (e && typeof e === 'object' && e.stack) 
                        console.log('exception thrown: ' + [e, e.stack]);
                }
            }
        };

        Module['noExitRuntime'] = true;
        Module['cocoswebsocket']['on'](event, thiz, callback ? _callback : null);
    },
    WebSocket_set_socket_error_callback__deps: ['__set_network_callback'],
    WebSocket_set_socket_error_callback: function(userData, callback)
    {
        ___set_network_callback('error', userData, callback);
    },
    WebSocket_set_socket_open_callback__deps: ['__set_network_callback'],
    WebSocket_set_socket_open_callback: function(userData, callback)
    {
        ___set_network_callback('open', userData, callback);
    },
    WebSocket_set_socket_listen_callback__deps: ['__set_network_callback'],
    WebSocket_set_socket_listen_callback: function(userData, callback)
    {
        ___set_network_callback('listen', userData, callback);
    },
    WebSocket_set_socket_connection_callback__deps: ['__set_network_callback'],
    WebSocket_set_socket_connection_callback: function(userData, callback)
    {
        ___set_network_callback('connection', userData, callback);
    },
    WebSocket_set_socket_message_callback__deps: ['__set_network_callback'],
    WebSocket_set_socket_message_callback: function(userData, callback)
    {
        ___set_network_callback('message', userData, callback);
    },
    WebSocket_set_socket_close_callback__deps: ['__set_network_callback'],
    WebSocket_set_socket_close_callback: function(userData, callback)
    {
        ___set_network_callback('close', userData, callback);
    }
};

mergeInto(LibraryManager.library, LibraryCocosWebSocket);

