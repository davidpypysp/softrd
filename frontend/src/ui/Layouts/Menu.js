import React from "react";

import RENDERER, { exampleRun } from "ui/renderer";

export default class Menu extends React.Component {
    render() {
        return (
            <div className="menu">
                {"Menu"}
                <button
                    onClick={() => {
                        console.log("drawing");
                        RENDERER.draw();
                    }}
                >
                    test
                </button>
                <button
                    onClick={() => {
                        exampleRun();
                    }}
                >
                    test2
                </button>
            </div>
        );
    }
}
