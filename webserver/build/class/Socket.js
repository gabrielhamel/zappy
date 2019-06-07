"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var net = require("net");
var Socket = /** @class */ (function () {
    function Socket(socket) {
        var _this = this;
        this.receiveServerDatas = function (datas) {
            _this.ioSocket.emit("datas", datas);
            console.log("data received from server:" + datas);
        };
        this.sendDatasToServer = function (datas) {
            _this.tcpSocket.write(datas);
            console.log("data sent to server: " + datas);
        };
        this.ioSocket = socket;
        this.tcpSocket = new net.Socket();
    }
    Socket.prototype.connectToServer = function (ip, port) {
        var _this = this;
        this.tcpSocket.connect(port, ip, function () {
            _this.tcpSocket.on("data", _this.receiveServerDatas);
            _this.ioSocket.on("data", _this.sendDatasToServer);
        });
    };
    return Socket;
}());
exports.default = Socket;