const softrd_js = require("bindings")("SoftrdJs");

const obj = new softrd_js.RendererAPIAddon(10);
const array = new Int32Array(10);

array[0] = 19;
array[1] = 41;
array[2] = 98;
array[3] = 122;
array[4] = 111;
array[5] = 12;
array[6] = 221;
array[7] = 49;
array[8] = 96;
array[9] = 1112;
obj.resetArrayBuffer(array.buffer);

console.log("array", array);
