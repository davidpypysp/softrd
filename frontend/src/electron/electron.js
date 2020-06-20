const electron = require("electron");
const { app, BrowserWindow } = electron;

const path = require("path");
const isDev = require("electron-is-dev");
const os = require("os");

let mainWindow = null;

function createWindow() {
    mainWindow = new BrowserWindow({
        width: 1280,
        height: 720,
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
        // mainWindow.webContents.openDevTools();

        console.log("home", os.homedir());

        BrowserWindow.addDevToolsExtension(
            path.join(
                os.homedir(),
                "/.config/google-chrome/Default/Extensions/",
                "fmkadmapgofadopljbjfkapdkoienihi/4.6.0_0"
            )
        );
        BrowserWindow.addDevToolsExtension(
            path.join(
                os.homedir(),
                "/.config/google-chrome/Default/Extensions/",
                "lmhkpmbekcpmknklioeibfkpmmfibljd/2.17.0_0"
            )
        );
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
