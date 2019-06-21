class Controller
{
	private form:HTMLElement = document.getElementById("play-form");
	private play:HTMLElement = document.getElementById("play");
	private forward:HTMLButtonElement = document.getElementById("forward") as HTMLButtonElement;
	private turnLeft:HTMLButtonElement = document.getElementById("turn-left") as HTMLButtonElement;
	private turnRight:HTMLButtonElement = document.getElementById("turn-right") as HTMLButtonElement;
	private grab:HTMLButtonElement = document.getElementById("grab") as HTMLButtonElement;
	private drop:HTMLButtonElement = document.getElementById("drop") as HTMLButtonElement;
	private teamName:string;
	private socketManager: SocketManager;
	private game:Game;
	private free:boolean = true;

	constructor(game:Game, socketManager: SocketManager)
	{
		this.game = game;
		this.socketManager = socketManager;
		this.forward.style.display = "none";
		this.turnLeft.style.display = "none";
		this.turnRight.style.display = "none";
		this.grab.style.display = "none";
		this.drop.style.display = "none";
		this.play.addEventListener("click", () => {
			this.teamName = this.form.getElementsByTagName("input")[0].value;
			this.socketManager.emit("requestPlay", this.teamName + '\n');
		});
		this.forward.addEventListener("click", () => {
			if (this.free == true) {
				socketManager.emit("play", "Forward\n");
				this.blockInput();
			}
		});
		this.turnLeft.addEventListener("click", () => {
			if (this.free == true) {
				socketManager.emit("play", "Left\n");
				this.blockInput();
			}
		});
		this.turnRight.addEventListener("click", () => {
			if (this.free == true) {
				socketManager.emit("play", "Right\n");
				this.blockInput();
			}
		});
	}

	public changeState():void
	{
		this.forward.style.display = "inline";
		this.turnLeft.style.display = "inline";
		this.turnRight.style.display = "inline";
		this.grab.style.display = "inline";
		this.drop.style.display = "inline";
		this.form.style.display = "none";
	}
	public blockInput():void
	{
		this.forward.disabled = true;
		this.turnLeft.disabled = true;
		this.turnRight.disabled = true;
		this.grab.disabled = true;
		this.drop.disabled = true;
		this.free = false;
	}
	public deblockInput():void
	{
		this.forward.disabled = false;
		this.turnLeft.disabled = false;
		this.turnRight.disabled = false;
		this.grab.disabled = false;
		this.drop.disabled = false;
		this.free = true;
	}
}
