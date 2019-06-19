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
		this.commands.set("bct", this.bct);
		this.commands.set("msz", this.msz);
		this.commands.set("sgt", this.sgt);
        this.commands.set("tna", this.tna);
		this.commands.set("pnw", this.pnw);
	}
	private getDatas = (datas:any):void =>
	{
		let array:Array<string> = datas.split("\n");
		let len:number = array.length;
		let cur:Array<string>;

		for (let i:number = 0; i < len; i++) {
			cur = array[i].split(" ");
			if (this.commands.get(cur[0]))
				this.commands.get(cur[0])(cur);
		}
	}
	private bct = (datas:Array<string>) =>
	{
		this.game.getStage().addTile(datas);
	}
	private msz = (datas:Array<string>) =>
	{
		let vector:BABYLON.Vector2 = new BABYLON.Vector2(0, 0);

		vector.x = parseInt(datas[1]);
		vector.y = parseInt(datas[2]);
		this.game.setup(vector);
	}
	private sgt = (datas:Array<string>) =>
	{
		Game.timeUnit = parseInt(datas[1]);
	}
	private tna = (datas:Array<string>) =>
	{
		this.game.addTeam(datas[1]);
	}
	private pnw = (datas:Array<string>) =>
	{
		this.game.getStage().addChungus(datas);
	}
}
