import React from "react";
import { Card } from "@blueprintjs/core";
import { Vector3Input } from "src/ui/Components/VectorInput";
import { Vec3 } from "src/interfaces/vector";
import { connect, ConnectedProps } from 'react-redux'
import { Object } from "src/interfaces/object";

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

const mapStateToProps = (state) => {
    const { objectSelector, objectList } = state;
    const object: Object = objectList[objectSelector];
    return { object }
};
const connector = connect(mapStateToProps);


const ObjectBoard = (props: ConnectedProps<typeof connector>) => {
    const { object } = props;
    return (
        object ? <Card>
            <ul className="bp3-list bp3-list-unstyled">
                <RowData
                    title="Object"
                    component={<div className="object-name">{object.name}</div>}
                />
                <RowData
                    title="Position"
                    component={<Vector3Input data={object.position} />}
                />
                <RowData
                    title="Rotation"
                    component={<Vector3Input data={object.rotation} />}
                />
            </ul>
        </Card> : null
    );
}

export default connector(ObjectBoard);

