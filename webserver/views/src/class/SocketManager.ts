class SocketManager
{
	private socket = io();
	private game:Game = new Game();
	private controller:Controller = new Controller(this.game, this);
	private commandsGraph:Map<string, Function> = new Map<string, Function>();
	private commandsPlay:Map<string, Function> = new Map<string, Function>();
	
	constructor()
	{
		this.initialise();
		this.socket.emit("data", "GRAPHIC\n");
		this.socket.on("data", this.getDatas);
		this.socket.on("play", this.getPlay);
	}

	private initialise():void
	{
		this.commandsGraph.set("bct", this.bct);
		this.commandsGraph.set("msz", this.msz);
		this.commandsGraph.set("pnw", this.pnw);
		this.commandsGraph.set("sgt", this.sgt);
        this.commandsGraph.set("tna", this.tna);
		this.commandsGraph.set("pnw", this.pnw);
		this.commandsGraph.set("ppo", this.ppo);
		this.commandsGraph.set("plv", this.plv);
		this.commandsGraph.set("plv", this.pin);
		this.commandsGraph.set("pex", this.pex);
		this.commandsGraph.set("pbc", this.pbc);
		this.commandsGraph.set("pic", this.pic);
		this.commandsGraph.set("pie", this.pie);
		this.commandsGraph.set("pfk", this.pfk);
		this.commandsGraph.set("pdr", this.pdr);
		this.commandsGraph.set("pgt", this.pgt);
		this.commandsGraph.set("pdi", this.pdi);
		this.commandsGraph.set("enw", this.enw);
		this.commandsGraph.set("eht", this.eht);
		this.commandsGraph.set("ebo", this.ebo);
		this.commandsGraph.set("edi", this.edi);
	}
	private getDatas = (datas:any):void =>
	{
		let array:Array<string> = datas.split("\n");
		let len:number = array.length;
		let cur:Array<string>;

		for (let i:number = 0; i < len; i++) {
			cur = array[i].split(" ");
			if (this.commandsGraph.get(cur[0]))
				this.commandsGraph.get(cur[0])(cur);
		}
	}
	private getPlay = (datas:any):void =>
	{
		let array:Array<string> = datas.split("\n");
		let len:number = array.length;
		let cur:Array<string>;

		for (let i:number = 0; i < len; i++) {
			cur = array[i].split(" ");
			if (cur[0] == "WELCOME")
				this.controller.changeState();
			if (this.commandsPlay.get(cur[0])) {
				this.commandsPlay.get(cur[0])(cur);
				continue;
			}
			if (cur[0] == "Elevation")
				this.controller.blockInput();
			else
				this.controller.deblockInput();
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
	private eht = (datas:Array<string>) =>
	{
		this.game.maturingEgg(datas);
	}
	private ebo = (datas:Array<string>) =>
	{
		this.game.hatchingEgg(datas);
	}
	private edi = (datas:Array<string>) =>
	{
		this.game.dyingEgg(datas);
	}

	public emit(event:string, datas:string)
	{
		this.socket.emit(event, datas);
	}
}
