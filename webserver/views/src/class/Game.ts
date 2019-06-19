class Game
{
	public static size:BABYLON.Vector2;
	public static timeUnit:number;
	private camera:Camera;
	private canvas:HTMLCanvasElement;
	private engine:BABYLON.Engine;
	private scene:BABYLON.Scene;
	private socketManager:SocketManager = new SocketManager(this);
	private stage:Stage;
	private teams:Map<string, Team> = new Map<string, Team>(); // DEPRACATED
	private chungus:Array<Player> = new Array<Player>();
	private eggs:Array<Egg> = new Array<Egg>();


	constructor(canvas:HTMLCanvasElement)
	{
		this.canvas = canvas;
		this.engine = new BABYLON.Engine(this.canvas, true);
		this.scene = new BABYLON.Scene(this.engine);
		this.stage = new Stage(this.scene);
		this.camera = new Camera(this.scene);

		this.initialiseScene();
		this.engine.runRenderLoop(this.render);
	}

	private initialiseScene():void
	{
		this.scene.collisionsEnabled = true;
		window.addEventListener("resize", () => {
			this.engine.resize();
		});
	}
	private render = ():void =>
	{
		this.stage.render();
		this.scene.render();
	}
	private isChungusAlreadyExist(id:number): boolean
	{
		for (let i:number = 0; i < this.chungus.length; i++) {
			if (id == this.chungus[i].getId())
				return (true);
		}
		return (false);
	}
	private getBigChungusById(id:number): Player
	{
		for (let i:number = 0; i < this.chungus.length; i++) {
			if (id == this.chungus[i].getId())
				return this.chungus[0];
		}
		return (this.chungus[0]);// normalement on protège avant la fonction avec un isChungusAlreadyExist() donc on n'arrive jamais ici
	}

	public addTeam(name:string)
	{
		this.teams.set(name, new Team(name));
	}
	public setup(size:BABYLON.Vector2)
	{
		Game.size = size;
		this.stage.createGround(size.x, size.y);
		this.camera.setTarget(new BABYLON.Vector3(size.x / 2, 0, size.y / 2));
	}
	public getStage():Stage
	{
		return (this.stage);
	}
	public addChungus(datas:Array<string>):void
	{
		if (datas.length < 7) {
			console.log("Not enough arguments to summon the big Chungus... CHUNG CHUNG CHUNG");
			console.log(datas);
			return;
		}
		if (isChungusAlreadyExist(parseInt(datas[1]))) {
			console.log("You can't clone the big unfamous big chungus !!!");
			console.log(datas);
			return;
		}
		chungus = new Player(parseInt(datas[1]), datas[6], this.scene);
		chungus.setPos(parseInt(datas[2]), parseInt(datas[3]));
		chungus.setOri(parseInt(datas[4]));
		chungus.setLvl(parseInt(datas[5]));
		this.chungus.push(chungus);
	}
	public updateChungusPos(datas:Array<string>):void
	{
		if (datas.length < 5) {
			console.log("Not enough arguments to move the big Chungus... CHUNG CHUNG CHUNG");
			console.log(datas);
			return;
		}
		if (!isChungusAlreadyExist(parseInt(datas[1]))) {
			console.log("This chungus doesn't exist");
			console.log(datas);
			return;
		}
		movingChungus = this.getBigChungusById(parseInt(datas[1]));
		movingChungus.setPos(parseInt(datas[2]), parseInt(datas[3]));
		movingChungus.setOri(parseInt(datas[4]));
	}
	public lvlUpChungus(datas:Array<string>):void
	{
		if (datas.length < 3) {
			console.log("Not enough arguments to upgrade the big Chungus... CHUNG CHUNG CHUNG");
			console.log(datas);
			return;
		}
		if (!isChungusAlreadyExist(parseInt(datas[1]))) {
			console.log("This chungus doesn't exist");
			console.log(datas);
			return;
		}
		levelingChungus = this.getBigChungusById(parseInt(datas[1]));
		levelingChungus.setLvl(parseInt(datas[2]));
	}
	public chungusBag(datas:Array<string>):void
	{
		if (datas.length < 11) {
			console.log("Not enough arguments to fill the big Chungus big bag... CHUNG CHUNG CHUNG");
			console.log(datas);
			return;
		}
		if (!isChungusAlreadyExist(parseInt(datas[1]))) {
			console.log("This chungus doesn't exist");
			console.log(datas);
			return;
		}
		fillingChungusBag = this.getBigChungusById(parseInt(datas[1]));
		fillingChungusBag.setPos(parseInt(datas[2]), parseInt(datas[3]));
		fillingChungusBag.setBag(parseInt(datas[4]), parseInt(datas[5]),
		parseInt(datas[6]), parseInt(datas[7]), parseInt(datas[8]),
		parseInt(datas[9]), parseInt(datas[10]));
	}
	public chungusYelling(datas:Array<string>):void
	{
		if (datas.length < 3) {
			console.log("To big Chungus the message isn't big enough");
			console.log(datas);
			return;
		}
		if (!isChungusAlreadyExist(parseInt(datas[1]))) {
			console.log("This chungus doesn't exist");
			console.log(datas);
			return;
		}
		voicingChungus = this.getBigChungusById(parseInt(datas[1]));
		voicingChungus.setMessage(datas[2]);
	}
	public chungusAccouching(datas:Array<string>):void
	{
		if (datas.length < 3) {
			console.log("Not enough arguments to reproduct the big Chungus... CHUNG CHUNG CHUNG");
			console.log(datas);
			return;
		}
		if (!isChungusAlreadyExist(parseInt(datas[1]))) {
			console.log("This chungus doesn't exist");
			console.log(datas);
			return;
		}
		accouchingChungus = this.getBigChungusById(parseInt(datas[1]));
		egg = new Egg(accouchingChungus.getX(), accouchingChungus.getY(),
		accouchingChungus.getTeamName(), this.scene);
		this.eggs.push(egg);
	}
	public chungusDroping(datas:Array<string>):void
	{
		if (datas.length < 3) {
			console.log("Not enough arguments to drop the big Chungus... CHUNG CHUNG CHUNG");
			console.log(datas);
			return;
		}
		if (!isChungusAlreadyExist(parseInt(datas[1]))) {
			console.log("This chungus doesn't exist");
			console.log(datas);
			return;
		}
		dropingChungus = this.getBigChungusById(parseInt(datas[1]));
		dropingChungus.drop(parseInt(datas[2]));
		let vector:BABYLON.Vector2 = new BABYLON.Vector2(0, 0);
		vector.x = dropingChungus.getX();
		vector.y = dropingChungus.getY();
		tile = this.stage.findTileByPosition(vector);
		tile.addItem(parseInt(datas[2]));
	}
}
