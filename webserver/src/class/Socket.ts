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

	private receiveServerDatas = (datas:string):void =>
	{
		this.ioSocket.emit("datas", datas);
	}
	private sendDatasToServer = (datas:string):void =>
	{
		this.tcpSocket.write(datas);
	}

	public connectToServer(ip:string, port:number):void
	{
		this.tcpSocket.connect(port, ip, ():void => {
			this.tcpSocket.on("data", this.receiveServerDatas);
			this.ioSocket.on("data", this.sendDatasToServer);
		});
	}
}

export default Socket;