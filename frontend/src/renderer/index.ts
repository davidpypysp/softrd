const { softrd } = window as any;

class Renderer {
    public canvasElement: any = null;
    public context2D: any = null;
    public imageData: any = null;
    public softrdAddon: any = null;

    init(canvasId: any) {
        this.canvasElement = document.getElementById(canvasId);
        this.context2D = this.canvasElement.getContext("2d");
        this.imageData = this.context2D.getImageData(0, 0,
            this.canvasElement.width, this.canvasElement.height);

        this.softrdAddon = new softrd.RendererAPIAddon(10);

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
}

const RENDERER = new Renderer();
export default RENDERER;

export function exampleRun() {
    const obj = new softrd.RendererAPIAddon(10);
    console.log(obj.plusOne()); // 11
    const po1 = obj.plusOne();
    console.log("po1=", po1);
}
