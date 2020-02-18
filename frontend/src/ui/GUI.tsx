import * as React from "react";

import "styles/main.scss";

import { Card } from "@blueprintjs/core";

import Header from "src/ui/Layouts/Header";
import MainView from "src/ui/Layouts/MainView";
import LeftPanel from "src/ui/Layouts/LeftPanel";
import RightPanel from "src/ui/Layouts/RightPanel";

export class GUI extends React.Component {
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
