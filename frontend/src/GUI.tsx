import * as React from "react";

import "styles/main.scss";

import { Card } from "@blueprintjs/core";

import Header from "src/Layouts/Header";
import MainView from "src/Layouts/MainView";
import LeftPanel from "src/Layouts/LeftPanel";
import RightPanel from "src/Layouts/RightPanel";

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
