import React from "react";

import RENDERER, { exampleRun } from "ui/renderer";

export default class extends React.Component {
    render() {
        return (
            <div className="left-panel">
                {"Menu"}
                <button
                    onClick={() => {
                        RENDERER.draw();
                    }}
                >
                    flat
                </button>
                <button
                    onClick={() => {
                        RENDERER.drawFrame();
                    }}
                >
                    frame
                </button>
                <button
                    onClick={() => {
                        RENDERER.clearImage();
                    }}
                >
                    clear
                </button>
                <button
                    onClick={() => {
                        exampleRun();
                    }}
                >
                    example
                </button>
            </div>
        );
    }
}
