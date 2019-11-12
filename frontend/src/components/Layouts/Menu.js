import React from "react";
import MIDDLEWARE_ENDPOINT from "components/utils/middleware_endpoint";

export default class Menu extends React.Component {
    render() {
        return (
            <div className="menu">
                {"Menu"}
                <button
                    onClick={() => {
                        MIDDLEWARE_ENDPOINT.send("test-channel", {
                            abc: "aqew"
                        });
                    }}
                >
                    test
                </button>
            </div>
        );
    }
}
