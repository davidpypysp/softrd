import React from "react";

import { Card, Button } from "@blueprintjs/core";

export default class extends React.Component {
    render() {
        return (
            <Card className="right-panel">
                {"Right Panel"}
                <button>
                    flat
                </button>
                <button>
                    frame
                </button>
            </Card>
        );
    }
}
