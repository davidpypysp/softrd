import React from "react";

import RENDERER from "src/renderer";

import {
    Card, Button, Tree,
    Icon, Tooltip, Intent,
    Classes, Position
} from "@blueprintjs/core";
import { Tab, Tabs } from "@blueprintjs/core";

import SceneMenu from "src/ui/Components/SceneMenu";

const testNodes: any[] = [
    {
        name: "camera"
    },
    {
        name: "tree",
        children: [
            {
                name: "subtree1"
            },
            {
                name: "subtree2"
            }
        ]
    }
]



class TestMenu extends React.Component {
    render() {
        return (
            <Card>
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
            </Card>
        );
    }
}


class Others extends React.Component {
    render() {
        return (
            <div>
                <h5><a href="#">Card heading</a></h5>
                <p>Card content</p>
                <Button>Submit</Button>
            </div>

        );
    }
}


export default class LeftPanel extends React.Component {
    render() {
        return (
            <Card className="left-panel">
                <Tabs id="TabsExample"
                    animate={false}
                    defaultSelectedTabId="scene"
                >
                    <Tab id="scene" title="Scene"
                        panel={<SceneMenu nodes={testNodes} />} />
                    <Tab id="test" title="Test"
                        panel={<TestMenu />} />
                    <Tab id="others" title="Others"
                        panel={<Others />}
                    />
                    <Tabs.Expander />
                </Tabs>
            </Card>
        );
    }
}
