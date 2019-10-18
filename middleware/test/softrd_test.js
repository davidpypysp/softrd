const R = require("bindings")("softrd-js");

const obj = new R.RendererAPIAddon(10);
console.log(obj.plusOne()); // 11
console.log(obj.plusOne()); // 12
console.log(obj.plusOne()); // 13

console.log(obj.multiply().value()); // 13
console.log(obj.multiply(10).value()); // 130

var newobj = obj.multiply(-1);
console.log(newobj.value()); // -13
console.log(obj === newobj); // false
