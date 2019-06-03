"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var Server_1 = require("./class/Server");
var PORT = parseInt(process.argv[2]);
var SERVER_PORT = parseInt(process.argv[3]);
var server;
if (!isNaN(PORT) && !isNaN(SERVER_PORT) && PORT > 1024)
    server = new Server_1.default(PORT, SERVER_PORT);
