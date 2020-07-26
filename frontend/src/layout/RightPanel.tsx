import React from "react";

import { Card, Button } from "@blueprintjs/core";
import { Tab, Tabs } from "@blueprintjs/core";

import ObjectBoard from "src/components/ObjectBoard";

import { createUseStyles } from "react-jss";

const useStyles = createUseStyles({
    rightPanel: {
        minWidth: 700,
    },
});

const RightPanel = () => {
    const classes = useStyles();
    return (
        <Card className={classes.rightPanel}>
            <Tabs
                id="TabsExample"
                animate={false}
                defaultSelectedTabId="objectBoard"
            >
                <Tab id="objectBoard" title="Object" panel={<ObjectBoard />} />
                <Tabs.Expander />
            </Tabs>
        </Card>
    );
};

export default RightPanel;
