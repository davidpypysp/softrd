import React from "react";
import { connect, ConnectedProps } from "react-redux";

import { Card, Button } from "@blueprintjs/core";
import { Tab, Tabs } from "@blueprintjs/core";
import SceneMenu from "src/components/SceneMenu";
import TestMenu from "src/components/TestMenu";

import { createUseStyles } from "react-jss";

const useStyles = createUseStyles({
    leftPanel: {
        width: 400,
    },
});

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

export default function LeftPanel() {
    const classes = useStyles();
    return (
        <Card className={classes.leftPanel}>
            <Tabs id="TabsExample" animate={false} defaultSelectedTabId="scene">
                <Tab id="scene" title="Scene" panel={<SceneMenu />} />
                <Tab id="test" title="Test" panel={<TestMenu />} />
                <Tab id="others" title="Others" panel={<Others />} />
                <Tabs.Expander />
            </Tabs>
        </Card>
    );
}
