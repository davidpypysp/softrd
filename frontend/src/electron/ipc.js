const electron = require("electron");
const { ipcMain } = electron;

const softrd = require("bindings")("SoftrdJs");


console.log("init ipc");

ipcMain.on("test-channel", (event, arg) => {
    console.log("arg", arg);
});

ipcMain.on("softrd", (event, arg) => {
    const obj = new softrd.RendererAPIAddon(10);
    console.log(obj.plusOne()); // 11
});

console.log("init ipc finished");
