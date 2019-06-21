/// <reference path="../node_modules/babylonjs/babylon.module.d.ts" />
/// <reference path="../node_modules/babylonjs-gltf2interface/babylon.glTF2Interface.d.ts" />
/// <reference path="../node_modules/babylonjs-loaders/babylonjs.loaders.module.d.ts" />
function main() {
    // let game:Game = new Game();
    var sockManager = new SocketManager();
}
function middleRand(value) {
    return (value - Math.random() * (value * 2));
}
document.addEventListener("DOMContentLoaded", main);
var BerkMesh = /** @class */ (function () {
    function BerkMesh(meshes) {
        this.MESHES = meshes;
    }
    BerkMesh.prototype.setPosition = function (position) {
        for (var i = this.MESHES.length - 1; i >= 0; i--)
            this.MESHES[i].position = position;
    };
    BerkMesh.prototype.setRotation = function (angle) {
        for (var i = this.MESHES.length - 1; i >= 0; i--)
            this.MESHES[i].rotation.y = angle;
    };
    BerkMesh.prototype.dispose = function () {
        for (var i = this.MESHES.length - 1; i >= 0; i--)
            this.MESHES[i].dispose();
    };
    return BerkMesh;
}());
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
            output.checkCollisions = true;
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
        this.camera.allowUpsideDown = false;
        this.camera.checkCollisions = true;
        this.camera.panningSensibility = 0;
        this.camera.collisionRadius = new BABYLON.Vector3(1, 1, 1);
        this.camera.attachControl(scene.getEngine().getRenderingCanvas(), false);
    }
    Camera.prototype.setTarget = function (target) {
        this.camera.setTarget(target);
    };
    Camera.KEYBOARD_SPEED = 10;
    Camera.MOUSE_SPEED = 1 / 20;
    Camera.ZOOM_SPEED = 1 / 10;
    return Camera;
}());
var Controller = /** @class */ (function () {
    function Controller(game, socketManager) {
        var _this = this;
        this.form = document.getElementById("login");
        this.play = document.getElementById("play");
        this.ui = document.getElementById("ui");
        this.forward = document.getElementById("forward");
        this.turnLeft = document.getElementById("turn-left");
        this.turnRight = document.getElementById("turn-right");
        this.grab = document.getElementById("grab");
        this.drop = document.getElementById("drop");
        this.free = true;
        this.handleConnection = function (datas) {
            console.log(datas);
            if (!(datas[0] == "ko")) {
                _this.ui.style.display = "block";
                _this.form.style.display = "none";
                _this.responseHandler = _this.handleNothing;
            }
            else {
                _this.socketManager.emit("play", "dead\n");
            }
        };
        this.handleNothing = function (datas) {
            console.log("message reçu mais pas traité");
            console.log(datas);
            _this.allowInput();
        };
        this.responseHandler = this.handleConnection;
        this.game = game;
        this.socketManager = socketManager;
        this.ui.style.display = "none";
        this.play.addEventListener("click", function () {
            _this.teamName = _this.form.getElementsByTagName("input")[0].value;
            _this.socketManager.emit("requestPlay", _this.teamName + '\n');
        });
        this.forward.addEventListener("click", function () {
            if (_this.free == true) {
                socketManager.emit("play", "Forward\n");
                _this.blockInput();
            }
        });
        this.turnLeft.addEventListener("click", function () {
            if (_this.free == true) {
                socketManager.emit("play", "Left\n");
                _this.blockInput();
            }
        });
        this.turnRight.addEventListener("click", function () {
            if (_this.free == true) {
                socketManager.emit("play", "Right\n");
                _this.blockInput();
            }
        });
    }
    Controller.prototype.blockInput = function () {
        this.forward.disabled = true;
        this.turnLeft.disabled = true;
        this.turnRight.disabled = true;
        this.grab.disabled = true;
        this.drop.disabled = true;
        this.free = false;
    };
    Controller.prototype.allowInput = function () {
        this.forward.disabled = false;
        this.turnLeft.disabled = false;
        this.turnRight.disabled = false;
        this.grab.disabled = false;
        this.drop.disabled = false;
        this.free = true;
    };
    Controller.prototype.handleResponse = function (datas) {
        this.responseHandler(datas);
    };
    return Controller;
}());
var Egg = /** @class */ (function () {
    function Egg(id, x, y, teamName, scene) {
        this.maturity = false;
        this.x = x;
        this.y = y;
        this.teamName = teamName;
    }
    Egg.prototype.setMaturity = function (maturity) {
        this.maturity = maturity;
    };
    Egg.prototype.getId = function () {
        return (this.id);
    };
    Egg.prototype.getMaturity = function () {
        return (this.maturity);
    };
    return Egg;
}());
var Game = /** @class */ (function () {
    function Game() {
        var _this = this;
        this.chungus = new Array();
        this.eggs = new Array();
        this.teamsNames = new Array();
        this.render = function () {
            _this.stage.render();
            _this.scene.render();
        };
        this.canvas = document.getElementsByTagName("canvas")[0];
        this.engine = new BABYLON.Engine(this.canvas, true);
        this.scene = new BABYLON.Scene(this.engine);
        this.scene.collisionsEnabled = true;
        this.stage = new Stage(this.scene);
        this.camera = new Camera(this.scene);
        this.CHUNGUS = new MeshBuilder("chungus.glb", this.scene);
        this.initialiseScene();
        this.engine.runRenderLoop(this.render);
    }
    Game.prototype.initialiseScene = function () {
        var _this = this;
        window.addEventListener("resize", function () {
            _this.engine.resize();
        });
    };
    Game.prototype.getBigChungusById = function (id) {
        for (var i = 0; i < this.chungus.length; i++) {
            if (id == this.chungus[i].getId())
                return this.chungus[0];
        }
        return (undefined);
    };
    Game.prototype.getEggById = function (id) {
        for (var i = 0; i < this.eggs.length; i++) {
            if (id == this.eggs[i].getId())
                return this.eggs[0];
        }
        return (undefined);
    };
    Game.prototype.setup = function (size) {
        Game.size = size;
        this.stage.createGround(size.x, size.y);
        this.camera.setTarget(new BABYLON.Vector3(size.x / 2, 0, size.y / 2));
    };
    Game.prototype.getStage = function () {
        return (this.stage);
    };
    Game.prototype.addTeam = function (name) {
        this.teamsNames.push(name);
    };
    Game.prototype.addChungus = function (datas) {
        if (datas.length < 7) {
            console.log("Not enough arguments to summon the big Chungus... CHUNG CHUNG CHUNG");
            console.log(datas);
            return;
        }
        if (this.getBigChungusById(parseInt(datas[1]))) {
            console.log("You can't clone the big unfamous big chungus !!!");
            console.log(datas);
            return;
        }
        var chungus = new Player(parseInt(datas[1]), datas[6], this.CHUNGUS.getInstance(), this.scene);
        chungus.setPos(parseInt(datas[2]), parseInt(datas[3]));
        chungus.setOri(parseInt(datas[4]));
        chungus.setLvl(parseInt(datas[5]));
        this.chungus.push(chungus);
    };
    Game.prototype.updateChungusPos = function (datas) {
        if (datas.length < 5) {
            console.log("Not enough arguments to move the big Chungus... CHUNG CHUNG CHUNG");
            console.log(datas);
            return;
        }
        var movingChungus = this.getBigChungusById(parseInt(datas[1]));
        if (!movingChungus) {
            console.log("This chungus doesn't exist");
            console.log(datas);
            return;
        }
        movingChungus.setPos(parseInt(datas[2]), parseInt(datas[3]));
        movingChungus.setOri(parseInt(datas[4]));
    };
    Game.prototype.lvlUpChungus = function (datas) {
        if (datas.length < 3) {
            console.log("Not enough arguments to upgrade the big Chungus... CHUNG CHUNG CHUNG");
            console.log(datas);
            return;
        }
        var levelingChungus = this.getBigChungusById(parseInt(datas[1]));
        if (!levelingChungus) {
            console.log("This chungus doesn't exist");
            console.log(datas);
            return;
        }
        levelingChungus.setLvl(parseInt(datas[2]));
    };
    Game.prototype.chungusBag = function (datas) {
        if (datas.length < 11) {
            console.log("Not enough arguments to fill the big Chungus big bag... CHUNG CHUNG CHUNG");
            console.log(datas);
            return;
        }
        var fillingChungusBag = this.getBigChungusById(parseInt(datas[1]));
        if (!fillingChungusBag) {
            console.log("This chungus doesn't exist");
            console.log(datas);
            return;
        }
        fillingChungusBag.setPos(parseInt(datas[2]), parseInt(datas[3]));
        fillingChungusBag.setBag(parseInt(datas[4]), parseInt(datas[5]), parseInt(datas[6]), parseInt(datas[7]), parseInt(datas[8]), parseInt(datas[9]), parseInt(datas[10]));
    };
    Game.prototype.chungusYelling = function (datas) {
        if (datas.length < 3) {
            console.log("To big Chungus the message isn't big enough");
            console.log(datas);
            return;
        }
        var voicingChungus = this.getBigChungusById(parseInt(datas[1]));
        if (!voicingChungus) {
            console.log("This chungus doesn't exist");
            console.log(datas);
            return;
        }
        voicingChungus.setMessage(datas[2]);
    };
    Game.prototype.chungusLaying = function (datas) {
        if (datas.length < 2) {
            console.log("Not enough arguments to reproduct the big Chungus... CHUNG CHUNG CHUNG");
            console.log(datas);
            return;
        }
        var layingChungus = this.getBigChungusById(parseInt(datas[1]));
        if (!layingChungus) {
            console.log("This chungus doesn't exist");
            console.log(datas);
            return;
        }
        layingChungus.setLayingState(true);
    };
    Game.prototype.chungusDroping = function (datas) {
        if (datas.length < 3) {
            console.log("Not enough arguments to drop the big Chungus... CHUNG CHUNG CHUNG");
            console.log(datas);
            return;
        }
        var dropingChungus = this.getBigChungusById(parseInt(datas[1]));
        if (!dropingChungus) {
            console.log("This chungus doesn't exist");
            console.log(datas);
            return;
        }
        dropingChungus.drop(parseInt(datas[2]));
        var vector = new BABYLON.Vector2(0, 0);
        vector.x = dropingChungus.getX();
        vector.y = dropingChungus.getY();
        var tile = this.stage.findTileByPosition(vector);
        tile.addItem(parseInt(datas[2]));
    };
    Game.prototype.chungusTaking = function (datas) {
        if (datas.length < 3) {
            console.log("Not enough arguments to take the big Chungus... CHUNG CHUNG CHUNG");
            console.log(datas);
            return;
        }
        var gatheringChungus = this.getBigChungusById(parseInt(datas[1]));
        if (!gatheringChungus) {
            console.log("This chungus doesn't exist");
            console.log(datas);
            return;
        }
        gatheringChungus.take(parseInt(datas[2]));
        var vector = new BABYLON.Vector2(0, 0);
        vector.x = gatheringChungus.getX();
        vector.y = gatheringChungus.getY();
        var tile = this.stage.findTileByPosition(vector);
        tile.removeItem(parseInt(datas[2]));
    };
    Game.prototype.removeChungus = function (datas) {
        if (datas.length < 2) {
            console.log("Not enough arguments to kill the big Chungus... CHUNG CHUNG CHUNG");
            console.log(datas);
            return;
        }
        if (!this.getBigChungusById(parseInt(datas[1]))) {
            console.log("This chungus doesn't exist");
            console.log(datas);
            return;
        }
        var i = 0;
        for (; i < this.chungus.length && this.chungus[i].getId() != parseInt(datas[1]); i++)
            ;
        this.chungus[i].die();
        this.chungus.splice(i, 1);
    };
    Game.prototype.chungusAccouching = function (datas) {
        if (datas.length < 5) {
            console.log("Not enough arguments to reproduct the big Chungus... CHUNG CHUNG CHUNG");
            console.log(datas);
            return;
        }
        var accouchingChungus = this.getBigChungusById(parseInt(datas[2]));
        if (!accouchingChungus || this.getEggById(parseInt(datas[1]))) {
            console.log("This chungus doesn't exist or egg already exist");
            console.log(datas);
            return;
        }
        var egg = new Egg(parseInt(datas[1]), parseInt(datas[3]), parseInt(datas[4]), accouchingChungus.getTeamName(), this.scene);
        this.eggs.push(egg);
        accouchingChungus.setLayingState(false);
    };
    Game.prototype.maturingEgg = function (datas) {
        if (datas.length < 2) {
            console.log("Not enough arguments to mature an egg");
            console.log(datas);
            return;
        }
        var egg = this.getEggById(parseInt(datas[1]));
        if (!egg) {
            console.log("This egg doesn't exist");
            console.log(datas);
            return;
        }
        egg.setMaturity(true);
    };
    Game.prototype.hatchingEgg = function (datas) {
        if (datas.length < 2) {
            console.log("Not enough arguments to mature an egg");
            console.log(datas);
            return;
        }
        var egg = this.getEggById(parseInt(datas[1]));
        if (!egg) {
            console.log("This egg doesn't exist");
            console.log(datas);
            return;
        }
        //ANIMATION => fade de l'oeuf
        var i = 0;
        for (; i < this.eggs.length && this.eggs[i].getId() != parseInt(datas[1]); i++)
            ;
        this.eggs.splice(i, 1);
    };
    Game.prototype.dyingEgg = function (datas) {
        if (datas.length < 2) {
            console.log("Not enough arguments to mature an egg");
            console.log(datas);
            return;
        }
        var egg = this.getEggById(parseInt(datas[1]));
        if (!egg) {
            console.log("This egg doesn't exist");
            console.log(datas);
            return;
        }
        //ANIMATION => destruction de l'oeuf
        var i = 0;
        for (; i < this.eggs.length && this.eggs[i].getId() != parseInt(datas[1]); i++)
            ;
        this.eggs.splice(i, 1);
    };
    return Game;
}());
var Infobox = /** @class */ (function () {
    function Infobox() {
        this.tileInfos = document.getElementById("tileInfos");
    }
    Infobox.prototype.updateTile = function (tile) {
        var list = this.tileInfos.getElementsByTagName("span");
        var datas = tile.getRawDatas();
        for (var i = datas.length - 1; i >= 0; i--) {
            list[i * 2 + 1].textContent = "" + datas[i];
        }
    };
    return Infobox;
}());
var MeshBuilder = /** @class */ (function () {
    function MeshBuilder(modelName, scene) {
        var _this = this;
        this.nbClones = 0;
        this.load = function (meshes) {
            _this.meshes = meshes;
            for (var i = _this.meshes.length - 1; i >= 0; i--) {
                _this.meshes[i].scaling = new BABYLON.Vector3(0.35, 0.35, 0.35);
                _this.meshes[i].position.y = 0.5;
                _this.meshes[i].isVisible = false;
            }
        };
        this.ID = modelName;
        BABYLON.SceneLoader.ImportMesh("", "/assets/", modelName, scene, this.load);
    }
    MeshBuilder.prototype.getInstance = function () {
        var meshes = new Array();
        for (var i = this.meshes.length - 1; i >= 0; i--) {
            meshes.push(this.meshes[i].createInstance(this.ID + this.nbClones + "-" + i));
        }
        this.nbClones++;
        return (new BerkMesh(meshes));
    };
    return MeshBuilder;
}());
var Player = /** @class */ (function () {
    function Player(id, teamName, skin, scene) {
        this.bag = new Array();
        this.message = "";
        this.incanting = false;
        this.laying = false;
        this.id = id;
        this.teamName = teamName;
        this.skin = skin;
        for (var i = 0; i < 7; i++)
            this.bag.push(0);
    }
    Player.prototype.setPos = function (x, y) {
        this.x = x;
        this.y = y;
        this.skin.setPosition(new BABYLON.Vector3(x, 0.5, y));
    };
    Player.prototype.setOri = function (o) {
        this.o = o;
        this.skin.setRotation(Math.PI / 2 * (o - 1));
    };
    Player.prototype.setLvl = function (lvl) {
        this.lvl = lvl;
    };
    Player.prototype.setBag = function (food, linemate, deraumere, sibur, mendiane, phiras, thystame) {
        this.bag[0] = food;
        this.bag[1] = linemate;
        this.bag[2] = deraumere;
        this.bag[3] = sibur;
        this.bag[4] = mendiane;
        this.bag[5] = phiras;
        this.bag[6] = thystame;
    };
    Player.prototype.setMessage = function (message) {
        this.message = message;
    };
    Player.prototype.setLayingState = function (state) {
        this.laying = state;
    };
    Player.prototype.getId = function () {
        return (this.id);
    };
    Player.prototype.getX = function () {
        return (this.id);
    };
    Player.prototype.getY = function () {
        return (this.id);
    };
    Player.prototype.getTeamName = function () {
        return (this.teamName);
    };
    Player.prototype.isLaying = function () {
        return (this.laying);
    };
    Player.prototype.drop = function (item) {
        this.bag[item]--;
    };
    Player.prototype.take = function (item) {
        this.bag[item]--;
    };
    Player.prototype.die = function () {
        this.skin.dispose();
    };
    return Player;
}());
var SocketManager = /** @class */ (function () {
    function SocketManager() {
        var _this = this;
        this.socket = io();
        this.game = new Game();
        this.controller = new Controller(this.game, this);
        this.commandsGraph = new Map();
        this.commandsPlay = new Map();
        this.getDatas = function (datas) {
            var array = datas.split("\n");
            var len = array.length;
            var cur;
            for (var i = 0; i < len; i++) {
                cur = array[i].split(" ");
                if (_this.commandsGraph.get(cur[0]))
                    _this.commandsGraph.get(cur[0])(cur);
            }
        };
        this.getPlay = function (datas) {
            var array = datas.split("\n");
            var len = array.length;
            var cur;
            for (var i = 0; i < len; i++) {
                cur = array[i].split(" ");
                if (cur[0] == "")
                    continue;
                if (_this.commandsPlay.get(cur[0])) { // GESTION DES EVENTS
                    _this.commandsPlay.get(cur[0])(cur);
                    continue;
                }
                _this.controller.handleResponse(cur); // GESTION D'UN RETOUR DE CMD
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
        this.pnw = function (datas) {
            _this.game.addChungus(datas);
        };
        this.ppo = function (datas) {
            _this.game.updateChungusPos(datas);
        };
        this.plv = function (datas) {
            _this.game.lvlUpChungus(datas);
        };
        this.pin = function (datas) {
            _this.game.chungusBag(datas);
        };
        this.pex = function (datas) {
            /// NEED GABI
        };
        this.pbc = function (datas) {
            _this.game.chungusYelling(datas);
        };
        this.pic = function (datas) {
            /// NEED GABI
        };
        this.pie = function (datas) {
            /// NEED GABI
        };
        this.pfk = function (datas) {
            _this.game.chungusLaying(datas);
        };
        this.pdr = function (datas) {
            _this.game.chungusDroping(datas);
        };
        this.pgt = function (datas) {
            _this.game.chungusTaking(datas);
        };
        this.pdi = function (datas) {
            _this.game.removeChungus(datas);
        };
        this.enw = function (datas) {
            _this.game.chungusAccouching(datas);
        };
        this.eht = function (datas) {
            _this.game.maturingEgg(datas);
        };
        this.ebo = function (datas) {
            _this.game.hatchingEgg(datas);
        };
        this.edi = function (datas) {
            _this.game.dyingEgg(datas);
        };
        this.nth = function (datas) {
            //ne doit rien faire
        };
        this.elv = function (datas) {
            _this.controller.blockInput();
        };
        this.initialise();
        this.socket.emit("data", "GRAPHIC\n");
        this.socket.on("data", this.getDatas);
        this.socket.on("play", this.getPlay);
    }
    SocketManager.prototype.initialise = function () {
        this.commandsGraph.set("bct", this.bct);
        this.commandsGraph.set("msz", this.msz);
        this.commandsGraph.set("pnw", this.pnw);
        this.commandsGraph.set("sgt", this.sgt);
        this.commandsGraph.set("tna", this.tna);
        this.commandsGraph.set("pnw", this.pnw);
        this.commandsGraph.set("ppo", this.ppo);
        this.commandsGraph.set("plv", this.plv);
        this.commandsGraph.set("plv", this.pin);
        this.commandsGraph.set("pex", this.pex);
        this.commandsGraph.set("pbc", this.pbc);
        this.commandsGraph.set("pic", this.pic);
        this.commandsGraph.set("pie", this.pie);
        this.commandsGraph.set("pfk", this.pfk);
        this.commandsGraph.set("pdr", this.pdr);
        this.commandsGraph.set("pgt", this.pgt);
        this.commandsGraph.set("pdi", this.pdi);
        this.commandsGraph.set("enw", this.enw);
        this.commandsGraph.set("eht", this.eht);
        this.commandsGraph.set("ebo", this.ebo);
        this.commandsGraph.set("edi", this.edi);
        this.commandsPlay.set("WELCOME", this.nth);
        this.commandsPlay.set("Elevation", this.elv);
    };
    SocketManager.prototype.emit = function (event, datas) {
        this.socket.emit(event, datas);
    };
    return SocketManager;
}());
var Stage = /** @class */ (function () {
    function Stage(scene) {
        var _this = this;
        this.blocs = new Array();
        this.infobox = new Infobox();
        this.tiles = new Array();
        this.onPointerDown = function (event) {
            var picked = _this.SCENE.pick(event.clientX, event.clientY);
            var pos;
            var tile;
            if (!picked || !picked.hit)
                return;
            pos = picked.pickedMesh.position;
            picked.pickedMesh.position.y -= 0.1;
            tile = _this.findTileByPosition(new BABYLON.Vector2(pos.x, pos.z));
            if (tile)
                _this.infobox.updateTile(tile);
            if (_this.selected)
                _this.selected.position.y += 0.1;
            _this.selected = picked.pickedMesh;
        };
        var lightDir = new BABYLON.Vector3(0, 1, 0);
        this.CANVAS = scene.getEngine().getRenderingCanvas();
        this.SCENE = scene;
        this.blocCollection = new BlocCollection(scene);
        this.light = new BABYLON.HemisphericLight("light", lightDir, scene);
        this.light.diffuse = new BABYLON.Color3(1, 1, 1);
        this.light.specular = new BABYLON.Color3(0, 0, 0);
        this.CANVAS.addEventListener("pointerdown", this.onPointerDown);
    }
    Stage.prototype.findTileByPosition = function (position) {
        return (this.tiles.find(function (tile) {
            return (position.equals(tile.getPosition()));
        }));
    };
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
        for (var i = width - 1; i >= 0; i--) {
            for (var j = height - 1; j >= 0; j--) {
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
        if (!tile)
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
            sprite.position.x = this.position.x + middleRand(Tile.SPREAD);
            sprite.position.y = Tile.Y;
            sprite.position.z = this.position.y + middleRand(Tile.SPREAD);
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
    Tile.prototype.getRawDatas = function () {
        var output = new Array();
        var it = this.stats.entries();
        var res = it.next();
        while (!res.done) {
            output.push(res.value[1]);
            res = it.next();
        }
        return (output);
    };
    Tile.prototype.addItem = function (item) {
        var convertArray = new Array("food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame");
        this.stats.set(convertArray[item], this.stats.get(convertArray[item]) + 1);
    };
    Tile.prototype.removeItem = function (item) {
        var convertArray = new Array("food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame");
        this.stats.set(convertArray[item], this.stats.get(convertArray[item]) - 1);
    };
    Tile.ANIMATION_BUMP = 0.15;
    Tile.ANIMATION_FPS = 10;
    Tile.SPREAD = 0.4;
    Tile.Y = 0.75;
    Tile.nb = 0;
    Tile.spriteManager = null;
    return Tile;
}());
