class SocketManager
{
	private socket = io();
	private game:Game;
	private commands:Map<string, Function> = new Map<string, Function>();
	
	constructor(game:Game)
	{
		this.game = game;
		this.initialise();
		this.socket.emit("data", "GRAPHIC\n");
		this.socket.on("data", this.getDatas);
	}

	private initialise():void
	{
		this.commands.set("msz", this.msz);
	}
	private getDatas = (datas:any):void =>
	{
		let array:Array<string> = datas.split("\n");
		let len:number = array.length;
		let cur:Array<string>;

		for (let i:number = 0; i < len; i++) {
			cur = array[i].split(" ");
			if (this.commands.get(cur[i]))
				this.commands.get(cur[i])(cur);
		}
	}
	private msz = (datas:Array<string>) =>
	{
		let vector:BABYLON.Vector2 = new BABYLON.Vector2(0, 0);

		vector.x = parseInt(datas[1]);
		vector.y = parseInt(datas[2]);
		this.game.setup(vector);
	}
}