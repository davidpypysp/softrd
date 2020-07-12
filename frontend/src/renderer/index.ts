import store from "src/store";
import Module from "softrd-js";

class Renderer {
    public canvasElement = null;
    public context2D = null;
    public imageData = null;
    public lastExcutedTime: number = 0;
    public fps: number = 0;
    public rendererWASM = null;

    public mouseX = 0;
    public mouseY = 0;
    public isMouseDown = false;

    constructor() {
        Module.onRuntimeInitialized = () => {
            console.info("onRuntimeInitialized");
            this.rendererWASM = Module;
            this.rendererWASM = new Module.RendererAPI();

            const bytes = this.rendererWASM.getFrameBufferView();
            const bytesClamped = new Uint8ClampedArray(
                bytes.buffer,
                bytes.byteOffset,
                bytes.length
            );
            this.imageData = new ImageData(bytesClamped, 640, 480);

            // this.rendererWASM.drawSceneObjects();
            // this.context2D.putImageData(this.imageData, 0, 0);

            this.drawFrameLoop();
        };

        this.onMouseDown = this.onMouseDown.bind(this);
        this.onMouseMove = this.onMouseMove.bind(this);
        this.onMouseUp = this.onMouseUp.bind(this);
    }

    init(canvasId) {
        this.canvasElement = document.getElementById(canvasId);
        this.context2D = this.canvasElement.getContext("2d");
        this.lastExcutedTime = performance.now();

        this.canvasElement.addEventListener("mousedown", this.onMouseDown);
        this.canvasElement.addEventListener("mousemove", this.onMouseMove);
        this.canvasElement.addEventListener("mouseup", this.onMouseUp);
    }

    onMouseDown(e) {
        this.mouseX = e.offsetX;
        this.mouseY = e.offsetY;
        this.isMouseDown = true;
    }

    onMouseMove(e) {
        if (this.isMouseDown) {
            const dx = (e.offsetX - this.mouseX) * 0.05;
            const dy = (e.offsetY - this.mouseY) * 0.05;
            this.rendererWASM.moveCamera({ x: dx, y: -dy, z: 0 });
            this.mouseX = e.offsetX;
            this.mouseY = e.offsetY;
        }
    }

    onMouseUp(e) {
        this.mouseX = 0;
        this.mouseY = 0;
        this.isMouseDown = false;
    }

    draw() {
        this.context2D.putImageData(this.imageData, 0, 0);
    }

    clearImage() {
        this.context2D.clearRect(
            0,
            0,
            this.canvasElement.width,
            this.canvasElement.height
        );
    }

    reDraw() {
        this.context2D.putImageData(this.imageData, 0, 0);
    }

    drawFrameLoop() {
        setInterval(() => {
            this.drawSceneObjects();
            const currentTime = performance.now();
            this.fps = 1000.0 / (currentTime - this.lastExcutedTime);
            this.lastExcutedTime = currentTime;
        }, 10);
    }

    drawScene() {
        const { buffer } = this.imageData.data;
        this.context2D.putImageData(this.imageData, 0, 0);
    }

    drawSceneObjects() {
        const state = store.getState();
        // console.info("objectList", state.objectList);
        // const { buffer } = this.imageData.data;
        // this.softrdAddon.drawSceneObjects(buffer, state.objectList);
        this.rendererWASM.drawSceneFromObjectList(state.objectList);
        this.context2D.putImageData(this.imageData, 0, 0);
    }
}

const RENDERER = new Renderer();
export default RENDERER;
