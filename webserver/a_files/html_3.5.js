(function(conf) {function eyeReturnAd(t){var e=-2,i=4;this.p=t,this.n=0,this.od=W[E].gD(document.location.href),this.g=(100*(new Date).getTime()+parseInt(100*Math.random())+"").substring(i),this.p.r.replace("[timestamp]",this.g),this.re=document.referrer,this.mw="I"===W[E].ptype?parent:self,this.md=this.mw.document,this.adi=!1,this.rimp=!1,this.tsUrl="https://voken.eyereturn.com/ts/",this.pageVisible="visible"===this.md.visibilityState,this.sa=W[E].dlgt(this,function(t,e){var i="https://d.ermisvc.com/au2/"+t+"?&id="+this.p.iid;for(var n in e)e.hasOwnProperty(n)&&(i+="&"+n+"="+e[n]);(new Image).src=i}),this.isFNI=function(){return"I"===W[E].ptype&&parent!==top},this.sendRImp=W[E].dlgt(this,function(){var t=!1;return this.p.rimpUrl&&!this.rimp&&((new Image).src=this.p.rimpUrl,t=this.rimp=!0),t}),this.iovTimer=W[E].dlgt(this,function(){this.inv&&this.pageVisible&&!this.ist?this.ist=(new Date).getTime():this.ist&&(this.inv&&this.pageVisible||(this.tiv+=(new Date).getTime()-this.ist,this.ist=0))}),this.sa("baseline",{t:this.p.tid,f:this.isFNI()?"C":W[E].ptype.charAt(0),vv:0,g:er_guid,dd:encodeURIComponent(this.mw.location.href),dr:encodeURIComponent(this.md.referrer),res:0,oid:this.p.oid});var n=0,r=0,s=W[E].dlgt(this,function(t){var e=t||window.event;0===n&&(n=e.clientX,r=e.clientY),n===e.clientX&&r===e.clientY||(this.sa("mousemove"),this.mw.removeEventListener("mousemove",s,!1))});if(this.mw.addEventListener("mousemove",s,!1),!this.inv)var a=100,o=setInterval(W[E].dlgt(this,function(){this.inv&&this.pageVisible&&(this.sa("view",{m:"I"}),clearInterval(o))}),a);this.render=function(){if(this.cb("prerender",e),this.p.b){var t=this.p.b;t.n=-1,t.id="er_ban16_"+this.g+this.p.sid,t.ct=this.ct(0),t.ds="width:"+t.w+"px;height:"+t.h+"px;z-index:"+t.z+";margin:0;padding:0;","function"==typeof dsm&&dsm(this).init();var i=/^http:\/\/resources/,n="https://resources";if(t.s=t.s.replace(i,n),t.bi=t.bi.replace(i,n),!t.ddr){if(this.cb("preload",-1),document.currentScript){var r=document.createElement("div");r.id=t.id,r.style=t.ds,document.currentScript.parentElement.appendChild(r)}else document.write('<div id="'+t.id+'" style="'+t.ds+'"></div>');t.d=document.getElementById(t.id);var s=4,a=5;t.s.toLowerCase().lastIndexOf(".gif")===t.s.length-s||t.s.toLowerCase().lastIndexOf(".jpg")===t.s.length-s?t.d.innerHTML=this.cI(t):t.s.toLowerCase().lastIndexOf(".html")===t.s.length-a||t.s.toLowerCase().lastIndexOf(".htm")===t.s.length-s||(t.s=t.bi,t.d.innerHTML=this.cI(t)),t.loaded=!0,this.aE(t.d,"mouseover","mo",-1),this.aE(t.d,"mouseout","mu",-1),this.aE(t.d,"mousedown","mousedown",-1),this.cb("load",-1)}if("function"==typeof IntersectionObserver&&this.p.b.d){var o={root:null,rootMargin:"0px",threshold:.5},h=this,d=function(t){h.inv=t[0].intersectionRatio>=o.threshold,h.iovTimer()},c=new IntersectionObserver(d,o);h.tiv=0,h.inv=!1,h.ist,c.observe(document.getElementById(this.p.b.id)),h.sa("viewability",{t:h.p.tid,m:"I"})}}!function(t){function e(t){for(var e=t,n=i(e);e.parentElement;)e=e.parentElement,n=i(e,n);try{if(window.frameElement)for(e=window.frameElement,n=i(e,n);e.parentElement;)e=e.parentElement,n=i(e,n)}catch(r){}return n}function i(t,e){try{var i=t.getBoundingClientRect();return t.style.overflow&&"visible"!==t.style.overflow||!e?e&&2===e.length?[Math.min(i.width,t.clientWidth,e[0]),Math.min(i.height,t.clientHeight,e[1])]:[Math.min(i.width,t.clientWidth),Math.min(i.height,t.clientHeight)]:e}catch(n){return[-1,-1]}}if(t.p.b&&t.p.b.d){var n=e(t.p.b.d);n.length&&2===n.length?t.sa("ahdim",{tid:t.p.tid,w:n[0],h:n[1]}):t.sa("ahdim",{tid:t.p.tid,w:null,h:null})}}(this),this.aE(this.md,"visibilitychange","_visibilitychange",e),""!==this.p.pix&&((new Image).src=this.p.pix.replace("[timestamp]",this.g)),this.cb("postrender",e),"undefined"==typeof htmlm&&this.sendRImp(),this.adi||W[E].ready(this.n)},this.l=function(){this.loaded||(this.loaded=!0,this.rmm&&this.rmm.l())},this.lC=function(t,e){var i=e.getBoundingClientRect(),n=t.clientX,r=t.clientY,s=Math.floor(n-i.left),a=Math.floor(r-i.top);this.sa("click",{x:s,y:a,t:this.p.tid})},this.aE=function(t,e,i,n){t.addEventListener(e,this.rCB(i,n),!1)},this.rCB=function(t,e){return this.er.dlgt(this,function(i){var n=i.srcElement||i.target,r={ev:i,target:n};this.cb(t,e,void 0,r)})},this.ul=function(){for(var t=0;t<this.p.rma.length;t++)this.p.rma[t].d.parentNode.removeChild(this.p.rma[t].d)},this.ct=function(t){var e=this.p.er_clkpre;return e?e+("function"==typeof fpm?"&fp="+er_params.er_brandID+"-"+this.er_FP:"")+"&cn="+t:"http://clicks.eyereturn.com/?tokenID="+this.p.tid+(this.p.pct?"&click="+escape(this.p.pct):"")+("undefined"==typeof this.p.iid?"":"&iid="+escape(this.p.iid))+("undefined"==typeof this.p.oid?"":"&oid="+escape(this.p.oid))+("function"==typeof fpm?"&fp="+er_params.er_brandID+"-"+this.er_FP:"")+"&cn="+t},this.hd=function(t){"object"==typeof this.rmm&&this.rmm.hd(t)},this.v=function(t,e){"object"==typeof this.rmm&&this.rmm.v(t,e)},this.cI=function(t){var e='<img src="'+t.s+'" border="0" width="'+t.w+'" height="'+t.h+'">';return 0===t.ct.length?e:this.cA(t.ct,e)},this.cA=function(t,e){return'<a href="'+t+'" target="_blank">'+e+"</a>"},this.cDW=function(t,e){return"<div "+(e?'style="'+e+'"':"")+">"+t+"</div>"},this.rp=function(){for(var t=this.p.b?-1:0;t<this.p.rma.length;t++){var e=t===-1?this.p.b:this.p.rma[t];if(e&&e.loaded){var i={t:0,l:0},n={t:0,l:0},r={t:0,l:0};if(!e.abs&&this.p.b){var s=document.getElementById(this.p.b.id);if(i=W[E].ap(s,e.pobj),this.er.iref){n=W[E].ap(this.er.iref,e.pobj);try{var a=this.er.iref.ownerDocument;0===a.body.offsetLeft&&a.body.offsetWidth!==a.body.parentNode.offsetWidth&&(r.l=Math.round((a.body.parentNode.offsetWidth-a.body.offsetWidth)/2))}catch(o){}}}else if(e.fc)try{i.l=Math.floor(parent.document.body.clientWidth/2)}catch(o){}var h=(e.y?e.y:0)+i.t+n.t,d=(e.x?e.x:0)+i.l+n.l;if("ie"!==this.er.info.bwr){var c=document.body.parentElement.getBoundingClientRect();h+=c.top,d+=c.left,"S"===this.er.ptype&&(h+=this.mw.scrollY,d+=this.mw.scrollX)}t>-1&&!e.dp&&(e.d.style.top=h+r.t+"px",e.d.style.left=d+"px",e.d.style.display="block"),e.rx=d,e.ry=h}}},this.cb=function(t,e,i,n){e===-2?this:e==-1?this.p.b:this.p.rma[e];switch(t){case"mo":this.st();break;case"mu":this.et();break;case"mousedown":this.lC(n.ev,n.target);break;case"_visibilitychange":this.pageVisible="visible"===this.md.visibilityState,"function"==typeof this.iovTimer&&this.iovTimer()}e===-1&&this.p.b?this.p.cb.apply(this.p.b,[this,t,e]):e>=0&&this.p.rma[e]?this.p.cb.apply(this.p.rma[e],[this,t,e]):this.p.cb(this,t,e)},this.st=function(){this.bt=new Date},this.et=function(){if(this.bt){var t=(new Date).getTime()-this.bt.getTime();t<this.p.ttu&&t>this.p.ttl&&((new Image).src=this.tsUrl+"?t="+this.p.tid+"&q="+t+"&g="+this.g+("undefined"==typeof this.p.iid?"":"&iid="+escape(this.p.iid))+("undefined"==typeof this.p.oid?"":"&oid="+escape(this.p.oid))+"&r="+Math.random()*(new Date).getTime()),this.bt=null}},"function"==typeof fpm&&fpm(this).init()}var W=window,E="eyeReturn_"+conf.mods;if(!W[E]){W[E]={ads:[],create:function(t){var e=new eyeReturnAd(t);return e.er=this,e.n=this.ads.length,this.ads[e.n]=e,e.render(),e},ptype:"S",sec:0===document.location.href.indexOf("https"),rp:function(){for(var t=0;t<W[E].ads.length;t++)W[E].ads[t].rp&&W[E].ads[t].rp()},ready:function(t){function e(){for(var t=0;t<W[E].ads.length;t++)i(t)}function i(t){W[E].ads[t].adi||(n(W[E].ads[t]),W[E].ads[t].l(),s(W[E].ads[t]),r(W[E].ads[t]),a(W[E].ads[t]),W[E].ads[t].adi=!0)}function n(t){var e=100;t.p.rma.length>0&&"function"==typeof rmm&&(setInterval(W[E].rp,e),rmm(t))}function r(t){"function"==typeof htmlm&&htmlm(t).init()}function s(t){"function"==typeof fctm&&fctm(t).init()}function a(t){"function"==typeof acm&&acm(t).init()}var o=t;"number"!=typeof o&&(o=void 0),"undefined"==typeof o?e():i(o)},gD:function(t){var e=new RegExp("^http(s|)://([^/:]+)(/|:).*$","i");return e.test(t),RegExp.$2},ap:function(t,e){var i=t;if(!i)return{t:0,l:0};for(var n=0,r=0;i&&i!==e;){n+=i.offsetTop,r+=i.offsetLeft;try{i=i.offsetParent}catch(s){i=null}}return{t:n,l:r}},f:function(t,e){var i,n=e;if(n||(n="NF"===W[E].ptype?self:top),n.W[E]){var r=n.W[E];for(i=0;i<r.ads.length;i++)if("#"===t.charAt(0)&&r.ads[i].p.sid===t.substring(1)||r.ads[i].name===t)return r.ads[i]}for(i=0;i<n.frames.length;i++){var s=W[E].f(t,n.frames[i]);if(s)return s}return null},mev:function(t){var e=0,i=0;"NF"!==W[E].ptype&&(e=parent.scrollX,i=parent.scrollY);for(var n=0;"undefined"!=typeof W[E]&&n<W[E].ads.length;n++)for(var r=W[E].ads[n],s=0;s<r.p.rma.length;s++){var a=r.p.rma[s];if(a.vs){var o=a.rx-e,h=a.ry-i;t.clientX<o+a.w&&t.clientX>o&&t.clientY<h+a.h&&t.clientY>h?a._mov||(a._mov=!0,r.cb("mo",s)):a._mov&&(a._mov=!1,r.cb("mu",s))}}},info:{bwrver:null,bwr:null,os:null},unload:function(){parent.document.removeEventListener("mousemove",W[E].mev,!1);for(var t=0;t<W[E].ads.length;t++)W[E].ads[t].ul()},dlgt:function(t,e){return function(){return e.apply(t,arguments)}},ver:conf.ver||-1},function(){try{for(var t=parent;;){if(t.document.location,t===top)break;t=t.parent}if("frameset"===parent.document.body.tagName.toLowerCase())W[E].ptype="FS";else for(var e=parent.document.getElementsByTagName("iframe"),i=0;i<e.length;i++)if(e[i].contentWindow===window){W[E].ptype="I",W[E].iref=e[i],window.addEventListener("unload",W[E].unload,!0);break}parent.document.addEventListener("mousemove",W[E].mev,!1)}catch(n){W[E].ptype="NF",document.addEventListener("mousemove",W[E].mev,!1)}}(),document.addEventListener("DOMContentLoaded",W[E].ready,!1);var ua=navigator.userAgent.toLowerCase(),os,bwr,bwrver;/win/.test(ua)?os="win":/iphone/.test(ua)?os="iph":/ipad/.test(ua)?os="ipa":/mac/.test(ua)?os="mac":/android/.test(ua)?os="and":(/linux/.test(ua)||/x11/.test(ua))&&(os="lnx"),W[E].info.os=os,/safari/.test(ua)&&!/chrome/.test(ua)&&(bwr="saf",bwrver=/version/.test(ua)?"3":"2"),/chrome/.test(ua)&&(bwr="chr",bwrver=(ua.match(/chrome\/([\d.]+)/)||[])[1]),/msie/.test(ua)&&!/opera/.test(ua)&&(bwr="ie",bwrver=(ua.match(/msie ([\d.]+)/)||[])[1]),/trident/.test(ua)&&/rv:/.test(ua)&&!/msie/.test(ua)&&(bwr="ie",bwrver=(ua.match(/rv:([\d.]+)/)||[])[1]),/firefox/.test(ua)&&(bwr="ff",bwrver=(ua.match(/firefox\/([\d.]+)/)||[])[1]),/opera/.test(ua)&&(bwr="op",bwrver=(ua.match(/opera\/([\d.]+)/)||[])[1]),W[E].info.bwr=bwr,W[E].info.bwrver=bwrver}var scriptSrc=!!document.currentScript&&document.currentScript.src,tokid=!!scriptSrc&&scriptSrc.slice(scriptSrc.lastIndexOf("#")+1),adp;adp="object"==typeof _ermap&&null!==_ermap&&tokid&&"object"==typeof _ermap[tokid]&&null!==_ermap[tokid]?_ermap[tokid]:er_params,_erad=W[E].create(adp);function htmlm(t){function e(t,e,i,n){var r=document.createElement("iframe");return r.setAttribute("src",t),n&&r.setAttribute("style",n),r.setAttribute("width",e),r.setAttribute("height",i),r.setAttribute("scrolling","no"),r.setAttribute("frameborder","0"),r}function i(e){if(e&&e.data){var i=e.data.split(":"),r=i[0],d=parseInt(i[1]);isNaN(d)&&(d=-1);var a=i[2];if("initialize"===r){var s={cmd:"initialize",data:{tid:t.p.tid,sid:t.p.sid,clicktag:t.ct(0),vars:t.p.vars}};n.contentWindow.postMessage(JSON.stringify(s),"*")}else t.p.tid===a&&t.cb(r,d)}}var n;return{init:function(){var r=9;if("ie"===t.er.info.bwr&&Number(t.er.info.bwrver)<=r)t.p.b.s=t.p.b.bi,t.p.b.d.innerHTML=t.cI(t.p.b);else{var d=document.createElement("div");d.setAttribute("id","hw_"+t.p.tid);var a="?tid="+t.p.tid+"&sid="+t.p.sid+"&guid="+t.g+"&clicktag="+encodeURIComponent(t.ct(0))+"&oob="+t.p.oob;n=e(t.p.b.s+a,t.p.b.w,t.p.b.h,"z-index: 2000; border: none !important; overflow: hidden"),d.appendChild(n),t.p.b.d.appendChild(d),t.p.b.ifr=n,window.attachEvent?window.attachEvent("onmessage",i):window.addEventListener("message",i)}t.sendRImp()}}}})({"mods":"mcs_html_3_5_js","ver":3.5})