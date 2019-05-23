class Camera
{
	private static readonly TARGET = new BABYLON.Vector3(30, 0, 50);
	private static readonly KEYBOARD_SPEED:number = 10;
	private static readonly MOUSE_SPEED:number = 1 / 20;
	private static readonly ZOOM_SPEED:number = 1 / 10;
	private camera:BABYLON.UniversalCamera;
	private lastMovement:BABYLON.Vector2;
	private focus:boolean = true;
	private shiftingSpeedX:number = 0;
	private shiftingSpeedZ:number = 0;

	constructor(scene:BABYLON.Scene)
	{
		let position:BABYLON.Vector3 = new BABYLON.Vector3(50, 30, 50);
		
		this.camera = new BABYLON.UniversalCamera("mainCamera", position, scene);
		this.camera.attachControl(scene.getEngine().getRenderingCanvas());
		this.camera.setTarget(Camera.TARGET);
	}
	/*private isNearFromBorders = ():boolean =>
	{
		if (this.camera.position.x >= 110) {
			this.camera.position.x -= 1;
			this.shiftingSpeedX = 0;
			return (false);
		}
		if (this.camera.position.x <= Camera.TARGET.x) {
			this.camera.position.x = Camera.TARGET.x + 1;
			this.shiftingSpeedX = 0;
			return (false);
		}
		if (this.camera.position.z >= 80) {
			this.camera.position.z -= 1;
			this.shiftingSpeedZ = 0;
			return (false);
		}
		if (this.camera.position.z <= 20) {
			this.camera.position.z = 21;
			this.shiftingSpeedZ = 0;
			return (false);
		}
		return (true);
	}*/
	public setFocus(focus:boolean):void
	{
		this.focus = focus;
	}
}