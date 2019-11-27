const { softrd } = window;

class Renderer {
    constructor() {
        this.canvasElement = null;
    }

    init(canvasId) {
        this.canvasElement = document.getElementById(canvasId);
    }

    draw() {
        const ctx = this.canvasElement.getContext("2d");
        ctx.fillStyle = "#FF0000";
        ctx.fillRect(0, 0, 150, 75);
    }
}

const RENDERER = new Renderer();
export default RENDERER;

export function exampleRun() {
    const obj = new softrd.RendererAPIAddon(10);
    console.log(obj.plusOne()); // 11
    const po1 = obj.plusOne();
    console.log("po1=", po1);
}
