import net = require("net");
import socketio = require("socket.io");

class Socket
{
	private readonly IP:string;
	private readonly PORT:number
	private ioSocket:socketio.Socket;
	private tcpSocket:net.Socket;
	private playSocket:net.Socket;

	constructor(ip:string, port:number, socket:socketio.Socket)
	{
		this.IP = ip;
		this.PORT = port;
		this.ioSocket = socket;
		this.tcpSocket = new net.Socket();
	}

	private requestPlay = (datas:string):void =>
	{
		if (this.playSocket)
			return;
		this.playSocket = new net.Socket();
		this.playSocket.connect(this.PORT, this.IP, ():void => {
			this.playSocket.write(datas);
			this.playSocket.on("data", this.receiveServerPlay);
			this.ioSocket.on("play", this.sendIADataToServer);
		});
	}
	private receiveServerDatas = (datas:ArrayBuffer):void =>
	{
		let str:string = String.fromCharCode.apply(null, datas);
		
		this.ioSocket.emit("data", str);
	}
	private receiveServerPlay = (datas:ArrayBuffer):void =>
	{
		let str:string = String.fromCharCode.apply(null, datas);
		
		console.log(str);
		this.ioSocket.emit("play", str);
	}
	private sendDatasToServer = (datas:string):void =>
	{
		this.tcpSocket.write(datas);
	}
	private sendIADataToServer = (datas:string):void =>
	{
		this.playSocket.write(datas);
	}

	public connectToServer():void
	{
		this.tcpSocket.connect(this.PORT, this.IP, ():void => {
			this.tcpSocket.on("data", this.receiveServerDatas);
			this.ioSocket.on("data", this.sendDatasToServer);
			this.ioSocket.on("requestPlay", this.requestPlay);
		});
	}
	public getId()
	{
		return (this.ioSocket.id);
	}
}

export default Socket;
