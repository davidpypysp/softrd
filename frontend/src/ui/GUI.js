import React from "react";

import "styles/main.scss";

import Header from "ui/Layouts/Header";
import MainView from "ui/Layouts/MainView";
import LeftPanel from "ui/Layouts/LeftPanel";
import RightPanel from "ui/Layouts/RightPanel";

export default class GUI extends React.Component {
    render() {
        return (
            <div className="gui">
                <Header />
                <div className="container">
                    <LeftPanel />
                    <MainView />
                    <RightPanel />
                </div>
            </div>
        );
    }
}
