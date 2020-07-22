import React from "react";
import { connect, ConnectedProps } from "react-redux";
import { addObject } from "src/store/actions/objectListAction";
import RENDERER from "src/renderer";
import { Card, Button } from "@blueprintjs/core";

const mapDispatchToProps = (dispatch) => ({
    addObject: () =>
        dispatch(
            addObject({
                id: "test_object",
                name: "Test Object",
                position: { x: 0, y: 0, z: 3 },
                rotation: { x: 1, y: 1, z: 1 },
            })
        ),
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
                        // RENDERER.draw();
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

export default connect(null, mapDispatchToProps)(TestMenu);
