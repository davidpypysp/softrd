import * as ReactDOM from "react-dom";
import * as React from "react";
import { GUI } from "src/ui/GUI";
import store from "src/store";
import { Provider } from "react-redux";

ReactDOM.render(
    <Provider store={store}>
        <GUI />
    </Provider>,
    document.getElementById("root")
);
