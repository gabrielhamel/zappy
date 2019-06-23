/// <reference path="../node_modules/babylonjs/babylon.module.d.ts" />
/// <reference path="../node_modules/babylonjs-gltf2interface/babylon.glTF2Interface.d.ts" />
/// <reference path="../node_modules/babylonjs-loaders/babylonjs.loaders.module.d.ts" />
function main() {
    var game = new Game();
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
        // this.camera.panningSensibility = 0;
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
        this.login = document.getElementById("login");
        this.play = document.getElementById("play");
        this.tchat = document.getElementById("tchat-form");
        this.send = document.getElementById("send");
        this.inventoryUI = document.getElementById("player-info");
        this.ui = document.getElementById("ui");
        this.forward = document.getElementById("forward");
        this.turnLeft = document.getElementById("turn-left");
        this.turnRight = document.getElementById("turn-right");
        this.waiter = document.getElementById("waiter");
        this.take = new Array();
        this.drop = new Array();
        this.inventorySpan = new Array();
        this.free = true;
        this.converterArray = new Array("food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame");
        this.inventory = new Array(7, 0, 0, 0, 0, 0, 0);
        this.lastItem = 0;
        this.inventoryBtn = document.getElementById("inventory");
        this.eject = document.getElementById("eject");
        this.egg = document.getElementById("egg");
        this.incantation = document.getElementById("incantation");
        this.handleConnection = function (datas) {
            console.log(datas);
            if (!(datas[0] == "ko")) {
                _this.ui.style.display = "block";
                _this.tchat.style.display = "block";
                _this.inventoryUI.style.display = "flex";
                _this.login.style.display = "none";
                _this.responseHandler = _this.handleNothing;
            }
            else {
                _this.socketManager.emit("play", "dead\n");
            }
        };
        this.handleTake = function (datas) {
            _this.responseHandler = _this.handleNothing;
            if (datas[0] == "ok")
                _this.inventory[_this.lastItem]++;
            _this.allowInput();
            _this.updateInventory(_this.lastItem);
        };
        this.handleDrop = function (datas) {
            _this.responseHandler = _this.handleNothing;
            if (datas[0] == "ok")
                _this.inventory[_this.lastItem]--;
            _this.allowInput();
            _this.updateInventory(_this.lastItem);
        };
        this.handleInventory = function (datas) {
            _this.responseHandler = _this.handleNothing;
            if (datas.length != 16)
                return;
            for (var i = 0; i < 6; i++) {
                var tmp = datas[2 + i * 2].substr(0, datas[2 + i * 2].length - 1);
                _this.inventory[i] = parseInt(tmp);
            }
            _this.inventory[6] = parseInt(datas[14]);
            _this.allowInput();
            for (var j = 0; j < 7; j++)
                _this.updateInventory(j);
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
        this.tchat.style.display = "none";
        this.inventoryUI.style.display = "none";
        this.play.addEventListener("click", function () {
            var temp = _this.login.getElementsByTagName("select")[0].selectedOptions;
            _this.teamName = temp.item(0).value;
            _this.socketManager.emit("requestPlay", _this.teamName + "\n");
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
        this.send.addEventListener("click", function () {
            if (_this.free == true) {
                var msg = _this.tchat.getElementsByTagName("input")[0].value;
                if (msg.length < 2)
                    return;
                _this.socketManager.emit("play", "Broadcast " + msg + "\n");
                _this.tchat.getElementsByTagName("input")[0].value = "";
                _this.blockInput();
            }
        });
        var _loop_1 = function (i) {
            this_1.drop.push(document.getElementById("drop-" + i));
            this_1.drop[i].addEventListener("click", function () {
                if (_this.free == true) {
                    _this.lastItem = i;
                    _this.responseHandler = _this.handleDrop;
                    socketManager.emit("play", "Set " + _this.converterArray[i] + "\n");
                    _this.blockInput();
                }
            });
        };
        var this_1 = this;
        for (var i = 0; i < 7; i++) {
            _loop_1(i);
        }
        var _loop_2 = function (i) {
            this_2.take.push(document.getElementById("take-" + i));
            this_2.take[i].addEventListener("click", function () {
                if (_this.free == true) {
                    _this.lastItem = i;
                    _this.responseHandler = _this.handleTake;
                    socketManager.emit("play", "Take " + _this.converterArray[i] + "\n");
                    _this.blockInput();
                }
            });
        };
        var this_2 = this;
        for (var i = 0; i < 7; i++) {
            _loop_2(i);
        }
        for (var i = 0; i < 7; i++) {
            this.inventorySpan.push(document.getElementById("inv-" + i));
        }
        this.eject.addEventListener("click", function () {
            if (_this.free == true) {
                _this.socketManager.emit("play", "Eject\n");
                _this.blockInput();
            }
        });
        this.egg.addEventListener("click", function () {
            if (_this.free == true) {
                _this.socketManager.emit("play", "Fork\n");
                _this.blockInput();
            }
        });
        this.incantation.addEventListener("click", function () {
            if (_this.free == true) {
                _this.socketManager.emit("play", "Incantation\n");
                _this.blockInput();
            }
        });
        this.inventoryBtn.addEventListener("click", function () {
            if (_this.free == true) {
                _this.responseHandler = _this.handleInventory;
                _this.socketManager.emit("play", "Inventory\n");
                _this.blockInput();
            }
        });
    }
    Controller.prototype.updateInventory = function (i) {
        this.inventorySpan[i].innerHTML = this.inventory[i].toString();
    };
    Controller.prototype.blockInput = function () {
        this.forward.disabled = true;
        this.turnLeft.disabled = true;
        this.turnRight.disabled = true;
        this.send.disabled = true;
        for (var i = 0; i < 7; i++) {
            this.drop[i].disabled = true;
            this.take[i].disabled = true;
        }
        this.waiter.style.display = "inline-block";
        this.free = false;
    };
    Controller.prototype.allowInput = function () {
        this.forward.disabled = false;
        this.turnLeft.disabled = false;
        this.turnRight.disabled = false;
        this.send.disabled = false;
        for (var i = 0; i < 7; i++) {
            this.drop[i].disabled = false;
            this.take[i].disabled = false;
        }
        this.waiter.style.display = "none";
        this.free = true;
    };
    Controller.prototype.die = function () {
        this.ui.style.display = "none";
        this.tchat.style.display = "none";
        this.login.style.display = "block";
        this.inventoryUI.style.display = "none";
        this.responseHandler = this.handleConnection;
    };
    Controller.prototype.handleResponse = function (datas) {
        this.responseHandler(datas);
    };
    return Controller;
}());
var Egg = /** @class */ (function () {
    function Egg(id, x, y, teamName, skin, scene) {
        this.maturity = false;
        this.x = x;
        this.y = y;
        this.teamName = teamName;
        this.skin = skin;
        this.skin.setPosition(new BABYLON.Vector3(x, 0.5, y));
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
        this.tchat = new Tchat();
        this.teamList = document.getElementById("team-list");
        this.select = document.getElementById("login-select");
        this.render = function () {
            _this.stage.render();
            _this.scene.render();
        };
        this.canvas = document.getElementsByTagName("canvas")[0];
        this.engine = new BABYLON.Engine(this.canvas, true);
        this.scene = new BABYLON.Scene(this.engine);
        this.scene.collisionsEnabled = true;
        this.EGG = new MeshBuilder("egg.obj", this.scene);
        this.CHUNGUS = new MeshBuilder("chungus.obj", this.scene, function () {
            _this.stage = new Stage(_this.scene);
            _this.camera = new Camera(_this.scene);
            _this.socketManager = new SocketManager(_this);
            _this.initialiseScene();
            _this.engine.runRenderLoop(_this.render);
        });
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
                return this.chungus[i];
        }
        return (undefined);
    };
    Game.prototype.getEggById = function (id) {
        for (var i = 0; i < this.eggs.length; i++) {
            if (id == this.eggs[i].getId())
                return this.eggs[i];
        }
        return (undefined);
    };
    Game.prototype.composeMsg = function (index, datas) {
        var res = "";
        for (var i = index; i < datas.length; i++)
            res = res + " " + datas[i];
        return res;
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
        var newTeam = document.createElement("li");
        newTeam.innerHTML = name;
        this.teamList.append(newTeam);
        var newOption = document.createElement("option");
        newOption.innerHTML = name;
        newOption.value = name;
        this.select.append(newOption);
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
        var msg = this.composeMsg(3, datas);
        voicingChungus.setMessage(msg);
        this.tchat.addMessage(voicingChungus.getTeamName(), datas[1], msg);
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
        var egg = new Egg(parseInt(datas[1]), parseInt(datas[3]), parseInt(datas[4]), accouchingChungus.getTeamName(), this.EGG.getInstance(), this.scene);
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
    function MeshBuilder(modelName, scene, onLoad) {
        var _this = this;
        if (onLoad === void 0) { onLoad = undefined; }
        this.nbClones = 0;
        this.load = function (meshes) {
            _this.meshes = meshes;
            for (var i = _this.meshes.length - 1; i >= 0; i--) {
                _this.meshes[i].scaling = new BABYLON.Vector3(0.35, 0.35, 0.35);
                _this.meshes[i].position.y = 0.5;
                _this.meshes[i].isVisible = false;
            }
            if (_this.onLoad)
                _this.onLoad();
        };
        this.ID = modelName;
        this.onLoad = onLoad;
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
    function SocketManager(game) {
        var _this = this;
        this.socket = io();
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
            _this.GAME.getStage().addTile(datas);
        };
        this.msz = function (datas) {
            var vector = new BABYLON.Vector2(0, 0);
            vector.x = parseInt(datas[1]);
            vector.y = parseInt(datas[2]);
            _this.GAME.setup(vector);
        };
        this.sgt = function (datas) {
            Game.timeUnit = parseInt(datas[1]);
        };
        this.tna = function (datas) {
            _this.GAME.addTeam(datas[1]);
        };
        this.pnw = function (datas) {
            _this.GAME.addChungus(datas);
        };
        this.ppo = function (datas) {
            _this.GAME.updateChungusPos(datas);
        };
        this.plv = function (datas) {
            _this.GAME.lvlUpChungus(datas);
        };
        this.pin = function (datas) {
            _this.GAME.chungusBag(datas);
        };
        this.pex = function (datas) {
            /// NEED GABI
        };
        this.pbc = function (datas) {
            _this.GAME.chungusYelling(datas);
        };
        this.pic = function (datas) {
            /// NEED GABI
        };
        this.pie = function (datas) {
            /// NEED GABI
        };
        this.pfk = function (datas) {
            _this.GAME.chungusLaying(datas);
        };
        this.pdr = function (datas) {
            _this.GAME.chungusDroping(datas);
        };
        this.pgt = function (datas) {
            _this.GAME.chungusTaking(datas);
        };
        this.pdi = function (datas) {
            _this.GAME.removeChungus(datas);
        };
        this.enw = function (datas) {
            _this.GAME.chungusAccouching(datas);
        };
        this.eht = function (datas) {
            _this.GAME.maturingEgg(datas);
        };
        this.ebo = function (datas) {
            _this.GAME.hatchingEgg(datas);
        };
        this.edi = function (datas) {
            _this.GAME.dyingEgg(datas);
        };
        this.nth = function (datas) {
            //ne doit rien faire
        };
        this.elv = function (datas) {
            _this.controller.blockInput();
        };
        this.die = function (datas) {
            _this.controller.die();
        };
        this.GAME = game;
        this.controller = new Controller(this.GAME, this);
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
        this.commandsPlay.set("dead", this.die);
    };
    SocketManager.prototype.emit = function (event, datas) {
        this.socket.emit(event, datas);
    };
    return SocketManager;
}());
var Sound = /** @class */ (function () {
    function Sound(src) {
        this.audio = document.createElement("audio");
        this.audio.src = src;
        this.audio.setAttribute("preload", "auto");
        this.audio.setAttribute("controls", "none");
        this.audio.style.display = "none";
        document.body.appendChild(this.audio);
    }
    Sound.prototype.stop = function () {
        this.audio.pause();
    };
    Sound.prototype.play = function () {
        this.audio.currentTime = 0;
        this.audio.play();
    };
    return Sound;
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
var Tchat = /** @class */ (function () {
    function Tchat() {
        this.msgs = new Array();
    }
    Tchat.prototype.addMessage = function (teamName, id, msg) {
        var tchat = document.getElementById("tchat-list");
        var newMsg = document.createElement("li");
        newMsg.innerHTML = "<strong> [" + teamName + " - " + id + "]</strong> " + msg;
        tchat.append(newMsg);
        var msgs = tchat.getElementsByTagName("li");
        if (msgs.length > 8) {
            msgs[2].classList.add("fade-out-second-last");
        }
        if (msgs.length > 9) {
            msgs[1].classList.add("fade-out");
            msgs[1].classList.remove("fade-out-second-last");
        }
        if (msgs.length > 10)
            msgs[0].remove();
    };
    return Tchat;
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
            sprite.size = 0.35;
            sprite.animations = [];
            sprite.animations.push(this.animation);
            this.sprites.push(sprite);
        }
    };
    Tile.prototype.updateDisplay = function () {
        this.destroy();
        if (this.position)
            this.initialise(this.position.x, this.position.y);
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
        this.updateDisplay();
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
        this.updateDisplay();
    };
    Tile.prototype.removeItem = function (item) {
        var convertArray = new Array("food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame");
        this.stats.set(convertArray[item], this.stats.get(convertArray[item]) - 1);
        this.updateDisplay();
    };
    Tile.ANIMATION_BUMP = 0.15;
    Tile.ANIMATION_FPS = 10;
    Tile.SPREAD = 0.4;
    Tile.Y = 0.75;
    Tile.nb = 0;
    Tile.spriteManager = null;
    return Tile;
}());
