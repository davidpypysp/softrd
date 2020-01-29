import React from "react";

import RENDERER, { exampleRun } from "ui/renderer";

export default class Menu extends React.Component {
    render() {
        return (
            <div className="menu">
                {"Menu"}
                <button
                    onClick={() => {
                        console.log("draw");
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
