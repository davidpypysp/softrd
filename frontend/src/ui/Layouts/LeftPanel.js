import React from "react";

import RENDERER from "ui/renderer";
import { Card, Button, Elevation } from "@blueprintjs/core";

export default class extends React.Component {
    render() {
        return (
            <div className="left-panel">
                {"Menu"}
                <Card
                    className="bp3-dark"
                    elevation={Elevation.ZERO}
                >
                    <Button
                        intent="primary"
                        text="Draw"
                        onClick={() => {
                            RENDERER.draw();
                        }}
                    />
                    <Button
                        intent="primary"
                        text="Frame"
                        onClick={() => {
                            RENDERER.drawFrame();
                        }}
                    />
                    <Button
                        intent="danger"
                        text="Clear"
                        onClick={() => {
                            RENDERER.clearImage();
                        }}
                    />
                    <Button intent="success" text="blueprint_button"
                        onClick={() => {
                            console.log("onclick blueprint button");
                        }}
                    />
                    <Card
                        // className="bp3-dark"
                        elevation={Elevation.ZERO}
                    >
                        <h5><a href="#">Card heading</a></h5>
                        <p>Card content</p>
                        <Button>Submit</Button>
                    </Card>
                </Card>



            </div>
        );
    }
}
