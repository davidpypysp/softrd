import React from "react";
import { Card, Classes } from "@blueprintjs/core";
import { Vec3Input } from "src/components/VectorInput";
import { useDispatch, useSelector } from "react-redux";
import { Object } from "src/interfaces/object";
import { Vec3 } from "src/interfaces/vector";
import { RootState } from "src/store";
import {
    updateObjectPosition,
    updateObjectRotation,
} from "src/store/objectList";
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

const ObjectBoard = () => {
    const classes = useStyles();
    const dispatch = useDispatch();
    const object = useSelector((state: RootState) => {
        const { objectSelector, objectList } = state;
        return objectList[objectSelector];
    });

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
                                dispatch(
                                    updateObjectPosition(object.id, position)
                                )
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
                                dispatch(
                                    updateObjectRotation(object.id, rotation)
                                )
                            }
                        />
                    }
                />
            </ul>
        </Card>
    ) : null;
};

export default ObjectBoard;
