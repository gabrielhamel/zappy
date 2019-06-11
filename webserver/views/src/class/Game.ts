class Game
{
	public static size:BABYLON.Vector2;
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
}