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
        for (var i = 0, len = BlocCollection.PATHS.length; i < len; i++) {
            id = this.blocs.length;
            cur = BABYLON.MeshBuilder.CreateBox("originalBloc" + id, { size: 1 }, scene);
            material = new BABYLON.StandardMaterial("blocMaterial" + id, scene);
            material.diffuseTexture = new BABYLON.Texture(BlocCollection.PATHS[i], scene);
            cur.material = material;
            cur.isVisible = false;
            this.blocs.push(cur);
        }
    }
    BlocCollection.ID_STRING = "blocInstance";
    BlocCollection.PATHS = [
        "/assets/texture.png"
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
        this.socketManager = new SocketManager(this);
        this.teams = new Map();
        this.render = function () {
            _this.stage.render();
            _this.scene.render();
        };
        this.canvas = canvas;
        this.engine = new BABYLON.Engine(this.canvas, true);
        this.scene = new BABYLON.Scene(this.engine);
        this.stage = new Stage(this.scene);
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
    Game.prototype.addTeam = function (name) {
        this.teams.set(name, new Team(name));
    };
    Game.prototype.setup = function (size) {
        Game.size = size;
        this.stage.createGround(size.x, size.y);
        this.camera.setTarget(new BABYLON.Vector3(size.x / 2, 0, size.y / 2));
    };
    Game.prototype.getStage = function () {
        return (this.stage);
    };
    return Game;
}());
var MeshBuilder = /** @class */ (function () {
    function MeshBuilder(modelName, scene) {
        var _this = this;
        this.nbClones = 0;
        this.load = function (meshes) {
            _this.mesh = meshes[0];
            _this.mesh.scaling = new BABYLON.Vector3(0.35, 0.35, 0.35);
            _this.mesh.position.y = 0.5;
            _this.mesh.isVisible = false;
        };
        this.ID = modelName;
        BABYLON.SceneLoader.ImportMesh("", "/assets/", modelName, scene, this.load);
    }
    MeshBuilder.prototype.getInstance = function () {
        var output;
        output = this.mesh.createInstance(this.ID + this.nbClones);
        output.isVisible = true;
        this.nbClones++;
        return (output);
    };
    return MeshBuilder;
}());
var Player = /** @class */ (function () {
    function Player() {
    }
    return Player;
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
                if (_this.commands.get(cur[0]))
                    _this.commands.get(cur[0])(cur);
            }
        };
        this.bct = function (datas) {
            _this.game.getStage().addTile(datas);
        };
        this.msz = function (datas) {
            var vector = new BABYLON.Vector2(0, 0);
            vector.x = parseInt(datas[1]);
            vector.y = parseInt(datas[2]);
            _this.game.setup(vector);
        };
        this.sgt = function (datas) {
            Game.timeUnit = parseInt(datas[1]);
        };
        this.tna = function (datas) {
            _this.game.addTeam(datas[1]);
        };
        this.game = game;
        this.initialise();
        this.socket.emit("data", "GRAPHIC\n");
        this.socket.on("data", this.getDatas);
    }
    SocketManager.prototype.initialise = function () {
        this.commands.set("bct", this.bct);
        this.commands.set("msz", this.msz);
        this.commands.set("sgt", this.sgt);
        this.commands.set("tna", this.tna);
    };
    return SocketManager;
}());
var Stage = /** @class */ (function () {
    function Stage(scene) {
        var _this = this;
        this.blocs = new Array();
        this.tiles = new Array();
        this.onPointerDown = function (event) {
            var picked = _this.SCENE.pick(event.clientX, event.clientY);
            if (!picked || !picked.hit)
                return;
            picked.pickedMesh.position.y -= 0.1;
            if (_this.selected)
                _this.selected.position.y += 0.1;
            _this.selected = picked.pickedMesh;
        };
        var lightDir = new BABYLON.Vector3(0, 1, 0);
        this.CHUNGUS = new MeshBuilder("chungus.glb", scene);
        this.CANVAS = scene.getEngine().getRenderingCanvas();
        this.SCENE = scene;
        this.blocCollection = new BlocCollection(scene);
        this.light = new BABYLON.HemisphericLight("light", lightDir, scene);
        this.light.diffuse = new BABYLON.Color3(1, 1, 1);
        this.light.specular = new BABYLON.Color3(0, 0, 0);
        window.addEventListener("pointerdown", this.onPointerDown);
    }
    Stage.prototype.addTile = function (datas) {
        var tile;
        var stats = new Array();
        var index;
        if (this.updateTile(datas))
            return;
        for (var i = 3; i < datas.length; i++) {
            stats.push(parseInt(datas[i]));
        }
        tile = new Tile(stats[0], stats[1], stats[2], stats[3], stats[4], stats[5], stats[6], this.SCENE);
        tile.initialise(parseInt(datas[1]), parseInt(datas[2]));
        tile.startAnimations(this.SCENE);
        this.tiles.push(tile);
    };
    Stage.prototype.createGround = function (width, height) {
        var cur;
        for (var i = width; i >= 0; i--) {
            for (var j = height; j >= 0; j--) {
                cur = this.blocCollection.getInstance(0);
                cur.position.x = i;
                cur.position.z = j;
                this.blocs.push(cur);
            }
        }
    };
    Stage.prototype.updateTile = function (datas) {
        var position = new BABYLON.Vector2(parseInt(datas[1]), parseInt(datas[2]));
        var stats = new Array();
        var tile;
        tile = this.tiles.find(function (tile) {
            return (position.equals(tile.getPosition()));
        });
        if (tile == undefined)
            return (false);
        for (var i = 3; i < datas.length; i++) {
            stats.push(parseInt(datas[i]));
        }
        tile.update(stats[0], stats[1], stats[2], stats[3], stats[4], stats[5], stats[6]);
        return (true);
    };
    Stage.prototype.render = function () {
    };
    return Stage;
}());
var Team = /** @class */ (function () {
    function Team(name) {
        this.players = new Array();
        this.NAME = name;
    }
    Team.prototype.addPlayer = function (player) {
        this.players.push(player);
    };
    return Team;
}());
var Tile = /** @class */ (function () {
    function Tile(food, linemate, deraumere, sibur, mendiane, phiras, thystame, scene) {
        this.stats = new Map();
        this.sprites = new Array();
        var size = Game.size.x * Game.size.y * 7;
        this.update(food, linemate, deraumere, sibur, mendiane, phiras, thystame);
        this.createAnimation();
        if (!Tile.spriteManager)
            Tile.spriteManager = new BABYLON.SpriteManager("spriteManager" + Tile.nb, "/assets/resources.png", size, 16, scene);
        Tile.nb++;
    }
    Tile.prototype.createAnimation = function () {
        var keys = new Array();
        var rnd = Math.random() * Tile.ANIMATION_BUMP;
        this.animation = new BABYLON.Animation("tileAnimation" + Tile.nb, "position.y", Tile.ANIMATION_FPS, BABYLON.Animation.ANIMATIONTYPE_FLOAT, BABYLON.Animation.ANIMATIONLOOPMODE_CYCLE);
        keys.push({
            frame: 0,
            value: Tile.Y
        });
        keys.push({
            frame: Tile.ANIMATION_FPS,
            value: Tile.Y - Tile.ANIMATION_BUMP / 2 + rnd
        });
        keys.push({
            frame: Tile.ANIMATION_FPS * 2,
            value: Tile.Y
        });
        this.animation.setKeys(keys);
    };
    Tile.prototype.generate = function (nb, type) {
        var ID = "tile" + Tile.nb + "-" + type;
        var sprite;
        for (var i = 0; i < nb; i++) {
            sprite = new BABYLON.Sprite(ID, Tile.spriteManager);
            sprite.cellIndex = type;
            sprite.isPickable = false;
            sprite.position.x = this.position.x + Math.random();
            sprite.position.y = Tile.Y;
            sprite.position.z = this.position.y + Math.random();
            sprite.size = 0.5;
            sprite.animations = [];
            sprite.animations.push(this.animation);
            this.sprites.push(sprite);
        }
    };
    Tile.prototype.destroy = function () {
        var cur;
        while (this.sprites.length > 0) {
            cur = this.sprites.pop();
            cur.dispose();
        }
    };
    Tile.prototype.initialise = function (x, y) {
        var ENTRIES = new Array("food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame");
        this.position = new BABYLON.Vector2(x, y);
        for (var i = ENTRIES.length - 1; i >= 0; i--) {
            this.generate(this.stats.get(ENTRIES[i]), i);
        }
    };
    Tile.prototype.startAnimations = function (scene) {
        for (var i = this.sprites.length - 1; i >= 0; i--) {
            scene.beginAnimation(this.sprites[i], 0, Tile.ANIMATION_FPS * 2, true);
        }
    };
    Tile.prototype.update = function (food, linemate, deraumere, sibur, mendiane, phiras, thystame) {
        this.stats.set("food", food);
        this.stats.set("linemate", linemate);
        this.stats.set("deraumere", deraumere);
        this.stats.set("sibur", sibur);
        this.stats.set("mendiane", mendiane);
        this.stats.set("phiras", phiras);
        this.stats.set("thystame", thystame);
        this.destroy();
        if (this.position)
            this.initialise(this.position.x, this.position.y);
    };
    Tile.prototype.getPosition = function () {
        return (this.position);
    };
    Tile.Y = 0.75;
    Tile.ANIMATION_BUMP = 0.15;
    Tile.ANIMATION_FPS = 10;
    Tile.nb = 0;
    Tile.spriteManager = null;
    return Tile;
}());
