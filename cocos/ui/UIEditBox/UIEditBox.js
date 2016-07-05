var LibraryUIEditBox = {
    $UIEditBox: {
        isSafariFullscreenMode : function()
        {
            if (document.getElementById('div_fullscreen') != null)
            {
                var nAgt = navigator.userAgent;
                var verOffset = -1;
                if ((verOffset = nAgt.indexOf("OPR")) != -1) browserName = "Opera";
                else if ((verOffset = nAgt.indexOf("MSIE")) != -1) browserName = "MSIE";
                else if ((verOffset = nAgt.indexOf("Netscape")) != -1) browserName = "MSIE";
                else if ((verOffset = nAgt.indexOf("Chrome")) != -1) browserName = "Chrome";
                else if ((verOffset = nAgt.indexOf("Safari")) != -1) browserName = "Safari";
                else if ((verOffset = nAgt.indexOf("Firefox")) != -1) browserName = "Firefox";

                if (browserName == "Safari")
                    return true;
            }
            return false;
        }
    },
    UIEditBox_setOnEnterCalback: function(id, data, callback)
    {
        if(Module.editBox !== undefined && Module.editBox[id] !== undefined)
        {
            Module.userData[id] = data;
            Module.callback[id] = callback;
        }
    },
    UIEditBox_init: function(multiLine)
    {
        if(Module.editBox === undefined)
        {
            Module.editBox = {};
            Module.defaultX = {};
            Module.defaultY = {};
            Module.countId = 0;
            Module.callback = {};
            Module.userData = {};
        }
         
        var id = Module.countId;
        Module.countId = Module.countId + 1;

        Module.target = null;
        Module.target = document.getElementById('div_fullscreen');

        if (Module.target == null)
            Module.target = document.querySelector('.emscripten_border');

        if (multiLine)
            Module.editBox[id] = document.createElement('textarea');
        else 
            Module.editBox[id] = document.createElement('input');

        Module.editBox[id].style.position = 'absolute';
        Module.editBox[id].id = "Module_editBox" + id;
        Module.editBox[id].style.resize = 'none';
        Module.editBox[id].style.backgroundColor = 'transparent';
        Module.editBox[id].style.outline = 'none';
        Module.editBox[id].style.border = 'none';
        Module.editBox[id].style.fontFamily = 'MyriadProRegular';
        Module.target.appendChild(Module.editBox[id]);

        var keyboardListeningElement = Module['keyboardListeningElement'] || document;
        keyboardListeningElement.removeEventListener("keypress", SDL.receiveEvent);
        keyboardListeningElement.removeEventListener("keyup", SDL.receiveEvent);
        keyboardListeningElement.removeEventListener("keydown", SDL.receiveEvent);

        Module.editBox[id].addEventListener("keyup", function(event)
        {
            if (event.keyCode == 13)
            {
                if(Module.callback[id] !== undefined)
                {
                    event.preventDefault();
                    var sp = Runtime.stackSave();
                    Runtime.dynCall('vi', Module.callback[id], [Module.userData[id]]);
                    Runtime.stackRestore(sp);
                }
            }
        });
        window.addEventListener('resize', function(event){

            if(Module.editBox !== undefined)
            {
                for(var id in Module.editBox)
                {
                    if(Module.editBox[id] !== undefined)
                    {
                        Module.editBox[id].style.left = Module['canvas'].offsetLeft + Module.defaultX[id] + 'px';

                        if (document.getElementById('div_fullscreen') == null)
                            Module.editBox[id].style.top = Module['canvas'].offsetTop + Module.defaultY[id] + 'px';
                        else
                            Module.editBox[id].style.top = Module.defaultY[id] + 'px';
                    }
                }
            }
        });

        return id;
    },
    UIEditBox_setPlaceholderColor: function(id, colorR, colorG, colorB)
    {
        dec2hex = function(d)
        {
            if(d > 15) { return d.toString(16) } 
            else { return "0" + d.toString(16) }
        }

        rgb = function(r,g,b) { return "#" + dec2hex(r) + dec2hex(g) + dec2hex(b) };

        if(Module.editBox !== undefined && Module.editBox[id] !== undefined)
        {
            var child = document.querySelector('.editBoxStyle' + id);
            if (child != null)
                document.querySelector('body').removeChild(child);

            var color = rgb(colorR, colorG, colorB);
            var st = document.createElement('style');
            st.innerHTML = '#Module_editBox' + id + '::-webkit-input-placeholder {color:' + color + ';} ::-moz-placeholder {color:' + color + ';} :-moz-placeholder {color:' + color + ';} :-ms-input-placeholder {color:' + color + ' !important;}';
            st.classList = 'editBoxStyle' + id;
            document.querySelector('body').appendChild(st);
        }
    },

    UIEditBox_setContentSize: function(id, x, y, width, height)
    {
        if(Module.editBox !== undefined && Module.editBox[id] !== undefined)
        {
            Module.defaultX[id] = x;
            Module.defaultY[id] = y;

            Module.editBox[id].style.left = Module['canvas'].offsetLeft + x + 'px';

            if (document.getElementById('div_fullscreen') == null)
                Module.editBox[id].style.top = Module['canvas'].offsetTop + y + 'px';
            else
                Module.editBox[id].style.top = y + 'px';
                

            Module.editBox[id].style.width = width + 'px';
            Module.editBox[id].style.height = height + 'px';

            if (UIEditBox.isSafariFullscreenMode())
            {
                Module.editBox[id].readOnly = true;
                Module.editBox[id].value = "For security reason Apple blocked keyboard input in Safari fullsceen mode";
            }
            else
            {
                Module.editBox[id].readOnly = false;
                Module.editBox[id].value = "";
            }
        }
    },
    UIEditBox_setInputType: function(id, type)
    {
        if(Module.editBox !== undefined && Module.editBox[id] !== undefined)
        {
            if (type == 1)
            {
                Module.editBox[id].style.textTransform = 'none';
                Module.editBox[id].type = 'password';
            }
            else if (type == 2)
            {
                Module.editBox[id].style.textTransform = 'capitalize';
                Module.editBox[id].type = 'text';
            }
            else if (type == 3)
            {
                Module.editBox[id].style.textTransform = 'uppercase';
                Module.editBox[id].type = 'text';
            }
        }
    },
    UIEditBox_setPlaceholder: function(id, str)
    {
        if(Module.editBox !== undefined && Module.editBox[id] !== undefined)
        {
            var text = Pointer_stringify(str);
            Module.editBox[id].placeholder = text;
        }
    },
    UIEditBox_setVisible: function(id, visible)
    {
        if(Module.editBox !== undefined && Module.editBox[id] !== undefined)
        {
            if (visible)
                Module.editBox[id].style.visibility = "";
            else
                Module.editBox[id].style.visibility = "hidden";
        }
    },
    UIEditBox_setMaxLength: function(id, length)
    {
        if(Module.editBox !== undefined && Module.editBox[id] !== undefined)
            Module.editBox[id].maxLength = length;
    },
    UIEditBox_close: function(id)
    {
        var keyboardListeningElement = Module['keyboardListeningElement'] || document;
        keyboardListeningElement.addEventListener("keypress", SDL.receiveEvent);
        keyboardListeningElement.addEventListener("keyup", SDL.receiveEvent);
        keyboardListeningElement.addEventListener("keydown", SDL.receiveEvent);

        if (Module.target != null)
        {
            if(Module.editBox !== undefined && Module.editBox[id] !== undefined)
            {
                var child = document.querySelector('.editBoxStyle' + id);
                if (child != null)
                    document.querySelector('body').removeChild(child);

                Module.target.removeChild(Module.editBox[id]);

                if (Module.callback !== undefined && Module.callback[id] !== undefined && Module.callback[id] != null)
                    delete Module.callback[id];

                if (Module.data !== undefined && Module.data[id] !== undefined && Module.data[id] != null)
                    delete Module.data[id];

                delete Module.editBox[id];
            }
        }
    },
    UIEditBox_setColor: function(id, colorR, colorG, colorB)
    {
        dec2hex = function(d)
        {
            if(d > 15) { return d.toString(16) } 
            else { return "0" + d.toString(16) }
        }

        rgb = function(r,g,b) { return "#" + dec2hex(r) + dec2hex(g) + dec2hex(b) };

        if(Module.editBox !== undefined && Module.editBox[id] !== undefined)
            Module.editBox[id].style.color = rgb(colorR, colorG, colorB);
    },
    UIEditBox_setFont: function(id, fontName, fontSize)
    {
        if(Module.editBox !== undefined && Module.editBox[id] !== undefined)
        {
            var font = Pointer_stringify(fontName);
            Module.editBox[id].style.fontFamily = font;
            Module.editBox[id].style.fontSize = fontSize + 'px';
        }
    },
    UIEditBox_setText: function(id, str)
    {
        if(Module.editBox !== undefined && Module.editBox[id] !== undefined)
        {
            var text = Pointer_stringify(str);
            Module.editBox[id].value = text;
        }
    },
    UIEditBox_getText: function(id)
    {
        if(Module.editBox !== undefined && Module.editBox[id] !== undefined)
        {
            if (!UIEditBox.isSafariFullscreenMode())
                return allocate(intArrayFromString(Module.editBox[id].value), 'i8', ALLOC_NORMAL);
        }
        return allocate(intArrayFromString("", 'i8', ALLOC_NORMAL));
    },
    UIEditBox_isFocused: function(id)
    {
        if(Module.editBox !== undefined && Module.editBox[id] !== undefined)
        {
            if (Module.editBox[id] == document.activeElement)
                return true;
        }
        return false;
    }
};

autoAddDeps(LibraryUIEditBox, '$UIEditBox');

mergeInto(LibraryManager.library, LibraryUIEditBox);

