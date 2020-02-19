import React from "react";
import RENDERER from "src/ui/renderer";

export default class Scene extends React.Component {
    public canvasId: string = "scene-canvas";

    componentDidMount() {
        RENDERER.init(this.canvasId);
    }

    render() {
        return (
            <div className="main-view" >
                <canvas
                    id={this.canvasId}
                    className="scene-canvas"
                    width="640"
                    height="480"
                >
                </canvas>
            </div>
        );
    }
}
