import * as ReactDOM from "react-dom";
// import App from "src/app";
import * as React from "react";
import { Hello } from "./Hello";


ReactDOM.render(
    <Hello compiler="TypeScript" framework = "React" />,
    document.getElementById("example")
);
