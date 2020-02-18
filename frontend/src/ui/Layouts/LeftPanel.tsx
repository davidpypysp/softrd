import React from "react";

import RENDERER from "src/ui/renderer";
import {
    Card, Button, Tree,
    Icon, Tooltip, Intent,
    Classes, Position
} from "@blueprintjs/core";
import { Tab, Tabs } from "@blueprintjs/core";



class SceneMenu extends React.Component {
    public nodes: any[] = [
        {
            id: 0,
            hasCaret: true,
            icon: "folder-close",
            label: "Folder 0",
        },
        {
            id: 1,
            icon: "folder-close",
            isExpanded: true,
            // label: ,
            childNodes: [
                {
                    id: 2,
                    icon: "document",
                    label: "Item 0",
                    secondaryLabel: (
                        <Tooltip content="An eye!">
                            <Icon icon="eye-open" />
                        </Tooltip>
                    ),
                },
                {
                    id: 3,
                    icon: <Icon icon="tag"
                        intent={Intent.PRIMARY}
                        className={Classes.TREE_NODE_ICON} />,
                    // label: "Organic meditation gluten-free,
                    // sriracha VHS drinking vinegar beard man.",
                },
                {
                    id: 4,
                    hasCaret: true,
                    icon: "folder-close",
                    label: (
                        <Tooltip content="foo" position={Position.RIGHT}>
                            Folder 2
                        </Tooltip>
                    ),
                    childNodes: [
                        { id: 5, label: "No-Icon Item" },
                        { id: 6, icon: "tag", label: "Item 1" },
                        {
                            id: 7,
                            hasCaret: true,
                            icon: "folder-close",
                            label: "Folder 3",
                            childNodes: [
                                {
                                    id: 8,
                                    icon: "document",
                                    label: "Item 0"
                                },
                                {
                                    id: 9,
                                    icon: "tag",
                                    label: "Item 1"
                                },
                            ],
                        },
                    ],
                },
            ],
        },
        {
            id: 2,
            hasCaret: true,
            icon: "folder-close",
            label: "Super secret files",
            disabled: true,
        },
    ];

    render() {
        return (
            <div>
                <Tree
                    contents={this.nodes}
                    className={Classes.ELEVATION_0}
                />
            </div>
        );
    }
}


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
                <Tabs id="TabsExample" animate={false}>
                    <Tab id="scene" title="Scene"
                        panel={<SceneMenu />} />
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
