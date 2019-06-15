/// <reference path="../node_modules/babylonjs/babylon.module.d.ts" />
/// <reference path="../node_modules/babylonjs-gltf2interface/babylon.glTF2Interface.d.ts" />
/// <reference path="../node_modules/babylonjs-loaders/babylonjs.loaders.module.d.ts" />

function main():void
{
	let canvas:HTMLCanvasElement = document.getElementsByTagName("canvas")[0];
	let game:Game = new Game(canvas);
}

function middleRand(value:number):number
{
	return (value - Math.random() * (value * 2));
}

document.addEventListener("DOMContentLoaded", main);