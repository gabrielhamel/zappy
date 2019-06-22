class Game
{
	public static size:BABYLON.Vector2;
	public static timeUnit:number;
	private readonly CHUNGUS:MeshBuilder;
	private readonly EGG:MeshBuilder;
	private camera:Camera;
	private canvas:HTMLCanvasElement;
	private engine:BABYLON.Engine;
	private scene:BABYLON.Scene;
	private socketManager:SocketManager;
	private stage:Stage;
	private chungus:Array<Player> = new Array<Player>();
	private eggs:Array<Egg> = new Array<Egg>();
	private teamsNames:Array<string> = new Array<string>();
	private tchat:Tchat = new Tchat();

	constructor()
	{
		this.canvas = document.getElementsByTagName("canvas")[0];
		this.engine = new BABYLON.Engine(this.canvas, true);
		this.scene = new BABYLON.Scene(this.engine);
		this.scene.collisionsEnabled = true;
		this.CHUNGUS = new MeshBuilder("chungus.glb", this.scene, () => {
			this.stage = new Stage(this.scene);
			this.camera = new Camera(this.scene);
			this.socketManager = new SocketManager(this);
			this.initialiseScene();
			this.engine.runRenderLoop(this.render);
		});
	}

	private initialiseScene():void
	{
		window.addEventListener("resize", () => {
			this.engine.resize();
		});
	}
	private render = ():void =>
	{
		this.stage.render();
		this.scene.render();
	}
	private getBigChungusById(id:number): Player
	{
		for (let i:number = 0; i < this.chungus.length; i++) {
			if (id == this.chungus[i].getId())
				return this.chungus[0];
		}
		return (undefined);
	}
	private getEggById(id:number): Egg
	{
		for (let i:number = 0; i < this.eggs.length; i++) {
			if (id == this.eggs[i].getId())
				return this.eggs[0];
		}
		return (undefined);
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
	public addTeam(name:string):void
	{
		this.teamsNames.push(name);
	}
	public addChungus(datas:Array<string>):void
	{
		if (datas.length < 7) {
			console.log("Not enough arguments to summon the big Chungus... CHUNG CHUNG CHUNG");
			console.log(datas);
			return;
		}
		if (this.getBigChungusById(parseInt(datas[1]))) {
			console.log("You can't clone the big unfamous big chungus !!!");
			console.log(datas);
			return;
		}
		let chungus = new Player(parseInt(datas[1]), datas[6], this.CHUNGUS.getInstance(), this.scene);
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
		let movingChungus = this.getBigChungusById(parseInt(datas[1]))
		if (!movingChungus) {
			console.log("This chungus doesn't exist");
			console.log(datas);
			return;
		}
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
		let levelingChungus = this.getBigChungusById(parseInt(datas[1]));

		if (!levelingChungus) {
			console.log("This chungus doesn't exist");
			console.log(datas);
			return;
		}
		levelingChungus.setLvl(parseInt(datas[2]));
	}
	public chungusBag(datas:Array<string>):void
	{
		if (datas.length < 11) {
			console.log("Not enough arguments to fill the big Chungus big bag... CHUNG CHUNG CHUNG");
			console.log(datas);
			return;
		}
		let fillingChungusBag = this.getBigChungusById(parseInt(datas[1]));
		if (!fillingChungusBag) {
			console.log("This chungus doesn't exist");
			console.log(datas);
			return;
		}
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
		let voicingChungus = this.getBigChungusById(parseInt(datas[1]));

		if (!voicingChungus) {
			console.log("This chungus doesn't exist");
			console.log(datas);
			return;
		}
		voicingChungus.setMessage(datas[2]);

	}
	public chungusLaying(datas:Array<string>):void
	{
		if (datas.length < 2) {
			console.log("Not enough arguments to reproduct the big Chungus... CHUNG CHUNG CHUNG");
			console.log(datas);
			return;
		}
		let layingChungus = this.getBigChungusById(parseInt(datas[1]));
		if (!layingChungus) {
			console.log("This chungus doesn't exist");
			console.log(datas);
			return;
		}
		layingChungus.setLayingState(true);
	}
	public chungusDroping(datas:Array<string>):void
	{
		if (datas.length < 3) {
			console.log("Not enough arguments to drop the big Chungus... CHUNG CHUNG CHUNG");
			console.log(datas);
			return;
		}
		let dropingChungus = this.getBigChungusById(parseInt(datas[1]));
		if (!dropingChungus) {
			console.log("This chungus doesn't exist");
			console.log(datas);
			return;
		}
		dropingChungus.drop(parseInt(datas[2]));
		let vector:BABYLON.Vector2 = new BABYLON.Vector2(0, 0);
		vector.x = dropingChungus.getX();
		vector.y = dropingChungus.getY();
		let tile = this.stage.findTileByPosition(vector);
		tile.addItem(parseInt(datas[2]));
	}
	public chungusTaking(datas:Array<string>):void
	{
		if (datas.length < 3) {
			console.log("Not enough arguments to take the big Chungus... CHUNG CHUNG CHUNG");
			console.log(datas);
			return;
		}
		let gatheringChungus = this.getBigChungusById(parseInt(datas[1]));
		if (!gatheringChungus) {
			console.log("This chungus doesn't exist");
			console.log(datas);
			return;
		}
		gatheringChungus.take(parseInt(datas[2]));
		let vector:BABYLON.Vector2 = new BABYLON.Vector2(0, 0);
		vector.x = gatheringChungus.getX();
		vector.y = gatheringChungus.getY();
		let tile = this.stage.findTileByPosition(vector);
		tile.removeItem(parseInt(datas[2]));
	}
	public removeChungus(datas:Array<string>):void
	{
		if (datas.length < 2) {
			console.log("Not enough arguments to kill the big Chungus... CHUNG CHUNG CHUNG");
			console.log(datas);
			return;
		}
		if (!this.getBigChungusById(parseInt(datas[1]))) {
			console.log("This chungus doesn't exist");
			console.log(datas);
			return;
		}
		let i = 0;
		for (;i < this.chungus.length && this.chungus[i].getId() != parseInt(datas[1]) ; i++);
		this.chungus[i].die();
		this.chungus.splice(i, 1);
	}
	public chungusAccouching(datas:Array<string>):void
	{
		if (datas.length < 5) {
			console.log("Not enough arguments to reproduct the big Chungus... CHUNG CHUNG CHUNG");
			console.log(datas);
			return;
		}
		let accouchingChungus = this.getBigChungusById(parseInt(datas[2]));
		if (!accouchingChungus || this.getEggById(parseInt(datas[1]))) {
			console.log("This chungus doesn't exist or egg already exist");
			console.log(datas);
			return;
		}
		let egg = new Egg(parseInt(datas[1]), parseInt(datas[3]), parseInt(datas[4]),
		accouchingChungus.getTeamName(), this.scene);
		this.eggs.push(egg);
		accouchingChungus.setLayingState(false);
	}
	public maturingEgg(datas:Array<string>):void
	{
		if (datas.length < 2) {
			console.log("Not enough arguments to mature an egg");
			console.log(datas);
			return;
		}
		let egg = this.getEggById(parseInt(datas[1]));
		if (!egg) {
			console.log("This egg doesn't exist");
			console.log(datas);
			return;
		}
		egg.setMaturity(true);
	}
	public hatchingEgg(datas:Array<string>):void
	{
		if (datas.length < 2) {
			console.log("Not enough arguments to mature an egg");
			console.log(datas);
			return;
		}
		let egg = this.getEggById(parseInt(datas[1]));
		if (!egg) {
			console.log("This egg doesn't exist");
			console.log(datas);
			return;
		}
		//ANIMATION => fade de l'oeuf
		let i = 0;
		for (;i < this.eggs.length && this.eggs[i].getId() != parseInt(datas[1]) ; i++);
		this.eggs.splice(i, 1);
	}
	public dyingEgg(datas:Array<string>):void
	{
		if (datas.length < 2) {
			console.log("Not enough arguments to mature an egg");
			console.log(datas);
			return;
		}
		let egg = this.getEggById(parseInt(datas[1]));
		if (!egg) {
			console.log("This egg doesn't exist");
			console.log(datas);
			return;
		}
		//ANIMATION => destruction de l'oeuf
		let i = 0;
		for (;i < this.eggs.length && this.eggs[i].getId() != parseInt(datas[1]) ; i++);
		this.eggs.splice(i, 1);
	}
}
