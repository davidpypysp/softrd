import React from "react";
import IPC from "ui/utils/ipc";

import { exampleRun } from "ui/renderer";

export default class Menu extends React.Component {
    render() {
        return (
            <div className="menu">
                {"Menu"}
                <button
                    onClick={() => {
                        IPC.send("softrd", {
                            abc: "aqew"
                        });
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
