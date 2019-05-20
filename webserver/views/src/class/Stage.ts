class Stage
{
	private static readonly GROUND_COLOR:BABYLON.Color3 = new BABYLON.Color3(0, 0.75, 0);
	private static readonly SELECTION_ELEVATION:number = 0.2;
	private static readonly SIZE:number = 100;
	private selectedObject:BABYLON.AbstractMesh;
	private canvas:HTMLCanvasElement;
	private light:BABYLON.HemisphericLight;
	private scene:BABYLON.Scene;
	private blocs:Array<BABYLON.InstancedMesh> = new Array<BABYLON.InstancedMesh>();
	private socketManager:SocketManager;

	constructor(socketManager:SocketManager, scene:BABYLON.Scene)
	{
		let lightDir = new BABYLON.Vector3(0, 1, 0);

		this.light = new BABYLON.HemisphericLight("light", lightDir, scene);
		this.scene = scene;
		this.canvas = scene.getEngine().getRenderingCanvas();
		this.socketManager = socketManager;

		this.light.diffuse = new BABYLON.Color3(1, 1, 1);
		this.light.specular = new BABYLON.Color3(0, 0, 0);

		window.addEventListener("pointerdown", this.onPointerDown);
	}
	private onPointerDown = (event:PointerEvent):void =>
	{
		let picked:BABYLON.PickingInfo = this.scene.pick(event.clientX, event.clientY);
	}

	public render():void
	{

	}
}