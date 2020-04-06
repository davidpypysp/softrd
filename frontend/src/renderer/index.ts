import store from "src/store"

const { softrd } = window as any;

class Renderer {
    public canvasElement = null;
    public context2D = null;
    public imageData = null;
    public softrdAddon = null;
    public lastExcutedTime: number = 0;
    public fps: number = 0;

    init(canvasId) {
        this.canvasElement = document.getElementById(canvasId);
        this.context2D = this.canvasElement.getContext("2d");
        this.imageData = this.context2D.getImageData(0, 0,
            this.canvasElement.width, this.canvasElement.height);

        this.softrdAddon = new softrd.RendererAPIAddon(10);
        this.lastExcutedTime = performance.now();
        // this.drawFrameLoop();
    }

    draw() {
        const { buffer } = this.imageData.data;
        this.softrdAddon.resetArrayBuffer(buffer);
        this.context2D.putImageData(this.imageData, 0, 0);
    }

    drawFrame() {
        const { buffer } = this.imageData.data;
        this.softrdAddon.drawFrame(buffer);
        this.context2D.putImageData(this.imageData, 0, 0);
    }

    clearImage() {
        this.context2D.clearRect(0, 0,
            this.canvasElement.width, this.canvasElement.height);
    }

    reDraw() {
        this.context2D.putImageData(this.imageData, 0, 0);
    }

    drawFrameLoop() {
        setInterval(() => {
            this.drawFrame();
            const currentTime = performance.now();
            this.fps = 1000.0 / (currentTime - this.lastExcutedTime)
            this.lastExcutedTime = currentTime;
        }, 0);
    }

    drawScene() {
        const { buffer } = this.imageData.data;
        this.softrdAddon.drawScene(buffer);
        this.context2D.putImageData(this.imageData, 0, 0);
    }

    drawSceneObjects() {
        const state = store.getState();
        console.log("state:", state.objectList);

        const { buffer } = this.imageData.data;
        this.softrdAddon.drawSceneObjects(buffer, state.objectList);
        this.context2D.putImageData(this.imageData, 0, 0);
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
