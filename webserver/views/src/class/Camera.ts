class Camera
{
	private static readonly KEYBOARD_SPEED:number = 10;
	private static readonly MOUSE_SPEED:number = 1 / 20;
	private static readonly ZOOM_SPEED:number = 1 / 10;
	private camera:BABYLON.ArcRotateCamera;
	private lastMovement:BABYLON.Vector2;
	private focus:boolean = true;
	private shiftingSpeedX:number = 0;
	private shiftingSpeedZ:number = 0;

	constructor(scene:BABYLON.Scene)
	{
		let target:BABYLON.Vector3 = BABYLON.Vector3.Zero();
		
		this.camera = new BABYLON.ArcRotateCamera("mainCamera", Math.PI / 2, Math.PI / 4, 30, target, scene);
		this.camera.allowUpsideDown = false;
		this.camera.checkCollisions = true;
		// this.camera.panningSensibility = 0;
		this.camera.collisionRadius = new BABYLON.Vector3(1, 1, 1);
		this.camera.attachControl(scene.getEngine().getRenderingCanvas(), false);
	}
	
	public setTarget(target:BABYLON.Vector3)
	{
		this.camera.setTarget(target);
	}
}
