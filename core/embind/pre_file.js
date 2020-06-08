const wasmURI = require('./softrd_api.wasm').default;
console.info("softrd_api.wasm URI:", wasmURI);

Module.locateFile = (path, scriptDirectory) => {
    return scriptDirectory + wasmURI;
};

