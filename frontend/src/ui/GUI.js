import React from "react";

import "styles/main.scss";

import { Card } from "@blueprintjs/core";

import Header from "ui/Layouts/Header";
import MainView from "ui/Layouts/MainView";
import LeftPanel from "ui/Layouts/LeftPanel";
import RightPanel from "ui/Layouts/RightPanel";

export default class GUI extends React.Component {
    render() {
        return (
            <Card className="bp3-dark gui">
                <Header />
                <div className="container">
                    <LeftPanel />
                    <MainView />
                    <RightPanel />
                </div>
            </Card>
        );
    }
}
