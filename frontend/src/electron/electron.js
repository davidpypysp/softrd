const electron = require("electron");
const { app, BrowserWindow } = electron;

const path = require("path");
const isDev = require("electron-is-dev");

require("./ipc")

let mainWindow;

function createWindow() {
    console.log("creating window......");
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


