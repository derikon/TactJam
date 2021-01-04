const { app, BrowserWindow, ipcMain, Menu } = require('electron');
// does not load like this
// const VTP = import('vtp.js');

function createWindow () {
    const win = new BrowserWindow({
        width: 1280,
        height: 720,
        webPreferences: {
            nodeIntegration: true,
            enableRemoteModule: true,
            webviewTag: true
        },
        resizable: false
    });

    // win.loadFile('login.html');
    //win.loadFile('tabs.html');
     win.loadFile('index.html');
    // win.loadFile('save.html');
    win.webContents.openDevTools();
}

// disable default menu
Menu.setApplicationMenu(null);

app.whenReady().then(createWindow);

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit()
    }
});

app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
        createWindow()
    }
});
