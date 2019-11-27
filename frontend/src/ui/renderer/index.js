const { softrd } = window;

export function exampleRun() {
    const obj = new softrd.RendererAPIAddon(10);
    console.log(obj.plusOne()); // 11
    const po1 = obj.plusOne();
    console.log("po1=", po1);
}
