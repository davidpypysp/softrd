import React from "react";

import { Card, Button } from "@blueprintjs/core";
import { Tab, Tabs } from "@blueprintjs/core";

import ObjectBoard from "src/ui/Components/ObjectBoard";

import { createUseStyles } from "react-jss";

const useStyles = createUseStyles({
    rightPanel: {
        width: 700,
    },
});

export default function RightPanel() {
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
}
