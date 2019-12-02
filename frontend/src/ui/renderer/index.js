const { softrd } = window;

class Renderer {
    constructor() {
        this.canvasElement = null;
    }

    init(canvasId) {
        this.canvasElement = document.getElementById(canvasId);
        this.context2D = this.canvasElement.getContext("2d");
        this.imageData = this.context2D.getImageData(0, 0,
            this.canvasElement.width, this.canvasElement.height);

        console.log("this.canvasElement", this.canvasElement);
    }

    draw() {
        const imageData = this.context2D.createImageData(
            this.canvasElement.width, this.canvasElement.height);

        const data = imageData.data;
        for (let i = 0; i < data.length; i += 4) {
            data[i] = 255;     // red
            data[i + 1] = 100; // green
            data[i + 2] = 100; // blue
            data[i + 3] = 255; // alpha
        }

        this.context2D.putImageData(imageData, 0, 0);
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
