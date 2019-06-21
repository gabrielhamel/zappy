class Controller
{
	private form:HTMLElement = document.getElementById("play-form");
	private play:HTMLElement = document.getElementById("play");
	private forward:HTMLElement = document.getElementById("forward");
	private turnLeft:HTMLElement = document.getElementById("turn-left");
	private turnRight:HTMLElement = document.getElementById("turn-right");
	private grab:HTMLElement = document.getElementById("grab");
	private drop:HTMLElement = document.getElementById("drop");
	private teamName:string;
	private socketManager: SocketManager;
	private game:Game;

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
			socketManager.emit("play", "Forward\n");
		});
		this.turnLeft.addEventListener("click", () => {
			socketManager.emit("play", "Left\n");
		});
		this.turnRight.addEventListener("click", () => {
			socketManager.emit("play", "Right\n");
		});
	}

	public changeState()
	{
		this.forward.style.display = "inline";
		this.turnLeft.style.display = "inline";
		this.turnRight.style.display = "inline";
		this.grab.style.display = "inline";
		this.drop.style.display = "inline";
		this.form.style.display = "none";
	}
}