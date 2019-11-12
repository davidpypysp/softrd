const { ipcRenderer } = window.electron;

class MiddlewareEndpoint {
    send(channel, data) {
        ipcRenderer.send(channel, data);
    }
}

const MIDDLEWARE_ENDPOINT = new MiddlewareEndpoint();
export default MIDDLEWARE_ENDPOINT;
