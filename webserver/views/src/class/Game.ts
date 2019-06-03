class Game
{
	private canvas:HTMLCanvasElement;
	private engine:BABYLON.Engine;
	private scene:BABYLON.Scene;
	private camera:Camera;
	private keyboard:Keyboard = new Keyboard();
	private socketManager:SocketManager = new SocketManager(this);
	private stage:Stage;

	constructor(canvas:HTMLCanvasElement)
	{
		this.canvas = canvas;
		this.engine = new BABYLON.Engine(this.canvas, true);
		this.scene = new BABYLON.Scene(this.engine);
		this.stage = new Stage(this.socketManager, this.scene);
		this.camera = new Camera(this.scene);

		this.stage.createGround(10, 10);
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
	
	public getStage():Stage
	{
		return (this.stage);
	}
}