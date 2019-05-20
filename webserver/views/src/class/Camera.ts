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
		this.camera.setTarget(Camera.TARGET);
		window.addEventListener("pointerdown", this.managePointerState);
		window.addEventListener("pointerup", this.managePointerState);
		window.addEventListener("wheel", this.zoom);
		window.addEventListener("mousewheel", this.zoom);
		window.addEventListener("DOMMouseScroll", this.zoom);
	}

	private managePointerState = (mouse:PointerEvent):void =>
	{
		this.lastMovement = new BABYLON.Vector2(mouse.screenX, mouse.screenY);
		if (mouse.type == "pointerdown")
			window.addEventListener("pointermove", this.moveFromPointer);
		else
			window.removeEventListener("pointermove", this.moveFromPointer);
	}
	private moveFromPointer = (mouse:PointerEvent):void =>
	{
		let coeff:number = Camera.MOUSE_SPEED * this.camera.position.y / 120;

		this.shiftingSpeedX = (mouse.screenY - this.lastMovement.y) * coeff;
		this.shiftingSpeedZ = (mouse.screenX - this.lastMovement.x) * coeff;
		this.lastMovement = new BABYLON.Vector2(mouse.screenX, mouse.screenY);
	}
	private zoom = (event:MouseWheelEvent):void =>
	{
		if (!event.deltaY || (this.camera.position.y <= 10 && event.deltaY < 0))
			return;
		this.camera.position.y += event.deltaY * Camera.ZOOM_SPEED;
		if (this.camera.position.y < 10)
			this.camera.position.y = 10;
	}
	private isNearFromBorders = ():boolean =>
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
	}
	
	public render = (keyboard:Keyboard, elapsedTime:number):void =>
	{
		if (!this.isNearFromBorders())
			return;
		this.moveFromKeyboard(keyboard, elapsedTime);
		this.camera.position.x -= this.shiftingSpeedX;
		this.camera.position.z -= this.shiftingSpeedZ;
		if (this.shiftingSpeedX < 0.01 && this.shiftingSpeedX > -0.01)
			this.shiftingSpeedX = 0;
		if (this.shiftingSpeedZ < 0.01 && this.shiftingSpeedZ > -0.01)
			this.shiftingSpeedZ = 0;
		this.shiftingSpeedX -= this.shiftingSpeedX > 0 ? 0.0001 * this.camera.position.y : 0;
		this.shiftingSpeedX += this.shiftingSpeedX < 0 ? 0.0001 * this.camera.position.y : 0;
		this.shiftingSpeedZ -= this.shiftingSpeedZ > 0 ? 0.0001 * this.camera.position.y : 0;
		this.shiftingSpeedZ += this.shiftingSpeedZ < 0 ? 0.0001 * this.camera.position.y : 0;
	}
	public moveFromKeyboard = (keyboard:Keyboard, elapsedTime:number):void =>
	{
		let speed:number = Camera.KEYBOARD_SPEED * (elapsedTime / 1000) * this.camera.position.y / 100;

		if (!this.focus)
			return;
		this.shiftingSpeedZ += keyboard.getKey(Keyboard.LEFT) ? speed : 0;
		this.shiftingSpeedZ -= keyboard.getKey(Keyboard.RIGHT) ? speed : 0;
		this.shiftingSpeedX += keyboard.getKey(Keyboard.UP) ? speed : 0;
		this.shiftingSpeedX -= keyboard.getKey(Keyboard.DOWN) ? speed : 0;
	}
	public setFocus(focus:boolean):void
	{
		this.focus = focus;
	}
}