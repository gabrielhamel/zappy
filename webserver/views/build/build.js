function main() {
    var canvas = document.getElementsByTagName("canvas")[0];
    var game = new Game(canvas);
}
document.addEventListener("DOMContentLoaded", main);
var Camera = /** @class */ (function () {
    function Camera(scene) {
        var _this = this;
        this.focus = true;
        this.shiftingSpeedX = 0;
        this.shiftingSpeedZ = 0;
        this.managePointerState = function (mouse) {
            _this.lastMovement = new BABYLON.Vector2(mouse.screenX, mouse.screenY);
            if (mouse.type == "pointerdown")
                window.addEventListener("pointermove", _this.moveFromPointer);
            else
                window.removeEventListener("pointermove", _this.moveFromPointer);
        };
        this.moveFromPointer = function (mouse) {
            var coeff = Camera.MOUSE_SPEED * _this.camera.position.y / 120;
            _this.shiftingSpeedX = (mouse.screenY - _this.lastMovement.y) * coeff;
            _this.shiftingSpeedZ = (mouse.screenX - _this.lastMovement.x) * coeff;
            _this.lastMovement = new BABYLON.Vector2(mouse.screenX, mouse.screenY);
        };
        this.zoom = function (event) {
            if (!event.deltaY || (_this.camera.position.y <= 10 && event.deltaY < 0))
                return;
            _this.camera.position.y += event.deltaY * Camera.ZOOM_SPEED;
            if (_this.camera.position.y < 10)
                _this.camera.position.y = 10;
        };
        this.isNearFromBorders = function () {
            if (_this.camera.position.x >= 110) {
                _this.camera.position.x -= 1;
                _this.shiftingSpeedX = 0;
                return (false);
            }
            if (_this.camera.position.x <= Camera.TARGET.x) {
                _this.camera.position.x = Camera.TARGET.x + 1;
                _this.shiftingSpeedX = 0;
                return (false);
            }
            if (_this.camera.position.z >= 80) {
                _this.camera.position.z -= 1;
                _this.shiftingSpeedZ = 0;
                return (false);
            }
            if (_this.camera.position.z <= 20) {
                _this.camera.position.z = 21;
                _this.shiftingSpeedZ = 0;
                return (false);
            }
            return (true);
        };
        this.render = function (keyboard, elapsedTime) {
            if (!_this.isNearFromBorders())
                return;
            _this.moveFromKeyboard(keyboard, elapsedTime);
            _this.camera.position.x -= _this.shiftingSpeedX;
            _this.camera.position.z -= _this.shiftingSpeedZ;
            if (_this.shiftingSpeedX < 0.01 && _this.shiftingSpeedX > -0.01)
                _this.shiftingSpeedX = 0;
            if (_this.shiftingSpeedZ < 0.01 && _this.shiftingSpeedZ > -0.01)
                _this.shiftingSpeedZ = 0;
            _this.shiftingSpeedX -= _this.shiftingSpeedX > 0 ? 0.0001 * _this.camera.position.y : 0;
            _this.shiftingSpeedX += _this.shiftingSpeedX < 0 ? 0.0001 * _this.camera.position.y : 0;
            _this.shiftingSpeedZ -= _this.shiftingSpeedZ > 0 ? 0.0001 * _this.camera.position.y : 0;
            _this.shiftingSpeedZ += _this.shiftingSpeedZ < 0 ? 0.0001 * _this.camera.position.y : 0;
        };
        this.moveFromKeyboard = function (keyboard, elapsedTime) {
            var speed = Camera.KEYBOARD_SPEED * (elapsedTime / 1000) * _this.camera.position.y / 100;
            if (!_this.focus)
                return;
            _this.shiftingSpeedZ += keyboard.getKey(Keyboard.LEFT) ? speed : 0;
            _this.shiftingSpeedZ -= keyboard.getKey(Keyboard.RIGHT) ? speed : 0;
            _this.shiftingSpeedX += keyboard.getKey(Keyboard.UP) ? speed : 0;
            _this.shiftingSpeedX -= keyboard.getKey(Keyboard.DOWN) ? speed : 0;
        };
        var position = new BABYLON.Vector3(50, 30, 50);
        this.camera = new BABYLON.UniversalCamera("mainCamera", position, scene);
        this.camera.setTarget(Camera.TARGET);
        window.addEventListener("pointerdown", this.managePointerState);
        window.addEventListener("pointerup", this.managePointerState);
        window.addEventListener("wheel", this.zoom);
        window.addEventListener("mousewheel", this.zoom);
        window.addEventListener("DOMMouseScroll", this.zoom);
    }
    Camera.prototype.setFocus = function (focus) {
        this.focus = focus;
    };
    Camera.TARGET = new BABYLON.Vector3(30, 0, 50);
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
            _this.camera.render(_this.keyboard, _this.engine.getDeltaTime());
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
        this.light.diffuse = new BABYLON.Color3(1, 1, 1);
        this.light.specular = new BABYLON.Color3(0, 0, 0);
        window.addEventListener("pointerdown", this.onPointerDown);
    }
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
