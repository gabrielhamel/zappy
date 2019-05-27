import http = require("http");
import express = require("express");
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
		this.server = this.app.listen(this.initialise);
		this.io = socketio(this.server);
	}

	private initialise = (err:string):void =>
	{
		if (err) {
			console.error(err);
			return;
		}
		console.log(`Server is listening on port ${this.port}.`)
	}
	private handleSocketConnection(socket:socketio.Socket)
	{
		this.sockets.push(new Socket(socket));
	}
}

export default Server;