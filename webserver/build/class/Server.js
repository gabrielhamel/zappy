"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var express = require("express");
var socketio = require("socket.io");
var Socket_1 = require("./Socket");
var Server = /** @class */ (function () {
    function Server(port) {
        var _this = this;
        this.app = express();
        this.sockets = new Array();
        this.initialise = function (err) {
            if (err) {
                console.error(err);
                return;
            }
            console.log("Server is listening on port " + _this.port + ".");
        };
        this.port = port;
        this.server = this.app.listen(this.initialise);
        this.io = socketio(this.server);
    }
    Server.prototype.handleSocketConnection = function (socket) {
        this.sockets.push(new Socket_1.default(socket));
    };
    return Server;
}());
exports.default = Server;
