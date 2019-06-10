/// <reference path="../node_modules/babylonjs/babylon.module.d.ts" />
/// <reference path="../node_modules/babylonjs-gltf2interface/babylon.glTF2Interface.d.ts" />
/// <reference path="../node_modules/babylonjs-loaders/babylonjs.loaders.module.d.ts" />
function main() {
    var canvas = document.getElementsByTagName("canvas")[0];
    var game = new Game(canvas);
}
document.addEventListener("DOMContentLoaded", main);
var BlocCollection = /** @class */ (function () {
    function BlocCollection(scene) {
        var _this = this;
        this.blocs = new Array();
        this.getInstance = function (type) {
            var id = BlocCollection.ID_STRING + BlocCollection.createdInstances;
            var output;
            BlocCollection.createdInstances++;
            output = _this.blocs[type].createInstance(id);
            output.position.y = BlocCollection.HEIGHTS[type];
            output.isVisible = true;
            return (output);
        };
        var cur;
        var material;
        var id;
        for (var i = 0, len = BlocCollection.TYPE_COLORS.length; i < len; i++) {
            id = this.blocs.length;
            cur = BABYLON.MeshBuilder.CreateBox("originalBloc" + id, { size: 1 }, scene);
            material = new BABYLON.StandardMaterial("blocMaterial" + id, scene);
            material.diffuseColor = BlocCollection.TYPE_COLORS[i];
            cur.material = material;
            cur.isVisible = false;
            this.blocs.push(cur);
        }
    }
    BlocCollection.ID_STRING = "blocInstance";
    BlocCollection.TYPE_COLORS = [
        new BABYLON.Color3(0, 0.6, 0),
    ];
    BlocCollection.HEIGHTS = [0.05];
    BlocCollection.createdInstances = 0;
    return BlocCollection;
}());
var Camera = /** @class */ (function () {
    function Camera(scene) {
        this.focus = true;
        this.shiftingSpeedX = 0;
        this.shiftingSpeedZ = 0;
        var target = BABYLON.Vector3.Zero();
        this.camera = new BABYLON.ArcRotateCamera("mainCamera", Math.PI / 2, Math.PI / 4, 30, target, scene);
        this.camera.attachControl(scene.getEngine().getRenderingCanvas());
    }
    Camera.prototype.setTarget = function (target) {
        this.camera.setTarget(target);
    };
    Camera.KEYBOARD_SPEED = 10;
    Camera.MOUSE_SPEED = 1 / 20;
    Camera.ZOOM_SPEED = 1 / 10;
    return Camera;
}());
var Game = /** @class */ (function () {
    function Game(canvas) {
        var _this = this;
        this.keyboard = new Keyboard();
        this.socketManager = new SocketManager(this);
        this.render = function () {
            _this.stage.render();
            _this.scene.render();
        };
        this.canvas = canvas;
        this.engine = new BABYLON.Engine(this.canvas, true);
        this.scene = new BABYLON.Scene(this.engine);
        this.stage = new Stage(this.socketManager, this.scene);
        this.camera = new Camera(this.scene);
        this.initialiseScene();
        this.engine.runRenderLoop(this.render);
    }
    Game.prototype.initialiseScene = function () {
        var _this = this;
        this.scene.collisionsEnabled = true;
        window.addEventListener("resize", function () {
            _this.engine.resize();
        });
    };
    Game.prototype.getStage = function () {
        return (this.stage);
    };
    Game.prototype.setSize = function (size) {
        this.stage.createGround(size.x, size.y);
        this.camera.setTarget(new BABYLON.Vector3(size.x / 2, 0, size.y / 2));
    };
    return Game;
}());
var SocketManager = /** @class */ (function () {
    function SocketManager(game) {
        var _this = this;
        this.socket = io();
        this.commands = new Map();
        this.getDatas = function (datas) {
            var array = datas.split("\n");
            var len = array.length;
            var cur;
            for (var i = 0; i < len; i++) {
                cur = array[i].split(" ");
                if (_this.commands.get(cur[i]))
                    _this.commands.get(cur[i])(cur);
            }
        };
        this.msz = function (datas) {
            var vector = new BABYLON.Vector2(0, 0);
            vector.x = parseInt(datas[1]);
            vector.y = parseInt(datas[2]);
            _this.game.setSize(vector);
        };
        this.game = game;
        this.initialise();
        this.socket.emit("data", "GRAPHIC\n");
        this.socket.on("data", this.getDatas);
    }
    SocketManager.prototype.initialise = function () {
        this.commands.set("msz", this.msz);
    };
    return SocketManager;
}());
var Stage = /** @class */ (function () {
    function Stage(socketManager, scene) {
        var _this = this;
        this.blocs = new Array();
        this.onPointerDown = function (event) {
            var picked = _this.scene.pick(event.clientX, event.clientY);
        };
        var lightDir = new BABYLON.Vector3(0, 1, 0);
        this.light = new BABYLON.HemisphericLight("light", lightDir, scene);
        this.scene = scene;
        this.canvas = scene.getEngine().getRenderingCanvas();
        this.socketManager = socketManager;
        this.blocCollection = new BlocCollection(scene);
        this.light.diffuse = new BABYLON.Color3(1, 1, 1);
        this.light.specular = new BABYLON.Color3(0, 0, 0);
        BABYLON.SceneLoader.LoadAssetContainer("/assets/", "chungus.glb", scene, function (container) {
            _this.model = container.meshes[0];
            _this.model.scaling = new BABYLON.Vector3(0.35, 0.35, 0.35);
            _this.model.position.y = 0.5;
            container.addAllToScene();
        });
        window.addEventListener("pointerdown", this.onPointerDown);
    }
    Stage.prototype.createGround = function (width, height) {
        var cur;
        for (var i = width - 1; i >= 0; i--) {
            for (var j = height - 1; j >= 0; j--) {
                cur = this.blocCollection.getInstance(0);
                cur.position.x = i;
                cur.position.z = j;
                this.blocs.push(cur);
            }
        }
    };
    Stage.prototype.render = function () {
    };
    return Stage;
}());
var Key = /** @class */ (function () {
    function Key(codes) {
        var _this = this;
        this.isPressed = false;
        this.setState = function (event) {
            for (var i = _this.codes.length; i >= 0; i--) {
                if (_this.codes[i] == event.which) {
                    _this.isPressed = (event.type == "keydown");
                }
            }
        };
        this.codes = codes;
    }
    Key.prototype.getState = function () {
        return (this.isPressed);
    };
    return Key;
}());
var Keyboard = /** @class */ (function () {
    function Keyboard() {
        var _this = this;
        this.keys = new Array();
        this.manageKeyEvents = function (key) {
            for (var i = _this.keys.length - 1; i >= 0; i--) {
                _this.keys[i].setState(key);
            }
        };
        this.keys.push(new Key(Keyboard.KEYS_LEFT));
        this.keys.push(new Key(Keyboard.KEYS_UP));
        this.keys.push(new Key(Keyboard.KEYS_RIGHT));
        this.keys.push(new Key(Keyboard.KEYS_DOWN));
        window.addEventListener("keydown", this.manageKeyEvents);
        window.addEventListener("keyup", this.manageKeyEvents);
    }
    Keyboard.prototype.getKey = function (id) {
        if (id < 0 || id >= this.keys.length)
            return (false);
        return (this.keys[id].getState());
    };
    Keyboard.KEYS_LEFT = [37, 81];
    Keyboard.KEYS_UP = [38, 90];
    Keyboard.KEYS_RIGHT = [39, 68];
    Keyboard.KEYS_DOWN = [40, 83];
    Keyboard.LEFT = 0;
    Keyboard.UP = 1;
    Keyboard.RIGHT = 2;
    Keyboard.DOWN = 3;
    return Keyboard;
}());
