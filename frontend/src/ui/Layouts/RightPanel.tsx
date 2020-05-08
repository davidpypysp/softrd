import React from "react";

import { Card, Button } from "@blueprintjs/core";
import { Tab, Tabs } from "@blueprintjs/core";

import ObjectBoard from "src/ui/Components/ObjectBoard";

export default class extends React.Component {
    render() {
        return (
            <Card className="right-panel">
                <Tabs id="TabsExample"
                    animate={false}
                    defaultSelectedTabId="objectBoard"
                >
                    <Tab id="objectBoard" title="Object"
                        panel={<ObjectBoard />}
                    />
                    <Tabs.Expander />
                </Tabs>
            </Card>
        );
    }
}
