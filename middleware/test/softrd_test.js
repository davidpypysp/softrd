const softrd_js = require("bindings")("SoftrdJs");

const obj = new softrd_js.RendererAPIAddon(10);
console.log(obj.plusOne()); // 11
console.log(obj.plusOne()); // 12
console.log(obj.plusOne()); // 13

console.log(obj.multiply().value()); // 13
console.log(obj.multiply(10).value()); // 130

var newobj = obj.multiply(-1);
console.log(newobj.value()); // -13
console.log(obj === newobj); // false


const array = new Int32Array(10);

array[0] = 19;
array[1] = -41;
array[2] = 98;
array[3] = -922;
array[4] = 587;
array[5] = 12;
array[6] = 221;
array[7] = 49;
array[8] = -96;
array[9] = -1;
obj.acceptArrayBuffer(array.buffer);
