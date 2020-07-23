import React from "react";
import { Card, Classes } from "@blueprintjs/core";
import { Vec3Input } from "src/components/VectorInput";
import { connect, ConnectedProps } from "react-redux";
import { Object } from "src/interfaces/object";
import { Vec3 } from "src/interfaces/vector";
import {
    updateObjectPosition,
    updateObjectRotation,
} from "src/store/objectList";
import { Dispatch } from "src/store";
import { createUseStyles } from "react-jss";

const useStyles = createUseStyles({
    rowData: {
        display: "flex",
    },
    rowDataTitle: {
        minWidth: 100,
        textAlign: "center",
        padding: 5,
    },
    objectName: {
        padding: [4, 10],
    },
});

export interface RowDataProps {
    title: string;
    component?: React.ReactNode;
    data?: any;
}

export const RowData = (props: RowDataProps) => {
    const classes = useStyles();
    return (
        <li className={classes.rowData}>
            <span className={classes.rowDataTitle}>{props.title}</span>
            {props.component}
        </li>
    );
};

const mapStateToProps = (state) => {
    const { objectSelector, objectList } = state;
    const object: Object = objectList[objectSelector];
    return { object };
};
const mapDispatchToProps = (dispatch: Dispatch) => ({
    updateObjectPosition: (id: string, position: Vec3) =>
        dispatch(updateObjectPosition(id, position)),
    updateObjectRotation: (id: string, rotation: Vec3) =>
        dispatch(updateObjectRotation(id, rotation)),
});
const connector = connect(mapStateToProps, mapDispatchToProps);

const ObjectBoard = (props: ConnectedProps<typeof connector>) => {
    const classes = useStyles();
    const { object, updateObjectPosition, updateObjectRotation } = props;
    return object ? (
        <Card>
            <ul className="bp3-list bp3-list-unstyled">
                <RowData
                    title="Object"
                    component={
                        <div className={classes.objectName}>{object.name}</div>
                    }
                />
                <RowData
                    title="Position"
                    component={
                        <Vec3Input
                            data={object.position}
                            onChangeHandler={(position) =>
                                updateObjectPosition(object.id, position)
                            }
                        />
                    }
                />
                <RowData
                    title="Rotation"
                    component={
                        <Vec3Input
                            data={object.rotation}
                            onChangeHandler={(rotation) =>
                                updateObjectRotation(object.id, rotation)
                            }
                        />
                    }
                />
            </ul>
        </Card>
    ) : null;
};

export default connector(ObjectBoard);
