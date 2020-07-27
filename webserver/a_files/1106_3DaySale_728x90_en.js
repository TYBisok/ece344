(function (cjs, an) {

var p; // shortcut to reference prototypes
var lib={};var ss={};var img={};
lib.webFontTxtInst = {}; 
var loadedTypekitCount = 0;
var loadedGoogleCount = 0;
var gFontsUpdateCacheList = [];
var tFontsUpdateCacheList = [];
lib.ssMetadata = [];



lib.updateListCache = function (cacheList) {		
	for(var i = 0; i < cacheList.length; i++) {		
		if(cacheList[i].cacheCanvas)		
			cacheList[i].updateCache();		
	}		
};		

lib.addElementsToCache = function (textInst, cacheList) {		
	var cur = textInst;		
	while(cur != null && cur != exportRoot) {		
		if(cacheList.indexOf(cur) != -1)		
			break;		
		cur = cur.parent;		
	}		
	if(cur != exportRoot) {		
		var cur2 = textInst;		
		var index = cacheList.indexOf(cur);		
		while(cur2 != null && cur2 != cur) {		
			cacheList.splice(index, 0, cur2);		
			cur2 = cur2.parent;		
			index++;		
		}		
	}		
	else {		
		cur = textInst;		
		while(cur != null && cur != exportRoot) {		
			cacheList.push(cur);		
			cur = cur.parent;		
		}		
	}		
};		

lib.gfontAvailable = function(family, totalGoogleCount) {		
	lib.properties.webfonts[family] = true;		
	var txtInst = lib.webFontTxtInst && lib.webFontTxtInst[family] || [];		
	for(var f = 0; f < txtInst.length; ++f)		
		lib.addElementsToCache(txtInst[f], gFontsUpdateCacheList);		

	loadedGoogleCount++;		
	if(loadedGoogleCount == totalGoogleCount) {		
		lib.updateListCache(gFontsUpdateCacheList);		
	}		
};		

lib.tfontAvailable = function(family, totalTypekitCount) {		
	lib.properties.webfonts[family] = true;		
	var txtInst = lib.webFontTxtInst && lib.webFontTxtInst[family] || [];		
	for(var f = 0; f < txtInst.length; ++f)		
		lib.addElementsToCache(txtInst[f], tFontsUpdateCacheList);		

	loadedTypekitCount++;		
	if(loadedTypekitCount == totalTypekitCount) {		
		lib.updateListCache(tFontsUpdateCacheList);		
	}		
};
// symbols:



(lib.bg728x901 = function() {
	this.initialize(img.bg728x901);
}).prototype = p = new cjs.Bitmap();
p.nominalBounds = new cjs.Rectangle(0,0,728,90);


(lib.Bitmap1 = function() {
	this.initialize(img.Bitmap1);
}).prototype = p = new cjs.Bitmap();
p.nominalBounds = new cjs.Rectangle(0,0,117,332);


(lib.glowlarge = function() {
	this.initialize(img.glowlarge);
}).prototype = p = new cjs.Bitmap();
p.nominalBounds = new cjs.Rectangle(0,0,92,92);


(lib.ray = function() {
	this.initialize(img.ray);
}).prototype = p = new cjs.Bitmap();
p.nominalBounds = new cjs.Rectangle(0,0,84,84);


(lib.ring = function() {
	this.initialize(img.ring);
}).prototype = p = new cjs.Bitmap();
p.nominalBounds = new cjs.Rectangle(0,0,57,57);


(lib.sku1 = function() {
	this.initialize(img.sku1);
}).prototype = p = new cjs.Bitmap();
p.nominalBounds = new cjs.Rectangle(0,0,276,274);


(lib.sku2 = function() {
	this.initialize(img.sku2);
}).prototype = p = new cjs.Bitmap();
p.nominalBounds = new cjs.Rectangle(0,0,217,154);


(lib.sku3 = function() {
	this.initialize(img.sku3);
}).prototype = p = new cjs.Bitmap();
p.nominalBounds = new cjs.Rectangle(0,0,192,222);// helper functions:

function mc_symbol_clone() {
	var clone = this._cloneProps(new this.constructor(this.mode, this.startPosition, this.loop));
	clone.gotoAndStop(this.currentFrame);
	clone.paused = this.paused;
	clone.framerate = this.framerate;
	return clone;
}

function getMCSymbolPrototype(symbol, nominalBounds, frameBounds) {
	var prototype = cjs.extend(symbol, cjs.MovieClip);
	prototype.clone = mc_symbol_clone;
	prototype.nominalBounds = nominalBounds;
	prototype.frameBounds = frameBounds;
	return prototype;
	}


(lib.twinkle2 = function(mode,startPosition,loop) {
	this.initialize(mode,startPosition,loop,{});

	// Layer 1
	this.shape = new cjs.Shape();
	this.shape.graphics.f("#FFFFFF").s().p("AgVAXIrigXILigVIAVriIAWLiILiAVIriAXIgWLhg");

	this.timeline.addTween(cjs.Tween.get(this.shape).wait(1));

}).prototype = getMCSymbolPrototype(lib.twinkle2, new cjs.Rectangle(-76,-76,152.1,152), null);


(lib.twinkle1 = function(mode,startPosition,loop) {
	this.initialize(mode,startPosition,loop,{});

	// ring
	this.instance = new lib.ring();
	this.instance.parent = this;
	this.instance.setTransform(-19.6,-26.2,0.814,0.814,8.2);

	this.timeline.addTween(cjs.Tween.get(this.instance).wait(1));

	// ray 1
	this.instance_1 = new lib.ray();
	this.instance_1.parent = this;
	this.instance_1.setTransform(48.1,5,0.814,0.814,0,51,-129);

	this.timeline.addTween(cjs.Tween.get(this.instance_1).wait(1));

	// ray 2
	this.instance_2 = new lib.ray();
	this.instance_2.parent = this;
	this.instance_2.setTransform(12.7,-46.5,0.814,0.814,60.4);

	this.timeline.addTween(cjs.Tween.get(this.instance_2).wait(1));

	// Layer 1
	this.shape = new cjs.Shape();
	this.shape.graphics.f("#FFFFFF").s().p("AgCAbIoJF3IHxmUIl3oJIGVHxIIIl3InwGUIF2IJg");

	this.timeline.addTween(cjs.Tween.get(this.shape).wait(1));

	// glow large
	this.instance_3 = new lib.glowlarge();
	this.instance_3.parent = this;
	this.instance_3.setTransform(-37.4,-37.4,0.814,0.814);

	this.timeline.addTween(cjs.Tween.get(this.instance_3).wait(1));

}).prototype = getMCSymbolPrototype(lib.twinkle1, new cjs.Rectangle(-52.3,-52.3,104.7,104.8), null);


(lib.sku3_1 = function(mode,startPosition,loop) {
	this.initialize(mode,startPosition,loop,{});

	// Layer 1
	this.instance = new lib.sku3();
	this.instance.parent = this;
	this.instance.setTransform(28,17,0.5,0.5);

	this.timeline.addTween(cjs.Tween.get(this.instance).wait(1));

}).prototype = getMCSymbolPrototype(lib.sku3_1, new cjs.Rectangle(28,17,96,111), null);


(lib.sku2_1 = function(mode,startPosition,loop) {
if (loop == null) { loop = false; }	this.initialize(mode,startPosition,loop,{});

	// Layer 1
	this.instance = new lib.sku2();
	this.instance.parent = this;
	this.instance.setTransform(-14,20,0.5,0.5);

	this.timeline.addTween(cjs.Tween.get(this.instance).wait(1));

}).prototype = getMCSymbolPrototype(lib.sku2_1, new cjs.Rectangle(-14,20,108.5,77), null);


(lib.sku1_1 = function(mode,startPosition,loop) {
	this.initialize(mode,startPosition,loop,{});

	// Layer 1
	this.instance = new lib.sku1();
	this.instance.parent = this;
	this.instance.setTransform(-9,-18,0.5,0.5);

	this.timeline.addTween(cjs.Tween.get(this.instance).wait(1));

}).prototype = getMCSymbolPrototype(lib.sku1_1, new cjs.Rectangle(-9,-18,138,137), null);


(lib.logo = function(mode,startPosition,loop) {
	this.initialize(mode,startPosition,loop,{});

	// Layer 1
	this.shape = new cjs.Shape();
	this.shape.graphics.f("#221F20").s().p("AgDAFIABgJIACAAQAAAAABAAQAAAAABAAQAAABABAAQAAAAAAABQABAAAAAAQAAABAAAAQAAABAAAAQAAAAAAAAQAAABAAAAQAAABAAAAQAAABgBAAQAAABAAAAQgBAAAAAAQAAABgBAAQAAAAgBAAQAAAAgBAAgAgCAEIABAAQADABABgFQAAgDgDAAIgBAAg");
	this.shape.setTransform(60.8,26.2,0.799,0.799);

	this.shape_1 = new cjs.Shape();
	this.shape_1.graphics.f("#221F20").s().p("AAEAFIAAgIIgDAIIgBAAIgCgIIgBAIIgBAAIABgJIACAAIABAHIAEgHIABAAIAAAJg");
	this.shape_1.setTransform(59.8,26.1,0.799,0.799);

	this.shape_2 = new cjs.Shape();
	this.shape_2.graphics.f("#221F20").s().p("AAAAHQgHgBABgGQABgHAGAAQAHABAAAGQgBAIgGAAIgBgBgAgFAAQgBAFAGABQAGAAAAgGQABgFgGAAIgBAAQgFAAAAAFgAACAEIgCgEIgBAAIAAAEIgBAAIABgIIACABIACAAIABACQAAABgBAAQAAAAAAAAQAAAAgBAAQAAAAgBAAIACAEgAgBAAIABAAQAAAAABAAQAAAAABAAQAAAAAAAAQABAAAAgBQAAAAgBAAQAAAAAAgBQAAAAgBAAQAAAAAAAAIgBgBg");
	this.shape_2.setTransform(58.4,26,0.799,0.799);

	this.shape_3 = new cjs.Shape();
	this.shape_3.graphics.f("#221F20").s().p("AALBOIhlgJIANiTIBXAIQBQAHgDApQgBAKgHAHQgIAHgOACIAAABQAkAMgCAbQgCAVgZAIQgQAGgVAAIgQgBgAgRAoIAIAAQANABAGgBQALgBABgIQABgNgfgCIgHgBgAgMgPIAHABQAKAAAFgBQAHgCABgGQAAgHgIgDQgEgCgLgBIgFAAg");
	this.shape_3.setTransform(16.2,14.2,0.799,0.799);

	this.shape_4 = new cjs.Shape();
	this.shape_4.graphics.f("#221F20").s().p("AgvBIIAJhjIgqgDIAFgwICcAOIgEAwIgqgFIgIBkg");
	this.shape_4.setTransform(55.7,17.7,0.799,0.799);

	this.shape_5 = new cjs.Shape();
	this.shape_5.graphics.f("#221F20").s().p("AgHBLQgsgEgjgQIAbgoIAEADQAXAPAWACQATACAAgJQABgGgQgEIgPgDQgXgFgOgKQgPgLACgRQACgZAdgNQAbgMAjADQAkADAdAQIgYAkQgXgOgUgBQgGgBgEACQgGABAAAEQgBAGAPADIARAEQA2AOgDAgQgCAZgeANQgTAIgaAAIgQgBg");
	this.shape_5.setTransform(42.2,16.8,0.799,0.799);

	this.shape_6 = new cjs.Shape();
	this.shape_6.graphics.f("#221F20").s().p("AhLBEIANiTICKAMIgEAoIg/gFIgBAOIA6AFIgDAmIg6gGIgCAOIBCAHIgEAog");
	this.shape_6.setTransform(29.7,15.7,0.799,0.799);

	this.shape_7 = new cjs.Shape();
	this.shape_7.graphics.f("#221F20").s().p("AAMBOIhmgJIANiTIBXAIQBQAHgDApQgBAKgHAHQgIAHgOACIAAABQAkAMgCAbQgCAUgZAJQgQAGgVAAIgPgBgAgRAoIAIAAQANABAGgBQALgBABgIQAAgIgKgEQgGgCgNgBIgIgBgAgMgPIAHABQAWACABgLQAAgHgIgDQgEgCgLgBIgFAAg");
	this.shape_7.setTransform(17.4,27.6,0.799,0.799);

	this.shape_8 = new cjs.Shape();
	this.shape_8.graphics.f("#221F20").s().p("AgIBPQgsgEgWgRQgYgSADggIAIhWIBIAGIgHBRQgBALACAFQAEAHANABQAMABAEgGQADgEABgLIAIhRIBIAGIgIBWQgCAggbAOQgTAJgeAAIgSAAg");
	this.shape_8.setTransform(32.8,29,0.799,0.799);

	this.shape_9 = new cjs.Shape();
	this.shape_9.graphics.f("#221F20").s().p("AgwBKIAGhAIhBhZIBVAHIATApIADAAIAHgNIARgYIBUAIIhOBMIgGBAg");
	this.shape_9.setTransform(48.9,30.3,0.799,0.799);

	this.shape_10 = new cjs.Shape();
	this.shape_10.graphics.f("#221F20").s().p("AgBAbQgMgBgHgJQgGgIAAgJIAAgCQABgKAJgIQAJgIAKACQALABAHAIQAIAJgCAKQAAAMgJAHQgIAGgKAAIgBAAgAgKgMQgFAEgBAHQgBAGAFAGQAFAFAHABQAGABAFgFQAFgFABgHQABgGgFgFQgEgFgHgBQgHAAgFAEg");
	this.shape_10.setTransform(4.9,19.5,0.799,0.799);

	this.shape_11 = new cjs.Shape();
	this.shape_11.graphics.f("#221F20").s().p("AkGDgIiQilIASjKICqiHIJxA3IgsH2gAl6iKIgRDBICKCfIJjA2IAqniIpjg1g");
	this.shape_11.setTransform(32.5,22.3,0.799,0.799);

	this.shape_12 = new cjs.Shape();
	this.shape_12.graphics.f("#FFF24B").s().p("AkEDbIiMiiIARjFICmiEIJqA2IgrHrgAlmgyQgHAGgBAJQAAAJAFAIQAGAGAJABQAKABAHgGQAHgGAAgJQABgJgGgHQgGgHgJgBIgBAAQgIAAgHAFg");
	this.shape_12.setTransform(32.5,22.2,0.799,0.799);

	this.timeline.addTween(cjs.Tween.get({}).to({state:[{t:this.shape_12},{t:this.shape_11},{t:this.shape_10},{t:this.shape_9},{t:this.shape_8},{t:this.shape_7},{t:this.shape_6},{t:this.shape_5},{t:this.shape_4},{t:this.shape_3},{t:this.shape_2},{t:this.shape_1},{t:this.shape}]}).wait(1));

}).prototype = getMCSymbolPrototype(lib.logo, new cjs.Rectangle(0,0,65,44.6), null);


(lib.cta = function(mode,startPosition,loop) {
	this.initialize(mode,startPosition,loop,{});

	// editable copy
	this.shape = new cjs.Shape();
	this.shape.graphics.f("#FFFFFF").s().p("ABkAbIgFgCIgGgCIgDgDIgEgFIgDgEIgBgFIAAgGIAAgFIABgGIADgEIAEgEIADgDIAGgDIAFgBIAGgBIAGABIAFABIAFADIAEADIAEAEIACAEIABAGIABAFIgBAGIgBAFIgCAEIgEAFIgEADIgFACIgFACIgGAAIgGAAgABjgOIgEADIgDAGIgBAFIABAGIADAGIAEADIAHABQADAAADgBIAEgDIADgGIACgGIgCgFIgDgGIgEgDIgGgBIgHABgAhWAbIgFgCIgGgCIgDgDIgEgFIgDgEIgBgFIgBgGIABgFIABgGIADgEIAEgEIADgDIAGgDIAFgBIAFgBIAHABIAFABIAFADIAEADIAEAEIACAEIABAGIABAFIgBAGIgBAFIgCAEIgEAFIgEADIgFACIgFACIgHAAIgFAAgAhXgOIgEADIgDAGIgBAFIABAGIADAGIAEADIAGABQAEAAADgBIAEgDIAEgGIABgGIgBgFIgEgGQgBgCgDgBIgHgBIgGABgAjGAbIgFgCIgFgCIgEgDIAIgIQACACADABIAHACQADAAABgCIACgBIABgCIgBgDIgCgCIgIgDIgFgCIgEgCIgDgEQgCgCABgEIAAgEIACgEQABgCADgCIAGgEIAIgBIAJACIAEACIAEADIgIAJIgEgEIgGgBIgFABIgBACIgBACQAAABABAAQAAABAAAAQAAABABAAQAAABAAAAIAGADIAGACIAFACIAEAEQABADABADIgBAEIgBADQgCAEgDACIgGADIgHABIgGAAgAC6AaIgKgiIgBAAIgKAiIgNAAIgPgzIAOAAIAJAhIAJghIANAAIAJAhIAAAAIAJghIANAAIgPAzgAA2AaIgVghIAAAhIgMAAIAAgzIAOAAIAVAhIAAAAIAAghIAMAAIAAAzgAgqAaIAAgzIATAAIAIABQAEABACACQADABACADIABAEIABAEIgBAEIgBADQgCACgDADQgDACgEABIgIAAIgFAAIAAAUgAgdgCIAEAAQAFgBACgBIACgCIABgDIgBgDIgCgCIgGgBIgFAAgAiCAaIAAgWIgVAAIAAAWIgMAAIAAgzIAMAAIAAAUIAVAAIAAgUIAMAAIAAAzg");
	this.shape.setTransform(49.2,-8.7);

	this.timeline.addTween(cjs.Tween.get(this.shape).wait(1));

	// bg
	this.shape_1 = new cjs.Shape();
	this.shape_1.graphics.f().s("#013D6B").ss(1,1,1).p("EggrgKhMBBXAAAQAUAAAAAUIAAUcQAAAUgUAAMhBXAAAQgUAAAAgUIAA0cQAAgUAUAAg");
	this.shape_1.setTransform(49.2,-8.8,0.143,0.143);

	this.shape_2 = new cjs.Shape();
	this.shape_2.graphics.f("#013D6B").s().p("EggrAKiQgUAAAAgUIAA0bQAAgVAUAAMBBXAAAQAUAAAAAVIAAUbQAAAUgUAAg");
	this.shape_2.setTransform(49.2,-8.8,0.143,0.143);

	this.timeline.addTween(cjs.Tween.get({}).to({state:[{t:this.shape_2},{t:this.shape_1}]}).wait(1));

}).prototype = getMCSymbolPrototype(lib.cta, new cjs.Rectangle(18,-19.4,62.4,21.3), null);


(lib.Copy = function(mode,startPosition,loop) {
	this.initialize(mode,startPosition,loop,{});

	// Layer 1 copy
	this.shape = new cjs.Shape();
	this.shape.graphics.f("#FFF24B").s().p("AyQCUQglgWgMgqIBGgTQAFARAOALQAPALAVABQASAAANgJQAPgMAAgUQAAgqhBAAIgUAAIAAg2IAWAAQA4AAAAgnQAAgQgNgKQgLgIgQAAQgRAAgLAKQgMAJgEAQIhGgQQALgmAigWQAggVAqAAQAtAAAgAWQAjAZAAArQAAAagPATQgPASgYAGIAAACQAbAGARATQARAVAAAbQAAAwgmAcQghAZgxAAQguAAghgUgADOCcQgggNgVgVIAyg0QAMAPATAKQAUAJASAAQAtAAAAgjQAAgQgSgLQgLgGgmgMQglgMgTgQQgZgYAAgmQAAgyAngbQAigXAyAAQA+AAArAmIgxA1QgKgNgQgHQgQgIgPAAQgtAAAAAgQAAAPAOAIQAJAGAaAIQAvAPATAPQAhAYAAApQAAA0glAdQghAZg0ABQgigBgggLgAPjCfIAAk9IDXAAIAABBIiNAAIAAA7ICFAAIAAA9IiFAAIAABDICVAAIAABBgAL7CfIAAk9IBOAAIAAD7IB7AAIAABCgAKQCfIgZg+Ih7AAIgYA+IhUAAICGk9IBLAAICFE9gAJiAjIgohtIgoBtIBQAAgAhqCfIAAiHIh4i2IBeAAIBDB2IBDh2IBbAAIh6C2IAACHgAkPCfIgZg+Ih7AAIgYA+IhUAAICGk9IBLAAICFE9gAk9AjIgohtIgoBtIBQAAgAsrCfIAAk9IB0AAQBNAAAwAhQA5ApAABUQAABNg5AtQgxAmhJgBgArgBdIAlAAQAuAAAbgVQAhgXAAgxQAAgygggXQgbgUgtABIgnAAgAu1BHIAAg7IByAAIAAA7g");
	this.shape.setTransform(166,-30.3);

	this.timeline.addTween(cjs.Tween.get(this.shape).wait(1));

}).prototype = getMCSymbolPrototype(lib.Copy, new cjs.Rectangle(44.3,-47.1,243.6,33.6), null);


(lib.button = function(mode,startPosition,loop) {
	this.initialize(mode,startPosition,loop,{});

	// Layer 1
	this.shape = new cjs.Shape();
	this.shape.graphics.f("#00FFFF").s().p("A3bTiMAAAgnDMAu3AAAMAAAAnDg");
	this.shape.setTransform(66,18.1);
	this.shape._off = true;

	this.timeline.addTween(cjs.Tween.get(this.shape).wait(3).to({_off:false},0).wait(1));

}).prototype = p = new cjs.MovieClip();
p.nominalBounds = null;


(lib.X2 = function(mode,startPosition,loop) {
if (loop == null) { loop = false; }	this.initialize(mode,startPosition,loop,{});

	// X2
	this.instance = new lib.twinkle2();
	this.instance.parent = this;
	this.instance.setTransform(0,0,0.008,0.008,0,-16,-15.3);

	this.timeline.addTween(cjs.Tween.get(this.instance).to({regX:0.2,regY:-0.5,scaleX:0.21,scaleY:0.21,skewX:4.8,skewY:4.5,x:0.1,y:-0.1},27).wait(3).to({regX:0,regY:0,scaleX:0.21,scaleY:0.21,skewX:6.3,skewY:6.2,x:0,y:0},0).to({scaleX:0.01,scaleY:0.01,rotation:29.3,skewX:0,skewY:0,x:-0.2},30).wait(1));

}).prototype = p = new cjs.MovieClip();
p.nominalBounds = new cjs.Rectangle(-0.7,-0.8,1.5,1.5);


(lib.X1 = function(mode,startPosition,loop) {
if (loop == null) { loop = false; }	this.initialize(mode,startPosition,loop,{});

	// X1
	this.instance = new lib.twinkle1();
	this.instance.parent = this;
	this.instance.setTransform(0,-0.1,0.01,0.01);

	this.timeline.addTween(cjs.Tween.get(this.instance).to({regX:-0.5,regY:-0.1,scaleX:0.26,scaleY:0.26,rotation:20.5,x:-0.1,y:-0.2},28).wait(3).to({regX:-0.8,regY:-0.3,scaleX:0.26,scaleY:0.26,rotation:22.8,y:-0.1},0).to({regX:0,regY:0,scaleX:0.01,scaleY:0.01,rotation:45,x:0,y:0},29).wait(1));

}).prototype = p = new cjs.MovieClip();
p.nominalBounds = new cjs.Rectangle(-0.5,-0.6,1,1);


(lib.mc_glitter = function(mode,startPosition,loop) {
	this.initialize(mode,startPosition,loop,{});

	// copy
	this.instance = new lib.Copy();
	this.instance.parent = this;
	this.instance.setTransform(-63.3,59.2,0.934,0.934,0,0,0,94.2,32.7);

	this.timeline.addTween(cjs.Tween.get(this.instance).wait(1));

	// Layer_1
	this.instance_1 = new lib.Bitmap1();
	this.instance_1.parent = this;
	this.instance_1.setTransform(-166,58.5,1,1,-90);

	this.timeline.addTween(cjs.Tween.get(this.instance_1).wait(1));

}).prototype = getMCSymbolPrototype(lib.mc_glitter, new cjs.Rectangle(-166,-58.5,332,117), null);


// stage content:
(lib._1106_3DaySale_728x90_en = function(mode,startPosition,loop) {
if (loop == null) { loop = false; }	this.initialize(mode,startPosition,loop,{});

	// timeline functions:
	this.frame_0 = function() {
		/* Clicktag*/
		eyeBuild.initialize();
		
		this.clickthrough_btn.addEventListener("click", fl_MouseClickHandler.bind(this));
		function fl_MouseClickHandler(e)
		
		{
		if (e.nativeEvent.button==0)
		{
		
		eyeBuild.doClick(0);
		}
		}
	}

	// actions tween:
	this.timeline.addTween(cjs.Tween.get(this).call(this.frame_0).wait(227));

	// clickthrough
	this.clickthrough_btn = new lib.button();
	this.clickthrough_btn.parent = this;
	this.clickthrough_btn.setTransform(268.9,41.1,2.427,0.36,0,0,0,26.8,7.1);
	new cjs.ButtonHelper(this.clickthrough_btn, 0, 1, 2, false, new lib.button(), 3);

	this.timeline.addTween(cjs.Tween.get(this.clickthrough_btn).wait(227));

	// Border
	this.shape = new cjs.Shape();
	this.shape.graphics.f().s("#000000").ss(1,1,1).p("Eg43gHBMBxvAAAIAAODMhxvAAAg");
	this.shape.setTransform(364,45);

	this.timeline.addTween(cjs.Tween.get(this.shape).wait(227));

	// logo
	this.instance = new lib.logo();
	this.instance.parent = this;
	this.instance.setTransform(672.5,45.2,1.144,1.144,0,0,0,32.5,22.4);

	this.timeline.addTween(cjs.Tween.get(this.instance).wait(227));

	// cta
	this.instance_1 = new lib.cta();
	this.instance_1.parent = this;
	this.instance_1.setTransform(607.1,45.1,0.423,0.422,0,0,0,50.1,-8.7);
	this.instance_1._off = true;

	this.timeline.addTween(cjs.Tween.get(this.instance_1).wait(141).to({_off:false},0).to({regX:50,scaleX:1.27,scaleY:1.27,x:578.5,y:45},14,cjs.Ease.backOut).wait(72));

	// X1
	this.instance_2 = new lib.X1();
	this.instance_2.parent = this;
	this.instance_2.setTransform(157.5,13);
	this.instance_2.shadow = new cjs.Shadow("rgba(255,255,255,1)",0,0,6);
	this.instance_2._off = true;

	this.timeline.addTween(cjs.Tween.get(this.instance_2).wait(119).to({_off:false},0).wait(108));

	// X2
	this.instance_3 = new lib.X2();
	this.instance_3.parent = this;
	this.instance_3.setTransform(235.1,79.1);
	this.instance_3._off = true;

	this.timeline.addTween(cjs.Tween.get(this.instance_3).wait(103).to({_off:false},0).to({_off:true},79).wait(45));

	// X1
	this.instance_4 = new lib.X1();
	this.instance_4.parent = this;
	this.instance_4.setTransform(580.5,37);
	this.instance_4.shadow = new cjs.Shadow("rgba(255,255,255,1)",0,0,6);
	this.instance_4._off = true;

	this.timeline.addTween(cjs.Tween.get(this.instance_4).wait(74).to({_off:false},0).to({_off:true},97).wait(56));

	// X2
	this.instance_5 = new lib.X2();
	this.instance_5.parent = this;
	this.instance_5.setTransform(75.6,16.6);
	this.instance_5._off = true;

	this.timeline.addTween(cjs.Tween.get(this.instance_5).wait(165).to({_off:false},0).wait(62));

	// X2
	this.instance_6 = new lib.X2();
	this.instance_6.parent = this;
	this.instance_6.setTransform(337.7,45.2,1,1,0,0,0,1.9,-2);
	this.instance_6.shadow = new cjs.Shadow("rgba(255,255,0,1)",0,0,6);
	this.instance_6._off = true;

	this.timeline.addTween(cjs.Tween.get(this.instance_6).wait(45).to({_off:false},0).to({_off:true},69).wait(63).to({_off:false,x:233.2,y:78.6},0).wait(50));

	// X1
	this.instance_7 = new lib.X1();
	this.instance_7.parent = this;
	this.instance_7.setTransform(5,24);
	this.instance_7.shadow = new cjs.Shadow("rgba(255,255,255,1)",0,0,6);
	this.instance_7._off = true;

	this.timeline.addTween(cjs.Tween.get(this.instance_7).wait(57).to({_off:false},0).to({_off:true},62).wait(108));

	// X2
	this.instance_8 = new lib.X2();
	this.instance_8.parent = this;
	this.instance_8.setTransform(235.7,76.2,1,1,0,0,0,1.9,-2);
	this.instance_8.shadow = new cjs.Shadow("rgba(255,255,0,1)",0,0,6);
	this.instance_8._off = true;

	this.timeline.addTween(cjs.Tween.get(this.instance_8).wait(16).to({_off:false},0).to({_off:true},58).wait(153));

	// X1
	this.instance_9 = new lib.X1();
	this.instance_9.parent = this;
	this.instance_9.setTransform(159.9,12,1,1,0,0,0,1.9,-2);
	this.instance_9.shadow = new cjs.Shadow("rgba(255,255,255,1)",0,0,6);
	this.instance_9._off = true;

	this.timeline.addTween(cjs.Tween.get(this.instance_9).wait(28).to({_off:false},0).to({_off:true},76).wait(123));

	// All_skus_3
	this.instance_10 = new lib.sku2_1();
	this.instance_10.parent = this;
	this.instance_10.setTransform(439.7,67.2,0.2,0.2,0,0,0,110.2,70.2);
	this.instance_10.alpha = 0;
	this.instance_10._off = true;

	this.timeline.addTween(cjs.Tween.get(this.instance_10).wait(159).to({_off:false},0).wait(1).to({regX:40.2,regY:58.5,scaleX:0.23,scaleY:0.23,x:423.8,y:64.5,alpha:0.072},0).wait(1).to({scaleX:0.25,scaleY:0.25,x:422,y:64.2,alpha:0.143},0).wait(1).to({scaleX:0.28,scaleY:0.28,x:420.2,y:63.9,alpha:0.212},0).wait(1).to({scaleX:0.3,scaleY:0.3,x:418.5,y:63.6,alpha:0.279},0).wait(1).to({scaleX:0.33,scaleY:0.33,x:416.8,y:63.3,alpha:0.343},0).wait(1).to({scaleX:0.35,scaleY:0.35,x:415.2,y:63.1,alpha:0.405},0).wait(1).to({scaleX:0.37,scaleY:0.37,x:413.7,y:62.8,alpha:0.464},0).wait(1).to({scaleX:0.39,scaleY:0.39,x:412.2,y:62.6,alpha:0.521},0).wait(1).to({scaleX:0.41,scaleY:0.41,x:410.8,y:62.3,alpha:0.575},0).wait(1).to({scaleX:0.43,scaleY:0.43,x:409.5,y:62.1,alpha:0.626},0).wait(1).to({scaleX:0.45,scaleY:0.45,x:408.3,y:61.9,alpha:0.675},0).wait(1).to({scaleX:0.47,scaleY:0.47,x:407.1,y:61.7,alpha:0.72},0).wait(1).to({scaleX:0.48,scaleY:0.48,x:406,y:61.5,alpha:0.764},0).wait(1).to({scaleX:0.5,scaleY:0.5,x:404.9,y:61.3,alpha:0.804},0).wait(1).to({scaleX:0.51,scaleY:0.51,x:403.9,y:61.1,alpha:0.842},0).wait(1).to({scaleX:0.52,scaleY:0.52,x:403,y:61,alpha:0.878},0).wait(1).to({scaleX:0.54,scaleY:0.54,x:402.1,y:60.8,alpha:0.912},0).wait(1).to({scaleX:0.55,scaleY:0.55,x:401.3,y:60.7,alpha:0.943},0).wait(1).to({scaleX:0.56,scaleY:0.56,x:400.6,y:60.6,alpha:0.972},0).wait(1).to({regX:110.4,regY:70.2,scaleX:0.57,scaleY:0.57,x:439.8,y:67.1,alpha:1},0).wait(48));

	// All_skus_2
	this.instance_11 = new lib.sku3_1();
	this.instance_11.parent = this;
	this.instance_11.setTransform(362.2,43.3,0.2,0.2,0,0,0,110,69.8);
	this.instance_11.alpha = 0;
	this.instance_11._off = true;

	this.timeline.addTween(cjs.Tween.get(this.instance_11).wait(165).to({_off:false},0).to({regX:109.9,regY:69.9,scaleX:0.66,scaleY:0.66,alpha:1},20,cjs.Ease.backOut).wait(42));

	// All_skus_1
	this.instance_12 = new lib.sku1_1();
	this.instance_12.parent = this;
	this.instance_12.setTransform(509.3,56.7,0.2,0.2,0,0,0,110,70);
	this.instance_12.alpha = 0;
	this.instance_12._off = true;

	this.timeline.addTween(cjs.Tween.get(this.instance_12).wait(152).to({_off:false},0).to({regX:109.8,regY:69.8,scaleX:0.63,scaleY:0.63,alpha:1},20,cjs.Ease.backOut).wait(55));

	// sku2
	this.instance_13 = new lib.sku2_1();
	this.instance_13.parent = this;
	this.instance_13.setTransform(662.5,55.6,0.273,0.273,0,0,0,72.2,97.1);
	this.instance_13._off = true;

	this.timeline.addTween(cjs.Tween.get(this.instance_13).wait(13).to({_off:false},0).to({regX:71.5,regY:96.5,scaleX:1.03,scaleY:1.03,x:506.3,y:84.2},12,cjs.Ease.backOut).wait(9).to({regX:71.6,x:516.5,y:84.3},4,cjs.Ease.quadIn).to({regX:71.8,regY:97,scaleX:0.26,scaleY:0.26,x:340.2,y:55},11,cjs.Ease.quadIn).to({_off:true},1).wait(177));

	// sku3
	this.instance_14 = new lib.sku3_1();
	this.instance_14.parent = this;
	this.instance_14.setTransform(685.2,53,0.319,0.319,0,0,0,72.3,97.4);
	this.instance_14._off = true;

	this.timeline.addTween(cjs.Tween.get(this.instance_14).wait(94).to({_off:false},0).to({regX:71.7,regY:96.5,scaleX:0.77,scaleY:0.77,x:472.9,y:63.4},12,cjs.Ease.backOut).wait(14).to({x:483.7},5).to({regX:72.1,regY:97.4,scaleX:0.32,scaleY:0.32,x:304.4,y:53},9).to({_off:true},1).wait(92));

	// Sku 1
	this.instance_15 = new lib.sku1_1();
	this.instance_15.parent = this;
	this.instance_15.setTransform(658.8,55.1,0.287,0.287,0,0,0,48.1,85.5);
	this.instance_15._off = true;

	this.timeline.addTween(cjs.Tween.get(this.instance_15).wait(50).to({_off:false},0).to({regX:48.2,regY:85.7,scaleX:0.61,scaleY:0.61,x:475.8,y:66.6},15,cjs.Ease.backOut).wait(10).to({x:505.8},4,cjs.Ease.quadIn).to({regX:48.1,regY:85.5,scaleX:0.29,scaleY:0.29,x:336.8,y:55.1},9,cjs.Ease.quadIn).to({_off:true},1).wait(138));

	// lockup
	this.instance_16 = new lib.mc_glitter();
	this.instance_16.parent = this;
	this.instance_16.setTransform(-171.4,45);

	this.timeline.addTween(cjs.Tween.get(this.instance_16).to({x:140.5},10,cjs.Ease.get(1)).wait(217));

	// bg
	this.instance_17 = new lib.bg728x901();
	this.instance_17.parent = this;

	this.timeline.addTween(cjs.Tween.get(this.instance_17).wait(227));

}).prototype = p = new cjs.MovieClip();
p.nominalBounds = new cjs.Rectangle(26.6,31.5,1066.5,117);
// library properties:
lib.properties = {
	id: 'BBDF2E309B0F4AD8BC2D906AE2277BD1',
	width: 728,
	height: 90,
	fps: 30,
	color: "#FFFFFF",
	opacity: 1.00,
	webfonts: {},
	manifest: [
		{src:"bg728x901.png", id:"bg728x901"},
		{src:"Bitmap1.png", id:"Bitmap1"},
		{src:"glowlarge.png", id:"glowlarge"},
		{src:"ray.png", id:"ray"},
		{src:"ring.png", id:"ring"},
		{src:"sku1.png", id:"sku1"},
		{src:"sku2.png", id:"sku2"},
		{src:"sku3.png", id:"sku3"}
	],
	preloads: []
};



// bootstrap callback support:

(lib.Stage = function(canvas) {
	createjs.Stage.call(this, canvas);
}).prototype = p = new createjs.Stage();

p.setAutoPlay = function(autoPlay) {
	this.tickEnabled = autoPlay;
}
p.play = function() { this.tickEnabled = true; this.getChildAt(0).gotoAndPlay(this.getTimelinePosition()) }
p.stop = function(ms) { if(ms) this.seek(ms); this.tickEnabled = false; }
p.seek = function(ms) { this.tickEnabled = true; this.getChildAt(0).gotoAndStop(lib.properties.fps * ms / 1000); }
p.getDuration = function() { return this.getChildAt(0).totalFrames / lib.properties.fps * 1000; }

p.getTimelinePosition = function() { return this.getChildAt(0).currentFrame / lib.properties.fps * 1000; }

an.bootcompsLoaded = an.bootcompsLoaded || [];
if(!an.bootstrapListeners) {
	an.bootstrapListeners=[];
}

an.bootstrapCallback=function(fnCallback) {
	an.bootstrapListeners.push(fnCallback);
	if(an.bootcompsLoaded.length > 0) {
		for(var i=0; i<an.bootcompsLoaded.length; ++i) {
			fnCallback(an.bootcompsLoaded[i]);
		}
	}
};

an.compositions = an.compositions || {};
an.compositions['BBDF2E309B0F4AD8BC2D906AE2277BD1'] = {
	getStage: function() { return exportRoot.getStage(); },
	getLibrary: function() { return lib; },
	getSpriteSheet: function() { return ss; },
	getImages: function() { return img; }
};

an.compositionLoaded = function(id) {
	an.bootcompsLoaded.push(id);
	for(var j=0; j<an.bootstrapListeners.length; j++) {
		an.bootstrapListeners[j](id);
	}
}

an.getComposition = function(id) {
	return an.compositions[id];
}



})(createjs = createjs||{}, AdobeAn = AdobeAn||{});
var createjs, AdobeAn;