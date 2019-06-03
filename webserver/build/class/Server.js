"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var express = require("express");
var path = require("path");
var socketio = require("socket.io");
var Socket_1 = require("./Socket");
var Server = /** @class */ (function () {
    function Server(port) {
        var _this = this;
        this.app = express();
        this.sockets = new Array();
        this.initialise = function () {
            console.log("Server is listening on port " + _this.port + ".");
            _this.app.use(express.static("views"));
            _this.app.get("/", function (req, res) {
                res.sendFile(path.resolve(__dirname + "/../views/index.html"));
            });
        };
        this.port = port;
        this.server = this.app.listen(port, this.initialise);
        this.io = socketio(this.server);
        this.io.on("connection", this.handleSocketConnection);
    }
    Server.prototype.handleSocketConnection = function (socket) {
        this.sockets.push(new Socket_1.default(socket));
    };
    return Server;
}());
exports.default = Server;
