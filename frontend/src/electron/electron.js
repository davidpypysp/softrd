const electron = require("electron");
const { app, BrowserWindow, ipcMain } = electron;
const softrd_js = require("bindings")("SoftrdJs");

const path = require("path");
const isDev = require("electron-is-dev");

const fs = require("fs");

let mainWindow;

function createWindow() {
    console.log("creating window......");

    const obj = new softrd_js.RendererAPIAddon(10);
    console.log(obj.plusOne()); // 11
    console.log(obj.plusOne()); // 12
    console.log(obj.plusOne()); // 13

    mainWindow = new BrowserWindow({
        width: 900,
        height: 680,
        webPreferences: {
            preload: __dirname + "/preload.js"
        }
    });
    mainWindow.loadURL(
        isDev
            ? "http://localhost:9000"
            : `file://${path.join(__dirname, "../../dist/index.html")}`
    );
    if (isDev) {
        // Open the DevTools.
        // BrowserWindow.addDevToolsExtension
        // ("<location to your react chrome extension>");
        mainWindow.webContents.openDevTools();
    }
    mainWindow.on("closed", () => {
        console.log("closing window......");
        mainWindow = null;
    });
}

app.on("ready", createWindow);

app.on("window-all-closed", () => {
    if (process.platform !== "darwin") {
        app.quit();
    }
});

app.on("activate", () => {
    if (mainWindow === null) {
        createWindow();
    }
});

ipcMain.on("test-channel", (event, arg) => {
    console.log("arg", arg);
});
