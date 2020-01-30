"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var express = require("express");
var path = require("path");
var socketio = require("socket.io");
var Socket_1 = require("./Socket");
var Server = /** @class */ (function () {
    function Server(port, serverPort) {
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
        this.handleSocketConnection = function (socket) {
            var sock = new Socket_1.default("127.0.0.1", _this.serverPort, socket);
            console.log("Client " + socket.id + " is connected to relay.");
            sock.connectToServer();
            socket.on("disconnect", function () {
                _this.handleSocketDisconnection(socket);
            });
            _this.sockets.push(sock);
        };
        this.handleSocketDisconnection = function (socket) {
            var index = _this.sockets.findIndex(function (sock) {
                return (sock.getId() == socket.id);
            });
            console.log("Client " + socket.id + " has been disconnected from relay.");
            if (index == -1)
                return;
            _this.sockets[index].shutDownTCPSocket();
            _this.sockets.splice(index, 1);
        };
        this.port = port;
        this.serverPort = serverPort;
        this.server = this.app.listen(port, this.initialise);
        this.io = socketio(this.server);
        this.io.on("connection", this.handleSocketConnection);
    }
    return Server;
}());
exports.default = Server;
