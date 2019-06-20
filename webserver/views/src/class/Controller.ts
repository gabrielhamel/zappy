class Controller
{
	private form:HTMLElement = document.getElementById("play-form");
	private play:HTMLElement = document.getElementById("play");
	private forward:HTMLElement = document.getElementById("forward");
	private turnLeft:HTMLElement = document.getElementById("turn-left");
	private turnRight:HTMLElement = document.getElementById("turn-right");
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
		this.play.addEventListener("click", () => {
			this.teamName = this.form.getElementsByTagName("input")[0].value;
			this.socketManager.emit("requestPlay", this.teamName + '\n');
		});
		this.forward.addEventListener("click", () => {
			
		});
		this.turnLeft.addEventListener("click", () => {

		});
		this.turnRight.addEventListener("click", () => {

		});
	}

	public changeState()
	{

	}
}