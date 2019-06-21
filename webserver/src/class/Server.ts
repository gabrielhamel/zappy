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
	private serverPort:number;
	private sockets:Array<Socket> = new Array<Socket>();

	constructor(port:number, serverPort:number)
	{
		this.port = port;
		this.serverPort = serverPort;
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
	private handleSocketConnection = (socket:socketio.Socket):void =>
	{
		let sock:Socket = new Socket("127.0.0.1", this.serverPort, socket);

		console.log(`Client ${socket.id} is connected to relay.`);
		sock.connectToServer();
		socket.on("disconnect", () => {
			this.handleSocketDisconnection(socket);
		});
		this.sockets.push(sock);
	}
	private handleSocketDisconnection = (socket:socketio.Socket) =>
	{
		let index:number = this.sockets.findIndex((sock:Socket) => {
			return (sock.getId() == socket.id);
		});


		console.log(`Client ${socket.id} has been disconnected from relay.`);
		if (index == -1)
			return;
		this.sockets.splice(index, 1);
	}
}

export default Server;