import React, { useEffect, useState } from "react";
import RENDERER from "src/renderer";

import { createUseStyles } from "react-jss";

const useStyles = createUseStyles({
    sceneView: {
        flexGrow: 1,
        position: "relative",
    },
    sceneCanvas: {
        width: "100%",
        height: "100%",
    },
    fpsText: {
        position: "absolute",
        top: 10,
        right: 0,
        paddingRight: 20,
        width: 120,
    },
});

const FPSText = () => {
    const [fps, setFps] = useState("");
    const classes = useStyles();

    useEffect(() => {
        setInterval(() => {
            setFps(RENDERER.fps.toFixed(1));
        }, 1000);
    }, []);

    return <div className={classes.fpsText}>{`FPS: ${fps}`}</div>;
};

export default function SceneView() {
    const canvasId: string = "scene-canvas";
    const classes = useStyles();

    useEffect(() => {
        RENDERER.init(canvasId);
    }, []);

    return (
        <div className={classes.sceneView}>
            <canvas
                id={canvasId}
                className={classes.sceneCanvas}
                width="640"
                height="480"
            />
            <FPSText />
        </div>
    );
}
