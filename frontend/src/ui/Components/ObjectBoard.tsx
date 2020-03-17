import React from "react";
import { Card } from "@blueprintjs/core";
import { Vector3Input } from "src/ui/Components/VectorInput";
import { Vec3 } from "src/interfaces/vector";

export interface RowDataProps {
    title: string;
    component?: React.ReactNode;
    data?: any;
}

const RowData = (props: RowDataProps) => (
    <li className="row-data">
        <span className="row-data-title">{props.title}</span>
        {props.component}
    </li>
);

export interface ObjectBoardProps {
    objectName: string;
    position?: Vec3;
    rotation?: Vec3;
}

export default function ObjectBoard(props: ObjectBoardProps) {
    return (
        <Card>
            <ul className="bp3-list bp3-list-unstyled">
                <RowData
                    title="Object"
                    component={<div className="object-name">{props.objectName}</div>}
                />
                <RowData
                    title="Position"
                    component={<Vector3Input data={props.position} />}
                />
                <RowData
                    title="Rotation"
                    component={<Vector3Input data={props.rotation} />}
                />
            </ul>
        </Card>
    );
}
