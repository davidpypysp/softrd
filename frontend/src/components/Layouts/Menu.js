import React from "react";
const { ipcRenderer } = window.electron;

export default class Menu extends React.Component {
    render() {
        return (
            <div className="menu">
                {"Menu"}
                <button
                    onClick={() => {
                        console.log("test button");
                        ipcRenderer.send("test-channel", { abc: "aqew" });
                    }}
                >
                    test
                </button>
            </div>
        );
    }
}
