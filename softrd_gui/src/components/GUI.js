import React from "react";
import "styles/main.scss";

export default class GUI extends React.Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <span className="gui">test gui</span>
        );
    }
}