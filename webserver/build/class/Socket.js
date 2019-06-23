"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var net = require("net");
var Socket = /** @class */ (function () {
    function Socket(ip, port, socket) {
        var _this = this;
        this.requestPlay = function (datas) {
            if (_this.playSocket)
                return;
            _this.playSocket = new net.Socket();
            _this.playSocket.connect(_this.PORT, _this.IP, function () {
                _this.playSocket.write(datas);
                _this.playSocket.on("data", _this.receiveServerPlay);
                _this.ioSocket.on("play", _this.sendIADataToServer);
            });
        };
        this.receiveServerDatas = function (datas) {
            var str = String.fromCharCode.apply(null, datas);
            _this.ioSocket.emit("data", str);
        };
        this.receiveServerPlay = function (datas) {
            var str = String.fromCharCode.apply(null, datas);
            if (str == "dead\n") {
                _this.playSocket.removeAllListeners();
                _this.ioSocket.removeListener("play", _this.sendIADataToServer);
                _this.playSocket.destroy();
                _this.playSocket = undefined;
                return;
            }
            _this.ioSocket.emit("play", str);
        };
        this.sendDatasToServer = function (datas) {
            _this.tcpSocket.write(datas);
        };
        this.sendIADataToServer = function (datas) {
            if (datas == "dead\n") {
                _this.playSocket.removeAllListeners();
                _this.ioSocket.removeListener("play", _this.sendIADataToServer);
                _this.playSocket.destroy();
                _this.playSocket = undefined;
                return;
            }
            _this.playSocket.write(datas);
        };
        this.IP = ip;
        this.PORT = port;
        this.ioSocket = socket;
        this.tcpSocket = new net.Socket();
    }
    Socket.prototype.connectToServer = function () {
        var _this = this;
        this.tcpSocket.connect(this.PORT, this.IP, function () {
            _this.tcpSocket.on("data", _this.receiveServerDatas);
            _this.ioSocket.on("data", _this.sendDatasToServer);
            _this.ioSocket.on("requestPlay", _this.requestPlay);
        });
    };
    Socket.prototype.getId = function () {
        return (this.ioSocket.id);
    };
    Socket.prototype.shutDownTCPSocket = function () {
        this.tcpSocket.destroy();
        this.tcpSocket = undefined;
        if (this.playSocket) {
            this.playSocket.destroy();
            this.playSocket = undefined;
        }
    };
    return Socket;
}());
exports.default = Socket;
