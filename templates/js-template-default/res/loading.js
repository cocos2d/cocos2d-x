/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

(function(){var createStyle=function(){return".cocosLoading{position:absolute;margin:-30px -60px;padding:0;top:50%;left:50%}"+".cocosLoading ul{margin:0;padding:0;}"+".cocosLoading span{color:#FFF;text-align:center;display:block;}"+".cocosLoading li{list-style:none;float:left;border-radius:15px;width:15px;height:15px;background:#FFF;margin:5px 0 0 10px}"+".cocosLoading li .ball,.cocosLoading li .unball{background-color:#2187e7;background-image:-moz-linear-gradient(90deg,#2187e7 25%,#a0eaff);background-image:-webkit-linear-gradient(90deg,#2187e7 25%,#a0eaff);width:15px;height:15px;border-radius:50px}"+".cocosLoading li .ball{transform:scale(0);-moz-transform:scale(0);-webkit-transform:scale(0);animation:showDot 1s linear forwards;-moz-animation:showDot 1s linear forwards;-webkit-animation:showDot 1s linear forwards}"+".cocosLoading li .unball{transform:scale(1);-moz-transform:scale(1);-webkit-transform:scale(1);animation:hideDot 1s linear forwards;-moz-animation:hideDot 1s linear forwards;-webkit-animation:hideDot 1s linear forwards}"+"@keyframes showDot{0%{transform:scale(0,0)}100%{transform:scale(1,1)}}"+"@-moz-keyframes showDot{0%{-moz-transform:scale(0,0)}100%{-moz-transform:scale(1,1)}}"+"@-webkit-keyframes showDot{0%{-webkit-transform:scale(0,0)}100%{-webkit-transform:scale(1,1)}}"+"@keyframes hideDot{0%{transform:scale(1,1)}100%{transform:scale(0,0)}}"+"@-moz-keyframes hideDot{0%{-moz-transform:scale(1,1)}100%{-moz-transform:scale(0,0)}}"+"@-webkit-keyframes hideDot{0%{-webkit-transform:scale(1,1)}100%{-webkit-transform:scale(0,0)}}"};var createDom=function(id,num){id=id||"cocosLoading";num=num||5;var i,item;var div=document.createElement("div");div.className="cocosLoading";div.id=id;var bar=document.createElement("ul");var list=[];for(i=0;i<num;i++){item=document.createElement("li");list.push({ball:document.createElement("div"),halo:null});item.appendChild(list[list.length-1].ball);bar.appendChild(item)}var span=document.createElement("span");span.innerHTML="Loading";div.appendChild(bar);div.appendChild(span);document.body.appendChild(div);return list};var startAnimation=function(list,callback){var index=0;var direction=true;var time=300;var animation=function(){setTimeout(function(){if(callback&&!callback()){return}var item=list[index];if(direction){item.ball.className="ball"}else{item.ball.className="unball"}index++;if(index>=list.length){direction=!direction;index=0;time=1000}else{time=300}animation()},time)};animation()};(function(){var bgColor=document.body.style.background;document.body.style.background="#000";var style=document.createElement("style");style.type="text/css";style.innerHTML=createStyle();document.head.appendChild(style);var list=createDom();startAnimation(list,function(){var div=document.getElementById("cocosLoading");if(!div){document.body.style.background=bgColor}return !!div})})()})();