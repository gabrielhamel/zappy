class Controller
{
	private form:HTMLElement = document.getElementById("login");
	private play:HTMLElement = document.getElementById("play");
	private ui:HTMLElement = document.getElementById("ui");
	private forward:HTMLButtonElement = document.getElementById("forward") as HTMLButtonElement;
	private turnLeft:HTMLButtonElement = document.getElementById("turn-left") as HTMLButtonElement;
	private turnRight:HTMLButtonElement = document.getElementById("turn-right") as HTMLButtonElement;
	private grab:HTMLButtonElement = document.getElementById("grab") as HTMLButtonElement;
	private drop:HTMLButtonElement = document.getElementById("drop") as HTMLButtonElement;
	private teamName:string;
	private socketManager: SocketManager;
	private game:Game;
	private free:boolean = true;
	private responseHandler:any;

	constructor(game:Game, socketManager: SocketManager)
	{
		this.responseHandler = this.handleConnection;
		this.game = game;
		this.socketManager = socketManager;
		this.ui.style.display = "none";
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

	private handleConnection = (datas:Array<string>): void =>
	{
		console.log(datas);
		if (!(datas[0] == "ko")) {
			this.ui.style.display = "block";
			this.form.style.display = "none";
			this.responseHandler = this.handleNothing;
		}
		else {
			this.socketManager.emit("play", "dead\n");
		}
	}
	private handleNothing = (datas:Array<string>): void =>
	{
		console.log("message reçu mais pas traité");
		console.log(datas);
		this.allowInput();
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
	public allowInput():void
	{
		this.forward.disabled = false;
		this.turnLeft.disabled = false;
		this.turnRight.disabled = false;
		this.grab.disabled = false;
		this.drop.disabled = false;
		this.free = true;
	}
	public handleResponse(datas:Array<string>):void
	{
		this.responseHandler(datas);
	}
}
