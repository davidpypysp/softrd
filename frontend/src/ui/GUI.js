import React from "react";

import "styles/main.scss";

import Header from "ui/Layouts/Header";
import MainView from "ui/Layouts/MainView";
import Menu from "ui/Layouts/Menu";

export default class GUI extends React.Component {
    render() {
        return (
            <div className="gui">
                <Header />
                <div className="container">
                    <Menu />
                    <MainView />
                </div>
            </div>
        );
    }
}
