import React from "react";

export default class MainView extends React.Component {
    render() {
        return (
            <div className="main-view">
                <canvas id="scene-canvas" className="scene-canvas"></canvas>
            </div>
        );
    }
}
