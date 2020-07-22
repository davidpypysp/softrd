import * as React from "react";

import "styles/main.scss";

import { Card } from "@blueprintjs/core";

import Header from "src/layout/Header";
import MainView from "src/layout/MainView";
import LeftPanel from "src/layout/LeftPanel";
import RightPanel from "src/layout/RightPanel";

import { createUseStyles } from "react-jss";

const useStyles = createUseStyles({
    gui: {
        display: "flex",
        flexDirection: "column",
        height: "100%",
        width: "100%",
        padding: 0,
    },
    container: {
        display: "flex",
        flexGrow: 1,
    },
});

export default function GUI(props) {
    const classes = useStyles();
    return (
        <Card className={`bp3-dark ${classes.gui}`}>
            <Header />
            <div className={classes.container}>
                <LeftPanel />
                <MainView />
                <RightPanel />
            </div>
        </Card>
    );
}
