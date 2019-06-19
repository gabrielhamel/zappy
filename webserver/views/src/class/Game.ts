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
		chungus = new Player(parseInt(datas[1]), datas[6], this.scene);
		chungus.setPos(parseInt(datas[2]), parseInt(datas[3]));
		chungus.setOri(parseInt(datas[4]));
		chungus.setLvl(parseInt(datas[5]));
		this.chungus.push(chungus);
	}
}
