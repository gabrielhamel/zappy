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
		this.commands.set("ppo", this.ppo);
		this.commands.set("plv", this.plv);
		this.commands.set("plv", this.pin);
		this.commands.set("pex", this.pex);
		this.commands.set("pbc", this.pbc);
		this.commands.set("pic", this.pic);
		this.commands.set("pie", this.pie);
		this.commands.set("pfk", this.pfk);
		this.commands.set("pdr", this.pdr);
		this.commands.set("pgt", this.pgt);
		this.commands.set("pdi", this.pdi);
		this.commands.set("enw", this.enw);
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
		this.game.addChungus(datas);
	}
	private ppo = (datas:Array<string>) =>
	{
		this.game.updateChungusPos(datas);
	}
	private plv = (datas:Array<string>) =>
	{
		this.game.lvlUpChungus(datas);
	}
	private pin = (datas:Array<string>) =>
	{
		this.game.chungusBag(datas);
	}
	private pex = (datas:Array<string>) =>
	{
		/// NEED GABI
	}
	private pbc = (datas:Array<string>) =>
	{
		this.game.chungusYelling(datas);
	}
	private pic = (datas:Array<string>) =>
	{
		/// NEED GABI
	}
	private pie = (datas:Array<string>) =>
	{
		/// NEED GABI
	}
	private pfk = (datas:Array<string>) =>
	{
		this.game.chungusLaying(datas);
	}
	private pdr = (datas:Array<string>) =>
	{
		this.game.chungusDroping(datas);
	}
	private pgt = (datas:Array<string>) =>
	{
		this.game.chungusTaking(datas);
	}
	private pdi = (datas:Array<string>) =>
	{
		this.game.removeChungus(datas);
	}
	private enw = (datas:Array<string>) =>
	{
		this.game.chungusAccouching(datas);
	}
}
