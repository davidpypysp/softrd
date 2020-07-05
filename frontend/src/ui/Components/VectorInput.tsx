import React from "react";
import { NumericInput } from "@blueprintjs/core";
import { Vec3 } from "src/interfaces/vector";

import { createUseStyles } from "react-jss";

const useStyles = createUseStyles({
    vector3Input: {
        display: "flex",
    },
    vector3InputNumeric: {
        margin: [0, 5],
        "& .bp3-input-group": {
            width: 80,
        },
    },
});

export function Vec3Input(props: { data: Vec3; onChangeHandler?: Function }) {
    const classes = useStyles();
    const { data, onChangeHandler } = props;
    return (
        <div className={classes.vector3Input}>
            <NumericInput
                className={classes.vector3InputNumeric}
                value={data.x}
                onValueChange={(value) => {
                    if (!isNaN(value) && onChangeHandler) {
                        onChangeHandler({ ...data, x: value });
                    }
                }}
            />
            <NumericInput
                className={classes.vector3InputNumeric}
                value={data.y}
                onValueChange={(value) => {
                    if (!isNaN(value) && onChangeHandler) {
                        onChangeHandler({ ...data, y: value });
                    }
                }}
            />
            <NumericInput
                className={classes.vector3InputNumeric}
                value={data.z}
                onValueChange={(value) => {
                    if (!isNaN(value) && onChangeHandler) {
                        onChangeHandler({ ...data, z: value });
                    }
                }}
            />
        </div>
    );
}
