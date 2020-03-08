import React from "react";

import {
    Card,
    NumericInput
} from "@blueprintjs/core";


export interface RowDataProps {
    title: string;
    component?: React.Component;
}


class RowData extends React.Component<RowDataProps, {}> {
    render() {
        return (
            <li className="row-data">
                <span className="row-data-title">{this.props.title}</span>
                <NumericInput placeholder="Enter a number..." />
            </li>
        )
    }
}

export default class ObjectBoard extends React.Component {
    render() {
        return (
            <Card>
                <ul className="bp3-list bp3-list-unstyled">
                    <RowData title="Position" />
                    <RowData title="Rotation" />
                </ul>
            </Card>
        );
    }
}
