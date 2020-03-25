import React from "react";
import { Card } from "@blueprintjs/core";
import { Vector3Input } from "src/ui/Components/VectorInput";
import { updateObjectPosition, updateObjectRotation } from "src/store/actions/objectListAction";
import { connect, ConnectedProps } from 'react-redux'
import { Object } from "src/interfaces/object";
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

const mapStateToProps = (state) => {
    const { objectSelector, objectList } = state;
    const object: Object = objectList[objectSelector];
    return { object }
};
const mapDispatchToProps = dispatch => ({
    updateObjectPosition: (id: string, position: Vec3) => dispatch(updateObjectPosition(id, position)),
    updateObjectRotation: (id: string, rotation: Vec3) => dispatch(updateObjectRotation(id, rotation)),
});
const connector = connect(mapStateToProps, mapDispatchToProps);


const ObjectBoard = (props: ConnectedProps<typeof connector>) => {
    const { object, updateObjectPosition, updateObjectRotation } = props;
    return (
        object ? <Card>
            <ul className="bp3-list bp3-list-unstyled">
                <RowData
                    title="Object"
                    component={<div className="object-name">{object.name}</div>}
                />
                <RowData
                    title="Position"
                    component={
                        <Vector3Input
                            data={object.position}
                            onChangeHandler={(position) => updateObjectPosition(object.id, position)}
                        />}
                />
                <RowData
                    title="Rotation"
                    component={
                        <Vector3Input
                            data={object.rotation}
                            onChangeHandler={(rotation) => updateObjectRotation(object.id, rotation)}
                        />
                    }
                />
            </ul>
        </Card> : null
    );
}

export default connector(ObjectBoard);

