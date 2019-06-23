class Controller
{
	private login:HTMLElement = document.getElementById("login");
	private play:HTMLElement = document.getElementById("play");
	private tchat:HTMLElement = document.getElementById("tchat-form");
	private send:HTMLButtonElement = document.getElementById("send") as HTMLButtonElement;
	private ui:HTMLElement = document.getElementById("ui");
	private forward:HTMLButtonElement = document.getElementById("forward") as HTMLButtonElement;
	private turnLeft:HTMLButtonElement = document.getElementById("turn-left") as HTMLButtonElement;
	private turnRight:HTMLButtonElement = document.getElementById("turn-right") as HTMLButtonElement;
	private waiter:HTMLButtonElement = document.getElementById("waiter") as HTMLButtonElement;
	private take:Array<HTMLButtonElement> = new Array<HTMLButtonElement>();
	private drop:Array<HTMLButtonElement> = new Array<HTMLButtonElement>();
	private teamName:string;
	private socketManager: SocketManager;
	private game:Game;
	private free:boolean = true;
	private responseHandler:any;
	private converterArray:Array<string> = new Array<string>(
		"food", "linemate", "deraumere", "sibur",
		"mendiane", "phiras", "thystame"
	);;


	constructor(game:Game, socketManager: SocketManager)
	{
		this.responseHandler = this.handleConnection;
		this.game = game;
		this.socketManager = socketManager;
		this.ui.style.display = "none";
		this.tchat.style.display = "none";
		this.play.addEventListener("click", () => {
			this.teamName = this.login.getElementsByTagName("input")[0].value;
			this.socketManager.emit("requestPlay", this.teamName + "\n");
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
		this.send.addEventListener("click", () => {
			if (this.free == true) {
				let msg = this.tchat.getElementsByTagName("input")[0].value;
				this.socketManager.emit("play", "Broadcast " +  msg + "\n");
				this.blockInput();
			}
		});

		for (let i = 0; i < 7; i++) {
			this.drop.push(document.getElementById("drop-" + i) as HTMLButtonElement);
			this.drop[i].addEventListener("click", () => {
				if (this.free == true) {
					socketManager.emit("play", "Drop " + this.converterArray[i] + "\n");
				}
			});
		}

		for (let i = 0; i < 7; i++) {
			this.take.push(document.getElementById("take-" + i) as HTMLButtonElement);
			this.take[i].addEventListener("click", () => {
				if (this.free == true) {
					socketManager.emit("play", "Take " + this.converterArray[i] + "\n");
				}
			});
		}
	}

	private handleConnection = (datas:Array<string>): void =>
	{
		console.log(datas);
		if (!(datas[0] == "ko")) {
			this.ui.style.display = "block";
			this.tchat.style.display = "block";
			this.login.style.display = "none";
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
		this.send.disabled = true;
		for (let i = 0; i < 7; i++) {
			this.drop[i].disabled = true;
			this.take[i].disabled = true;
		}
		this.waiter.style.display = "inline-block";
		this.free = false;
	}
	public allowInput():void
	{
		this.forward.disabled = false;
		this.turnLeft.disabled = false;
		this.turnRight.disabled = false;
		this.send.disabled = false;
		for (let i = 0; i < 7; i++) {
			this.drop[i].disabled = false;
			this.take[i].disabled = false;
		}
		this.waiter.style.display = "none";
		this.free = true;
	}
	public die():void
	{
		this.ui.style.display = "none";
		this.tchat.style.display = "none";
		this.login.style.display = "block";
		this.responseHandler = this.handleConnection;
	}
	public handleResponse(datas:Array<string>):void
	{
		this.responseHandler(datas);
	}
}
