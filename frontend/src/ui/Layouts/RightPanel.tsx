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
                        panel={
                            <ObjectBoard
                                objectName="Box1"
                                position={{ x: 1.05, y: 2, z: 3 }}
                                rotation={{ x: 1, y: 1, z: 1 }}
                            />
                        }
                    />
                    <Tabs.Expander />
                </Tabs>
            </Card>
        );
    }
}
