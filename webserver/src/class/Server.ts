import http = require("http");
import express = require("express");
import path = require("path");
import socketio = require("socket.io");
import Socket from "./Socket"

class Server
{
	private server:http.Server;
	private app = express();
	private io:socketio.Server;
	private port:number;
	private sockets:Array<Socket> = new Array<Socket>();
	
	constructor(port:number)
	{
		this.port = port;
		this.server = this.app.listen(port, this.initialise);
		this.io = socketio(this.server);
		this.io.on("connection", this.handleSocketConnection);
	}

	private initialise = ():void =>
	{
		console.log(`Server is listening on port ${this.port}.`);
		this.app.use(express.static("views"));
		this.app.get("/", (req, res):void => {
			res.sendFile(path.resolve(__dirname + "/../views/index.html"));
		});
	}
	private handleSocketConnection(socket:socketio.Socket):void
	{
		this.sockets.push(new Socket(socket));
	}
}

export default Server;