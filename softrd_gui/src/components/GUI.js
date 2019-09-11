import React from "react";

import "styles/main.scss";

import Header from "components/Layouts/Header";
import MainView from "components/Layouts/MainView";
import Menu from "components/Layouts/Menu";

export default class GUI extends React.Component {
    constructor(props) {
        super(props);
    }

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
