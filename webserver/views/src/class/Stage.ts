class Stage
{
	private selectedObject:BABYLON.AbstractMesh;
	private canvas:HTMLCanvasElement;
	private light:BABYLON.HemisphericLight;
	private scene:BABYLON.Scene;
	private blocs:Array<BABYLON.InstancedMesh> = new Array<BABYLON.InstancedMesh>();
	private socketManager:SocketManager;
	private blocCollection:BlocCollection;
	private model:BABYLON.AbstractMesh;

	constructor(socketManager:SocketManager, scene:BABYLON.Scene)
	{
		let lightDir = new BABYLON.Vector3(0, 1, 0);

		this.light = new BABYLON.HemisphericLight("light", lightDir, scene);
		this.scene = scene;
		this.canvas = scene.getEngine().getRenderingCanvas();
		this.socketManager = socketManager;
		this.blocCollection = new BlocCollection(scene);

		this.light.diffuse = new BABYLON.Color3(1, 1, 1);
		this.light.specular = new BABYLON.Color3(0, 0, 0);

		BABYLON.SceneLoader.LoadAssetContainer("/assets/", "chungus.glb", scene, (container:BABYLON.AssetContainer) => {
			this.model = container.meshes[0];
			this.model.scaling = new BABYLON.Vector3(0.35, 0.35, 0.35);
			this.model.position.y = 0.5;
			container.addAllToScene();
		});
		window.addEventListener("pointerdown", this.onPointerDown);
	}

	private onPointerDown = (event:PointerEvent):void =>
	{
		let picked:BABYLON.PickingInfo = this.scene.pick(event.clientX, event.clientY);
	}

	public createGround(width:number, height:number):void
	{
		let cur:BABYLON.InstancedMesh;
		
		for (let i:number = width - 1; i >= 0; i--) {
			for (let j:number = height - 1; j >= 0; j--) {
				cur = this.blocCollection.getInstance(0);
				cur.position.x = i;
				cur.position.z = j;
				this.blocs.push(cur);
			}
		}
	}

	public render():void
	{

	}
}