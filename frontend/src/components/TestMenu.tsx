import React from "react";
import { useDispatch } from "react-redux";
import RENDERER from "src/renderer";
import { Card, Button } from "@blueprintjs/core";
import { addObject } from "src/store/objectList";

const TestMenu = () => {
    const dispatch = useDispatch();

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
                    dispatch(
                        addObject({
                            id: "test_object",
                            name: "Test Object",
                            position: { x: 0, y: 0, z: 3 },
                            rotation: { x: 1, y: 1, z: 1 },
                        })
                    );
                }}
            />
        </Card>
    );
};

export default TestMenu;
