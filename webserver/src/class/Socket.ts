import net = require("net");
import socketio = require("socket.io");

class Socket
{
	private ioSocket:socketio.Socket;
	private tcpSocket:net.Socket;
	
	constructor(socket:socketio.Socket)
	{
		this.ioSocket = socket;
		this.tcpSocket = new net.Socket();
	}

	private receiveServerDatas = (datas:ArrayBuffer):void =>
	{
		this.ioSocket.emit("data", String.fromCharCode.apply(null, datas));
		console.log("data received from server:" + datas);
	}
	private sendDatasToServer = (datas:string):void =>
	{
		this.tcpSocket.write(datas);
		console.log("data sent to server: " + datas);
	}

	public connectToServer(ip:string, port:number):void
	{
		this.tcpSocket.connect(port, ip, ():void => {
			this.tcpSocket.on("data", this.receiveServerDatas);
			this.ioSocket.on("data", this.sendDatasToServer);
		});
	}
	public getId()
	{
		return (this.ioSocket.id);
	}
}

export default Socket;