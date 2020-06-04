Module.locateFile = (path, scriptDirectory) => {
    return scriptDirectory + 'wasm/' + path;
};