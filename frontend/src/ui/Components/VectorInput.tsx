import React from "react";
import { NumericInput } from "@blueprintjs/core";
import { Vec3 } from "src/interfaces/vector";

export class Vec3Input extends React.Component<
    { data: Vec3; onChangeHandler?: Function },
    {}
> {
    render() {
        const { data, onChangeHandler } = this.props;
        return (
            <div className="vector3-input">
                <NumericInput
                    className="vector3-input-numeric"
                    value={data.x}
                    onValueChange={(value) => {
                        if (!isNaN(value) && onChangeHandler) {
                            onChangeHandler({ ...data, x: value });
                        }
                    }}
                />
                <NumericInput
                    className="vector3-input-numeric"
                    value={data.y}
                    onValueChange={(value) => {
                        if (!isNaN(value) && onChangeHandler) {
                            onChangeHandler({ ...data, y: value });
                        }
                    }}
                />
                <NumericInput
                    className="vector3-input-numeric"
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
}
