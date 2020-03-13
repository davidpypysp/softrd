import React from "react";
import { NumericInput } from "@blueprintjs/core";
import { Vec3 } from "src/utils/math";

export class Vector3Input extends React.Component<{ data: Vec3 }, {}> {
    render() {
        const { data } = this.props;
        return (
            <div className="vector3-input">
                <NumericInput className="vector3-input-numeric"
                    value={data.x}
                />
                <NumericInput className="vector3-input-numeric"
                    value={data.y}
                />
                <NumericInput className="vector3-input-numeric"
                    value={data.z}
                />
            </div>
        )
    }
}
