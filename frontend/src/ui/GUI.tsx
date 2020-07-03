import * as React from "react";

import "styles/main.scss";

import { Card } from "@blueprintjs/core";

import Header from "src/ui/Layouts/Header";
import MainView from "src/ui/Layouts/MainView";
import LeftPanel from "src/ui/Layouts/LeftPanel";
import RightPanel from "src/ui/Layouts/RightPanel";

import { createUseStyles } from "react-jss";

const useStyles = createUseStyles({
    gui: {
        display: "flex",
        flexDirection: "column",
        height: "100%",
        width: "100%",
        padding: 0
    }
});

export default function GUI(props) {
    const classes = useStyles();
    return (
        <Card className={`bp3-dark ${classes.gui}`}>
            <Header />
            <div className="container">
                <LeftPanel />
                <MainView />
                <RightPanel />
            </div>
        </Card>
    );
}
