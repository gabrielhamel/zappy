function main():void
{
	let canvas:HTMLCanvasElement = document.getElementsByTagName("canvas")[0];
	let game:Game = new Game(canvas);
}

document.addEventListener("DOMContentLoaded", main);