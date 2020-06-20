import React from "react";
import RENDERER from "src/renderer";

class FPSText extends React.Component<{}, { fps: string }> {
    state = {
        fps: ""
    };

    componentDidMount() {
        setInterval(() => {
            this.setState({ fps: RENDERER.fps.toFixed(1) });
        }, 1000);
    }

    render() {
        return <div className="fps-text">{`FPS: ${this.state.fps}`}</div>;
    }
}

export default class SceneView extends React.Component {
    public canvasId: string = "scene-canvas";

    componentDidMount() {
        RENDERER.init(this.canvasId);
    }

    render() {
        return (
            <div className="scene-view">
                <canvas
                    id={this.canvasId}
                    className="scene-canvas"
                    width="640"
                    height="480"
                />
                <FPSText />
            </div>
        );
    }
}
