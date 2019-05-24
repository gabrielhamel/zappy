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
        var position = new BABYLON.Vector3(50, 30, 50);
        this.camera = new BABYLON.UniversalCamera("mainCamera", position, scene);
        this.camera.attachControl(scene.getEngine().getRenderingCanvas());
        this.camera.setTarget(Camera.TARGET);
    }
    /*private isNearFromBorders = ():boolean =>
    {
        if (this.camera.position.x >= 110) {
            this.camera.position.x -= 1;
            this.shiftingSpeedX = 0;
            return (false);
        }
        if (this.camera.position.x <= Camera.TARGET.x) {
            this.camera.position.x = Camera.TARGET.x + 1;
            this.shiftingSpeedX = 0;
            return (false);
        }
        if (this.camera.position.z >= 80) {
            this.camera.position.z -= 1;
            this.shiftingSpeedZ = 0;
            return (false);
        }
        if (this.camera.position.z <= 20) {
            this.camera.position.z = 21;
            this.shiftingSpeedZ = 0;
            return (false);
        }
        return (true);
    }*/
    Camera.prototype.setFocus = function (focus) {
        this.focus = focus;
    };
    Camera.TARGET = new BABYLON.Vector3(30, 0, 50);
    Camera.KEYBOARD_SPEED = 10;
    Camera.MOUSE_SPEED = 1 / 20;
    Camera.ZOOM_SPEED = 1 / 10;
    return Camera;
}());
/// <reference path="../../node_modules/babylonjs/babylon.module.d.ts" />
/// <reference path="../../node_modules/babylonjs-gltf2interface/babylon.glTF2Interface.d.ts" />
/// <reference path="../../node_modules/babylonjs-loaders/babylonjs.loaders.module.d.ts" />
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
        this.stage.createGround(10, 10);
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
    return Game;
}());
var SocketManager = /** @class */ (function () {
    function SocketManager(game) {
        this.game = game;
    }
    SocketManager.ADDRESS = "127.0.0.1";
    SocketManager.PORT = 5555;
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
        BABYLON.SceneLoader.LoadAssetContainer("./assets/", "chungus.glb", scene, function (container) {
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
    Stage.GROUND_COLOR = new BABYLON.Color3(0, 0.75, 0);
    Stage.SELECTION_ELEVATION = 0.2;
    Stage.SIZE = 100;
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
