import React from "react";
import IPC from "components/utils/ipc";

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
                        const obj = new window.softrd.RendererAPIAddon(10);
                        console.log(obj.plusOne()); // 11

                        const po1 = obj.plusOne();
                        console.log("po1=", po1);
                    }}
                >
                    test2
                </button>
            </div>
        );
    }
}
