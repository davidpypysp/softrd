import React from "react";
import { connect, ConnectedProps } from "react-redux";
import { addObject } from "src/store/actions/objectListAction";
import RENDERER from "src/renderer";

import { Card, Button } from "@blueprintjs/core";
import { Tab, Tabs } from "@blueprintjs/core";
import SceneMenu from "src/ui/Components/SceneMenu";

const mapDispatchToProps = (dispatch) => ({
    addObject: () =>
        dispatch(
            addObject({
                id: "test_object",
                name: "Test Object",
                position: { x: 0, y: 0, z: 3 },
                rotation: { x: 1, y: 1, z: 1 }
            })
        )
});

const connector = connect(null, mapDispatchToProps);

type PropsFromRedux = ConnectedProps<typeof connector>;

class TestMenu extends React.Component<PropsFromRedux, {}> {
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
                    text="Draw Scene"
                    onClick={() => {
                        RENDERER.drawScene();
                    }}
                />
                <Button
                    intent="primary"
                    text="Draw Scene Objects"
                    onClick={() => {
                        RENDERER.drawSceneObjects();
                    }}
                />
                <Button
                    intent="danger"
                    text="Clear"
                    onClick={() => {
                        RENDERER.clearImage();
                    }}
                />
                <Button
                    intent="success"
                    text="Add_Object"
                    onClick={() => {
                        this.props.addObject();
                    }}
                />
            </Card>
        );
    }
}

const ConnectTestMenu = connect(null, mapDispatchToProps)(TestMenu);

class Others extends React.Component {
    render() {
        return (
            <div>
                <h5>
                    <a href="#">Card heading</a>
                </h5>
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
                <Tabs
                    id="TabsExample"
                    animate={false}
                    defaultSelectedTabId="scene"
                >
                    <Tab id="scene" title="Scene" panel={<SceneMenu />} />
                    <Tab id="test" title="Test" panel={<ConnectTestMenu />} />
                    <Tab id="others" title="Others" panel={<Others />} />
                    <Tabs.Expander />
                </Tabs>
            </Card>
        );
    }
}
