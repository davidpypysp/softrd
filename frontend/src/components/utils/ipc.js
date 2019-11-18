const { ipcRenderer } = window.electron;

class Ipc {
    send(channel, data) {
        ipcRenderer.send(channel, data);
    }
}

const IPC = new Ipc();
export default IPC;
